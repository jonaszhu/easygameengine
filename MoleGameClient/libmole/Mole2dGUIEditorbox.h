#ifndef _MOLE2D_GUI_EDITOR_BOX_H_
#define _MOLE2D_GUI_EDITOR_BOX_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.4
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
	//namespace graphics
	//{

		class MOLEXPORT CMolGUIEditorBox : public CMolBaseGUIElement
		{
		public:
			/// ���캯��
			CMolGUIEditorBox();
			/// �������Ĺ��캯��
			CMolGUIEditorBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);

			/// ����Ҫ��ʾ������
			void SetText(std::string t);
			/// �õ�Ҫ��ʾ������
			inline std::string GetText(void)
			{
				return m_Text;
			}
			/// ����Ҫ��ʾ������
			inline void SetTipText(std::string text) { m_TipText = text; }
			/// �õ�Ҫ��ʾ������
			inline std::string GetTipText(void) { return m_TipText; }
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
			/// �������ֵ�������
			inline void SetMaxCount(int max)
			{
				m_maxcount = max;
			}
			/// �õ����ֵ�������
			inline int GetMaxCount(void)
			{
				return m_maxcount;
			}
			/// �����Ƿ�Ϊ�����
			inline void SetIsPassword(bool password) { m_isPassword = password; }
			/// �õ��Ƿ�Ϊ�����
			inline bool IsPassword(void) { return m_isPassword; }

			/// ���ؼ�
			virtual void Draw();
			/// ���ڴ�����յ����¼�
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// ����ʧ������¼�
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);
			/// ���õ�ǰ�ؼ��Ƿ�õ�����
			virtual void SetFocus(bool focus);

		protected:
			/// ���ڴ���IME��Ϣ
			bool processIme(const CMolEvent& event);
			/// ���ڴ��������Ϣ
			bool processMouse(const CMolEvent& event);
			/// ���ڴ�������Ϣ
			bool processKey(const CMolEvent& event);
			/// ���һ���µ��ı����༭����
			void inputString(std::string str);
			/// ���㵱ǰ�Ĺ�������
			int calculateScrollPos();
			/// ���㵱ǰ�����ʾ����
			void calculateCursorPos(void);
			/// �ж�ָ���ַ��Ƿ�Ϊ����
			bool IsChinese(char c);
			/// �õ���ָ��λ�ÿ�ʼָ�����ȵ��ַ���
			std::string GetSubString(int startpos,int length);
			/// ��ָ��λ����ʾ�������
			void DisplayInputSymbol(CMolPosition2d<s32> pos);
			/// �õ�ָ��λ�õ���ʵλ��
			int GetRealPosWith(int pos);
			/// �����ַ�����ʵλ�õõ��ַ����ַ����е�����
			int GetIndexWidth(int pos);
			/// �õ���ǰ�ж��ٸ��ַ�
			int GetCharCount(void);
			/// �õ�ָ���ַ����ж��ٸ��ַ�
			int GetCharCountFromString(std::string str);
			/// �õ���ǰҳ����ʾ���ٸ��ַ�
			int GetChrCountPage(bool isstart=true);

		private:
			std::string m_Text;                             /**< Ҫ��ʾ������ */
			std::string m_TipText;                          /**< ��ʾ������ */
			CMolColor m_Color;                              /**< ������ʾ����ɫ */
			int m_startpos;                                 /**< ���ֵ��ַ���ʼλ�� */
			int m_startIndex;                               /**< �������ַ����е����� */
			int m_cursorStringIndex;                        /**< ����������е����� */
			int m_cursorpos;                                /**< ���λ�� */
			int m_maxcount;                                 /**< �������ֵ������� */

			std::string m_TempStr;                          /**< �û��ո�������ַ��� */
			MOLIME_EVENT_TYPE m_TempType;                   /**< ���ڸո������ַ����ķ�ʽ */
			bool m_isPassword;                              /**< �Ƿ�������� */

			DWORD m_curTime,m_TimeSpace;                    /**< ���ڿ���������ŵ���ʾ */
			CMolPosition2d<s32> m_inputpos;                 /**< ������ŵ���ʾλ�� */
		};

	//}
//}

#endif
