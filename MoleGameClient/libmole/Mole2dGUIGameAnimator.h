#ifndef _MOLE2D_GUI_GAME_ANIMATOR_H_
#define _MOLE2D_GUI_GAME_ANIMATOR_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.2.3 写于平武,图像控件,用于显示整副图像或图像一部分
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dAnimator.h"

#include <string>
#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIGameAnimator : public CMolBaseGUIElement
	{
	public:
		/** 
		 * 动画帧结构
		 */
		struct GameFrame
		{
			GameFrame():isShow(true),tex(0) { }
			GameFrame(bool isDis,HTEXTURE t):isShow(isDis),tex(t) { }

			bool isShow;                    // 是否显示这帧
			HTEXTURE tex;                   // 这帧的纹理
		};

		/// 构造函数
		CMolGUIGameAnimator();
		/// 带参数的构造函数
		CMolGUIGameAnimator(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// 导入动画
		bool LoadAnimator(std::string path);
		/// 得到动画路径
		inline std::string GetAnimatorPath(void) { return m_AnimatorPath; }
		/// 得到动画的高宽
		inline CMolDimension2d<int> GetAnimSize(void) { return m_AnimSize; }
		/// 得到动画总的帧数
		inline int GetFrameCount(void) { return m_AnimFrameCount; }
		/// 得到动画的播放速度
		inline int GetSpeed(void) { return m_Speed; }
		/// 设置是否循环播放动画
		inline void SetLoop(bool loop) { m_isLoop = loop; }
		/// 得到是否循环播放动画
		inline bool IsLoop(void) { return m_isLoop; }
		/// 设置播放次数
		inline void SetLoopCount(int count) { m_loopCount = count; }
		/// 得到播放次数
		inline int GetLoopCount(void) { return m_loopCount; }
		/// 播放动画
		inline void Play(void) { m_isPlay = true; m_curPlayCount = 1; }
		/// 停止播放动画
		inline void Stop(void) 
		{ 
			m_isPlay = false; 
			m_CurFrameIndex = 0; 
			m_CurTime = 0;
		}
		/// 暂停播放动画
		inline void Pause(void) { m_isPlay = false; }
		/// 重新播放动画
		inline void Restart(void) 
		{ 
			m_CurFrameIndex = 0;
			m_CurTime = 0;
			m_isPlay = true; 
		}
		/// 得到当前动画播放状态
		inline bool isPlaying(void) { return m_isPlay; }
		/// 得到当前动画播放帧索引
		inline int GetCurrentFrame(void) { return m_CurFrameIndex; }
		/// 清空动画数据
		void Clear(void);

		/// 画控件
		virtual void Draw();
		/// 用于处理接收到的事件
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// 处理丢失焦点的事件
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolAnimator m_GameAnimator;                      /**< 用于读取动画数据 */
		std::string m_AnimatorPath;                       /**< 动画路径 */
		CMolDimension2d<s32> m_AnimSize;                  /**< 动画高宽 */
		int m_AnimFrameCount;                             /**< 动画帧数 */
		int m_Speed;                                      /**< 动画播放速度 */
		int m_CurFrameIndex;                            /**< 当前动画显示帧索引 */
		DWORD m_CurTime;                                /**< 用于控制动画的播放 */
		bool m_isPlay;                                    /**< 是否播放动画 */
		bool m_isLoop;                                    /**< 是否循环播放动画 */
		int m_loopCount;                                  /**< 循环次数 */
		int m_curPlayCount;                               /**< 当前播放次数 */

		std::vector<GameFrame> m_FrameList;                /**< 动画帧列表 */
	};

	//}
//}

#endif
