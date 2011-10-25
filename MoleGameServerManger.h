#ifndef _MOLE_GAME_SERVER_MANAGER_H_INCLUDE_
#define _MOLE_GAME_SERVER_MANAGER_H_INCLUDE_

#include "defines.h"

#include <string>
#include <vector>
#include <map>

#define IDD_GAME_ROOM_LIST         (WM_USER+600)          // ��Ϸ�б���Ϣ
#define IDD_SHOW_GAME_SERVER       (WM_USER+601)          // ��ʾ��Ϸ�������б�
#define IDD_GET_GAME_RULE          (WM_USER+602)          // �õ���Ϸ������Ϣ
#define IDD_ENTER_GAME_SERVER      (WM_USER+603)          // ������Ϸ������

//��ť��
class CRadioButton : public CButton
{
	//��������
protected:
	CImage  							m_ImageBack;					//��ťλͼ
	bool                                m_isCheck;                      

	//��������
public:
	//���캯��
	CRadioButton();
	//��������
	virtual ~CRadioButton();

	inline void SetCheck(bool check) { m_isCheck = check; }
	inline bool GetCheck(void) { return m_isCheck; }

	//���غ���
protected:
	//�ؼ����໯
	virtual void PreSubclassWindow();
	//����滭����
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	//����λ��
	bool FixButtonSize();
	//����λͼ
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=true);

	//��Ϣ����
protected:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//����뿪
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//������Ϣ
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
};


/**
 * ��Ϸ��������
 */
struct GameParam
{
	GameParam():gameId(0) {}
	GameParam(int gi,std::string gl,std::string gr):gameId(gi),gamelogo(gamerule) {}

	int gameId;           // ��ϷID
	std::string gamelogo; // ��ϷlogoͼƬ
	std::string gamerule; // ��Ϸ����ͼƬ
};

/** 
 * ��ť״̬
 */
enum ButtonState
{
	BTN_STATE_NORMAL = 0,         // ����
	BTN_STATE_OVER,               // ����
	BTN_STATE_DOWN,               // ����
	BTN_STATE_DISABLE             // ����
};

//��ť��
class CSkinButton : public CButton
{
	//��������
protected:
	CImage							m_ImageBack;					//��ťλͼ
	COLORREF							m_crTextColor;					//������ɫ
	ButtonState                     m_ButtonState;                  //��ť״̬

	//��������
public:
	//���캯��
	CSkinButton();
	//��������
	virtual ~CSkinButton();

	//���غ���
protected:
	//�ؼ����໯
	virtual void PreSubclassWindow();
	//����滭����
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//���ú���
public:
	//����λ��
	bool FixButtonSize();
	//������ɫ
	bool SetTextColor(COLORREF crTextColor);
	//����λͼ
	bool SetButtonImage(LPCTSTR pszFileName, bool bExpandImage=false);
	//Ĭ�ϰ�ť
	void SetDefaultButton(bool bResetIcon=true, bool bResetColor=true, bool bResetImage=true);

	//��ѯ����
public:
	//��ȡ��ɫ
	COLORREF GetButtonColor() { return m_crTextColor; }

	//��Ϣ����
protected:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//����뿪
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	//������Ϣ
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinButton)
};

class CGameRoomNode : public CWnd
{
public:
	/** 
	 * �������
	 */
	enum NodeType
	{
		NODETYPE_GAME = 0,          // ��Ϸ
		NODETYPE_SERVER = 1         // ��Ϸ������
	};

	/// ���캯��
	CGameRoomNode();
	/// ��������
	virtual ~CGameRoomNode();

	/// ���ý��ͼƬ����
	void CreateNode(std::string bgImg,std::string logoImg,std::string enterImg,std::string ruleImg);

	/// ���ý������
	inline void SetNodeType(CGameRoomNode::NodeType type) { m_NodeType = type; }
	/// �õ��������
	inline CGameRoomNode::NodeType GetNodeType(void) { return m_NodeType; }
	/// ���ý���ʾ����Ϸ��Ϣ
	inline void SetGameServerInfo(GameServerInfo info) { m_GameServerInfo = info; }
	/// �õ�����ʾ����Ϸ��Ϣ
	inline GameServerInfo GetGameServerInfo(void) { return m_GameServerInfo; }
	/// ���ù������ӵ�ַ
	inline void SetRuleAddress(std::string address) { m_ruleAddress = address; }
	/// �õ��������ӵ�ַ
	inline std::string GetRuleAddress(void) { return m_ruleAddress; }
	/// ������ϷID
	inline void SetGameId(int gameId) { m_GameId = gameId; }
	/// �õ���ϷID
	inline int GetGameId(void) { return m_GameId; }
	/// �����Ƿ�У����
	inline void SetRegulate(bool regulate) { m_isRegulate = regulate; }
	/// ����Ƿ�У����
	inline bool IsRegulate(void) { return m_isRegulate; } 

	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, LPRECT lpRect);

protected:
	afx_msg void OnPaint();
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()

private:
	GameServerInfo m_GameServerInfo;   /**< ������� */
	CImage m_gameLogo;                 /**< ��ϷlogoͼƬ */
	CImage m_bgImg;                    /**< ��㱳��ͼƬ */
	NodeType m_NodeType;               /**< ������� */
	CSkinButton m_enterBtn;                /**< ���밴ť */
	CSkinButton m_ruleBtn;                 /**< ����ť */
	std::string m_ruleAddress;             /**< �������ӵ�ַ */
	int m_GameId;                          /**< ��ϷID */
	bool m_isRegulate;                     /**< �Ƿ��Ѿ�У������ */

	DWORD m_dwWidth;		// mask width
	DWORD m_dwHeight;		// mask height

private:
	HRGN CreateRgnFromFile( HBITMAP hBmp, COLORREF color );
};

class CGameRoomManager : public CWnd
{
public:
	/// ���캯��
	CGameRoomManager();
	/// ��������
	virtual ~CGameRoomManager();

	/// ������еķ���
	void Clear(void);
	/// ���뷿������
	bool LoadRoomConfig(std::string configfile);
	/// �õ���ǰѡ����ϷID
	inline int GetCurSelGameID(void) { return m_curSelGameId; }
	/// ����һ����Ϸ��㵽��������
	void InsertGameNode(int gameId);
	/// ����һ����������㵽��������
	void InsertServerNode(GameServerInfo gsf);
	/// �Ƿ���ʾ���е���Ϸ���
	void ShowAllGameRoomNodes(int show);
	/// �Ƿ���ʾָ����ϷID�ķ��������
	void ShowAllGameServerNodes(int gameId,int show);
	/// ��յ�ǰѡ��
	inline void ClearCurSel(void) { m_curSelGameId = -1; }

	/// У����Ϸ���λ��
	void RegulateGameNodes(void);
	/// У��ָ����Ϸ�ķ�����λ��
	void RegulateGameServerNodes(int gameId);
	/// ��ʾ����Ϸ�б����
	void ShowMainGameNodes(void);

protected:
	afx_msg void OnPaint();
	//��ʾ��Ϸ�������б�
	afx_msg LRESULT OnShowGameServerList(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
private:
	std::map<int,std::vector<CGameRoomNode*> > m_GameRoomNodes;                /**< ���ڱ������еķ����� */
	std::map<int,CGameRoomNode*>               m_GameServerNodes;              /**< �����Լ��Ľ�� */

	CSize                                      m_rowlist;                      /**< ������������� */
	CSize                                      m_rowlistspace;                 /**< ��������м�� */
	CPoint                                     m_ShowPosition;                 /**< �����б����ʾλ�� */
	CImage                                     m_bgImage;                      /**< ������ʾ����ͼƬ */
	std::string                                m_showbtnimg;                   /**< ��ʾ�����б�ťͼƬ·�� */
	std::string                                m_enterbtnimg;                  /**< ������Ϸ��ťͼƬ·�� */
	std::string                                m_rulebtnimg;                   /**< ����ťͼƬ·�� */
	std::string                                m_gamebgimg;                    /**< ��Ϸ��㱳��ͼƬ */
	std::string                                m_gameroomimg;                  /**< ��Ϸ���䱳��ͼƬ */
	int                                        m_curSelGameId;                 /**< ��ǰѡ����ϷID */

	std::map<int,GameParam>                    m_GameParams;                   /**< ���ڱ�����Ϸ���� */
};

#endif
