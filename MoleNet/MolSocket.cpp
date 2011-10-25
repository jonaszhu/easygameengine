#include "MolSocket.h"

#include "MolSocketOps.h"
#include "MolSocketMgrWin32.h"
#include "MolListenSocketWin32.h"

#pragma pack(push, 1)
typedef struct
{
	uint16 opcode;
	uint32 size;
}logonpacket;
#pragma pack(pop)

initialiseSingleton(SocketGarbageCollector);

MolNetworkUpdate *m_NetworkUpdate = NULL;

/** 
 * 构造函数
 *
 * @param fd socket的文件描述
 * @param sendbuffersize 发送缓冲区的大小
 * @param recvbuffersize 接收缓冲区的大小
 */
Socket::Socket(SOCKET fd,uint32 sendbuffersize,uint32 recvbuffersize)
: m_fd(fd), m_connected(false),	m_deleted(false), m_writeLock(0)
{
	readBuffer.Allocate(recvbuffersize);
	writeBuffer.Allocate(sendbuffersize);

	//m_writeLock = 0;
	m_completionPort = 0;

	m_BytesSent = 0;
	m_BytesRecieved = 0;

	if(m_fd == 0)
		m_fd = SocketOps::CreateTCPFileDescriptor();
}

/** 
 * 析构函数
 */
Socket::~Socket()
{

}

/** 
 * 连接指定的机器
 *
 * @param Address 要连接的服务器的网络地址
 * @param Port 要连接的服务器的端口
 *
 * @return 如果服务器连接成功返回真，否则返回假
 */
bool Socket::Connect(const char * Address,uint32 Port)
{
	struct hostent * ci = gethostbyname(Address);
	if(ci == 0)
		return false;

	m_client.sin_family = ci->h_addrtype;
	m_client.sin_port = ntohs((u_short)Port);
	memcpy(&m_client.sin_addr.s_addr,ci->h_addr_list[0],ci->h_length);

	SocketOps::Blocking(m_fd);
	if(connect(m_fd,(const sockaddr*)&m_client,sizeof(m_client)) == -1)
		return false;

	m_completionPort = sSocketMgr.GetCompletionPort();

    _OnConnect();

	return true;
}

/** 
 * 接收已经设置的文件描述符
 *
 * @param address 要接收的客户端的地址
 */
void Socket::Accept(sockaddr_in * address)
{
	memcpy(&m_client,address,sizeof(*address));
	_OnConnect();
}

/** 
 * 当连接打开时调用
 */
void Socket::_OnConnect()
{
	SocketOps::Nonblocking(m_fd);
	SocketOps::DisableBuffering(m_fd);

	m_connected.SetVal(true);

	AssignToCompletionPort();
	SetupReadEvent();

	sSocketMgr.AddSocket(m_fd,this);

	OnConnect();
}

/** 
 * 发送数据
 *
 * @param out 要发送的数据
 *
 * @return 如果数据发送成功返回真,否则返回假
 */
bool Socket::Send(CMolMessageOut &out)
{
	if(out.getLength() <= 0 || out.getLength() > MOL_REV_BUFFER_SIZE)
		return false;

	int pSendCount = 10;
	bool rv = true;

	while(pSendCount > 0)
	{
		BurstBegin();

		logonpacket header;
		header.opcode = 100;
		header.size = out.getLength();

		rv = BurstSend((uint8*)&header,sizeof(logonpacket));
		if(rv)
		{
			int uSendSize = 0;
			char *sdata = sSocketMgr.compress(out,&uSendSize);

			rv = BurstSend((uint8*)sdata,uSendSize);
		}

		if(rv)
			BurstPush();
		BurstEnd();

		if(rv) break;
		else 
		{
			Sleep(10);
			pSendCount-=1;
		}
	}

	return rv;
}

/** 
 * 锁定发送互斥锁,发送数据，解锁互斥锁
 *
 * @param Bytes 要发送的数据
 * @param Size 要发送的数据的大小
 *
 * @return 如果数据发送成功返回真，否则返回假
 */
bool Socket::Send(const uint8 * Bytes,uint32 Size)
{
	bool rv;

	BurstBegin();
	rv = BurstSend(Bytes,Size);
	if(rv)
		BurstPush();
	BurstEnd();

	Sleep(1);

	return rv;
}

/** 
 * 爆裂系统 - 添加数据到发送缓冲区
 *
 * @param Bytes 要发送的数据
 * @param Size 要发送的数据的大小
 *
 * @return 如果数据发送成功返回真，否则返回假
 */
bool Socket::BurstSend(const uint8 * Bytes,uint32 Size)
{
	return writeBuffer.Write(Bytes,Size);
}

std::string Socket::GetRemoteIP()
{
	char* ip = (char*)inet_ntoa( m_client.sin_addr );
	if( ip != NULL )
		return std::string( ip );
	else
		return std::string( "noip" );
}

void Socket::Disconnect()
{
	//if returns false it means it's already disconnected
	if(!m_connected.SetVal(false))
		return;

	// remove from mgr
	sSocketMgr.RemoveSocket(this);

	// Call virtual ondisconnect
	OnDisconnect();

	if(!IsDeleted()) 
		Delete();
}

void Socket::Delete()
{
	//if returns true it means it's already delete
	if(m_deleted.SetVal(true))
		return;

	if(IsConnected()) Disconnect();

	SocketOps::CloseSocket( m_fd );

	sSocketGarbageCollector.QueueSocket(this);
}

/** 
 * 构造函数
 *
 * @param fd socket的文件描述
 */
NetClient::NetClient(SOCKET fd)
: Socket(fd, 524288, 524288),remaining(0),opcode(0)
{

}

/** 
 * 析构函数
 */
NetClient::~NetClient()
{

}

/** 
 * 当数据达到时调用
 *
 * @param size 接收到的数据的大小
 */
void NetClient::OnRead(uint32 size)
{
	while(true)
	{
		if(!remaining)
		{
			if(GetReadBuffer().GetSize() < sizeof(logonpacket)) 
				return;

			// 首先取得版本号
			GetReadBuffer().Read((uint8*)&opcode,sizeof(uint16));

			if(opcode != 100) 
				return;

			// 首先取得包头
			GetReadBuffer().Read((uint8*)&remaining,sizeof(uint32));
		}

		if(GetReadBuffer().GetSize() < remaining)
			return;

		memset(buffer,0,MOL_REV_BUFFER_SIZE);

		// 取得实际数据包
		GetReadBuffer().Read((uint8*)buffer,remaining);

		int dlength = 0;
		//sSocketMgr.uncompress((unsigned char*)myBuffer,myheader.nDataLen,&dlength);
		char* rdata = sSocketMgr.uncompress((unsigned char*)buffer,remaining,&dlength);

		if(rdata && dlength > 0 && dlength < MOL_REV_BUFFER_SIZE_TWO)
		{
			CMolMessageIn *in = new CMolMessageIn(rdata,dlength);
			sSocketMgr.AddMessage(MessageStru(MES_TYPE_ON_READ,(uint32)GetFd(),in));
		}

		remaining = 0;
		opcode = 0;
	}
}

/** 
 * 当一个连接成功建立时调用
 */
void NetClient::OnConnect()
{
	sSocketMgr.AddMessage(MessageStru(MES_TYPE_ON_CONNECTED,(uint32)GetFd()));
}

/** 
 * 当一个连接断开时调用
 */
void NetClient::OnDisconnect()
{
	sSocketMgr.AddMessage(MessageStru(MES_TYPE_ON_DISCONNECTED,(uint32)GetFd()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** 
 * 构造函数
 */
MolNetworkUpdate::MolNetworkUpdate()
: m_curTime(0),m_TimeSpeed(2000)
{

}

/** 
 * 析构函数
 */
MolNetworkUpdate::~MolNetworkUpdate()
{

}

bool MolNetworkUpdate::run()
{
	if(m_ServerSocket == NULL) return true;

	while(m_ServerSocket->IsOpen())
	{
		if(m_curTime == 0)
			m_curTime = GetTickCount();

		if(GetTickCount() > m_curTime + m_TimeSpeed)
		{
			sSocketGarbageCollector.Update();

			m_curTime = 0;
		}

		Sleep(10);
	}

	return false;
}
