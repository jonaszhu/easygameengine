#include "stdafx.h"

#include "Mole2dTcpSocketClient.h"

#include "Mole2dCircularBuffer.h"
#include "MolServerDlg.h"

//#include "lzo/minilzo.h"

//#define HEAP_ALLOC(var,size) \
//    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]
//
//static HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);

#pragma pack(push, 1)
typedef struct
{
	unsigned short opcode;
	unsigned int size;
}logonpacket;
#pragma pack(pop)

BEGIN_MESSAGE_MAP(CMolTcpSocketClient, CWnd)
	ON_MESSAGE(IDD_WM_SOCKET_MESSAGE,&CMolTcpSocketClient::OnSocketNotifyMessage)
END_MESSAGE_MAP()
	
/** 
 * 构造函数
 *
 * @param pParent 当前控件的父控件
 */
CMolTcpSocketClient::CMolTcpSocketClient(CWnd *pParent)
: m_Parent(pParent),m_Socket(NULL),m_bConnectState(NOCONNECT),
  m_ReadBuffer(NULL),m_BaseFrame(NULL),uncombuf(NULL),combuf(NULL),remaining(0),opcode(0)
{
	if(!GetSafeHwnd())
		CreateSocketHwnd(m_Parent);

	m_ReadBuffer = new CMolCircularBuffer();

	m_ReadBuffer->Allocate(REV_SIZE);

     //if (lzo_init() != LZO_E_OK)
     //{
     //   LOG_ERRORR("lzo初始失败。");
     //}

	 combuf = (unsigned char*)malloc(MOL_REV_BUFFER_SIZE);
	 uncombuf = (unsigned char*)malloc(MOL_REV_BUFFER_SIZE);
}

/** 
 * 析构函数
 */
CMolTcpSocketClient::~CMolTcpSocketClient(void)
{
	// 管理连接
	CloseConnect();

	delete m_ReadBuffer;
	m_ReadBuffer = NULL;

	if(combuf) free(combuf);
	combuf = NULL;
	if(uncombuf) free(uncombuf);
	uncombuf = NULL;
}

/** 
 * 连接指定的服务器
 *
 * @param ipaddress 要连接的服务器IP地址
 * @param port 要连接的服务器端口
 *
 * @return 如果服务器连接成功返回真,否则返回假
 */
bool CMolTcpSocketClient::Connect(std::string ipaddress,int port)
{
	if(ipaddress.empty())
		return false;

	long dwServerIP = inet_addr(ipaddress.c_str());
	if(dwServerIP == INADDR_NONE)
	{
		LPHOSTENT lpHost = ::gethostbyname(ipaddress.c_str());
		if(lpHost != NULL) return false;

		dwServerIP = ((LPIN_ADDR)(lpHost->h_addr))->s_addr;
	}

	// 如果winsock窗口没有建立的话，建立窗口
	if(!GetSafeHwnd())
		CreateSocketHwnd(m_Parent);

	m_Socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(::WSAAsyncSelect(m_Socket,GetSafeHwnd(),IDD_WM_SOCKET_MESSAGE,FD_READ|FD_CONNECT|FD_CLOSE) == SOCKET_ERROR)
	{
		LOG_ERRORR("WSAAsyncSelect 建立失败!");
		return false;
	}

	sockaddr_in SocketAddr;
	SocketAddr.sin_family = AF_INET;
	SocketAddr.sin_port = htons(port);
	SocketAddr.sin_addr.S_un.S_addr = dwServerIP;

	if((::connect(m_Socket,(const sockaddr*)(&SocketAddr),sizeof(SocketAddr)) == SOCKET_ERROR) &&
		(::WSAGetLastError() != WSAEWOULDBLOCK))
	{
		LOG_ERRORR("服务器:" << ipaddress << "连接失败!");
		return false;
	}

	m_bConnectState = CONNECTTING;

	return true;
}

/** 
 * 建立socket对话框
 *
 * @param pParent 当前窗口的父窗口
 */
void CMolTcpSocketClient::CreateSocketHwnd(CWnd *pParnet)
{
	if(pParnet == NULL &&
		AfxGetApp())
	{
		pParnet = AfxGetApp()->GetMainWnd();
	}

	if(!CreateEx(NULL,NULL,"",WS_CHILD,CRect(0,0,0,0),pParnet,IDD_SOCKET_WND))
		LOG_ERRORR("WinSocket窗口建立失败");
}

/** 
 * 关闭连接
 */
void CMolTcpSocketClient::CloseConnect(void)
{
	bool bClose = (m_Socket != INVALID_SOCKET);
	m_bConnectState = NOCONNECT;
	if(m_Socket != INVALID_SOCKET)
	{
		::WSAAsyncSelect(m_Socket,GetSafeHwnd(),IDD_WM_SOCKET_MESSAGE,0);
		::closesocket(m_Socket);

		m_Socket = INVALID_SOCKET;
	}
}

/** 
 * 发送数据
 *
 * @param msg 要发送的数据
 *
 * @return 返回数据发送的数量，如果数据全部发送成功返回数据的大小，否则返回SOCKET_ERROR
 */
int CMolTcpSocketClient::Send(CMolMessageOut &msg)
{
	if(msg.getData() == NULL ||
		msg.getLength() <= 0)
		return SOCKET_ERROR;

	if(m_Socket == INVALID_SOCKET) return SOCKET_ERROR;

	int iSendCount = 0;
	int uSended,uSendSize,iErrorCode;
		
	uSended = iErrorCode = 0;
	char *sdata = compress(msg,&uSendSize);

	try
	{
		do 
		{
			iErrorCode = ::send(m_Socket,(sdata+uSended),uSendSize-uSended,0);
			if(iErrorCode == SOCKET_ERROR)
			{
				if(::WSAGetLastError() == WSAEWOULDBLOCK)
				{
					if(iSendCount++ > 100)
						return SOCKET_ERROR;
					else
					{
						Sleep(10);
						continue;
					}
				}
				else
				{
					return SOCKET_ERROR;
				}
			}

			uSended += iErrorCode;
			iSendCount = 0;
		} while (uSended < uSendSize);
	}
	catch(...)
	{
		LOG_ERRORR("winsockt发送数据出现错误!");
	}

	return uSendSize;
}

/** 
 * 处理socket网络消息
 *
 * @param wParam,lParam 要处理的网络消息
 *
 * @return 返回处理结果
 */
LRESULT CMolTcpSocketClient::OnSocketNotifyMessage(WPARAM wParam,LPARAM lParam)
{
	CMolMessageIn in;

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:                      // 处理客户端连接
		{
			UINT uErrorCode = WSAGETSELECTERROR(lParam);

			if(uErrorCode == 0)
				m_bConnectState = CONNECTED;
			else
				CloseConnect();

			return 0;
		}
		break;
	case FD_READ:                         // 处理收到数据
		{
			int iLen = ::recv(m_Socket,(char*)(m_ReadBuffer->GetBuffer()),(int)m_ReadBuffer->GetSpace(),0);
			if(iLen == SOCKET_ERROR)
			{
				CloseConnect();
				return 0;
			}

			try
			{
				if(iLen != 0xFFFFFFFF)
					m_ReadBuffer->IncrementWritten(iLen);

				while(true)
				{
					if(!remaining)
					{
						if(m_ReadBuffer->GetSize() < sizeof(logonpacket)) 
							return 0;	

						// 首先取得版本号
						m_ReadBuffer->Read((unsigned char*)&opcode,sizeof(unsigned short));

						if(opcode != 100) 
							return 0;

						// 首先取得包头
						m_ReadBuffer->Read((unsigned char*)&remaining,sizeof(unsigned int));
					}

					if(m_ReadBuffer->GetSize() < remaining)
						return 0;

                    m_bConnectState = MESPROCESS;
                    memset(buffer,0,MOL_REV_BUFFER_SIZE);
                   
                    // 取得实际数据包
                    m_ReadBuffer->Read((unsigned char*)buffer,remaining);

                    int dlength = 0;
                    char* rdata = uncompress((unsigned char*)buffer,remaining,&dlength);

					remaining = 0;
					opcode = 0;
				}
			}
			catch (...)
			{
				CloseConnect();
			}

			return 0;
		}
		break;
	case FD_CLOSE:                        // 处理连接关闭
		{
			CloseConnect();

			return 0;
		}
		break;
	default:
		break;
	}
	return 0;
}

/** 
 * 压缩我们要传输的数据
 *
 * @param out 我们要压缩的数据
 * @param declength 压缩后的数据长度
 *
 * @return 返回压缩后的数据
 */
char* CMolTcpSocketClient::compress(CMolMessageOut &out,int *declength)
{
	if(out.getData() == NULL || out.getLength() <= 0) return NULL;

	int length = out.getLength();
//	lzo_uint out_len = length;
	int result=0;

    memset(combuf,0,MOL_REV_BUFFER_SIZE);

    logonpacket header;
	header.opcode = 100;
	header.size = length;

    // 先拷贝包头
    memcpy(combuf,&header,sizeof(logonpacket));

    // 加密数据
    Encrypto((unsigned char*)out.getData(),length);

    // 加上实际的数据
    memcpy(combuf+sizeof(logonpacket),out.getData(),length);

	//result = lzo1x_1_compress((unsigned char*)out.getData(),length,combuf,&out_len,wrkmem);

 //   if(result == LZO_E_OK) 
	//{

 //   }
	//else 
	//{
 //       LOG_ERRORR("lzo压缩出现问题。");
 //   }

	*declength = length+sizeof(logonpacket);

	return (char*)combuf;
}

/**
 * 解压我们接收到的数据
 *
 * @param data 要解压的数据
 * @param srclength 解压的数据的长度
 * @param declength 解压后的数据的长度
 *
 * @return 返回解压后的数据
 */
char* CMolTcpSocketClient::uncompress(unsigned char *data,int srclength,int *declength)
{
	if(data == NULL || srclength <= 0) return NULL;

     int src_length = srclength;
//     lzo_uint in_len;
     int result=0;

     //src_length = src_length * 200;

     memset(uncombuf,0,MOL_REV_BUFFER_SIZE);

	 memcpy(uncombuf,data,srclength);

	 // 加密数据
	 Decrypto((unsigned char*)uncombuf,srclength);

  //   result = lzo1x_decompress(data,srclength,uncombuf,&in_len,NULL);

  //   if(result == LZO_E_OK) 
	 //{
  //      //删除原来的数据
  //      //if(data) free(data);
  //      //  data = NULL;
  //   }
	 //else 
	 //{
  //      LOG_ERRORR("lzo解压出现问题。");
  //   }

     *declength = srclength;
     return (char*)uncombuf;
}


/**
* 加密数据
*
* @param data 要加密的数据
* @param length 要加密的数据的长度
*/
void CMolTcpSocketClient::Encrypto(unsigned char *data,unsigned long length)
{
	if(data == NULL || length <= 0) return;

	unsigned char pKeyList[] = {76,225,112,120,103,92,84,105,8,12,238,122,206,165,222,21,117,217,106,214,239,66,32,3,85,67,224,180,
		240,233,236,171,89,13,52,109,123,99,132,213,15,137,226,69,231,228,60,28,190,193,74,144,81,53,17,101,230,207,79,93,88,36,30,
		141,115,110,20,169,173,243,219,80,72,184,125,175,174,139,95,24,148,48,113,182,50,223,61,118,140,14,78,181,16,4,121,73,187,		147,168,9,116,23,63,216,215,244,232,59,195,154,200,55,62,220,75,161,196,68,159,6,167,40,45,0,22,155,64,127,27,237,192,212,58,		26,98,201,41,209,179,130,211,208,82,152,172,7,35,205,107,46,33,146,185,87,199,25,2,77,39,156,164,102,194,163,241,96,166,10,11,		235,198,157,229,126,94,56,189,134,5,153,133,242,1,31,119,37,145,47,178,18,177,176,86,129,197,65,210,111,54,43,70,188,128,90,		227,162,104,186,108,114,158,142,57,218,151,202,170,234,150,100,183,71,135,160,42,203,49,97,138,91,124,29,149,83,44,51,19,143,
		131,38,34,136,221,191,204,245,246,247,248,249,250,251,252,253,254,255};

	for(int i=0;i<(int)length;i++)
	{
		data[i] = pKeyList[data[i]];
	}
}

/**
* 解密数据
*
* @param data 要解密的数据
* @param length 要解密的数据的长度
*/
void CMolTcpSocketClient::Decrypto(unsigned char *data,unsigned long length)
{
	if(data == NULL || length <= 0) return;

	unsigned char pKeyList[] = {123,182,156,23,93,178,119,145,8,99,167,168,9,33,89,40,92,54,189,236,66,15,124,101,79,155,133,128,47,231,		62,183,22,150,240,146,61,185,239,158,121,136,224,199,234,122,149,187,81,226,84,235,34,53,198,111,175,212,132,107,46,86,112,102,		126,195,21,25,117,43,200,221,72,95,50,114,0,157,90,58,71,52,142,233,6,24,192,153,60,32,203,229,5,59,174,78,165,227,134,37,219,55,		161,4,206,7,18,148,208,35,65,197,2,82,209,64,100,16,87,184,3,94,11,36,230,74,173,127,202,193,139,238,38,180,177,222,241,41,228,77,		88,63,211,237,51,186,151,97,80,232,218,214,143,179,109,125,159,171,210,118,223,115,205,163,160,13,166,120,98,67,216,31,144,68,76,75,		191,190,188,138,27,91,83,220,73,152,207,96,201,176,48,243,130,49,162,108,116,194,170,154,110,135,215,225,244,147,12,57,141,137,196,		140,131,39,19,104,103,17,213,70,113,242,14,85,26,1,42,204,45,172,56,44,106,29,217,169,30,129,10,20,28,164,181,69,105,245,246,247,248,
		249,250,251,252,253,254,255};

	for(int i=0;i<(int)length;i++)
	{
		data[i] = pKeyList[data[i]];
	}
}
