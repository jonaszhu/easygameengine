#ifndef _MOLE2D_GUI_TEXTAREA_H_
#define _MOLE2D_GUI_TEXTAREA_H_

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

#define IDD_ITEM_SPACE 2

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUITextarea : public CMolBaseGUIElement
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
			RowStruct(CMolColor col,std::string t)
				: color(col),text(t)
			{
			}

			CMolColor color;            // ����������ʾ����ɫ
			std::string text;           // ����������ʾ���ı�
		};

		/// ���캯��
		CMolGUITextarea();
		/// �������Ĺ��캯��
		CMolGUITextarea(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// ����ָ���ı��ļ�
		void LoadStringFromFile(std::string path);
		/// ����ַ������ؼ���
		void AddString(std::string text,CMolColor col=CMolColor(255,0,0,0),bool isEnd=true);
		/// �����Ƿ�ʹ�ù�����
		void SetUseScrollBar(bool isuse);
		/// �õ���ȡ���ļ��ļ�·��
		inline std::string GetReadFilePath(void) { return m_readfilepath; }
		/// �õ��Ƿ�ʹ�ù�����
		inline bool IsUseScrollBar(void) { return m_IsUseScrollbar; }
		/// ���ù������Ŀ��
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// �õ��������Ŀ��
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// �õ�������
		inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// �õ���ǰ�ؼ�������ʾ�������ַ�
		int GetDisplayLineCount(void);
		/// ������е�����
		void Clear(void);

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// �õ�ָ��λ�õ���ʵλ��
		int GetRealPosWith(std::string text,int pos);
		/// �ж�ָ���ַ��Ƿ�Ϊ����
		bool IsChinese(char c);
		/// �õ���ǰ�ж��ٸ��ַ�
		int GetCharCount(std::string text);
		/// �õ���ָ��λ�ÿ�ʼָ�����ȵ��ַ���
		std::string GetSubString(std::string text,int startpos,int length);

	private:
		std::vector<RowStruct> m_Rows;                /**< �ؼ���ʾ���ı� */
		int m_curRowIndex;                            /**< ��ǰ��ʾ������ */
		int m_scrollbarWidth;                         /**< �������Ŀ�� */
	    std::string m_readfilepath;                  /**< Ҫ��ȡ���ı��ļ���·�� */

		bool m_IsUseScrollbar;                        /**< �Ƿ�ʹ�ù����� */

		CMolGUIScrollBar *m_ScrollBar;                /**< �ı���ʾ��Ĺ����� */
	};

	//}
//}

#endif
