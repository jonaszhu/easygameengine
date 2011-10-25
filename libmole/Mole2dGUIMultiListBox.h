#ifndef _MOLE2D_GUI_MULTI_LISTBOX_H_
#define _MOLE2D_GUI_MULTI_LISTBOX_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.12.5
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dRect.h"
#include "Mole2dGUIScrollBar.h"
#include "Mole2dGUIProcessBar.h"

#include <vector>

#define IDD_LIST_BOX_MOVE_SPACE 5
#define IDD_LIST_HEADER_HEIGHT 20
#define IDD_LIST_ROW_HEIGHT 22
#define IDD_LIST_PROCESSBAR_SPACE 3

//namespace mole2d
//{
//namespace graphics
//{

class MOLEXPORT CMolGUIMultiListBox : public CMolBaseGUIElement
{
public:
	/**
	 * �б�ͷ�ṹ
	 */
	struct LBHeader
	{
		LBHeader()
			: caption(""),tex(0),width(0)
		{		
		}
		LBHeader(std::string c,int w,HTEXTURE t)
			: caption(c),tex(t),width(w)
		{
		}

		CMolRect<s32> rect;                 // ��Χ
		int width;                          // �б�ͷ�Ŀ��
		std::string caption;                // ���� 
		HTEXTURE tex;                       // ����
	};

	/** 
	 * �ı����нṹ
	 */
	struct RowStruct
	{
		RowStruct()
			: processbar(NULL),sortId(0)
		{
		}

		int sortId;                              // ���������ID
		CMolRect<s32> rect;                      // �ı������ʾ��Χ
		std::vector<HTEXTURE> texList;           // Ҫ��ʾ��һ��ͼƬ
		std::string  text;                       // Ҫ��ʾ������
		CMolGUIProcessBar *processbar;           // ������
	};

	/// ���캯��
	CMolGUIMultiListBox();
	/// �������Ĺ��캯��
	CMolGUIMultiListBox(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// ��������
	virtual ~CMolGUIMultiListBox();

	/// �õ�������
	inline CMolGUIScrollBar* GetScrollBar(void) { return m_ScrollBar; }
	/// ����������
	void CreateScrollBar(void);
	/// ���ù������Ŀ��
	inline void SetScrollBarWidth(int w) { m_scrollbarWidth = w; }
	/// �õ��������Ŀ��
	inline int GetScrollBarWidth(void) { return m_scrollbarWidth; }
	/// �õ���ǰ�ؼ�������ʾ�������ַ�
	int GetDisplayLineCount(void);

	/// �����Ƿ�����
	inline void SetIsSort(bool sort) { m_HeaderIsMouse = sort; }
	/// �õ��Ƿ�����
	inline bool IsSort(void) { return m_HeaderIsMouse; }
	/// �����б�ͷ��ʹ�õ�����
	void SetHeaderImage(std::string path);
	/// �õ��б�ͷ��ʹ�õ�����
	inline std::string GetHeaderImage(void) { return m_headerImagePath; }
	/// ���һ���б�ͷ
	void AddHeader(std::string caption,int width);
	/// �����б�ͷ��ʾ��Ϣ
	inline void SetHeaderMessage(std::string mes) { m_HeaderMessage = mes; }
	/// �õ��б�ͷ��ʾ��Ϣ
	inline std::string GetHeaderMessage(void) { return m_HeaderMessage; }
	/// �����б�ͷ������ɫ
	inline void SetHeaderBgColor(CMolColor col) { m_HeaderBgColor = col; }
	/// �õ��б�ͷ������ɫ
	inline CMolColor GetHeaderBgColor(void) { return m_HeaderBgColor; }
	/// �����б�ͷ������ɫ
	inline void SetHeaderTextColor(CMolColor col) { m_HeaderTextColor = col; }
	/// �õ��б�ͷ������ɫ
	inline CMolColor GetHeaderTextColor(void) { return m_HeaderTextColor; }

	/// ���ý�������ʾ������ɫ
	inline void SetProTipColor(CMolColor col) { m_tipColor = col; }
	/// �õ���������ʾ������ɫ
	inline CMolColor GetProTipColor(void) { return m_tipColor; }
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

	/// ������е�������
	void ClearAllRows(void);
	/// �����µ�һ��
	int CreateNewRow(void);
	/// ���ָ����ָ����ָ�����ַ���
	void AddText(std::string text,int sortId,int row,int list);
	/// ���ͼƬ��ָ����ָ������
	void AddImage(std::string path,int sortId,int row,int list);
	/// ��ӽ�������ָ����ָ������
	void AddProcessBar(int cur,int max,int sortId,int row,int list);

	/// �õ���ǰѡ��������
	inline int GetSelectedItem(void) { return m_curSeletecRowIndex; }
	/// ���ñ�����ɫ
	inline void SetBgColor(CMolColor col) { m_bgColor = col; }
	/// �õ�������ɫ
	inline CMolColor GetBgColor(void) { return m_bgColor; }
	/// ����������ɫ
	inline void SetTextColor(CMolColor col) { m_TextColor = col; }
	/// �õ�������ɫ
	inline CMolColor GetTextColor(void) { return m_TextColor; }
	/// ����ѡ�����ɫ
	inline void SetSelectColor(CMolColor col) { m_SelectColor = col; }
	/// �õ�ѡ�����ɫ
	inline CMolColor GetSelectColor(void) { return m_SelectColor; }
	/// ����ѡ������ɫ
	inline void SetSelectedColor(CMolColor col) { m_SelectedColor = col; }
	/// �õ�ѡ������ɫ
	inline CMolColor GetSelectedColor(void) { return m_SelectedColor; }

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);
	/// �ƶ��ؼ���ָ����λ��
	virtual void Move(CMolPosition2d<int> pos);
	/// ����ָ���ж��������ݽ�������
	void SortAllData(int list,bool isForward=true);
	/// ��С��������
	static bool sort1(const std::vector<RowStruct> &t1,const std::vector<RowStruct> &t2);
	/// �Ӵ�С����
	static bool sort2(const std::vector<RowStruct> &t1,const std::vector<RowStruct> &t2);

private:
	/// �õ���ǰ�б�ͷ�Ŀ��
	int GetCurHeadersWidth(int index);
	/// �õ���ǰ�ܹ��ж��ٸ��ı�
	int GetTotalLineCount(void);
	/// ��ʾ�б�ͷ
	void DrawListBoxHeader(CMolBaseFrame* driver);
	/// ��ʾ���е���
	void DrawAllRows(CMolBaseFrame* driver);
	/// �õ������е���ʾλ��
	void GetRowsPosition();
	/// ��ָ�����꿪ʼ�õ������ı�����ʾλ��
	void GetAllRows(CMolPosition2d<s32> position);

private:
	CMolGUIScrollBar *m_ScrollBar;                /**< �ı���ʾ��Ĺ����� */
	int m_scrollbarWidth;                         /**< �������Ŀ�� */

	CMolColor m_bgColor;                          /**< �����б�򱳾���ɫ */
	CMolColor m_TextColor;                        /**< �����б��������ɫ */
	CMolColor m_SelectColor;                      /**< �����б��ѡ�����ɫ */
	CMolColor m_SelectedColor;                    /**< �����б��ѡ�к����ɫ */

	int m_curMouseRowIndex;                       /**< ��ǰ��꾭����һ���ı� */ 
	int m_curSeletecRowIndex;                     /**< ��ǰ���ѡ�е���һ���ı� */
	int m_curMouseHeaderIndex;                    /**< ��ǰ��꾭��ͷ�ı� */
	
	bool m_HeaderIsMouse;                         /**< �Ƿ�������� */
	std::string m_HeaderMessage;                  /**< �б�ͷ����ʾ����Ϣ */
	std::string m_headerImagePath;                /**< �б�ͷ��ʹ�������·�� */
	HTEXTURE m_headerImage;                       /**< �б�ͷ��ʹ�õ����� */
	CMolColor m_HeaderBgColor;                    /**< �б�ͷ��ʹ�õı�����ɫ */
	CMolColor m_HeaderTextColor;                  /**< �б�ͷ��ʹ�õ�������ɫ */
	int m_curRowIndex;                            /**< ��ǰ��ʾ������ */

	bool m_IsForward;                             /**< ����ʽ */
	static int m_sortIndex;                       /**< �������� */

	CMolColor m_tipColor;                      /**< ��ǰ������������ʾ��ɫ */
	std::string m_BgImageOnePath;              /**< ��������һ��ͼƬ·�� */
	std::string m_BgImageTwoPath;              /**< �������ڶ���ͼƬ·�� */
	std::string m_BgImageThreePath;            /**< ������������ͼƬ·�� */
	std::string m_BgImageFourPath;             /**< ������������ͼƬ·�� */

	std::vector<LBHeader> m_LBHeaderList;         /**< �б�ͷ */
	std::vector< std::vector<RowStruct> > m_LBRowList;  /**< ������ */
};

//}
//}

#endif
