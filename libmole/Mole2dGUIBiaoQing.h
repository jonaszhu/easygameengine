#ifndef _MOLE2D_GUI_BIAOQING_H_
#define _MOLE2D_GUI_BIAOQING_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.8.13
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIGameAnimator.h"
#include "Mole2dGUIButton.h"
#include "Mole2dDimension2d.h"

#include <vector>

/// ����֮�����ʾ��� 
#define IDD_ANIMATOR_SPACE 5  

/// ѡ�����߶�
#define IDD_SELECT_PANELHEIGHT 20

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIBiqoQing : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIBiqoQing();
	/// �������Ĺ��캯��
	CMolGUIBiqoQing(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// ��������
	virtual ~CMolGUIBiqoQing();

	/// ����һҳ��ʾ���ٸ�����
	void SetPageSize(CMolDimension2d<s32> size);
	/// �õ�һҳ��ʾ���ٸ�����
	inline CMolDimension2d<s32> GetPageSize(void) { return m_PageSize; }
	/// ��ָ��·��������鶯��
	void LoadAnimators(std::string path);
	/// ������еı��鶯��
	void ClearAllAnimator(void);
	/// ��������ť
	void SetLeftButton(std::string btnImage);
	/// �õ�����ťͼƬ
	inline std::string GetLeftButton(void) { return m_LeftBtnImg; }
	/// �������Ұ�ť
	void SetRightButton(std::string btnImage);
	/// �õ����Ұ�ťͼƬ
	inline std::string GetRightButton(void) { return m_RightBtnImg; }
	/// �����������еĲ���
	void Reset(void);
	/// �õ�ѡ�к�Ķ�����������·��
	std::string GetSelectedPath(void);

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	/// ���ݵ�ǰ����ҳ����ʾ���鶯��
	void DrawBiaoQingAnim();
	/// �������еı��鶯��
	void HideAllBiaoQingAnims(void);
	/// ���������������ҵ�ǰѡ�б���
	void GetSelectBiaoQingByMouse(CMolPosition2d<s32> pos);
	/// ���ݵ�ǰ���ѡ�л�ѡ���
	void DrawSelectFrame(CMolBaseFrame* driver);

private:
	CMolDimension2d<s32> m_PageSize;                            /**< һҳ��ʾ���ٸ� */
	CMolDimension2d<s32> m_animSize;                        /**< ������ʾ�ĸ߿� */
	std::string m_animPath;                                 /**< ���鶯����·�� */

	int m_curPage;                                              /**< ��ǰ��ʾҳ */
	int m_curMouseIndex;                                        /**< ��ǰ��꾭���ı��� */
	int m_totalPage;                                            /**< �ܵ�ҳ���� */

	std::vector<CMolGUIGameAnimator*> m_AnimList;           /**< ���鶯���б� */
	CMolGUIButton *m_LeftBtn;                               /**< ����ť */
	std::string m_LeftBtnImg;                               /**< ����ťʹ�õ�ͼƬ */
	CMolGUIButton *m_RightBtn;                              /**< ���Ұ�ť */
	std::string m_RightBtnImg;                              /**< ���Ұ�ťʹ�õ�ͼƬ */
};

//}
//}

#endif
