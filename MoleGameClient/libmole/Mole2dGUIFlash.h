#ifndef _GUI_FLASH_H_
#define _GUI_FLASH_H_

#include "Mole2dBaseGUIElement.h"
#include "MolMutex.h"
#include "Mole2dColor.h"

#include "Flash/FlashPlayer.h"

class MOLEXPORT CMolGUIFlash : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIFlash();
	/// 带参数的构造函数
	CMolGUIFlash(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIFlash();

	/// 加载flash动画，可以加载本地和网络两种
	void SetFlashPath(std::string path);
	/// 得到flash动画路径
	inline std::string GetFlashPath(void) { return m_flashPath; }
	/// 打开本地指定的flash
	bool LoadFlashFromFile(std::string filepath);
	/// 锁住下载操作
	inline void LockFlashDownload(void) { m_imgDownloadMutex.Acquire(); }
	/// 解锁下载操作
	inline void UnlockFlashDownload(void) { m_imgDownloadMutex.Release(); }

	BOOL	IsPlaying();
	void	Pause();
	void	Unpause();
	void	Back();
	void	Rewind();
	void	Forward();	
	BOOL	GetLoopPlay();
	void	SetLoopPlay(BOOL bLoop);

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// 处理画之前更新
	virtual bool OnProcessPostUpdate();

private:
	/// 游戏更新函数
	static unsigned __stdcall ThreadFlashDownload(void * pParam);
	/// 关闭flash动画下载线程
	void CloseFlashDownloadThread(void);

private:
	FlashPlayer*	           m_pFlashPlayer;
	std::string			   m_flashPath;

	HTEXTURE                   m_texRending;                         /**< 动画显示使用的纹理图片 */
	HANDLE                     m_imgDownloadThread;                  /**< 图片下载线程 */                    
	unsigned                   m_imgDownloadThreadID;                /**< 图片下载线程ID */    
	Mutex                      m_imgDownloadMutex;                   /**< 用于图片下载 */
};

#endif
