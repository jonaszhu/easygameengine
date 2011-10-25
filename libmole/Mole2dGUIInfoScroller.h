#ifndef _MOLE2D_GUI_INFO_SCROLLER_H_
#define _MOLE2D_GUI_INFO_SCROLLER_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3 д��ƽ��,ͼ��ؼ�,������ʾ����ͼ���ͼ��һ����
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIInfoScroller : public CMolBaseGUIElement
	{
	public:
		/** 
		 * ��Ϣ�Ĺ�����ʽ
		 */
		enum InfoScrType
		{
			SCRTYPE_LEFT_TO_RIGHT = 0,            // ������
			SCRTYPE_RIGHT_TO_LEFT                 // ���ҵ���
		};

		/// ���캯��
		CMolGUIInfoScroller();
		/// �������Ĺ��캯��
		CMolGUIInfoScroller(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// ���û����ֵ�����
		inline void SetFont(CMolGUIBaseFont *font)
		{
			m_Font = font;
		}
		/// �õ������ֵ�����
		inline CMolGUIBaseFont* GetFont(void)
		{
			return m_Font;
		}
		/// �������ִ�С
		inline void SetSize(int s)
		{
			m_Size = s;
		}
		/// �õ����ִ�С
		inline int GetSize(void)
		{
			return m_Size;
		}
		/// ����Ҫ��ʾ������
		inline void SetText(std::string t)
		{
			m_Text = t;
		}
		/// �õ�Ҫ��ʾ������
		inline std::string GetText(void)
		{
			return m_Text;
		}
		/// ����������ʾ����ɫ
		inline void SetColor(CMolColor color)
		{
			m_Color = color;
		}
		/// �õ�������ʾ����ɫ
		inline CMolColor GetColor(void)
		{
			return m_Color;
		}
		/// ������Ϣ������ʽ
		inline void SetInfoScrType(CMolGUIInfoScroller::InfoScrType type) { m_InfoScrType = type; }
		/// �õ���Ϣ������ʽ
		inline CMolGUIInfoScroller::InfoScrType GetInfoScrType(void) { return m_InfoScrType; }

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolGUIBaseFont *m_Font;                        /**< Ҫ�����ֵ����� */
		int m_Size;                                     /**< ���ֵ���ʾ��С */
		std::string m_Text;                             /**< Ҫ��ʾ������ */
		CMolColor m_Color;                              /**< ������ʾ����ɫ */
		InfoScrType m_InfoScrType;                      /**< ��Ϣ�Ĺ������� */

		int m_StartPos,m_ctrlWidth;                     /**< ���ڿ��ƿؼ�����ʾ */
		CMolPosition2d<s32> m_ctlStartPos;              /**< �ؼ��Ŀ�ʼ��ʾλ�� */
		DWORD m_curTime;
	};

	//}
//}

#endif
