#ifndef _MOLE2D_GUI_SCROLL_BAR_H_
#define _MOLE2D_GUI_SCROLL_BAR_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.1
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

//namespace mole2d
//{
	//namespace graphics
	//{

		/** 
		 * ������ṹ
		 */
		class MyScrollBar
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
			MyScrollBar();
			/// ��������
			~MyScrollBar();

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

		class MOLEXPORT CMolGUIScrollBar : public CMolBaseGUIElement
		{
		public:
			/// ���캯��
			CMolGUIScrollBar();
			/// �������Ĺ��캯��
			CMolGUIScrollBar(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);
			virtual ~CMolGUIScrollBar();

			/// �������ϵİ�ťͼƬ
			void SetUpBtnImg(std::string path);
			/// �õ����ϵİ�ťͼƬ
			inline std::string GetUpBtnImg(void) { return m_UpButtonImg; }
			/// �������µİ�ťͼƬ
			void SetDownButtonImg(std::string path);
			/// �õ����µİ�ťͼƬ
			inline std::string GetDownButtonImg(void) { return m_DownButtonImg; }
			/// ���û�����ʹ�õ�ͼƬ
			void SetScrollBarImg(std::string path);
			/// �õ�������ʹ�õ�ͼƬ
			inline std::string GetScrollBarImg(void) { return m_ScrollBarImg; }
			/// ���ù����������ֵ
			inline void SetMaxValue(int value);
			/// �õ������������ֵ
			inline int GetMaxValue(void) { return m_MaxValue; }
			/// ���ù������ĵ�ǰֵ
			void SetCurValue(int value);
			/// �õ��������ĵ�ǰֵ
			inline int GetCurValue(void) { return m_CurValue; }
			/// ����ҳ����
			inline void SetPageCount(int count) { m_PageCount = count; }
			/// �õ�ҳ����
			inline int GetPageCount(void) { return m_PageCount; }
			/// ���ÿؼ�������ɫ
			inline void SetBackgroundColor(CMolColor col) { m_bgColor = col; }
			/// �õ��ؼ�������ɫ
			inline CMolColor GetBackgroundColor(void) { return m_bgColor; }
			/// �õ����ϰ�ť
			inline CMolGUIButton* GetUpButton(void) { return m_UpButton; }
			/// �õ����°�ť
			inline CMolGUIButton* GetDownButton(void) { return m_DownButton; }
			/// �����Ƿ�����ƶ�������
			inline void SetMoveScrollBar(bool isMove) { m_isMoving = isMove; }
			/// �õ��Ƿ�����ƶ�������
			inline bool IsMoveScrollBar(void) { return m_isMoving; }

			/// ���ؼ�
			virtual void Draw();
			/// ���ڴ�����յ����¼�
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// ����ʧ������¼�
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);
			/// �ƶ��ؼ���ָ����λ��
			virtual void Move(CMolPosition2d<int> pos);

		private:
			/// ��ʾ������
			void DrawScrollbar(CMolBaseFrame* driver);
			/// �϶�������
			void MoveScrollBar(void);

		private:
			std::string m_UpButtonImg;                  /**< ���ϵİ�ťͼƬ */
			std::string m_DownButtonImg;                /**< ���µİ�ťͼƬ */
			std::string m_ScrollBarImg;                 /**< ������ʹ�õ�ͼƬ */
			int m_UpButtonHeight;                       /**< ���ϰ�ť�ĸ߶� */
			int m_MaxValue,m_CurValue;                  /**< ���ù����������ֵ�͵�ǰֵ */
			int m_PageCount;                            /**< ����ÿҳ��ʾ���� */
			CMolColor m_bgColor;                        /**< ������Ҫ��ʾ�ı�����ɫ */

			DWORD m_curTime;                            /**< ���ڿ��ƹ����ٶ� */

			bool m_isMoving;                            /**< �Ƿ��ƶ������� */
			bool m_BtnDown;                             /**< �ƶ���ť�Ƿ��� */
			int  m_BtnDownIndex;                        /**< ��ǰ��ť������� */

			CMolGUIButton *m_UpButton;                  /**< ���ϰ�ť */
			CMolGUIButton *m_DownButton;                /**< ���°�ť */
			MyScrollBar m_MyScrollBar;                  /**< ������ */
		};

	//}
//}

#endif
