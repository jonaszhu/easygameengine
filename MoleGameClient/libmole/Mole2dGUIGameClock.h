#ifndef _MOLE2D_GUI_GAME_CLOCK_H_
#define _MOLE2D_GUI_GAME_CLOCK_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3 д��ƽ��,ͼ��ؼ�,������ʾ����ͼ���ͼ��һ����
*/

#include "Mole2dBaseGUIElement.h"

#include <vector>
#include <string>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIGameClock : public CMolBaseGUIElement
	{
	public:
		/** 
		* ʱ�ӵĶ��뷽ʽ
		*/
		enum ClockSnapType
		{
			CLOCK_SNAP_LEFT = 0,                   // ����
			CLOCK_SNAP_CENTER,                     // ����
			CLOCK_SNAP_RIGHT                       // ����
		};

		/// ���캯��
		CMolGUIGameClock();
		/// �������Ĺ��캯��
		CMolGUIGameClock(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// ����ʱ�ӿؼ������õ���ͼƬ
		inline void SetClockNumImg(HTEXTURE tex) { m_clocknumtex = tex; }
		/// �õ�ʱ�ӿؼ������õ���ͼƬ
		inline HTEXTURE GetClockNumImg(void) { return m_clocknumtex; }
		/// ����ʱ�ӿؼ���ʾ������
		void SetClockNum(int num);
		/// �õ�ʱ�ӿؼ���ʾ������
		inline int GetClockNum(void) { return m_DefaultNum; }
		/// ����ʱ�ӿؼ��Ķ��뷽ʽ
		inline void SetSnapType(CMolGUIGameClock::ClockSnapType type) { m_ClockSnapType = type; }
		/// �õ�ʱ�ӿؼ��Ķ��뷽ʽ
		inline CMolGUIGameClock::ClockSnapType GetSnapType(void) { return m_ClockSnapType; }
		/// ����ʱ�ӿؼ�����֮�����ʾ���
		inline void SetNumSpace(int space) { m_NumSpace = space; }
		/// �õ�ʱ�ӿؼ�����֮�����ʾ���
		inline int GetNumSpace(void) { return m_NumSpace; }

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		/// ��ָ��λ����ʾ�Զ�������
		void DrawGameClockNum(CMolPosition2d<s32> pos);

	private:
		HTEXTURE m_clocknumtex;                            /**< ʱ�ӿؼ������õ���ͼƬ */
		int m_DefaultNum;                                  /**< ʱ�ӿؼ���ʾ������ */
		int m_NumSpace;                                    /**< ����֮�����ʾ��� */
		ClockSnapType m_ClockSnapType;                     /**< ʱ�ӿؼ��Ķ��뷽ʽ */

		int m_DisNums[100];                                /**< Ҫ��ʾ������ */
		int m_numcount;                                    /**< ��ǰ��ʾ���� */
	};

	//}
//}

#endif
