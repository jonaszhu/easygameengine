#ifndef _MOLE2D_GUI_IMAGE_H_
#define _MOLE2D_GUI_IMAGE_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3 写于平武,图像控件,用于显示整副图像或图像一部分
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
	 * gif动画帧
	 */
	struct GifAnimStr
	{
		GifAnimStr():speed(0),tex(0),disposalMethod(0) {}
		GifAnimStr(int s,HTEXTURE t,CMolPosition2d<int> p,CMolDimension2d<int> ss,int dm):speed(s),tex(t),pos(p),size(ss),disposalMethod(dm) {}

		int speed;               // 动画播放的延迟时间
		HTEXTURE tex;            // 动画播放的纹理
		CMolPosition2d<int> pos; // 开始显示位置
		CMolDimension2d<int> size; // 显示高宽
		int disposalMethod;       // 动画处理方式
	};

	/// 构造函数
	CMolGUIImage();
	/// 带参数的构造函数
	CMolGUIImage(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIImage();

	/// 设置图片地址
	void SetImagePath(std::string path);
	/// 得到图片地址
	inline std::string GetImagePath(void) { return m_imgPath; }
	/// 设置图片的显示位置
	inline void SetSrcStartPos(int x,int y)
	{
		pSrcStartX = x;
		pSrcStartY = y;
	}
	/// 得到图片的显示位置
	inline void GetSrcStartPos(int *x,int *y)
	{
		*x = pSrcStartX;
		*y = pSrcStartY;
	}
	/// 设置图片的显示高宽
	inline void SetSrcHeightAndWidth(int w,int h)
	{
		pSrcWidth = w;
		pSrcHeight = h;	
	}
	/// 得到图片的显示高宽
	inline void GetSrcHeightAndWidth(int *w,int *h)
	{
		*w = pSrcWidth;
		*h = pSrcHeight;
	}
	/// 设置图片的颜色
	inline void SetColor(CMolColor col) { m_Color = col; }
	/// 得到图片的颜色
	inline CMolColor GetColor(void) { return m_Color;}
	/// 锁住下载操作
	inline void LockImageDownload(void) { m_imgDownloadMutex.Acquire(); }
	/// 解锁下载操作
	inline void UnlockImageDownload(void) { m_imgDownloadMutex.Release(); }
	/// 打开指定的图片
	bool LoadImageFromFile(std::string filepath);
	/// 设置图片的显示角度
	inline void SetAngle(int angle) { m_angle = angle; }
	/// 得到图片的显示角度
	inline int GetAngle(void) { return m_angle; }

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// 游戏更新函数
	static unsigned __stdcall ThreadImageDownload(void * pParam);
	/// 关闭图片下载线程
	void CloseImageDownloadThread(void);
	/// 清除所有的动画纹理
	void ClearAllTextures(void);

private:
	int pSrcStartX,pSrcStartY,pSrcWidth,pSrcHeight;
	CMolColor m_Color;
	std::string m_imgPath;

	HANDLE                     m_imgDownloadThread;                  /**< 图片下载线程 */                    
	unsigned                   m_imgDownloadThreadID;                /**< 图片下载线程ID */    
	Mutex                      m_imgDownloadMutex;                   /**< 用于图片下载 */

	CGif89a                    m_Gif89a;                             /**< 用于导入gif动画 */
	CMolDimension2d<int>       m_animSize;                           /**< gif动画的高宽 */
	std::vector<GifAnimStr>    m_GifTexList;                         /**< gif纹理列表 */
	int                        m_CurFrameIndex;                      /**< 当前动画显示帧索引 */
	bool                       m_isRendering;                        /**< 是否渲染动画 */
	int                        m_DisMode;                            /**< 1 - 表示显示图片；2 - 表示显示gif动画 */
	DWORD                      m_CurTime;                            /**< 用于控制动画的播放 */
	int                        m_angle;                              /**< 要旋转的图片的角度 */
	//Mutex                      m_imgDisplayMutex;                    /**< 用于图片显示 */
};

//}
//}

#endif
