#ifndef _ANIMATOR_RESOURCE_H_INCLUDE_
#define _ANIMATOR_RESOURCE_H_INCLUDE_

#include "Mole2dCommon.h"
#include "Mole2dDimension2d.h"
#include "Mole2dRect.h"
#include "Mole2dPosition2d.h"
#include "Mole2dColor.h"
#include "Mole2dEventReceiver.h"

#include <string>
#include <vector>
#include <map>
#include <list>

class CMolBaseFrame;

/** 
 * 动画帧结构
 */
struct AnimFrameStru
{
	AnimFrameStru()
		: offsetX(0),offsetY(0),isDisplay(false),tex(0)
	{
	}
	AnimFrameStru(std::string fn,int ox,int oy,bool isdis,HTEXTURE t)
		: filename(fn),offsetX(ox),offsetY(oy),isDisplay(isdis),tex(t)
	{
	}

	std::string filename;                           // 文件完整名称
	int offsetX,offsetY;                            // 这帧图像的偏移位置
	bool isDisplay;                                 // 是否要显示这帧图像
	HTEXTURE tex;                                   // 帧纹理索引
};

class CMolAnimatorResource
{
public:
	/// 构造函数
	CMolAnimatorResource(CMolBaseFrame* driver);
	/// 析构函数
	~CMolAnimatorResource();

	/// 导入动画文件 
	bool LoadFile(std::string path);

	/// 得到动画名称
	inline std::string GetAnimatorName(void) { return m_AnimatorName; }
	/// 得到动画帧数
	inline int GetFrameCount(void) { return m_AnimFrameCount; }
	/// 得到动画播放速度
	inline int GetSpeed(void) { return m_Speed; }
	/// 得到动画高宽
	inline CMolDimension2d<s32> GetSize(void) { return m_AnimSize; }
	/// 得到指定索引的帧
	AnimFrameStru* GetFrame(int index);

private:
	CMolBaseFrame *m_Driver;                         /**< 画图设备 */
	std::vector<AnimFrameStru> m_FrameList;           /**< 帧列表 */

	std::string m_AnimatorName;                      /**< 动画名称 */
	CMolDimension2d<s32> m_AnimSize;                  /**< 动画高宽 */
	int m_AnimFrameCount;                             /**< 动画帧数 */
	int m_Speed;                                      /**< 动画播放速度 */
};

class MOLEXPORT CMolAnimatorNode
{
public:
	/// 构造函数
	CMolAnimatorNode(CMolBaseFrame* driver);
	/// 析构函数
	~CMolAnimatorNode();

	/// 设置动画结点所使用到的动画资源
	inline void SetResource(CMolAnimatorResource *res) { m_AnimatorResource = res; }
	/// 得到动画结点所使用到的动画资源
	inline CMolAnimatorResource* GetResource(void) { return m_AnimatorResource; }
	/// 设置动画名称
	inline void SetName(std::string name) { m_Name = name; }
	/// 得到动画名称
	inline std::string GetName(void) { return m_Name; }
	/// 设置当前动画结点所在的世界范围
	inline void SetWorldRect(CMolRect<int> rect) { m_worldRect = rect; }
	/// 得到当前动画结点所在的世界范围
	inline CMolRect<int> GetWorldRect(void) { return m_worldRect; }
	/// 设置动画结点所在世界的坐标
	inline void SetPosition(CMolPosition2d<int> pos) { m_worldPosition = pos; }
	/// 得到动画结点所在世界的坐标
	inline CMolPosition2d<int> GetPosition(void) { return m_worldPosition; }
	/// 设置动画显示的偏移位置
	inline void SetOffset(CMolDimension2d<int> pos) { m_offsetPosition = pos; }
	/// 得到动画显示的偏移位置
	inline CMolDimension2d<int> GetOffset(void) { return m_offsetPosition; }
	/// 设置是否循环播放动画
	inline void SetLoop(bool loop) { m_isLoop = loop; }
	/// 得到是否循环播放动画
	inline bool IsLoop(void) { return m_isLoop; }
	/// 设置是否显示
	inline void SetVisible(bool visible) { m_IsVisible = visible; }
	/// 得到是否显示
	inline bool isVisible() const { return m_IsVisible; }
	/// 设置动画显示的颜色
	inline void SetColor(CMolColor col) { m_AnimColor = col; }
	/// 得到动画显示的颜色
	inline CMolColor GetColor(void) { return m_AnimColor; }
	/// 检测是否可见
	bool isLookat(void);
	/// 设置是否播放动画
	inline void Play(void) { m_isPlay = true; }
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

	bool operator < (const CMolAnimatorNode node)
	{
		return m_worldPosition.Y < node.m_worldPosition.Y;
	}

	/// 画控件
	virtual void Draw();
	/// 处理画之前更新
	virtual bool OnProcessPostUpdate();
	/// 用于处理接收到的事件
	virtual bool OnProcessEvent(const CMolEvent& event);

	CMolPosition2d<int> m_worldPosition;              /**< 动画所在的世界坐标 */

private:
	CMolBaseFrame *m_Driver;                         /**< 画图设备 */
	CMolAnimatorResource *m_AnimatorResource;             /**< 动画所使用的动画资源 */
	std::string m_Name;                              /**< 动画名称 */
	DWORD m_CurTime;                                  /**< 用于控制动画的播放 */
	int m_CurFrameIndex;                              /**< 当前动画显示帧索引 */
	bool m_isPlay;                                    /**< 是否播放动画 */
	bool m_isLoop;                                    /**< 是否循环播放动画 */
	bool m_IsVisible;                                 /**< 是否要显示动画 */
	bool m_isHover;                                   /**< 动画是否处于悬停状态 */

	CMolColor m_AnimColor;                            /**< 动画所使用的颜色 */
	CMolRect<int> m_worldRect;                        /**< 当前世界的范围 */
	CMolDimension2d<int> m_offsetPosition;            /**< 动画显示的偏移位置 */
};

class MOLEXPORT CMolAnimatorManager
{
public:
	/// 初始的构造函数
	CMolAnimatorManager();
	/// 构造函数
	CMolAnimatorManager(CMolBaseFrame* driver);
	/// 析构函数
	~CMolAnimatorManager();

	/// 添加一个动画在系统中
	CMolAnimatorNode* AddAnimator(std::string name,std::string respath,bool isPlay=true,bool isLoop=true);	
	/// 根据动画名称得到动画结点
	CMolAnimatorNode* GetAnimator(std::string name);
	/// 根据名称得到指定的资源
	CMolAnimatorResource* GetResource(std::string name);
	/// 设置画图设备
	inline void SetDriver(CMolBaseFrame *driver) { m_Driver = driver; }
	/// 得到画图设备
	inline CMolBaseFrame* GetDriver(void) { return m_Driver; }
	/// 设置是否对所有动画进行排序
	inline void SetSort(bool sort) { m_isSorting = sort; }
	/// 得到是否对所有动画进行排序
	inline int IsSort(void) { return m_isSorting; }
	/// 设置当前动画结点所在的世界范围
	void SetWorldRect(CMolRect<int> rect);
	/// 得到当前动画结点所在的世界范围
	inline CMolRect<int> GetWorldRect(void) { return m_worldRect; }
	/// 设置指定动画的世界位置
	void SetAnimWorldPos(std::string name,CMolPosition2d<int> pos);
	/// 设置指定动画的世界范围
	void SetAnimWorldRect(std::string name,CMolRect<int> rect);

	/// 清空所有的动画资源
	void ClearAllResources(void);
	/// 清空所有的动画结点
	void ClearAllAnimators(void);

	/// 画控件
	void Draw();
	/// 处理画之前更新
	bool OnProcessPostUpdate();
	/// 用于处理接收到的事件
	bool OnProcessEvent(const CMolEvent& event);

private:
	CMolBaseFrame *m_Driver;                                       /**< 画图设备 */
	CMolRect<int> m_worldRect;                                      /**< 当前世界的范围 */
	bool m_isSorting;                                               /**< 是否对所有动画进行排序 */

	std::map<std::string,CMolAnimatorResource*> m_ResourceList;        /**< 资源列表 */
	std::map<std::string,CMolAnimatorNode*> m_AnimatorList;            /**< 动画列表 */
	std::list<CMolAnimatorNode*> m_DisAnimList;                         /**< 用于显示的动画列表 */
};

#endif
