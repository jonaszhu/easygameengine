#ifndef _MOLE2D_GUI_IMAGE_H_
#define _MOLE2D_GUI_IMAGE_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3 д��ƽ��,ͼ��ؼ�,������ʾ����ͼ���ͼ��һ����
*/

#include "Mole2dBaseGUIElement.h"
#include "MolMutex.h"
#include "Mole2dColor.h"

#include "gif89a.h"

#include <vector>

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIImage : public CMolBaseGUIElement
{
public:
	/**
	 * gif����֡
	 */
	struct GifAnimStr
	{
		GifAnimStr():speed(0),tex(0),disposalMethod(0) {}
		GifAnimStr(int s,HTEXTURE t,CMolPosition2d<int> p,CMolDimension2d<int> ss,int dm):speed(s),tex(t),pos(p),size(ss),disposalMethod(dm) {}

		int speed;               // �������ŵ��ӳ�ʱ��
		HTEXTURE tex;            // �������ŵ�����
		CMolPosition2d<int> pos; // ��ʼ��ʾλ��
		CMolDimension2d<int> size; // ��ʾ�߿�
		int disposalMethod;       // ��������ʽ
	};

	/// ���캯��
	CMolGUIImage();
	/// �������Ĺ��캯��
	CMolGUIImage(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIImage();

	/// ����ͼƬ��ַ
	void SetImagePath(std::string path);
	/// �õ�ͼƬ��ַ
	inline std::string GetImagePath(void) { return m_imgPath; }
	/// ����ͼƬ����ʾλ��
	inline void SetSrcStartPos(int x,int y)
	{
		pSrcStartX = x;
		pSrcStartY = y;
	}
	/// �õ�ͼƬ����ʾλ��
	inline void GetSrcStartPos(int *x,int *y)
	{
		*x = pSrcStartX;
		*y = pSrcStartY;
	}
	/// ����ͼƬ����ʾ�߿�
	inline void SetSrcHeightAndWidth(int w,int h)
	{
		pSrcWidth = w;
		pSrcHeight = h;	
	}
	/// �õ�ͼƬ����ʾ�߿�
	inline void GetSrcHeightAndWidth(int *w,int *h)
	{
		*w = pSrcWidth;
		*h = pSrcHeight;
	}
	/// ����ͼƬ����ɫ
	inline void SetColor(CMolColor col) { m_Color = col; }
	/// �õ�ͼƬ����ɫ
	inline CMolColor GetColor(void) { return m_Color;}
	/// ��ס���ز���
	inline void LockImageDownload(void) { m_imgDownloadMutex.Acquire(); }
	/// �������ز���
	inline void UnlockImageDownload(void) { m_imgDownloadMutex.Release(); }
	/// ��ָ����ͼƬ
	bool LoadImageFromFile(std::string filepath);
	/// ����ͼƬ����ʾ�Ƕ�
	inline void SetAngle(int angle) { m_angle = angle; }
	/// �õ�ͼƬ����ʾ�Ƕ�
	inline int GetAngle(void) { return m_angle; }

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// ��Ϸ���º���
	static unsigned __stdcall ThreadImageDownload(void * pParam);
	/// �ر�ͼƬ�����߳�
	void CloseImageDownloadThread(void);
	/// ������еĶ�������
	void ClearAllTextures(void);

private:
	int pSrcStartX,pSrcStartY,pSrcWidth,pSrcHeight;
	CMolColor m_Color;
	std::string m_imgPath;

	HANDLE                     m_imgDownloadThread;                  /**< ͼƬ�����߳� */                    
	unsigned                   m_imgDownloadThreadID;                /**< ͼƬ�����߳�ID */    
	Mutex                      m_imgDownloadMutex;                   /**< ����ͼƬ���� */

	CGif89a                    m_Gif89a;                             /**< ���ڵ���gif���� */
	CMolDimension2d<int>       m_animSize;                           /**< gif�����ĸ߿� */
	std::vector<GifAnimStr>    m_GifTexList;                         /**< gif�����б� */
	int                        m_CurFrameIndex;                      /**< ��ǰ������ʾ֡���� */
	bool                       m_isRendering;                        /**< �Ƿ���Ⱦ���� */
	int                        m_DisMode;                            /**< 1 - ��ʾ��ʾͼƬ��2 - ��ʾ��ʾgif���� */
	DWORD                      m_CurTime;                            /**< ���ڿ��ƶ����Ĳ��� */
	int                        m_angle;                              /**< Ҫ��ת��ͼƬ�ĽǶ� */
	//Mutex                      m_imgDisplayMutex;                    /**< ����ͼƬ��ʾ */
};

//}
//}

#endif
