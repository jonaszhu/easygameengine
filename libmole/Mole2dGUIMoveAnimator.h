#ifndef _MOLE2D_GUI_MOVE_ANIMATOR_H_
#define _MOLE2D_GUI_MOVE_ANIMATOR_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.9.2 ·�������ؼ�
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dGUIImage.h"

#define IDD_BERNSTEIN_COUNT 1000                   // ���������ߵ����
#define IDD_CONTROL_POINT_COUNT 4                  // ���Ƶ����
#define IDD_CONTROL_RECT_WIDTH 5                   // ���ƿ���

//namespace mole2d
//{
////namespace graphics
////{

class MOLEXPORT CMolGUIMoveAnimator : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIMoveAnimator();
	/// �������Ĺ��캯��
	CMolGUIMoveAnimator(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIMoveAnimator();

	/// ���ñ��������߿��Ƶ�
	void SetControlPoint(CMolPosition2d<int> point,int index);
	/// �õ����������߿��Ƶ�
	CMolPosition2d<int> GetControlPoint(int index);
	/// �õ�����������
	void GetBernstern(void);
	/// ���ö�����ʼ��
	void SetStartPosition(CMolPosition2d<int> point);
	/// �õ�������ʼ��
	inline CMolPosition2d<int> GetStartPosition(void) { return m_contrlpoints[3]; }
	/// ���ö���������
	void SetEndPosition(CMolPosition2d<int> point);
	/// �õ�����������
	inline CMolPosition2d<int> GetEndPosition(void) { return m_contrlpoints[0]; }
	/// �����Ƿ���Ա༭
	inline void setIsEdit(bool edit) { m_IsEditMode = edit; }
	/// �õ��Ƿ���Ա༭ 
	inline bool isEdit(void) { return m_IsEditMode; }
	/// ���ض���ͼƬ
	void LoadAnimImage(std::string imgpath);
	/// �����Ƿ񲥷Ŷ���
	inline void Play(void) { m_isPlaying = true; }
	/// ��⶯���Ƿ񲥷�
	inline bool isPlaying(void) { return m_isPlaying; }
	/// ��ͣ���Ŷ���
	inline void Pause(void) { m_isPlaying = false; }
	/// ֹͣ���Ŷ���
	inline void Stop(void) { m_isPlaying = false; m_curFrame = 0; }
	/// ���¿�ʼ���Ŷ���
	inline void Restart(void) { m_curFrame = 0; m_isPlaying = true; }
	/// ���ö��������ٶ�
	inline void SetSpeed(float s) { m_Speed = s; }
	/// �õ����������ٶ�
	inline float GetSpeed(void) { return m_Speed; }
	/// ���ö�������֡
	void SetPlayFrame(int frame);
	/// �õ���ǰ��������֡
	inline int GetCurPlayFrame(void) { return m_curFrame; }

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// ����4�����Ƶ�õ��µı����������
	CMolPosition2d<int> Bernstein(float u, CMolPosition2d<int> *p);
	/// ����4�����Ƶ�õ�����������
	void GetBernsternByControlPoint(CMolPosition2d<int> *p);
	/// ���¶���
	bool UpdateAnimator(void);

private:
	CMolPosition2d<int> m_points[IDD_BERNSTEIN_COUNT];                        /**< ���ڴ洢���������ߵ� */ 
	CMolPosition2d<int> m_contrlpoints[IDD_CONTROL_POINT_COUNT];              /**< ���ڴ洢4�����Ƶ� */
	CMolRect<int> m_contrlRect[IDD_CONTROL_POINT_COUNT];                      /**< �ĸ����ƻ��飬���ڱ༭4�����Ƶ� */

	CMolGUIImage *m_animImage;                                                /**< ����ͼƬ */
	CMolDimension2d<int> m_animImgSize;                                       /**< ����ͼƬ�߿� */

	int m_curFrame;                                                           /**< ��ǰ���Ŷ���֡ */
	bool m_isPlaying;                                                         /**< �Ƿ��ڲ��Ŷ��� */
	float m_Speed;                                                              /**< ���������ٶ� */

	int  m_curSelectRect;                                                     /**< ��ǰѡ�еĿ��ƻ������� */
	bool m_IsEditMode;                                                        /**< �Ƿ��ڱ༭ģʽ��������ڱ༭ģʽ�£������޸����� */
};

//}
//}

#endif
