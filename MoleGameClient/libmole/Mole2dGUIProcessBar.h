#ifndef _MOLE2D_GUI_PROCESS_BAR_H_
#define _MOLE2D_GUI_PROCESS_BAR_H_

/** 
* Mole2d 图像引擎
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
			/// 构造函数
			CMolGUIProcessBar();
			/// 带参数的构造函数
			CMolGUIProcessBar(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
				s32 id,std::string caption,CMolRect<s32> rect);

			/// 设置当前滚动条进度
			void SetProcess(int pro); 
			/// 得到当前滚动条进度
			inline int GetProcess(void) { return process; }
			/// 设置当前进度条最大值
			void SetMaxValue(int value);
			/// 得到当前进度条最大值
			inline int GetMaxValue(void) { return m_maxvalue; }
			/// 设置当前滚动条要显示的字符串
			inline void SetText(std::string t) { m_Text = t; }
			/// 得到当前滚动条要显示的字符串
			inline std::string GetText(void) { return m_Text; }
			/// 设置进度条背景颜色
			inline void SetBgColor(CMolColor col) { m_bgColor = col; }
			/// 得到进度条背景颜色
			inline CMolColor GetBgColor(void) { return m_bgColor; }
			/// 设置进度条颜色
			inline void SetProcessColor(CMolColor col) { m_proColor = col; }
			/// 得到进度条颜色
			inline CMolColor GetProcessColor(void) { return m_proColor; }
			/// 设置进度条提示字体颜色
			inline void SetProTipColor(CMolColor col) { m_tipColor = col; }
			/// 得到进度条提示字体颜色
			inline CMolColor GetProTipColor(void) { return m_tipColor; }
			/// 设置是否提示当前进度
			inline void SetIsTip(bool isTip) { m_isTipPro = isTip; }
			/// 得到是否提示当前进度
			inline bool IsTip(void) { return m_isTipPro; }
			/// 设置进度条第一张图片
			void SetBgImageOne(std::string path);
			/// 得到进度条第一张图片
			inline std::string GetBgImageOne(void) { return m_BgImageOnePath; }
			/// 设置进度条第二张图片
			void SetBgImageTwo(std::string path);
			/// 得到进度条第二张图片
			inline std::string GetBgImageTwo(void) { return m_BgImageTwoPath; }
			/// 设置进度条第三张图片
			void SetBgImageThree(std::string path);
			/// 得到进度条第三张图片
			inline std::string GetBgImageThree(void) { return m_BgImageThreePath; }
			/// 设置进度条第四张图片
			void SetBgImageFour(std::string path);
			/// 得到进度条第四张图片
			inline std::string GetBgImageFour(void) { return m_BgImageFourPath; }

			/// 画控件
			virtual void Draw();
			/// 用于处理接收到的事件
			virtual bool OnProcessEvent(const CMolEvent& event);
			/// 处理丢失焦点的事件
			virtual void OnProcessLostFocusEvent(const CMolEvent& event);

		private:
			int process;                               /**< 当前进度条的进度 */
			int m_maxvalue;                            /**< 当前进度条最大值 */
			bool m_isTipPro;                           /**< 是否提示当前进度 */ 
			std::string m_Text;                        /**< 当前进度条显示的字符串 */
			CMolColor m_bgColor;                       /**< 当前进度条的背景颜色 */
			CMolColor m_proColor;                      /**< 当前进度条的颜色 */
			CMolColor m_tipColor;                      /**< 当前进度条进度提示颜色 */

			std::string m_BgImageOnePath;              /**< 进度条第一张图片路径 */
			HTEXTURE m_BgImageOneImage;                /**< 进度条第一张图片纹理 */
			std::string m_BgImageTwoPath;              /**< 进度条第二张图片路径 */
			HTEXTURE m_BgImageTwoImage;                /**< 进度条第二张图片纹理 */
			std::string m_BgImageThreePath;            /**< 进度条第三张图片路径 */
			HTEXTURE m_BgImageThreeImage;              /**< 进度条第三张图片纹理 */
			std::string m_BgImageFourPath;             /**< 进度条第四张图片路径 */
			HTEXTURE m_BgImageFourImage;               /**< 进度条第四张图片纹理 */
		};

	//}
//}

#endif
