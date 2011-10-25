#ifndef _MOLE2D_GUI_CHAT_MESSAGE_H_
#define _MOLE2D_GUI_CHAT_MESSAGE_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

#include "Mole2dGUIScrollBar.h"

#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIChatMessage : public CMolBaseGUIElement
	{
	public:
		/** 
		 * �ı����нṹ
		 */
		struct RowStruct
		{
			RowStruct()
				: color(CMolColor(255,0,0,0))
			{
			}
			RowStruct(std::string t,CMolColor col=CMolColor(255,0,0,0))
				: color(col),text(t)
			{
			}

			CMolColor color;            // ����������ʾ����ɫ
			std::string text;           // ����������ʾ���ı�
		};

		/// ���캯��
		CMolGUIChatMessage();
		/// �������Ĺ��캯��
		CMolGUIChatMessage(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// �����ı���ʾ��ɫ
		inline void SetTextColor(CMolColor col) { m_TextColor = col; }
		/// �õ��ı���ʾ��ɫ
		inline CMolColor GetTextColor(void) { return m_TextColor; }
		/// ����ѡ���ı�����ʾ����ɫ
		inline void SetSelectTextColor(CMolColor col) { m_SelectTextColor = col; }
		/// �õ�ѡ���ı�����ʾ����ɫ
		inline CMolColor GetSelectTextColor(void) { return m_SelectTextColor; }
		/// �õ�������
		CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// ����������
		void CreateScrollBar(void);
		/// ����ַ�����������Ϣ��ʾ����
		void AddString(std::string text);
		/// ȡ��ָ��ָ���������ַ���
		std::string GetStringByIndex(int index);
		/// �õ���ǰѡ����ַ���
		std::string GetSelectString(void);
		/// ���ù������Ŀ��
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// �õ��������Ŀ��
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// �õ���ǰ�ؼ�������ʾ�������ַ�
		int GetDisplayLineCount(void);
		/// �������õ�ǰ�ؼ�״̬
		void Reset(void);

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolColor m_TextColor;                          /**< ������ʾ��ɫ */
		CMolColor m_SelectTextColor;                    /**< ѡ���ı������ɫ */

		std::vector<RowStruct> m_Rows;                /**< �ؼ���ʾ���ı� */
		int m_curRowIndex;                            /**< ��ǰ��ʾ������ */
		int m_scrollbarWidth;                         /**< �������Ŀ�� */
		int m_curMouseRowIndex;                         /**< ��ǰ������������� */

		CMolGUIScrollBar *m_ScrollBar;                  /**< ������Ϣ��Ĺ����� */
	};

	//}
//}

#endif
