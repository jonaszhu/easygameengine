#ifndef _GUI_FLASH_H_
#define _GUI_FLASH_H_

#include "Mole2dBaseGUIElement.h"
#include "MolMutex.h"
#include "Mole2dColor.h"

#include "Flash/FlashPlayer.h"

class MOLEXPORT CMolGUIFlash : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIFlash();
	/// �������Ĺ��캯��
	CMolGUIFlash(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIFlash();

	/// ����flash���������Լ��ر��غ���������
	void SetFlashPath(std::string path);
	/// �õ�flash����·��
	inline std::string GetFlashPath(void) { return m_flashPath; }
	/// �򿪱���ָ����flash
	bool LoadFlashFromFile(std::string filepath);
	/// ��ס���ز���
	inline void LockFlashDownload(void) { m_imgDownloadMutex.Acquire(); }
	/// �������ز���
	inline void UnlockFlashDownload(void) { m_imgDownloadMutex.Release(); }

	BOOL	IsPlaying();
	void	Pause();
	void	Unpause();
	void	Back();
	void	Rewind();
	void	Forward();	
	BOOL	GetLoopPlay();
	void	SetLoopPlay(BOOL bLoop);

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// ����֮ǰ����
	virtual bool OnProcessPostUpdate();

private:
	/// ��Ϸ���º���
	static unsigned __stdcall ThreadFlashDownload(void * pParam);
	/// �ر�flash���������߳�
	void CloseFlashDownloadThread(void);

private:
	FlashPlayer*	           m_pFlashPlayer;
	std::string			   m_flashPath;

	HTEXTURE                   m_texRending;                         /**< ������ʾʹ�õ�����ͼƬ */
	HANDLE                     m_imgDownloadThread;                  /**< ͼƬ�����߳� */                    
	unsigned                   m_imgDownloadThreadID;                /**< ͼƬ�����߳�ID */    
	Mutex                      m_imgDownloadMutex;                   /**< ����ͼƬ���� */
};

#endif
