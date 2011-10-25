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
 * ����֡�ṹ
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

	std::string filename;                           // �ļ���������
	int offsetX,offsetY;                            // ��֡ͼ���ƫ��λ��
	bool isDisplay;                                 // �Ƿ�Ҫ��ʾ��֡ͼ��
	HTEXTURE tex;                                   // ֡��������
};

class CMolAnimatorResource
{
public:
	/// ���캯��
	CMolAnimatorResource(CMolBaseFrame* driver);
	/// ��������
	~CMolAnimatorResource();

	/// ���붯���ļ� 
	bool LoadFile(std::string path);

	/// �õ���������
	inline std::string GetAnimatorName(void) { return m_AnimatorName; }
	/// �õ�����֡��
	inline int GetFrameCount(void) { return m_AnimFrameCount; }
	/// �õ����������ٶ�
	inline int GetSpeed(void) { return m_Speed; }
	/// �õ������߿�
	inline CMolDimension2d<s32> GetSize(void) { return m_AnimSize; }
	/// �õ�ָ��������֡
	AnimFrameStru* GetFrame(int index);

private:
	CMolBaseFrame *m_Driver;                         /**< ��ͼ�豸 */
	std::vector<AnimFrameStru> m_FrameList;           /**< ֡�б� */

	std::string m_AnimatorName;                      /**< �������� */
	CMolDimension2d<s32> m_AnimSize;                  /**< �����߿� */
	int m_AnimFrameCount;                             /**< ����֡�� */
	int m_Speed;                                      /**< ���������ٶ� */
};

class MOLEXPORT CMolAnimatorNode
{
public:
	/// ���캯��
	CMolAnimatorNode(CMolBaseFrame* driver);
	/// ��������
	~CMolAnimatorNode();

	/// ���ö��������ʹ�õ��Ķ�����Դ
	inline void SetResource(CMolAnimatorResource *res) { m_AnimatorResource = res; }
	/// �õ����������ʹ�õ��Ķ�����Դ
	inline CMolAnimatorResource* GetResource(void) { return m_AnimatorResource; }
	/// ���ö�������
	inline void SetName(std::string name) { m_Name = name; }
	/// �õ���������
	inline std::string GetName(void) { return m_Name; }
	/// ���õ�ǰ����������ڵ����緶Χ
	inline void SetWorldRect(CMolRect<int> rect) { m_worldRect = rect; }
	/// �õ���ǰ����������ڵ����緶Χ
	inline CMolRect<int> GetWorldRect(void) { return m_worldRect; }
	/// ���ö�������������������
	inline void SetPosition(CMolPosition2d<int> pos) { m_worldPosition = pos; }
	/// �õ���������������������
	inline CMolPosition2d<int> GetPosition(void) { return m_worldPosition; }
	/// ���ö�����ʾ��ƫ��λ��
	inline void SetOffset(CMolDimension2d<int> pos) { m_offsetPosition = pos; }
	/// �õ�������ʾ��ƫ��λ��
	inline CMolDimension2d<int> GetOffset(void) { return m_offsetPosition; }
	/// �����Ƿ�ѭ�����Ŷ���
	inline void SetLoop(bool loop) { m_isLoop = loop; }
	/// �õ��Ƿ�ѭ�����Ŷ���
	inline bool IsLoop(void) { return m_isLoop; }
	/// �����Ƿ���ʾ
	inline void SetVisible(bool visible) { m_IsVisible = visible; }
	/// �õ��Ƿ���ʾ
	inline bool isVisible() const { return m_IsVisible; }
	/// ���ö�����ʾ����ɫ
	inline void SetColor(CMolColor col) { m_AnimColor = col; }
	/// �õ�������ʾ����ɫ
	inline CMolColor GetColor(void) { return m_AnimColor; }
	/// ����Ƿ�ɼ�
	bool isLookat(void);
	/// �����Ƿ񲥷Ŷ���
	inline void Play(void) { m_isPlay = true; }
	/// ֹͣ���Ŷ���
	inline void Stop(void) 
	{ 
		m_isPlay = false; 
		m_CurFrameIndex = 0; 
		m_CurTime = 0;
	}
	/// ��ͣ���Ŷ���
	inline void Pause(void) { m_isPlay = false; }
	/// ���²��Ŷ���
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

	/// ���ؼ�
	virtual void Draw();
	/// ����֮ǰ����
	virtual bool OnProcessPostUpdate();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);

	CMolPosition2d<int> m_worldPosition;              /**< �������ڵ��������� */

private:
	CMolBaseFrame *m_Driver;                         /**< ��ͼ�豸 */
	CMolAnimatorResource *m_AnimatorResource;             /**< ������ʹ�õĶ�����Դ */
	std::string m_Name;                              /**< �������� */
	DWORD m_CurTime;                                  /**< ���ڿ��ƶ����Ĳ��� */
	int m_CurFrameIndex;                              /**< ��ǰ������ʾ֡���� */
	bool m_isPlay;                                    /**< �Ƿ񲥷Ŷ��� */
	bool m_isLoop;                                    /**< �Ƿ�ѭ�����Ŷ��� */
	bool m_IsVisible;                                 /**< �Ƿ�Ҫ��ʾ���� */
	bool m_isHover;                                   /**< �����Ƿ�����ͣ״̬ */

	CMolColor m_AnimColor;                            /**< ������ʹ�õ���ɫ */
	CMolRect<int> m_worldRect;                        /**< ��ǰ����ķ�Χ */
	CMolDimension2d<int> m_offsetPosition;            /**< ������ʾ��ƫ��λ�� */
};

class MOLEXPORT CMolAnimatorManager
{
public:
	/// ��ʼ�Ĺ��캯��
	CMolAnimatorManager();
	/// ���캯��
	CMolAnimatorManager(CMolBaseFrame* driver);
	/// ��������
	~CMolAnimatorManager();

	/// ���һ��������ϵͳ��
	CMolAnimatorNode* AddAnimator(std::string name,std::string respath,bool isPlay=true,bool isLoop=true);	
	/// ���ݶ������Ƶõ��������
	CMolAnimatorNode* GetAnimator(std::string name);
	/// �������Ƶõ�ָ������Դ
	CMolAnimatorResource* GetResource(std::string name);
	/// ���û�ͼ�豸
	inline void SetDriver(CMolBaseFrame *driver) { m_Driver = driver; }
	/// �õ���ͼ�豸
	inline CMolBaseFrame* GetDriver(void) { return m_Driver; }
	/// �����Ƿ�����ж�����������
	inline void SetSort(bool sort) { m_isSorting = sort; }
	/// �õ��Ƿ�����ж�����������
	inline int IsSort(void) { return m_isSorting; }
	/// ���õ�ǰ����������ڵ����緶Χ
	void SetWorldRect(CMolRect<int> rect);
	/// �õ���ǰ����������ڵ����緶Χ
	inline CMolRect<int> GetWorldRect(void) { return m_worldRect; }
	/// ����ָ������������λ��
	void SetAnimWorldPos(std::string name,CMolPosition2d<int> pos);
	/// ����ָ�����������緶Χ
	void SetAnimWorldRect(std::string name,CMolRect<int> rect);

	/// ������еĶ�����Դ
	void ClearAllResources(void);
	/// ������еĶ������
	void ClearAllAnimators(void);

	/// ���ؼ�
	void Draw();
	/// ����֮ǰ����
	bool OnProcessPostUpdate();
	/// ���ڴ�����յ����¼�
	bool OnProcessEvent(const CMolEvent& event);

private:
	CMolBaseFrame *m_Driver;                                       /**< ��ͼ�豸 */
	CMolRect<int> m_worldRect;                                      /**< ��ǰ����ķ�Χ */
	bool m_isSorting;                                               /**< �Ƿ�����ж����������� */

	std::map<std::string,CMolAnimatorResource*> m_ResourceList;        /**< ��Դ�б� */
	std::map<std::string,CMolAnimatorNode*> m_AnimatorList;            /**< �����б� */
	std::list<CMolAnimatorNode*> m_DisAnimList;                         /**< ������ʾ�Ķ����б� */
};

#endif
