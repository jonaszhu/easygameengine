#ifndef _MOLE2D_GUI_PROCESS_BAR_H_
#define _MOLE2D_GUI_PROCESS_BAR_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.1
*/

#include "Mole2dBaseGUIElement.h"

//namespace mole2d
//{
	//namespace graphics
	//{

		class MOLEXPORT CMolGUIProcessBar : public CMolBaseGUIElement
		{
		public:
			/// ���캯��
			CMolGUIProcessBar();
			/// �������Ĺ��캯��
			CMolGUIProcessBar(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);

			/// ���õ�ǰ����������
			void SetProcess(int pro); 
			/// �õ���ǰ����������
			inline int GetProcess(void) { return process; }
			/// ���õ�ǰ���������ֵ
			void SetMaxValue(int value);
			/// �õ���ǰ���������ֵ
			inline int GetMaxValue(void) { return m_maxvalue; }
			/// ���õ�ǰ������Ҫ��ʾ���ַ���
			inline void SetText(std::string t) { m_Text = t; }
			/// �õ���ǰ������Ҫ��ʾ���ַ���
			inline std::string GetText(void) { return m_Text; }
			/// ���ý�����������ɫ
			inline void SetBgColor(CMolColor col) { m_bgColor = col; }
			/// �õ�������������ɫ
			inline CMolColor GetBgColor(void) { return m_bgColor; }
			/// ���ý�������ɫ
			inline void SetProcessColor(CMolColor col) { m_proColor = col; }
			/// �õ���������ɫ
			inline CMolColor GetProcessColor(void) { return m_proColor; }
			/// ���ý�������ʾ������ɫ
			inline void SetProTipColor(CMolColor col) { m_tipColor = col; }
			/// �õ���������ʾ������ɫ
			inline CMolColor GetProTipColor(void) { return m_tipColor; }
			/// �����Ƿ���ʾ��ǰ����
			inline void SetIsTip(bool isTip) { m_isTipPro = isTip; }
			/// �õ��Ƿ���ʾ��ǰ����
			inline bool IsTip(void) { return m_isTipPro; }
			/// ���ý�������һ��ͼƬ
			void SetBgImageOne(std::string path);
			/// �õ���������һ��ͼƬ
			inline std::string GetBgImageOne(void) { return m_BgImageOnePath; }
			/// ���ý������ڶ���ͼƬ
			void SetBgImageTwo(std::string path);
			/// �õ��������ڶ���ͼƬ
			inline std::string GetBgImageTwo(void) { return m_BgImageTwoPath; }
			/// ���ý�����������ͼƬ
			void SetBgImageThree(std::string path);
			/// �õ�������������ͼƬ
			inline std::string GetBgImageThree(void) { return m_BgImageThreePath; }
			/// ���ý�����������ͼƬ
			void SetBgImageFour(std::string path);
			/// �õ�������������ͼƬ
			inline std::string GetBgImageFour(void) { return m_BgImageFourPath; }

			/// ���ؼ�
			virtual void Draw();
			/// ���ڴ�����յ����¼�
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// ����ʧ������¼�
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);

		private:
			int process;                               /**< ��ǰ�������Ľ��� */
			int m_maxvalue;                            /**< ��ǰ���������ֵ */
			bool m_isTipPro;                           /**< �Ƿ���ʾ��ǰ���� */ 
			std::string m_Text;                        /**< ��ǰ��������ʾ���ַ��� */
			CMolColor m_bgColor;                       /**< ��ǰ�������ı�����ɫ */
			CMolColor m_proColor;                      /**< ��ǰ����������ɫ */
			CMolColor m_tipColor;                      /**< ��ǰ������������ʾ��ɫ */

			std::string m_BgImageOnePath;              /**< ��������һ��ͼƬ·�� */
			HTEXTURE m_BgImageOneImage;                /**< ��������һ��ͼƬ���� */
			std::string m_BgImageTwoPath;              /**< �������ڶ���ͼƬ·�� */
			HTEXTURE m_BgImageTwoImage;                /**< �������ڶ���ͼƬ���� */
			std::string m_BgImageThreePath;            /**< ������������ͼƬ·�� */
			HTEXTURE m_BgImageThreeImage;              /**< ������������ͼƬ���� */
			std::string m_BgImageFourPath;             /**< ������������ͼƬ·�� */
			HTEXTURE m_BgImageFourImage;               /**< ������������ͼƬ���� */
		};

	//}
//}

#endif
