#ifndef _MOLE2D_GUI_GAME_CARD_H_
#define _MOLE2D_GUI_GAME_CARD_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3 д��ƽ��,ͼ��ؼ�,������ʾ����ͼ���ͼ��һ����
*/

#include "Mole2dBaseGUIElement.h"
#include "Mole2dVector.h"

#include <map>
#include <vector>
#include <deque>

//namespace mole2d
//{
	//namespace graphics
	//{

	/** 
	 * �˿˳�������
	 */
	enum CardOutType
	{
		OUTTYPE_SINGLE = 0,                   // ����
		OUTTYPE_YIDUI,                        // һ��
		OUTTYPE_SANZHANG,                     // ����
		OUTTYPE_SANDAIYI,                     // ����һ
		OUTTYPE_SANDAIYIDUI,                  // ����һ��
		OUTTYPE_SHUIZI,                       // ˳��
		OUTTYPE_LIANDUI,                      // ����
		OUTTYPE_SANZHANGSHUIZI,               // ���ŵ�˳��
		OUTTYPE_SANZHANGSHUIZIDAIYI,          // ���ŵ�˳�Ӵ�һ
		OUTTYPE_SANZHANGSUUIZIDAIYIDUI,       // ����˳�Ӵ�һ��
		OUTTYPE_SIDAILIANGZHANG,              // �Ĵ����ŵ���
		OUTTYPE_SIDAILIANGDUI,                // �Ĵ�����
		OUTTYPE_ZHADAN,                       // ը��
		OUTTYPE_HUOJIAN,                      // ���
		OUTTYPE_NULL                          
	};

	class MOLEXPORT CMolGUIGameCard : public CMolBaseGUIElement
	{
	public:
		/** 
		 * �˿˽ṹ
		 */
		struct GameCard
		{
			GameCard():data(0),isUp(false),isSelected(false),isDisplay(false) { }
			GameCard(BYTE d,bool up=false,bool issel=false,bool isdis=true):data(d),isUp(up),isSelected(issel),isDisplay(isdis) { }

			BYTE data;                // �˿�����
			bool isUp;                // �Ƿ�����
			bool isSelected;          // �˿��Ƿ�ѡ��
			bool isDisplay;           // �Ƿ���ʾ
		};

		/** 
		 * �˿˵ķ���
		 */
		enum CardDir
		{
			CARDDIR_HENGXIANG = 0,                // ������ʾ�˿�
			CARDDIR_ZONGXIANG                     // ������ʾ�˿�
		};

		/** 
		 * �˿˵Ķ��뷽ʽ
		 */
		enum CardSnapType
		{
			CARD_SNAP_LEFT = 0,                   // ����
			CARD_SNAP_CENTER,                     // ����
			CARD_SNAP_RIGHT                       // ����
		};

		/**
		 * �˿���ʾ����
		 */
		enum CardDisType
		{
			DISTYPE_NORMAL = 0,                   // ������ʾ
			DISTYPE_LEFTSLOPE,                    // ������б��ʾ
			DISTYPE_RIGHTSLOPE                    // ������б��ʾ
		};

		/** 
		 * ��������˿�����
		 */
		struct AnaCards
		{
			CardOutType type;                     // ����
			int value;                            // ֵ
			std::vector<BYTE> data;               // ���ڴ洢����
		};

		/// ���캯��
		CMolGUIGameCard();
		/// �������Ĺ��캯��
		CMolGUIGameCard(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

	/// �����˿˸߿�
	inline void SetCardWidthAndHeight(int w,int h) 
	{ 
		m_CardWidth = w;
		m_CardHeight = h;
	}
	/// �õ��˿˿��
	inline int GetCardWidth(void) { return m_CardWidth; }
	/// �õ��˿˸߶�
	inline int GetCardHeight(void) { return m_CardHeight; }
	/// �õ�ָ���˿����ݵĻ�ɫ
	inline int GetCardHuaSe(int card) { return ((BYTE)card >> 4) & 0x0F; }
	/// �õ�ָ���˿����ݵ�����
	inline int GetCardDianShu(int card) { return (BYTE)card & 0x0F; }
	/// �����˿�����
	void SetCardData(CMolVector<int> data,bool isdis=true);
	/// �õ��˿�����
	CMolVector<int> GetCardData(void);
	/// �õ���ǰ�ж������˿�
	inline int GetCardCount(void) { return (int)m_CardData.size(); }
	/// �����˿�֮��ļ��
	inline void SetCardSpace(int space) { m_CardSpace = space; }
	/// �õ��˿�֮��ļ��
	inline int GetCardSpace(void) { return m_CardSpace; }
	/// �����˿�̧��ļ��
	inline void SetCardUpSpace(int space) { m_CardUpSpace = space; }
	/// �õ��˿�̧��ļ��
	inline int GetCardUpSpace(void) { return m_CardUpSpace; }
	/// �����˿˱���ͼƬ
	inline void SetCardBackTex(HTEXTURE tex) { m_CardBackImg = tex; }
	/// �õ��˿˱���ͼƬ
	inline HTEXTURE GetCardBackTex(void) { return m_CardBackImg; }
	/// �����˿˵���ʾ����
	inline void SetCardDirection(CMolGUIGameCard::CardDir dir) { m_CardDir = dir; }
	/// �õ��˿˵���ʾ����
	inline CMolGUIGameCard::CardDir GetCardDirection(void) { return m_CardDir; }
	/// �����Ƿ���ʾ�˿�
	inline void SetShowCards(bool isShow) { m_IsShowCard = isShow; }
	/// �õ��Ƿ���ʾ�˿�
	inline bool IsShowCards(void) { return m_IsShowCard; }
	/// ������ʾ�������˿�
	void SetDisplayCard(int count);
	/// �õ���ǰ����������˿�
	inline int GetCardUpCount(void) 
	{ 
		int count = 0;
		for(int i=0;i<(int)m_CardData.size();i++) 
			if(m_CardData[i].isUp) count+=1;

		return count;
	}
	/// �����Ƿ�����ʾ�˿�
	inline void SetReverseShowCards(bool isReverse) { m_IsReverse = isReverse; }
	/// �õ��Ƿ�����ʾ�˿�
	inline bool IsReverseShowCards(void) { return m_IsReverse; }
	/// �����˿˵Ķ��뷽ʽ
	inline void SetSnapType(CMolGUIGameCard::CardSnapType type) { m_CardSnapType = type; }
	/// �õ��˿˵Ķ��뷽ʽ
	inline CMolGUIGameCard::CardSnapType GetSnapType(void) { return m_CardSnapType; }

		/// �����˿˵���ʾ����
		inline void SetDisType(CMolGUIGameCard::CardDisType type) { m_carddistype = type; }
		/// �õ��˿˵���ʾ����
		inline CMolGUIGameCard::CardDisType GetDisType(void) { return m_carddistype; }
		/// �����˿˵���б��Χ
		inline void SetSlopeAngle(int angle) { m_slopeangle = angle; }
		/// �õ��˿˵���б��Χ
		inline int GetSlopeAngle(void) { return m_slopeangle; }
		/// �����˿���б��ʹ�õ�ͼƬ
		inline void SetSlopeImage(std::string path);
		/// �õ��˿���бʹ�õ�ͼƬ
		inline std::string GetSlopeImage(void) { return m_slopeimagepath; }
		/// ����ѡ���˿˺�ʹ�õ�ͼƬ
		inline void SetSelectedCardImage(std::string path);
		/// �õ�ѡ���˿˺�ʹ�õ�ͼƬ
		inline std::string GetSelectedCardImage(void) { return m_selecteimagepath; }
		/// �����˿˵���ת�Ƕ�
		inline void SetAngle(int angle) { m_angle = angle; }
		/// �õ��˿˵���ת�Ƕ�
		inline int GetAngle(void) { return m_angle; }

		/// �õ���ǰѡ����Ƶ�����
		inline int GetSelectedCardCount(void) { return (int)m_CurSelCards.size(); }
		/// ��ָ���������˿�
		void OutRandomCards(int count);
		/// �õ���ǰѡ���������
		CMolVector<int> GetSelectedCards(void);
		/// ��ʼ����
		void StartOutCards(void);
		/// ������е�������
		void ClearAllCards(void);
		/// ����������
		void ResetAllCards(void);
		/// �����е��ƽ�������
		void SortAllCards(void);
		/// ��������ֵ�õ���Ӧ��������
		void GetCardsByOutType(CMolVector<int> cards);
		/// �õ�ָ���Ƶ�����
		CardOutType GetOutType(CMolVector<int> cards);
	/// Ѱ��ָ��λ�õ�ָ��λ�õ�����
	void FindGameCard(int startPos,int startEnd);
		/// �ӵ�ǰ�ؼ���ɾ��ָ����������
		void RemoveCards(CMolVector<int> cards);
		/// �õ�ָ���������˿�����
		int GetCardDataByIndex(int index);
		/// �õ�ָ�����͵��˿˵�����
		int GetCardTypeCount(CardOutType type);
	/// �õ������˿˵ĸ߿�
	CMolDimension2d<s32> GetCardSize(void);
		/// �õ���ǰ�����͵���ֵ
		inline int GetCurOutCardValue(void) { return m_curcardvalue; }
		/// ���ڷֽ�ָ���ַ���Ϊ������
		CMolVector<int> ParseStringToCards(std::string str,std::string chr=";");
		/// ���ָ�����������Ƿ��ù���һ��������
		bool Comparison(CMolVector<int> src,CMolVector<int> dec);

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// ����ָ������������
		void UpCardsByIndex(std::vector<int> data);
		/// ����������
		void AnalyseAllCards(void);
		/// �õ��������͵�������
		bool GetBaseCardsByOutType(std::map< BYTE,std::vector<int> > analycards,CardOutType type,int card,bool isUp=true);
		/// �õ��������͵�������
		bool GetLianPaiCardsByOutType(CardOutType type,int card,int count,bool isUp=true);
		/// ����ƿؼ���ѡ��״̬
		void ClearCardSelecteState(void);
		/// ��ʾָ��ID���˿�
		void DrawGameCard(int index);
		/// �õ������˿˵Ŀ��
		int GetWidthWidthAllCards(void);
		/// �����˿˵Ķ��뷽ʽ�õ��˿˵���ʾλ��
		CMolPosition2d<s32> GetCardDisplayPos(void);
		/// ��С��������
		static bool sort1(const GameCard &t1,const GameCard &t2);
		/// �Ӵ�С����
		static bool sort2(const GameCard &t1,const GameCard &t2);
		/// �������ָ�������Ƿ����
		bool IsEquation(CMolVector<int> src,CMolVector<int> dec);

	private:
		int m_CardWidth,m_CardHeight;                           /**< �˿˸߿� */
		int m_CardSpace,m_CardUpSpace;                          /**< �˿�֮��ļ����̧��ļ�� */
		std::deque<GameCard>  m_CardData;                      /**< Ҫ��ʾ���˿����� */

		CardDisType m_carddistype;                              /**< �˿���ʾ���� */
		int m_slopeangle;                                       /**< ��б�ķ�Χ */
		std::string m_slopeimagepath;                           /**< ��бʹ�õ�ͼƬ·�� */
		HTEXTURE m_slopeimage;                                  /**< ��бʹ�õ�ͼƬ */
		std::string m_selecteimagepath;                        /**< ѡ�к���ʾ����ͼƬ·�� */
		HTEXTURE m_selecteimage;                                /**< ѡ�к���ʾ����ͼƬ */
		CMolDimension2d<s32> selImgSize;                        /**< ѡ�к���ͼƬ�ĸ߿� */

		bool m_IsForward;                                       /**< ����ʽ */

		std::map<CardOutType,int> m_sortpos;                    /**< �����˿����ݵ�λ�� */
		std::map<CardOutType,int> m_sortstartpos;               /**< �����˿����ݳ�ʼ��λ�� */
		CMolVector<int> m_sordcarddata;                         /**< ��ǰ���������� */
		CardOutType m_sortouttype;                              /**< ��ǰ���������˿����� */
		std::map< BYTE,std::vector<int> >  m_analysecards;        /**< ������������� */
		int m_curcardvalue;                                     /**< ��ǰ��ֵ */

		std::vector<std::string>  m_Parameters;                 /**< Ҫ�ֽ�Ĳ��� */

		bool m_CurSelected;                                     /**< ��ǰ�Ƿ�ѡ���� */
		std::vector<int> m_CurSelCards;                         /**< ��ǰѡ��������� */
		int m_CurSelStart,m_CurSelEnd;                          /**< ��ǰѡ��ʼ�ͽ��� */
		int m_CurMousePos;                                      /**< ��ǰ��������Ƶ����� */
		CardDir m_CardDir;                                      /**< ��ǰ�˿˵ķ��� */
		CardSnapType m_CardSnapType;                            /**< ��ǰ�˿˵Ķ��뷽ʽ */
		bool m_IsShowCard;                                      /**< �Ƿ���ʾ�˿� */
		bool m_IsReverse;                                       /**< �Ƿ�����ʾ�˿� */
		int m_angle;                                            /**< �˿���ת�Ƕ� */
		CMolVector<BYTE> m_AutoOut;                              /**< ������ʾ��3��λ�� */

		HTEXTURE m_CardBackImg;                                 /**< �˿˱�����ʾͼƬ */
	};

	//}
//}

#endif
