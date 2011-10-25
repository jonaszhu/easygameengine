#ifndef _MOLE2D_BASE_FRAME_H_
#define _MOLE2D_BASE_FRAME_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/

#include "Mole2d.h"

#include <string>

#include <map>
#include <vector>
#include <list>
#include <assert.h>
#include <imm.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

//#include "libvideo/TheoraPlayer.h"
#include "RegisterKey.h"

class TiXmlElement;

int  tolua_Mole2d_open (lua_State* tolua_S);

//namespace mole2d
//{

/** 
 * 用于记录日志信息
 */
struct MolLogStruct
{
	MolLogStruct()
		: count(0)
	{

	}

	int count;
	char logStr[MOL_SHARE_MEORY_COUNT][MOL_SHARE_MEMORY_SIZE];
};

/** 
 * 声音类型
 */
enum MolSoundType
{
	SOUNDTYPE_EFFECT = 0,            // 音效
	SOUNDTYPE_MUSIC,                 // 音乐
	SOUNDTYPE_NULL
};

/**
 * 声音结构
 */
struct MolSouStr
{
	MolSouStr()
		: type(SOUNDTYPE_NULL),id(0),data(0) {}
	MolSouStr(MolSoundType t,DWORD i,void *pData)
		: type(t),id(i),data(pData) {}

	MolSoundType type;               // 类型
	DWORD id;                        // ID
	void *data;                      // 用于存储音乐数据
};

/**
 * 带轮廓的字体结构
 */
struct CMolFigureFont
{
	CMolFigureFont():size(0),fontIndex(0),tex(0),top(0),left(0),texw(0),texh(0),imgw(0),imgh(0)
	{}
	CMolFigureFont(HTEXTURE t,u32 fi,int s,CMolColor tc,CMolColor fc,u32 pTop,u32 pLeft,u32 pTexw,u32 pTexh,u32 pImgw,u32 pImgh)
		: tex(t),fontIndex(fi),size(s),textColor(tc),figureColor(fc),top(pTop),left(pLeft),texw(pTexw),texh(pTexh),imgw(pImgw),imgh(pImgh)
	{}

	u32 fontIndex;          // 文字索引
	int size;               // 字体大小
	CMolColor textColor;    // 字体颜色
	CMolColor figureColor;  // 轮廓颜色
	HTEXTURE tex;           // 字体纹理

	u32 top;
	u32 left;
	u32 texw;
	u32 texh;
	u32 imgw;
	u32 imgh;
};


//namespace graphics
//{

class CMolMessageIn;
class CMolMessageOut;
class CMolTcpSocketClient;
class CMolGUIBaseFont;
class CMolGUITTFace;
class CMolGUITTFont;
class CMolAnimatorNode;
class CMolAnimatorResource;
class CMolAnimatorManager;

class MOLEXPORT CMolBaseFrame : public CWnd , public CMolBaseGUIContainer
{
public:
	/** 
	* 用于存储更新的配置
	*/
	struct UpdataSet
	{
		UpdataSet()
			: ver(0)
		{}
		UpdataSet(float v,std::string a)
			: ver(v),address(a)
		{}

		float ver;             // 当前程序版本
		std::string address; // 当前更新的服务器
	};

	CMolBaseFrame(CWnd* pParent = NULL);	// 标准构造函数
	/// 析构函数
	virtual ~CMolBaseFrame();

	inline static CMolBaseFrame & getSingleton() { assert(m_Singleton); return *m_Singleton; }
	inline static CMolBaseFrame * getSingletonPtr() { return m_Singleton; }
	/// 初始化引擎
	bool Initialize(std::string caption,CMolDimension2d<int> size);
	/// 关闭游戏窗体
	void CloseGameFrame(int state=MOLE2D_GUI_CLOSE_FRAME);
	/// 设置是否可以切换游戏模式
	inline void SetSwitchGameMode(bool isSwitch) { m_isSwitchMode = isSwitch; }
	/// 检查当前是否可以切换游戏模式
	inline bool IsSwitchGameMode(void) { return m_isSwitchMode; }
	/// 开始指定ID的游戏定时器
	void StartGameTimer(unsigned int id,unsigned int time);
	/// 停止指定ID的游戏定时器
	void StopGameTimer(unsigned int id);
	/// 打印日志到日志文件中
	void SystemLog(Level le,std::string msg);
	/// 得到指定名称的命令
	std::string GetStartCommond(std::string name);
	/// 设置光标
	void ChangeCursor(std::string path);
	/// 游戏窗体最小化
	void MinGameFrame(void);
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 用于处理定时器消息
	virtual void OnProcessGameTimer(unsigned int IdTimer);
	/// 在全屏和窗口之前切换
	void SwitchScreenAndWindow(void);
	/// 在窗口模式下抖动游戏窗口
	void DitherMainFrame(void);
	/// 检测指定的文件是否存在
	bool FileIsExist(std::string filename);
	/// 得到程序永久性目录
	inline std::string GetProgressDirection(void) { return m_prodirection; }
	/// 得到当前程序的工作路径
	inline std::string GetWorkingDirection(void) { return m_curWorkingDir; }
	/// 改变游戏工作目录（改变了工作目录，就意味着以前的资源不能使用了，需要重新加载新的资源）
	void ChangePlayerWorkingDir(std::string filename,bool loadscript=true);
	/// 保存屏幕截图
	void Snapshot(std::string filename="");	
	/// 转换多字节到双字节
	std::wstring ConverToWideChar(const std::string& str);
	/// 转换双字节到多字节
	std::string ConverToMultiChar(const std::wstring& str);
	/// 向注册表写入数据
	void WriteRegisterKey(std::string pszKey,std::string pVal);
	/// 读取注册表中的数据
	std::string ReadRegisterKey(std::string pszKey);
	/// 获取指定字符串的MD5码
	std::string GetStringMD5(std::string str);
	/// 设置游戏下载状态
	inline void SetDownloadState(DownloadStatus state) { m_DownloadStatus = state; }
	/// 得到游戏下载状态
	inline DownloadStatus GetDownloadState(void) { return m_DownloadStatus; }
	/// 得到下载的目标目录
	inline std::string GetDownloadDecPath(void) { return m_UpdateDecPath; }
	/// 通过网站得到信息
	std::string GetNetMessage(std::string address);
	/// 得到玩家列表
	inline CMolGUIRoomList* GetRoomList(void) { return m_MainRoomList; }
	/// 初始化脚本引擎
	void InitScriptSystem(void);
	/// 释放脚本引擎
	void DestroyScriptSystem(void);
	/// 模式对话框
	int DoModal(void);

	/// 初始配置文件
	void Ini_SetFile(const char *filename);
	/// 得到配置文件
	char* Ini_GetFile(void);
	/// 设置整形参数
	void Ini_SetInt(const char *section, const char *name, int value);
	/// 得到整形参数
	int Ini_GetInt(const char *section, const char *name, int def_val);
	/// 设置浮点参数
	void Ini_SetFloat(const char *section, const char *name, float value);
	/// 得到浮点参数
	float Ini_GetFloat(const char *section, const char *name, float def_val);
	/// 设置字符串参数
	void Ini_SetString(const char *section, const char *name, const char *value);
	/// 得到字符串参数
	char* Ini_GetString(const char *section, const char *name, const char *def_val);

	/// 关闭连接
	void CloseConnect(void);
	/// 连接指定的服务器
	bool Connect(std::string ipaddress,int port);
	/// 发送数据
	int Send(CMolMessageOut &msg);
	/// 检测当前是否连接
	bool IsConnected(void);

	/// 得到屏幕大小
	CMolDimension2d<s32> getScreenSize();
	/// 从指定文件中导入数据
	void* LoadResource(const char* filename, unsigned long *size=0);
	/// 从系统中导入一张纹理
	HTEXTURE LoadTexture(const char* filename,unsigned long size=0);
	/// 建立一张指定大小的空白纹理
	HTEXTURE CreateTexture(const char* filename,int width,int height);
	/// 释放指定ID的纹理
	void FreeTexture(HTEXTURE tex);
	/// 得到指定纹理的宽度
	int GetTextureWidth(HTEXTURE tex,bool bOriginal=false);
	/// 得到指定纹理的高度
	int GetTextureHeight(HTEXTURE tex,bool bOriginal=false);
	/// 根据字体索引，大小，字体颜色，轮廓颜色查找当前是否存在这个字体的纹理
	CMolFigureFont* FindFigureTexture(u32 findex,int fsize,CMolColor textcol,CMolColor figurecol);
	/// 添加一个轮廓文字到系统中
	void AddFigureTexture(HTEXTURE tex,u32 findex,int fsize,CMolColor textcol,CMolColor figurecol,u32 pTop,u32 pLeft,u32 pTexw,u32 pTexh,u32 pImgw,u32 pImgh);
	/// 锁定纹理
	unsigned long* LockTexture(HTEXTURE tex, bool bReadOnly=true, int left=0, int top=0, int width=0, int height=0);
	/// 解锁纹理
	void UnLockTexture(HTEXTURE tex);
	/// 得到纹理指定位置的颜色值
	CMolColor GetTexColor(HTEXTURE tex,int posx,int posy);
	/// 清除当前系统中所有的纹理
	void ClearAllTextures(void);

	/// 添加一个压缩包到系统中
	void AddPackager(std::string filepath);
	/// 清空所有的压缩包
	void ClearAllPackagers(void);

	/// 导入指定的字体
	CMolGUIBaseFont* LoadFont(const char* fontname,int size,const char* filename="");
	/// 清除系统所有的字体
	void ClearAllFonts(void);

	/// 清除场景
	void Clear(CMolColor col=CMolColor(0,0,0,0));
	/// 选择指定的结点
	void Rotate(int rot,CMolPosition2d<s32> pos,CMolDimension2d<s32> size,CMolDimension2d<s32> hot=CMolDimension2d<s32>(0,0),float hscale=1.0f, float vscale=0.0f);
	/// 开始渲染场景
	bool BeginScene();
	/// 结束场景渲染
	void EndScene();

	/// 画一条2D的线
	void Draw2dLine(const CMolPosition2d<s32>& start,
		const CMolPosition2d<s32>& end,
		CMolColor col=CMolColor(255,255,255,255));
	/// 画一个2D的矩形
	void Draw2dRectangle(const CMolRect<s32>& pos,
		CMolColor colorLeftUp,CMolColor colorRightUp,
		CMolColor colorLeftDown,CMolColor colorRightDown,
		const CMolRect<s32>* clip = 0);
	/// 画一个2D的矩形
	void Draw2dRectangle(const CMolRect<s32>& pos,CMolColor color,const CMolRect<s32>* clip = 0);
	/// 在屏幕上画一个2D的图像
	void Draw2DImage(HTEXTURE tex,CMolPosition2d<s32>& destPos,CMolColor col=CMolColor(255,255,255,255));
	/// 在屏幕上用指定颜色画图像
	void Draw2DImage(HTEXTURE tex, const CMolPosition2d<s32>& destPos,
		const CMolRect<s32>& sourceRect,const CMolRect<s32>* clipRect = 0,
		CMolColor col = CMolColor(255,255,255,255));
	/// 在屏幕上画图像
	void Draw2DImage(HTEXTURE tex, const CMolRect<s32>& destRect,
		const CMolRect<s32>& sourceRect, const CMolRect<s32>* clipRect = 0,
		const CMolColor col = CMolColor(255,255,255,255));

	/// 画字符串
	void DrawString(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// 画带轮廓字符串
	void DrawStringf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol=CMolColor(255,30,30,30),bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// 得到指定字符串的高宽
	CMolDimension2d<s32> GetTextDimension(const char* text);

	/// 从配置文件中导入GUI界面
	virtual bool LoadGUIConfig(const char* filepath);
	/// 从指定GUI文件中导入一个包容器
	void ShowGUIContainer(int id,const char* filepath,SnapStyle style=SANPSTYLE_CENTER,bool isShow=true);
	/// 从指定GUI文件中导入一个包容器，然后显示在指定的位置
	void ShowGUIContainer(int id,const char* filepath,CMolPosition2d<s32> pos,bool isShow=true);

	/// 播放指定的音乐文件
	void MusicPlay(std::string sound,bool isLoop=false);
	/// 播放指定的音效文件
	void EffectPlay(std::string sound);
	/// 停止指定的声音文件
	void SoundStop(std::string sound);
	/// 暂停指定的声音文件
	void SoundPause(std::string sound);
	/// 设置所有音乐的播放音量
	void MusicSetVolume(int _volume);
	/// 得到指定的音乐的播放音量
	int MusicGetVolume(void);
	/// 设置所有音效的播放音量
	void EffectSetVolume(int _volume);
	/// 得到指定的音效的播放音量
	int EffectGetVolume(void);
	/// 检测指定的声音的播放状态
	bool SoundIsPlaying(std::string sound);
	/// 停止播放所有的声音
	void SoundStopAll(void);

	/// 添加一个动画结点到系统中
	CMolAnimatorNode* AddAnimator(std::string name,std::string respath,bool isPlay=true,bool isLoop=true);
	/// 根据动画名称得到动画结点
	CMolAnimatorNode* GetAnimator(std::string name);
	/// 根据名称得到指定的资源
	CMolAnimatorResource* GetResource(std::string name);
	/// 设置当前所有动画结点所在的世界范围
	void SetWorldRect(CMolRect<int> rect);
	/// 得到当前所有动画结点所在的世界范围
	inline CMolRect<int> GetWorldRect(void);
	/// 设置指定动画的世界位置
	void SetAnimWorldPos(std::string name,CMolPosition2d<int> pos);
	/// 设置指定动画的世界范围
	void SetAnimWorldRect(std::string name,CMolRect<int> rect);
	/// 清空所有的动画结点
	void ClearAllAnimators(void);

	/// 根据客户端下载配置文件从服务器更新游戏
	void UpdateGame(std::string configfile,std::string decpath="");
	/// 下载指定网址的文件到指定的目录中，我们的下载基于http协议，这个下载一次只能下载一个文件,而且文件必须是以pak打包过的压缩文件
	bool DownloadFile(std::string file,std::string path="");
	/// 下载指定网址的文件到指定的目录中
	bool DownloadSingleFile(std::string file,std::string path="",bool isTip=true);
	/// 得到当前下载的文件
	inline std::string GetCurrentFile(void) { return m_CurDownloadFile; }
	/// 设置当前下载状态
	void SetUpdateState(DownloadStatus state);
	/// 得到当前下载状态
	inline DownloadStatus GetUpdateState(void) { return m_DownloadStatus; }
	/// 得到当前下载的配置
	inline CMolBaseFrame::UpdataSet GetUpdateSet(void) { return m_UpdataSet; }
	/// 根据服务器下载的更新配置文件得到要更新的文件列表
	bool GetUpdateFileList(std::string config);

	/// 初始化游戏资源
	virtual void LoadResources(void) { }
	/// 游戏场景渲染
	virtual void DrawScene(void);
	/// 下载进度更新
	virtual int OnProcessFileDownload(std::string file,double dt, double dn, double ut, double un); 
	/// 处理游戏更新
	virtual void OnProcessGameUpdate(void);

	/// 处理接收到网络消息
	virtual void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);
	
	/// 处理用户进入房间消息
	void OnProcessEnterRoomMsg(unsigned int nChairID,CMolMessageIn &msg);
	/// 处理用户离开房间消息
	void OnProcessLeaveRoomMsg(unsigned int nChairID,CMolMessageIn &msg);	
	/// 处理用户断开连接消息
	void OnProcessDisconnectNetMes(unsigned int nChairID,CMolMessageIn &mes);	
	/// 处理用户断线重连消息
	void OnProcessDisconnectBackNetMes(unsigned int nChairID,CMolMessageIn &mes);	

	/// 处理用户准备开始消息
	void OnProcessPlayerReadyMes(unsigned int nChairID);
	/// 处理用户房间消息
	void OnProcessPlayerGameRoomMsg(CMolMessageIn &msg);	
	
	
	/// 根据用户椅子号得到用户在游戏中的位置
	int SwitchViewChairID(int nChairID);
	/// 得到玩家自己的椅子号
	int GetMeChairID();
	/// 根据玩家ID得到玩家的椅子号
	int GetUserChairID(int playerID);
	/// 根据用户椅子号得到用户数据
	Player* GetUserData(int nChairID);
	/// 根据用户在本地游戏中的位置得到用户数据
	Player* GetUserInfo(int nViewChairID);
	/// 设置定时器
	bool SetGameTimer(int wChairID, unsigned int nTimerID, unsigned int nElapse);
	/// 删除定时器
	bool KillGameTimer(unsigned int nTimerID);	
	/// 获取用在本地游戏中的位置的用户时间
	int GetUserTimer(int nViewChairID);
	/// 关闭所有的房间定时器
	void CloseAllRoomTimers(void);
	/// 是否旁观模式
	bool IsLookonMode();	

protected:
	/// 得到当前程序的路径
	std::string GetCurrentPath(void);
	/// 处理系统事件
	virtual bool postEventFromUser(const CMolEvent& event);

private:
	/// 初始化D3D
	bool InitD3D(int wWidth,int wHeight,bool isWindow=true);
	/// 重新载入游戏资源
	void ReLoadGameResources(void);
	/// 初始化D3D，可以使用全屏或者窗口模式
	bool CreateD3DScreenOrWindow(int wWidth,int wHeight,bool isWindow=true);
	/// 找寻真确的屏幕格式
	int	 Format_Id(D3DFORMAT fmt);
	/// 场景渲染
	void RenderScene(void);
	/// 卸载D3D
	void ShutdownD3D(void);
	/// 卸载顶点和索引缓冲区
	void ShutdownVertexAndIndexBuffer(void);
	/// 设置当前系统使用平行投影
	void SetProjectionMatrix(int width, int height);
	/// 初始顶点缓冲区和索引缓冲区
	bool InitVertexBufferAndIndexBuffer(void);
	/// 重新设置D3D
	bool RestoreD3D(void);
	/// 改变游戏窗口的高宽
	void ChangeGameFrameSize(CMolDimension2d<s32> size);
	/// 渲染所有的基本对象
	void Render_batch(bool bEndScene=false);
	/// 设置渲染模式
	void SetBlendMode(int blend);
	/// 在当前系统中查找指定名称的纹理
	MOLTexture* FindTextureByName(const std::string filename);
	/// 在当前系统中查找自定名称的压缩包
	CMolPackager* FindPackagerByName(std::string filename);
	/// 在当前系统所有的压缩包中查找指定的资源文件
	unsigned char* GetResourceFromThePackager(std::string filename,unsigned long* datasize);
	/// 加载当前游戏目录下所有的游戏资源文件
	void LoadGameResources(void);
	/// 导入系统初始配置文件
	void LoadSystemInitConfig(void);
	/// 根据文件路径名建立相应的目录
	void CreateDirectionByPath(std::string path,std::string filename);
	///// 解压zip文件
	//bool unzip(std::string zipfile,std::string decpath="");
	/// 从当前目录下加载所有的压缩资源文件
	void LoadGameResourcesFromCurDir(void);
	/// 在指定的字符串中用指定的字符串替换指定的字符串
	std::string replace( const std::string& inStr, const char* pSrc, const char* pReplace);

	/// curl 使用的下载进度更新函数
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// 游戏更新函数
	static unsigned __stdcall ThreadGameUpdate(void * pParam);
	/// 游戏下载函数
	static unsigned __stdcall ThreadGameDownload(void * pParam);
	/// 根据游戏更新状态发送相应的消息
	void OnProcessUpdateState(void);

	/// 初始winsocket
	bool InitWinSocket(void);
	/// 导入系统初始字体
	void loadBuiltInFont();
	/// 检查是否有指定名称的字体面
	CMolGUITTFace* IsExitTTFace(std::string filename);
	/// 检查是否有指定名称指定大小的字体
	CMolGUITTFont* IsExitTTFont(std::string filename,int size);
	/// 建立logo纹理
	HTEXTURE GetLogoTexture(void);
	/// 渲染logo纹理
	void DrawLogoTexture(void);

	/// 释放系统所有的音乐文件
	void DeleteAllSounds(void);
	/// 检测系统中是否有指定名称的音乐文件
	MolSouStr* GetSoundByName(std::string filename);

private:
	/// 清除输入法文字候选列表
	void           ClearCandidateList(void);
	/// 取得输入法文字候选列表
	BOOL           GetCandidateList(HWND hWnd);
	/// 转换候选文字列表到字符串
	BOOL           CandidateToString(LPCANDIDATELIST lpCandidateList);

public:

	/// 处理WM_CHAR消息
	void           OnChar(TCHAR ch);
	/// 处理WM_IME_NOTIFY消息
	void           OnImeNotify(HWND hWnd,WPARAM wParam);
	/// 处理WM_IME_COMPOSITION消息
	void           OnImeComposition(HWND hWnd,LPARAM lParam);

	/// 取得输入的字符串
	char* GetImeString(void);
	/// 清除输入的字符串
	void  ClearImeString(void);

private:
	CWnd                    *m_Parent;
	IDirect3D9*				pD3D;
	IDirect3DDevice9*		pD3DDevice;
	D3DPRESENT_PARAMETERS*  d3dpp;
	D3DPRESENT_PARAMETERS   d3dppW;
	D3DPRESENT_PARAMETERS   d3dppFS;
	IDirect3DVertexBuffer9*	pVB;
	IDirect3DIndexBuffer9*	pIB;
	bool                    m_isWindow;
	bool                    m_isSwitchMode;                              /**< 是否允许进行游戏中全屏，窗口切换 */
	CMolDimension2d<int>    m_ScreenSize;
	std::string				m_szIniFile;                                 /**< 当前操作的配置文件 */
	char	                m_szIniString[256];
	HANDLE                  m_hOneInstance;                              /**< 用于游戏单开的控制 */
	std::string             m_curWorkingDir;                             /**< 当前工作的目录 */
	std::string             m_prodirection;                              /**< 程序永久性目录 */
	std::string             m_caption;                                   /**< 窗口标题 */

	D3DXMATRIX			    matView;
	D3DXMATRIX			    matProj;

	MOLVertex*			    VertArray;

	int					    nPrim;
	int					    CurPrimType;
	int					    CurBlendMode;
	HTEXTURE			    CurTexture;
	HTEXTURE                m_LogoTexture; 

	CMolTcpSocketClient     m_TcpSocketClient;                     /**< 网络客户端 */
	int                     m_ServerSocket;                        /**< 要连接的服务器SOCKET */

	std::map<HTEXTURE,MOLTexture*>   pTexturesList;                        /**< 系统使用的纹理列表 */
	std::map<std::string,CMolPackager*> m_PackagerList;                /**< 系统使用的压缩包 */

	std::map<std::string,std::string>  m_StartCommonds;            /**< 启动参数列表 */

	/** 
	 * 字体面结构
	 */
	struct TTFaceStruct
	{
		TTFaceStruct():face() {}
		TTFaceStruct(std::string name,CMolGUITTFace *f)
			: face(f)
		{
			if(!name.empty()) 
				strcpy(filename,name.c_str());
		}

		char filename[256];
		CMolGUITTFace *face;
	};

	/** 
	 * 字体结构
	 */
	struct TTFontStruct
	{
		TTFontStruct()
			: size(0),font(NULL)
		{

		}
		TTFontStruct(std::string name,int s,CMolGUITTFont *f)
			: size(s),font(f)
		{
			if(!name.empty()) 
				strcpy(filename,name.c_str());
		}

		char filename[256];
		int size;
		CMolGUITTFont *font;
	};

	CMolGUITTFont              *m_defaultFont;                   /**< 系统使用的初始字体 */
	std::vector<TTFaceStruct>  m_GUITTFaceList;                  /**< 保存字体所用到的面 */
	std::vector<TTFontStruct>  m_GUITTFontList;                  /**< 系统所使用到的字体列表 */
	std::list<CMolFigureFont>  pFigrueFontList;                    /**< 带轮廓的文字列表 */

	int					       m_SampleRate;                      /**< 声音相关 */
	std::map<std::string,MolSouStr> m_soundlist;                  /**< 系统中所使用到的声音文件 */
	std::vector<MolSouStr>  m_pausesoundlist;                     /**< 暂停的声音列表 */

	char                       *m_CurlError;                      /**< 存储curl产生的错误信息 */
	std::string                m_CurDownloadFile;                 /**< 当前下载的文件 */
	DownloadStatus             m_DownloadStatus;                  /**< 当前下载状态 */
	std::string                m_UpdateConfigFile;                /**< 更新的配置文件 */
	std::string                m_UpdateDecPath;                   /**< 游戏下载的目标目录 */
	UpdataSet                  m_UpdataSet;                       /**< 当前下载配置 */
	std::vector<std::string>   m_UpdateList;                      /**< 要更新的文件列表 */
	int                        m_DownloadProcess;                 /**< 当前下载文件的进度 */
	float                      m_UpdateVer;                       /**< 要更新的文件版本,只有当大于当前版本时才更新 */
	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;

	// 资源相关
	HANDLE				       m_Search;
	WIN32_FIND_DATA		       m_SearchData;

	//输入法相关
	LPCANDIDATELIST            m_lpCandList;                                  /**< 输入法候选文字列表 */
	char                       m_lpszImeInput[1024];                          /**< 指向IME输入的文字字符串指针 */
	LPSTR                      m_lpszCurInputLanguageDesc;                    /**< 指向当前语言描述的指针 */
	char                       m_cCandidateList[1024];                        /**< 候选文字列表缓冲区 */

	static CMolBaseFrame       *m_Singleton;

	lua_State                  *m_ScriptState;                                /**< 引擎脚本接口 */

	HANDLE                     m_hShareMemory;                                /**< 用于进程之间通信 */
	std::list<std::string>     m_hLogStrList;                                 /**< 日志列表 */

	//OpenAL_AudioInterfaceFactory* iface_factory;                              /**< 管理视频声音设备 */
	CRegisterKey               m_RegisterKey;                                 /**< 用于操作数据库 */

	std::string                m_curGUIFile;                                  /**< 当前使用的GUI配置 */
	bool                       m_GUIIsRending;                                /**< GUI渲染标志 */

	CMolAnimatorManager        *m_AnimatorManager;                            /**< 动画管理器 */
	
	/**
	 * 游戏房间中定时器结构
	 */
	struct RoomTimer
	{
		RoomTimer():wChairID(0),wTimerID(0),wElapse(0),wCurTimer(0)
		{}
		RoomTimer(int cID,unsigned int tID,unsigned int e)
			: wChairID(cID),wTimerID(tID),wElapse(e)
		{
			wCurTimer = e;
		}
		
		int wChairID;            // 用户在房间中的桌位
		unsigned int wTimerID;   // 定时器ID
		unsigned int wElapse;    // 定时间隔
		int wCurTimer;           // 当前时间
	};

	
	std::map<unsigned int,RoomTimer>     m_RoomTimers;                                  /**< 房间定时器 */
	std::map<unsigned int,unsigned int>  m_OtherRoomTimers;                             /**< 另一个房间定时器 */

	// 实现
protected:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); 
	LRESULT OnGameUpdate(WPARAM wParam,LPARAM lParam); 
	afx_msg LRESULT OnHotHey(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//extern CMolBaseFrame *m_MolBaseFrame;
//extern TheoraVideoManager *m_mgrVideo;

//}
//}

#endif