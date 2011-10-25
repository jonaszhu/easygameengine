#ifndef _MOLE2D_GUI_VIDEO_H_INCLUDE
#define _MOLE2D_GUI_VIDEO_H_INCLUDE

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.5.3
*/

#include "Mole2dBaseGUIElement.h"

//#include "libvideo/TheoraPlayer.h"
//#include "libvideo/TheoraDataSource.h"


//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIVideo : public CMolBaseGUIElement
	{
	public:
		/// 构造函数
		CMolGUIVideo();
		/// 带参数的构造函数
		CMolGUIVideo(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);
		/// 析构函数
		virtual ~CMolGUIVideo();

		///// 设置视频的路径
		//void LoadVideo(std::string path,bool isPlay=false);
		///// 得到视频的路径
		//inline std::string GetVideoPath(void) { return m_videpath; }
		///// 播放视频
		//void Play();
		///// 暂停视频播放
		//void Pause();
		///// 停止视频播放
		//void Stop();
		///// 重新开始播放视频
		//void Restart();

		/// 画控件
		virtual void Draw();
		/// 处理画之前更新
		virtual bool OnProcessPostUpdate();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		//HTEXTURE m_FrameTex;                  /**< 帧纹理 */
		//std::string m_videpath;

		//TheoraVideoClip* clip;                  /**< 视频剪辑 */
		//TheoraMemoryFileDataSource *mTheoraDataSource;     /**< 用于存储视频数据 */
	};

	//}
//}

#endif
