#ifndef _MOLE2D_GUI_DRAG_CONTROL_H_
#define _MOLE2D_GUI_DRAG_CONTROL_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.9.3 �϶�����ؼ�
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
//namespace graphics
//{

/** 
 * ������ṹ
 */
class DragScrollBar
{
public:
	/** 
	 * ��ť״̬
	 */
	enum ButtonState
	{
		STATE_NORMAL = 0,            // ����״̬
		STATE_DOWND,                 // ����״̬
		STATE_HOVERED,               // ��꾭��״̬
		STATE_DISABLED,              // ��ť������״̬
		STATE_NULL
	};

	/// ���캯��
	DragScrollBar();
	/// ��������
	~DragScrollBar();

	/// ���û��������ʾ��Χ
	inline void SetRect(CMolRect<s32> pRect) { rect = pRect; }
	/// �õ����������ʾ��Χ
	inline CMolRect<s32> GetRect(void) { return rect; }
	/// ���û�����ʹ�õ�����
	inline void SetTexture(HTEXTURE t) { tex = t; }
	/// �õ�������ʹ�õ�����
	inline HTEXTURE GetTexture(void) { return tex; }
	/// �õ���������ƶ����
	inline int GetMoveSpace(void) { return m_MoveSpace; }

	/// ��ʾ������
	void Draw(CMolBaseFrame* driver);
	/// ��������¼�
	void OnProcessMouse(const CMolEvent& event);
	/// ������궪ʧ���¼�
	void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	CMolRect<s32> rect;         // ������ķ�Χ
	HTEXTURE tex;               // �������ͼƬ
	ButtonState mButtonState;   // �������״̬

	int  m_MoveSpace;           /**< �������ƶ��ļ�� */
};

class MOLEXPORT CMolGUIDragControl : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIDragControl();
	/// �������Ĺ��캯��
	CMolGUIDragControl(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		int id,std::string caption,CMolRect<int> rect);
	virtual ~CMolGUIDragControl();

	/// ���ñ���ͼƬ1
	void SetBgImageOne(std::string imgpath);
	/// �õ�����ͼƬ1
	inline std::string GetBgImageOne(void) { return m_dragbgimgonepath; }
	/// ���ñ���ͼƬ2
	void SetBgImageTwo(std::string imgpath);
	/// �õ�����ͼƬ2
	inline std::string GetBgImageTwo(void) { return m_dragbgimgtwopath; }
	/// ���ñ���ͼƬ3
	void SetBgImageThree(std::string imgpath);
	/// �õ�����ͼƬ3
	inline std::string GetBgImageThree(void) { return m_dragbgimgthreepath; }
	/// ���û�����ʹ�õ�������
	void SetDragScrollBar(HTEXTURE tex);
	/// �õ���ǰ���������
	inline int GetCurrentProcess(void) { return m_curProcess; }
	/// ���õ�ǰ����������
	void SetCurrentProcess(int pro);

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// �ƶ��ؼ���ָ����λ��
	virtual void Move(CMolPosition2d<int> pos);

private:
	std::string m_dragbgimgonepath,m_dragbgimgtwopath,m_dragbgimgthreepath;       /**< �ؼ�ʹ�õ���ͼƬ��·�� */
	HTEXTURE m_dragbgimgone,m_dragbgimgtwo,m_dragbgimgthree;         /**< �ؼ���ʹ�õ��ı���ͼƬ */

	DragScrollBar m_DragScrollBar;                                                /**< �ؼ�ʹ�õ����϶��� */
	int m_curProcess;                                                             /**< ��ǰ�϶����� */
	bool m_isDragging;                                                            /**< �Ƿ����϶������� */
};

//}
//}

#endif
