#ifndef _GUI_GAME_LIST_H_
#define _GUI_GAME_LIST_H_

#include "Mole2dBaseGUIElement.h"

#include "Mole2dGUIButton.h"

#include <vector>
#include <map>

class CMolGUIGameList;

/** 
 * ��Ϸ����
 */
struct CMolGameRule
{
	CMolGameRule()
		: Id(0)
	{}
	CMolGameRule(int pId,std::string pName,std::string pBgImg,std::string pEnterImg,std::string pRuleImg,std::string pRuleAddress)
		: Id(pId),Name(pName),bgImg(pBgImg),enterImg(pEnterImg),ruleImg(pRuleImg),ruleaddress(pRuleAddress)
	{}

	int Id;                  // ��ϷID
	std::string Name;       // ��Ϸ����
	std::string bgImg;      // ��Ϸ�ı�־ͼƬ
	std::string enterImg;   // ��Ϸ���밴ťͼƬ
	std::string ruleImg;    // ��Ϸ����ťͼƬ
	std::string ruleaddress; // ��Ϸ������ַ
};

/** 
 * ��Ϸ����ṹ
 */
class CMolGameRoom
{
public:
	/// ���캯��
	CMolGameRoom(CMolGUIGameList *gl,int index);
	/// ��������
	~CMolGameRoom();

	/// ������ϷID
	inline void SetGameID(int gameId) { m_gameId = gameId; }
	/// �õ���ϷID
	inline int GetGameID(void) { return m_gameId; }
	/// ������Ϸ����
	inline void SetGameName(std::string name) { m_gameName = name; }
	/// �õ���Ϸ����
	inline std::string GetGameName(void) { return m_gameName; }
	/// ������Ϸ����Ҫ�򿪵���ַ
	inline void SetGameRuleAddress(std::string address) { m_gameruleaddress = address; }
	/// �õ���Ϸ����Ҫ�򿪵���ַ
	inline std::string GetGameRuleAddress(void) { return m_gameruleaddress; }
	/// ������ϷͼƬ
	inline void SetGameImage(HTEXTURE tex) { m_gamebgimg = tex; }
	/// ������Ϸ��ʾ������
	inline void SetGameRect(CMolRect<s32> rect) { m_gameRect = rect; }
	/// �õ���Ϸ��ʾ������
	inline CMolRect<s32> GetGameRect(void) { return m_gameRect; }
	/// ������Ϸ���밴ťƫ��
	inline void SetGameEnterBtnOffset(CMolDimension2d<s32> offset) { m_gameenterbtnoffset = offset; }
	/// �õ���Ϸ���밴ťƫ��
	inline CMolDimension2d<s32> GetGameEnterBtnOffset(void) { return m_gameenterbtnoffset; }
	///������Ϸ����ťƫ��
	inline void SetGameRuleBtnOffset(CMolDimension2d<s32> offset) { m_gamerulebtnoffset = offset; }
	///�õ���Ϸ����ťƫ��
	inline CMolDimension2d<s32> GetGameRuleBtnOffset(void) { return m_gamerulebtnoffset; }
	/// ������Ϸ���밴ť
	void SetGameEnterBtn(std::string imgpath);
	/// ������Ϸ����ť
	void SetGameRuleBtn(std::string imgpath);
	/// �õ���Ϸ���밴ť
	inline CMolGUIButton* GetBtnGameEnter(void) { return m_gameenterbtn; }
	/// �õ���Ϸ����ť
	inline CMolGUIButton* GetBtnGameRule(void) { return m_gamerulebtn; }
	/// ������Ϸ�Ƿ���ʾ
	void SetVisible(bool isVisible);
	/// �õ���Ϸ�Ƿ���ʾ
	inline bool IsVisible(void) { return m_isVisible; }

	/// ��ʾ����
	void Draw(CMolBaseFrame *pdriver);

private:
	int               m_gameId;                       /**< ��ϷID */
	std::string      m_gameName;                     /**< ��Ϸ���� */
	std::string      m_gameruleaddress;              /**< ��Ϸ������ַ */
	CMolRect<s32>	  m_gameRect;                     /**< ��Ϸ����ʾ���� */
	HTEXTURE          m_gamebgimg;                    /**< ��Ϸ����ͼƬ */
	CMolGUIButton     *m_gameenterbtn;                /**< ��Ϸ���밴ť */
	CMolGUIButton     *m_gamerulebtn;                 /**< ��Ϸ����ť */

	CMolDimension2d<s32> m_gameenterbtnoffset;        /**< ��Ϸ���밴ťƫ�ƣ���������Ͻǣ� */
	CMolDimension2d<s32> m_gamerulebtnoffset;         /**< ��Ϸ����ťƫ�ƣ���������Ͻǣ� */
	CMolGUIGameList   *m_gamelist;                    /**< ��Ϸ�б�ؼ� */
	bool              m_isVisible;                    /**< �Ƿ���ʾ��Ϸ */
	int               m_gameIndex;                    /**< ��Ϸ���б��е����� */
};

class MOLEXPORT CMolGUIGameList : public CMolBaseGUIElement
{
public:
	/// ���캯��
	CMolGUIGameList();
	/// �������Ĺ��캯��
	CMolGUIGameList(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
		s32 id,std::string caption,CMolRect<s32> rect);
	/// ��������
	virtual ~CMolGUIGameList();

	/// ������Ϸ��ʾ���к���
	inline void SetGameRowAndList(CMolDimension2d<s32> size) { m_gameRowList = size; }
	/// �õ���Ϸ��ʾ���к���
	inline CMolDimension2d<s32> GetGameRowAndList(void) { return m_gameRowList; }
	/// ������Ϸ����
	void LoadGameRule(std::string configpath);
	/// ���һ��ƫ�Ƶ���Ϸ�б���
	inline void AddGameOffset(CMolDimension2d<s32> offset) { m_gameoffsets.push_back(offset); }
	/// ���һ����Ϸ����Ϸ�б���
	void AddGameToList(int gameId);
	/// ���ָ����ť�Ƿ��ǹ���ť
	int IsRuleButton(CMolGUIButton *btn);
	/// ���ָ����ť�Ƿ��ǽ��밴ť
	int IsEnterButton(CMolGUIButton *btn);
	/// �õ�ָ����������Ϸ
	CMolGameRoom* GetGameByIndex(int index);	
	/// �õ���ǰѡ�е���Ϸ
	inline CMolGameRoom* GetGameSelected(void) { return GetGameByIndex(m_selectedGame); }
	///��һҳ
	void PageUp(void);
	///��һҳ
	void PageDown(void);
	///��ҳ
	void Home(void);
	///βҳ
	void End(void);

	/// ���ؼ�
	virtual void Draw();
	/// ���ڴ�����յ����¼�
	virtual bool OnProcessEvent(const CMolEvent& event);
	/// ����ʧ������¼�
	virtual void OnProcessLostFocusEvent(const CMolEvent& event);

private:
	CMolDimension2d<s32> m_gameRowList;                /**< ��Ϸ��ʾ���к��� */
	std::map<int,CMolGameRule> m_gamerules;            /**< ��Ϸ���� */
	std::vector<CMolDimension2d<s32> > m_gameoffsets;   /**< ��Ϸ�н��밴ť������ť��ƫ�� */
	std::vector<CMolGameRoom*> m_gamelist;              /**< ��Ϸ�����б� */
	int m_curRoomIndex;                                /**< ��ǰ�������� */
	int m_selectedGame;                                /**< ��ǰѡ�еķ������������ */
};

#endif
