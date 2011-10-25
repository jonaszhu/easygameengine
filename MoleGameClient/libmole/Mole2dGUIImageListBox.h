#ifndef _MOLE2D_GUI_IMAGE_LIST_BOX_H_
#define _MOLE2D_GUI_IMAGE_LIST_BOX_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dBaseFont.h"

#include "Mole2dGUIScrollBar.h"
#include "Mole2dGUIImage.h"

#include <vector>

#define IDD_LIST_BOX_SPACE 6
#define IDD_LIST_BOX_MOVE_SPACE 5

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIImageListBox : public CMolBaseGUIElement
	{
	public:
		/**
		 * �ı���������ṹ
		 */
		struct RowFontStruct
		{
			RowFontStruct()
				: color(CMolColor(255,255,255,255))
			{
			}
			RowFontStruct(std::string t,CMolColor col=CMolColor(255,255,255,255))
				: color(col),text(t)
			{
			}

			CMolColor color;            // ����������ʾ����ɫ
			std::string text;           // ����������ʾ���ı�
		};

		/** 
		 * �ı����нṹ
		 */
		struct RowStruct
		{
			RowStruct()
				: image(NULL)
			{
			}
			RowStruct(CMolRect<s32> r,std::string path)
				: imgPath(path),rect(r),image(NULL)
			{
			}

			/// ���һ���ַ������ı�����
			void AddString(std::string text,CMolColor col=CMolColor(255,255,255,255))
			{
				TextRows.push_back(RowFontStruct(text,col));
			}

			CMolRect<s32> rect;                    // �ı������ʾ��Χ
			std::string imgPath;                   // �ı���ͼƬ·��
			CMolGUIImage *image;                   // Ҫ��ʾ��ͼƬ
			CMolPosition2d<s32> startPos;          // �ؼ��Ŀ�ʼ��ʼλ��
			std::vector<RowFontStruct> TextRows;     // �ı����е���������
		};

		/// ���캯��
		CMolGUIImageListBox();
		/// �������Ĺ��캯��
		CMolGUIImageListBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);
		/// ��������
		virtual ~CMolGUIImageListBox();

		/// ���ÿؼ��ı�����ɫ
		inline void SetBgColor(CMolColor col) { m_BgColor = col; }
		/// �õ��ؼ��ı�����ɫ
		inline CMolColor GetBgColor(void) { return m_BgColor; }
		/// ���ÿؼ��ĳ�ʼ��ʾͼƬ
		inline void SetDefaultImage(std::string path) { m_DefaultImage = path; }
		/// �õ��ؼ��ĳ�ʼ��ʾͼƬ
		inline std::string GetDefaultImage(void) { return m_DefaultImage; }
		/// ���ù������Ŀ��
		inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
		/// �õ��������Ŀ��
		inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
		/// ����ѡ�к���ʾ����ɫ
		inline void SetSelectColor(CMolColor col) { m_SelectColor = col; }
		/// �õ�ѡ�к���ʾ����ɫ
		inline CMolColor GetSelectColor(void) { return m_SelectColor; }
		/// �õ�������
		inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
		/// ����������
		void CreateScrollBar(void);
		/// ����ͼƬ�ĸ߿�
		inline void SetImageSize(CMolDimension2d<s32> size) { m_imageSize = size; }
		/// �õ�ͼƬ�ĸ߿�
		CMolDimension2d<s32> GetImageSize(void) { return m_imageSize; }
		/// �õ���ǰ�ؼ�������ʾ�������ַ�
		int GetDisplayLineCount(void);
		/// ���һ��ͼƬ���б����
		void AddImageToListBox(std::string path);
		/// ���ָ�������ֵ�ָ��������
		void AddTextToListBox(int index,std::string text,CMolColor col=CMolColor(255,255,255,255));
		/// �õ���ǰ�б�����ж�����
		inline int GetTotalRows(void) { return (int)m_Rows.size(); }
		/// ������е���
		void ClearAllRows(void);
		/// �õ���ǰѡ��������
		inline int GetCurrentSelected(void) { return m_curMouseRowIndex; }
		/// �õ�ָ��������ͼƬ·��
		std::string GetImageByIndex(int index);
		/// �õ�ָ������ָ���е��ı�
		std::string GetStringByIndex(int rowIndex,int tIndex);

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);
		/// �ƶ��ؼ���ָ����λ��
		virtual void Move(CMolPosition2d<int> pos);

	private:
		/// �������е��ı�
		void DrawAllRows(CMolBaseFrame* driver);
		/// �õ�����ͼƬ����ʾλ��
		void GetImagesPosition();
		/// �õ���ǰ�ܹ��ж��ٸ��ı�
		int GetTotalLineCount(void);
		/// ��ָ�����꿪ʼ��ʾ�����ı�
		void DrawAllImages(CMolPosition2d<s32> position);

	private:
		CMolColor m_BgColor;                          /**< ������ɫ */
		CMolColor m_SelectColor;                      /**< ѡ�����ʾ����ɫ */
		int m_scrollbarWidth;                         /**< �������Ŀ�� */
		CMolDimension2d<s32> m_imageSize;             /**< ͼƬ��ʾ�ĸ߿� */
		int m_curRowIndex;                            /**< ��ǰ��ʾ������ */
		int m_curMouseRowIndex;                       /**< ��ǰ��꾭����һ���ı� */ 
		std::string m_DefaultImage;                   /**< ��ʼ����ʾͼƬ�����ͼƬ����ʧ�ܣ�����ʾ���ͼƬ */

		std::vector<RowStruct*> m_Rows;               /**< �ؼ���ʾ���ı� */

		CMolGUIScrollBar *m_ScrollBar;                /**< �ı���ʾ��Ĺ����� */
	};

	//}
//}

#endif
