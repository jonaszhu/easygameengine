#ifndef _MOLE2D_BASE_FRAME_H_
#define _MOLE2D_BASE_FRAME_H_

/** 
* Mole2d ͼ������
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
 * ���ڼ�¼��־��Ϣ
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
 * ��������
 */
enum MolSoundType
{
	SOUNDTYPE_EFFECT = 0,            // ��Ч
	SOUNDTYPE_MUSIC,                 // ����
	SOUNDTYPE_NULL
};

/**
 * �����ṹ
 */
struct MolSouStr
{
	MolSouStr()
		: type(SOUNDTYPE_NULL),id(0),data(0) {}
	MolSouStr(MolSoundType t,DWORD i,void *pData)
		: type(t),id(i),data(pData) {}

	MolSoundType type;               // ����
	DWORD id;                        // ID
	void *data;                      // ���ڴ洢��������
};

/**
 * ������������ṹ
 */
struct CMolFigureFont
{
	CMolFigureFont():size(0),fontIndex(0),tex(0),top(0),left(0),texw(0),texh(0),imgw(0),imgh(0)
	{}
	CMolFigureFont(HTEXTURE t,u32 fi,int s,CMolColor tc,CMolColor fc,u32 pTop,u32 pLeft,u32 pTexw,u32 pTexh,u32 pImgw,u32 pImgh)
		: tex(t),fontIndex(fi),size(s),textColor(tc),figureColor(fc),top(pTop),left(pLeft),texw(pTexw),texh(pTexh),imgw(pImgw),imgh(pImgh)
	{}

	u32 fontIndex;          // ��������
	int size;               // �����С
	CMolColor textColor;    // ������ɫ
	CMolColor figureColor;  // ������ɫ
	HTEXTURE tex;           // ��������

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
	* ���ڴ洢���µ�����
	*/
	struct UpdataSet
	{
		UpdataSet()
			: ver(0)
		{}
		UpdataSet(float v,std::string a)
			: ver(v),address(a)
		{}

		float ver;             // ��ǰ����汾
		std::string address; // ��ǰ���µķ�����
	};

	CMolBaseFrame(CWnd* pParent = NULL);	// ��׼���캯��
	/// ��������
	virtual ~CMolBaseFrame();

	inline static CMolBaseFrame & getSingleton() { assert(m_Singleton); return *m_Singleton; }
	inline static CMolBaseFrame * getSingletonPtr() { return m_Singleton; }
	/// ��ʼ������
	bool Initialize(std::string caption,CMolDimension2d<int> size);
	/// �ر���Ϸ����
	void CloseGameFrame(int state=MOLE2D_GUI_CLOSE_FRAME);
	/// �����Ƿ�����л���Ϸģʽ
	inline void SetSwitchGameMode(bool isSwitch) { m_isSwitchMode = isSwitch; }
	/// ��鵱ǰ�Ƿ�����л���Ϸģʽ
	inline bool IsSwitchGameMode(void) { return m_isSwitchMode; }
	/// ��ʼָ��ID����Ϸ��ʱ��
	void StartGameTimer(unsigned int id,unsigned int time);
	/// ָֹͣ��ID����Ϸ��ʱ��
	void StopGameTimer(unsigned int id);
	/// ��ӡ��־����־�ļ���
	void SystemLog(Level le,std::string msg);
	/// �õ�ָ�����Ƶ�����
	std::string GetStartCommond(std::string name);
	/// ���ù��
	void ChangeCursor(std::string path);
	/// ��Ϸ������С��
	void MinGameFrame(void);
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ���ڴ���ʱ����Ϣ
	virtual void OnProcessGameTimer(unsigned int IdTimer);
	/// ��ȫ���ʹ���֮ǰ�л�
	void SwitchScreenAndWindow(void);
	/// �ڴ���ģʽ�¶�����Ϸ����
	void DitherMainFrame(void);
	/// ���ָ�����ļ��Ƿ����
	bool FileIsExist(std::string filename);
	/// �õ�����������Ŀ¼
	inline std::string GetProgressDirection(void) { return m_prodirection; }
	/// �õ���ǰ����Ĺ���·��
	inline std::string GetWorkingDirection(void) { return m_curWorkingDir; }
	/// �ı���Ϸ����Ŀ¼���ı��˹���Ŀ¼������ζ����ǰ����Դ����ʹ���ˣ���Ҫ���¼����µ���Դ��
	void ChangePlayerWorkingDir(std::string filename,bool loadscript=true);
	/// ������Ļ��ͼ
	void Snapshot(std::string filename="");	
	/// ת�����ֽڵ�˫�ֽ�
	std::wstring ConverToWideChar(const std::string& str);
	/// ת��˫�ֽڵ����ֽ�
	std::string ConverToMultiChar(const std::wstring& str);
	/// ��ע���д������
	void WriteRegisterKey(std::string pszKey,std::string pVal);
	/// ��ȡע����е�����
	std::string ReadRegisterKey(std::string pszKey);
	/// ��ȡָ���ַ�����MD5��
	std::string GetStringMD5(std::string str);
	/// ������Ϸ����״̬
	inline void SetDownloadState(DownloadStatus state) { m_DownloadStatus = state; }
	/// �õ���Ϸ����״̬
	inline DownloadStatus GetDownloadState(void) { return m_DownloadStatus; }
	/// �õ����ص�Ŀ��Ŀ¼
	inline std::string GetDownloadDecPath(void) { return m_UpdateDecPath; }
	/// ͨ����վ�õ���Ϣ
	std::string GetNetMessage(std::string address);
	/// �õ�����б�
	inline CMolGUIRoomList* GetRoomList(void) { return m_MainRoomList; }
	/// ��ʼ���ű�����
	void InitScriptSystem(void);
	/// �ͷŽű�����
	void DestroyScriptSystem(void);
	/// ģʽ�Ի���
	int DoModal(void);

	/// ��ʼ�����ļ�
	void Ini_SetFile(const char *filename);
	/// �õ������ļ�
	char* Ini_GetFile(void);
	/// �������β���
	void Ini_SetInt(const char *section, const char *name, int value);
	/// �õ����β���
	int Ini_GetInt(const char *section, const char *name, int def_val);
	/// ���ø������
	void Ini_SetFloat(const char *section, const char *name, float value);
	/// �õ��������
	float Ini_GetFloat(const char *section, const char *name, float def_val);
	/// �����ַ�������
	void Ini_SetString(const char *section, const char *name, const char *value);
	/// �õ��ַ�������
	char* Ini_GetString(const char *section, const char *name, const char *def_val);

	/// �ر�����
	void CloseConnect(void);
	/// ����ָ���ķ�����
	bool Connect(std::string ipaddress,int port);
	/// ��������
	int Send(CMolMessageOut &msg);
	/// ��⵱ǰ�Ƿ�����
	bool IsConnected(void);

	/// �õ���Ļ��С
	CMolDimension2d<s32> getScreenSize();
	/// ��ָ���ļ��е�������
	void* LoadResource(const char* filename, unsigned long *size=0);
	/// ��ϵͳ�е���һ������
	HTEXTURE LoadTexture(const char* filename,unsigned long size=0);
	/// ����һ��ָ����С�Ŀհ�����
	HTEXTURE CreateTexture(const char* filename,int width,int height);
	/// �ͷ�ָ��ID������
	void FreeTexture(HTEXTURE tex);
	/// �õ�ָ������Ŀ��
	int GetTextureWidth(HTEXTURE tex,bool bOriginal=false);
	/// �õ�ָ������ĸ߶�
	int GetTextureHeight(HTEXTURE tex,bool bOriginal=false);
	/// ����������������С��������ɫ��������ɫ���ҵ�ǰ�Ƿ����������������
	CMolFigureFont* FindFigureTexture(u32 findex,int fsize,CMolColor textcol,CMolColor figurecol);
	/// ���һ���������ֵ�ϵͳ��
	void AddFigureTexture(HTEXTURE tex,u32 findex,int fsize,CMolColor textcol,CMolColor figurecol,u32 pTop,u32 pLeft,u32 pTexw,u32 pTexh,u32 pImgw,u32 pImgh);
	/// ��������
	unsigned long* LockTexture(HTEXTURE tex, bool bReadOnly=true, int left=0, int top=0, int width=0, int height=0);
	/// ��������
	void UnLockTexture(HTEXTURE tex);
	/// �õ�����ָ��λ�õ���ɫֵ
	CMolColor GetTexColor(HTEXTURE tex,int posx,int posy);
	/// �����ǰϵͳ�����е�����
	void ClearAllTextures(void);

	/// ���һ��ѹ������ϵͳ��
	void AddPackager(std::string filepath);
	/// ������е�ѹ����
	void ClearAllPackagers(void);

	/// ����ָ��������
	CMolGUIBaseFont* LoadFont(const char* fontname,int size,const char* filename="");
	/// ���ϵͳ���е�����
	void ClearAllFonts(void);

	/// �������
	void Clear(CMolColor col=CMolColor(0,0,0,0));
	/// ѡ��ָ���Ľ��
	void Rotate(int rot,CMolPosition2d<s32> pos,CMolDimension2d<s32> size,CMolDimension2d<s32> hot=CMolDimension2d<s32>(0,0),float hscale=1.0f, float vscale=0.0f);
	/// ��ʼ��Ⱦ����
	bool BeginScene();
	/// ����������Ⱦ
	void EndScene();

	/// ��һ��2D����
	void Draw2dLine(const CMolPosition2d<s32>& start,
		const CMolPosition2d<s32>& end,
		CMolColor col=CMolColor(255,255,255,255));
	/// ��һ��2D�ľ���
	void Draw2dRectangle(const CMolRect<s32>& pos,
		CMolColor colorLeftUp,CMolColor colorRightUp,
		CMolColor colorLeftDown,CMolColor colorRightDown,
		const CMolRect<s32>* clip = 0);
	/// ��һ��2D�ľ���
	void Draw2dRectangle(const CMolRect<s32>& pos,CMolColor color,const CMolRect<s32>* clip = 0);
	/// ����Ļ�ϻ�һ��2D��ͼ��
	void Draw2DImage(HTEXTURE tex,CMolPosition2d<s32>& destPos,CMolColor col=CMolColor(255,255,255,255));
	/// ����Ļ����ָ����ɫ��ͼ��
	void Draw2DImage(HTEXTURE tex, const CMolPosition2d<s32>& destPos,
		const CMolRect<s32>& sourceRect,const CMolRect<s32>* clipRect = 0,
		CMolColor col = CMolColor(255,255,255,255));
	/// ����Ļ�ϻ�ͼ��
	void Draw2DImage(HTEXTURE tex, const CMolRect<s32>& destRect,
		const CMolRect<s32>& sourceRect, const CMolRect<s32>* clipRect = 0,
		const CMolColor col = CMolColor(255,255,255,255));

	/// ���ַ���
	void DrawString(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// ���������ַ���
	void DrawStringf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol=CMolColor(255,30,30,30),bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// �õ�ָ���ַ����ĸ߿�
	CMolDimension2d<s32> GetTextDimension(const char* text);

	/// �������ļ��е���GUI����
	virtual bool LoadGUIConfig(const char* filepath);
	/// ��ָ��GUI�ļ��е���һ��������
	void ShowGUIContainer(int id,const char* filepath,SnapStyle style=SANPSTYLE_CENTER,bool isShow=true);
	/// ��ָ��GUI�ļ��е���һ����������Ȼ����ʾ��ָ����λ��
	void ShowGUIContainer(int id,const char* filepath,CMolPosition2d<s32> pos,bool isShow=true);

	/// ����ָ���������ļ�
	void MusicPlay(std::string sound,bool isLoop=false);
	/// ����ָ������Ч�ļ�
	void EffectPlay(std::string sound);
	/// ָֹͣ���������ļ�
	void SoundStop(std::string sound);
	/// ��ָͣ���������ļ�
	void SoundPause(std::string sound);
	/// �����������ֵĲ�������
	void MusicSetVolume(int _volume);
	/// �õ�ָ�������ֵĲ�������
	int MusicGetVolume(void);
	/// ����������Ч�Ĳ�������
	void EffectSetVolume(int _volume);
	/// �õ�ָ������Ч�Ĳ�������
	int EffectGetVolume(void);
	/// ���ָ���������Ĳ���״̬
	bool SoundIsPlaying(std::string sound);
	/// ֹͣ�������е�����
	void SoundStopAll(void);

	/// ���һ��������㵽ϵͳ��
	CMolAnimatorNode* AddAnimator(std::string name,std::string respath,bool isPlay=true,bool isLoop=true);
	/// ���ݶ������Ƶõ��������
	CMolAnimatorNode* GetAnimator(std::string name);
	/// �������Ƶõ�ָ������Դ
	CMolAnimatorResource* GetResource(std::string name);
	/// ���õ�ǰ���ж���������ڵ����緶Χ
	void SetWorldRect(CMolRect<int> rect);
	/// �õ���ǰ���ж���������ڵ����緶Χ
	inline CMolRect<int> GetWorldRect(void);
	/// ����ָ������������λ��
	void SetAnimWorldPos(std::string name,CMolPosition2d<int> pos);
	/// ����ָ�����������緶Χ
	void SetAnimWorldRect(std::string name,CMolRect<int> rect);
	/// ������еĶ������
	void ClearAllAnimators(void);

	/// ���ݿͻ������������ļ��ӷ�����������Ϸ
	void UpdateGame(std::string configfile,std::string decpath="");
	/// ����ָ����ַ���ļ���ָ����Ŀ¼�У����ǵ����ػ���httpЭ�飬�������һ��ֻ������һ���ļ�,�����ļ���������pak�������ѹ���ļ�
	bool DownloadFile(std::string file,std::string path="");
	/// ����ָ����ַ���ļ���ָ����Ŀ¼��
	bool DownloadSingleFile(std::string file,std::string path="",bool isTip=true);
	/// �õ���ǰ���ص��ļ�
	inline std::string GetCurrentFile(void) { return m_CurDownloadFile; }
	/// ���õ�ǰ����״̬
	void SetUpdateState(DownloadStatus state);
	/// �õ���ǰ����״̬
	inline DownloadStatus GetUpdateState(void) { return m_DownloadStatus; }
	/// �õ���ǰ���ص�����
	inline CMolBaseFrame::UpdataSet GetUpdateSet(void) { return m_UpdataSet; }
	/// ���ݷ��������صĸ��������ļ��õ�Ҫ���µ��ļ��б�
	bool GetUpdateFileList(std::string config);

	/// ��ʼ����Ϸ��Դ
	virtual void LoadResources(void) { }
	/// ��Ϸ������Ⱦ
	virtual void DrawScene(void);
	/// ���ؽ��ȸ���
	virtual int OnProcessFileDownload(std::string file,double dt, double dn, double ut, double un); 
	/// ������Ϸ����
	virtual void OnProcessGameUpdate(void);

	/// ������յ�������Ϣ
	virtual void OnProcessNetMessage(ConnectState state,CMolMessageIn &msg);
	
	/// �����û����뷿����Ϣ
	void OnProcessEnterRoomMsg(unsigned int nChairID,CMolMessageIn &msg);
	/// �����û��뿪������Ϣ
	void OnProcessLeaveRoomMsg(unsigned int nChairID,CMolMessageIn &msg);	
	/// �����û��Ͽ�������Ϣ
	void OnProcessDisconnectNetMes(unsigned int nChairID,CMolMessageIn &mes);	
	/// �����û�����������Ϣ
	void OnProcessDisconnectBackNetMes(unsigned int nChairID,CMolMessageIn &mes);	

	/// �����û�׼����ʼ��Ϣ
	void OnProcessPlayerReadyMes(unsigned int nChairID);
	/// �����û�������Ϣ
	void OnProcessPlayerGameRoomMsg(CMolMessageIn &msg);	
	
	
	/// �����û����Ӻŵõ��û�����Ϸ�е�λ��
	int SwitchViewChairID(int nChairID);
	/// �õ�����Լ������Ӻ�
	int GetMeChairID();
	/// �������ID�õ���ҵ����Ӻ�
	int GetUserChairID(int playerID);
	/// �����û����Ӻŵõ��û�����
	Player* GetUserData(int nChairID);
	/// �����û��ڱ�����Ϸ�е�λ�õõ��û�����
	Player* GetUserInfo(int nViewChairID);
	/// ���ö�ʱ��
	bool SetGameTimer(int wChairID, unsigned int nTimerID, unsigned int nElapse);
	/// ɾ����ʱ��
	bool KillGameTimer(unsigned int nTimerID);	
	/// ��ȡ���ڱ�����Ϸ�е�λ�õ��û�ʱ��
	int GetUserTimer(int nViewChairID);
	/// �ر����еķ��䶨ʱ��
	void CloseAllRoomTimers(void);
	/// �Ƿ��Թ�ģʽ
	bool IsLookonMode();	

protected:
	/// �õ���ǰ�����·��
	std::string GetCurrentPath(void);
	/// ����ϵͳ�¼�
	virtual bool postEventFromUser(const CMolEvent& event);

private:
	/// ��ʼ��D3D
	bool InitD3D(int wWidth,int wHeight,bool isWindow=true);
	/// ����������Ϸ��Դ
	void ReLoadGameResources(void);
	/// ��ʼ��D3D������ʹ��ȫ�����ߴ���ģʽ
	bool CreateD3DScreenOrWindow(int wWidth,int wHeight,bool isWindow=true);
	/// ��Ѱ��ȷ����Ļ��ʽ
	int	 Format_Id(D3DFORMAT fmt);
	/// ������Ⱦ
	void RenderScene(void);
	/// ж��D3D
	void ShutdownD3D(void);
	/// ж�ض��������������
	void ShutdownVertexAndIndexBuffer(void);
	/// ���õ�ǰϵͳʹ��ƽ��ͶӰ
	void SetProjectionMatrix(int width, int height);
	/// ��ʼ���㻺����������������
	bool InitVertexBufferAndIndexBuffer(void);
	/// ��������D3D
	bool RestoreD3D(void);
	/// �ı���Ϸ���ڵĸ߿�
	void ChangeGameFrameSize(CMolDimension2d<s32> size);
	/// ��Ⱦ���еĻ�������
	void Render_batch(bool bEndScene=false);
	/// ������Ⱦģʽ
	void SetBlendMode(int blend);
	/// �ڵ�ǰϵͳ�в���ָ�����Ƶ�����
	MOLTexture* FindTextureByName(const std::string filename);
	/// �ڵ�ǰϵͳ�в����Զ����Ƶ�ѹ����
	CMolPackager* FindPackagerByName(std::string filename);
	/// �ڵ�ǰϵͳ���е�ѹ�����в���ָ������Դ�ļ�
	unsigned char* GetResourceFromThePackager(std::string filename,unsigned long* datasize);
	/// ���ص�ǰ��ϷĿ¼�����е���Ϸ��Դ�ļ�
	void LoadGameResources(void);
	/// ����ϵͳ��ʼ�����ļ�
	void LoadSystemInitConfig(void);
	/// �����ļ�·����������Ӧ��Ŀ¼
	void CreateDirectionByPath(std::string path,std::string filename);
	///// ��ѹzip�ļ�
	//bool unzip(std::string zipfile,std::string decpath="");
	/// �ӵ�ǰĿ¼�¼������е�ѹ����Դ�ļ�
	void LoadGameResourcesFromCurDir(void);
	/// ��ָ�����ַ�������ָ�����ַ����滻ָ�����ַ���
	std::string replace( const std::string& inStr, const char* pSrc, const char* pReplace);

	/// curl ʹ�õ����ؽ��ȸ��º���
	static int UpdateProgress(void *ptr,double dt, double dn, double ut, double un);
	/// ��Ϸ���º���
	static unsigned __stdcall ThreadGameUpdate(void * pParam);
	/// ��Ϸ���غ���
	static unsigned __stdcall ThreadGameDownload(void * pParam);
	/// ������Ϸ����״̬������Ӧ����Ϣ
	void OnProcessUpdateState(void);

	/// ��ʼwinsocket
	bool InitWinSocket(void);
	/// ����ϵͳ��ʼ����
	void loadBuiltInFont();
	/// ����Ƿ���ָ�����Ƶ�������
	CMolGUITTFace* IsExitTTFace(std::string filename);
	/// ����Ƿ���ָ������ָ����С������
	CMolGUITTFont* IsExitTTFont(std::string filename,int size);
	/// ����logo����
	HTEXTURE GetLogoTexture(void);
	/// ��Ⱦlogo����
	void DrawLogoTexture(void);

	/// �ͷ�ϵͳ���е������ļ�
	void DeleteAllSounds(void);
	/// ���ϵͳ���Ƿ���ָ�����Ƶ������ļ�
	MolSouStr* GetSoundByName(std::string filename);

private:
	/// ������뷨���ֺ�ѡ�б�
	void           ClearCandidateList(void);
	/// ȡ�����뷨���ֺ�ѡ�б�
	BOOL           GetCandidateList(HWND hWnd);
	/// ת����ѡ�����б��ַ���
	BOOL           CandidateToString(LPCANDIDATELIST lpCandidateList);

public:

	/// ����WM_CHAR��Ϣ
	void           OnChar(TCHAR ch);
	/// ����WM_IME_NOTIFY��Ϣ
	void           OnImeNotify(HWND hWnd,WPARAM wParam);
	/// ����WM_IME_COMPOSITION��Ϣ
	void           OnImeComposition(HWND hWnd,LPARAM lParam);

	/// ȡ��������ַ���
	char* GetImeString(void);
	/// ���������ַ���
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
	bool                    m_isSwitchMode;                              /**< �Ƿ����������Ϸ��ȫ���������л� */
	CMolDimension2d<int>    m_ScreenSize;
	std::string				m_szIniFile;                                 /**< ��ǰ�����������ļ� */
	char	                m_szIniString[256];
	HANDLE                  m_hOneInstance;                              /**< ������Ϸ�����Ŀ��� */
	std::string             m_curWorkingDir;                             /**< ��ǰ������Ŀ¼ */
	std::string             m_prodirection;                              /**< ����������Ŀ¼ */
	std::string             m_caption;                                   /**< ���ڱ��� */

	D3DXMATRIX			    matView;
	D3DXMATRIX			    matProj;

	MOLVertex*			    VertArray;

	int					    nPrim;
	int					    CurPrimType;
	int					    CurBlendMode;
	HTEXTURE			    CurTexture;
	HTEXTURE                m_LogoTexture; 

	CMolTcpSocketClient     m_TcpSocketClient;                     /**< ����ͻ��� */
	int                     m_ServerSocket;                        /**< Ҫ���ӵķ�����SOCKET */

	std::map<HTEXTURE,MOLTexture*>   pTexturesList;                        /**< ϵͳʹ�õ������б� */
	std::map<std::string,CMolPackager*> m_PackagerList;                /**< ϵͳʹ�õ�ѹ���� */

	std::map<std::string,std::string>  m_StartCommonds;            /**< ���������б� */

	/** 
	 * ������ṹ
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
	 * ����ṹ
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

	CMolGUITTFont              *m_defaultFont;                   /**< ϵͳʹ�õĳ�ʼ���� */
	std::vector<TTFaceStruct>  m_GUITTFaceList;                  /**< �����������õ����� */
	std::vector<TTFontStruct>  m_GUITTFontList;                  /**< ϵͳ��ʹ�õ��������б� */
	std::list<CMolFigureFont>  pFigrueFontList;                    /**< �������������б� */

	int					       m_SampleRate;                      /**< ������� */
	std::map<std::string,MolSouStr> m_soundlist;                  /**< ϵͳ����ʹ�õ��������ļ� */
	std::vector<MolSouStr>  m_pausesoundlist;                     /**< ��ͣ�������б� */

	char                       *m_CurlError;                      /**< �洢curl�����Ĵ�����Ϣ */
	std::string                m_CurDownloadFile;                 /**< ��ǰ���ص��ļ� */
	DownloadStatus             m_DownloadStatus;                  /**< ��ǰ����״̬ */
	std::string                m_UpdateConfigFile;                /**< ���µ������ļ� */
	std::string                m_UpdateDecPath;                   /**< ��Ϸ���ص�Ŀ��Ŀ¼ */
	UpdataSet                  m_UpdataSet;                       /**< ��ǰ�������� */
	std::vector<std::string>   m_UpdateList;                      /**< Ҫ���µ��ļ��б� */
	int                        m_DownloadProcess;                 /**< ��ǰ�����ļ��Ľ��� */
	float                      m_UpdateVer;                       /**< Ҫ���µ��ļ��汾,ֻ�е����ڵ�ǰ�汾ʱ�Ÿ��� */
	HANDLE                     m_UpdateThread;                    
	unsigned                   m_UpdateThreadID;

	// ��Դ���
	HANDLE				       m_Search;
	WIN32_FIND_DATA		       m_SearchData;

	//���뷨���
	LPCANDIDATELIST            m_lpCandList;                                  /**< ���뷨��ѡ�����б� */
	char                       m_lpszImeInput[1024];                          /**< ָ��IME����������ַ���ָ�� */
	LPSTR                      m_lpszCurInputLanguageDesc;                    /**< ָ��ǰ����������ָ�� */
	char                       m_cCandidateList[1024];                        /**< ��ѡ�����б����� */

	static CMolBaseFrame       *m_Singleton;

	lua_State                  *m_ScriptState;                                /**< ����ű��ӿ� */

	HANDLE                     m_hShareMemory;                                /**< ���ڽ���֮��ͨ�� */
	std::list<std::string>     m_hLogStrList;                                 /**< ��־�б� */

	//OpenAL_AudioInterfaceFactory* iface_factory;                              /**< ������Ƶ�����豸 */
	CRegisterKey               m_RegisterKey;                                 /**< ���ڲ������ݿ� */

	std::string                m_curGUIFile;                                  /**< ��ǰʹ�õ�GUI���� */
	bool                       m_GUIIsRending;                                /**< GUI��Ⱦ��־ */

	CMolAnimatorManager        *m_AnimatorManager;                            /**< ���������� */
	
	/**
	 * ��Ϸ�����ж�ʱ���ṹ
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
		
		int wChairID;            // �û��ڷ����е���λ
		unsigned int wTimerID;   // ��ʱ��ID
		unsigned int wElapse;    // ��ʱ���
		int wCurTimer;           // ��ǰʱ��
	};

	
	std::map<unsigned int,RoomTimer>     m_RoomTimers;                                  /**< ���䶨ʱ�� */
	std::map<unsigned int,unsigned int>  m_OtherRoomTimers;                             /**< ��һ�����䶨ʱ�� */

	// ʵ��
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