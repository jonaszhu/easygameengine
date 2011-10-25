#ifndef _MOLE2D_GUI_MOVE_ANIMATOR_H_
#define _MOLE2D_GUI_MOVE_ANIMATOR_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2010.9.2 路径动画控件
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dGUIImage.h"

#define IDD_BERNSTEIN_COUNT 1000                   // 贝塞儿曲线点个数
#define IDD_CONTROL_POINT_COUNT 4                  // 控制点个数
#define IDD_CONTROL_RECT_WIDTH 5                   // 控制块宽度

//namespace mole2d
//{
////namespace graphics
////{

class MOLEXPORT CMolGUIMoveAnimator : public CMolBaseGUIElement
{
public:
	/// 构造函数
	CMolGUIMoveAnimator();
	/// 带参数的构造函数
	CMolGUIMoveAnimator(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIMoveAnimator();

	/// 设置贝塞儿曲线控制点
	void SetControlPoint(CMolPosition2d<int> point,int index);
	/// 得到贝塞儿曲线控制点
	CMolPosition2d<int> GetControlPoint(int index);
	/// 得到贝塞儿曲线
	void GetBernstern(void);
	/// 设置动画开始点
	void SetStartPosition(CMolPosition2d<int> point);
	/// 得到动画开始点
	inline CMolPosition2d<int> GetStartPosition(void) { return m_contrlpoints[3]; }
	/// 设置动画结束点
	void SetEndPosition(CMolPosition2d<int> point);
	/// 得到动画结束点
	inline CMolPosition2d<int> GetEndPosition(void) { return m_contrlpoints[0]; }
	/// 设置是否可以编辑
	inline void setIsEdit(bool edit) { m_IsEditMode = edit; }
	/// 得到是否可以编辑 
	inline bool isEdit(void) { return m_IsEditMode; }
	/// 加载动画图片
	void LoadAnimImage(std::string imgpath);
	/// 设置是否播放动画
	inline void Play(void) { m_isPlaying = true; }
	/// 检测动画是否播放
	inline bool isPlaying(void) { return m_isPlaying; }
	/// 暂停播放动画
	inline void Pause(void) { m_isPlaying = false; }
	/// 停止播放动画
	inline void Stop(void) { m_isPlaying = false; m_curFrame = 0; }
	/// 重新开始播放动画
	inline void Restart(void) { m_curFrame = 0; m_isPlaying = true; }
	/// 设置动画播放速度
	inline void SetSpeed(float s) { m_Speed = s; }
	/// 得到动画播放速度
	inline float GetSpeed(void) { return m_Speed; }
	/// 设置动画播放帧
	void SetPlayFrame(int frame);
	/// 得到当前动画播放帧
	inline int GetCurPlayFrame(void) { return m_curFrame; }

	/// 画控件
	virtual void Draw();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// 处理丢失焦点的事件
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// 根据4个控制点得到新的贝塞儿坐标点
	CMolPosition2d<int> Bernstein(float u, CMolPosition2d<int> *p);
	/// 根据4个控制点得到贝塞儿曲线
	void GetBernsternByControlPoint(CMolPosition2d<int> *p);
	/// 更新动画
	bool UpdateAnimator(void);

private:
	CMolPosition2d<int> m_points[IDD_BERNSTEIN_COUNT];                        /**< 用于存储贝塞儿曲线点 */ 
	CMolPosition2d<int> m_contrlpoints[IDD_CONTROL_POINT_COUNT];              /**< 用于存储4个控制点 */
	CMolRect<int> m_contrlRect[IDD_CONTROL_POINT_COUNT];                      /**< 四个控制滑块，用于编辑4个控制点 */

	CMolGUIImage *m_animImage;                                                /**< 动画图片 */
	CMolDimension2d<int> m_animImgSize;                                       /**< 动画图片高宽 */

	int m_curFrame;                                                           /**< 当前播放动画帧 */
	bool m_isPlaying;                                                         /**< 是否在播放动画 */
	float m_Speed;                                                              /**< 动画播放速度 */

	int  m_curSelectRect;                                                     /**< 当前选中的控制滑块索引 */
	bool m_IsEditMode;                                                        /**< 是否处于编辑模式，如果处于编辑模式下，可以修改曲线 */
};

//}
//}

#endif
