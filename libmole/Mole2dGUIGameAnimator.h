#ifndef _MOLE2D_GUI_GAME_ANIMATOR_H_
#define _MOLE2D_GUI_GAME_ANIMATOR_H_

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.2.3 д��ƽ��,ͼ��ؼ�,������ʾ����ͼ���ͼ��һ����
*/

#include "Mole2dBaseGUIElement.h"

#include "Mole2dAnimator.h"

#include <string>
#include <vector>

//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIGameAnimator : public CMolBaseGUIElement
	{
	public:
		/** 
		 * ����֡�ṹ
		 */
		struct GameFrame
		{
			GameFrame():isShow(true),tex(0) { }
			GameFrame(bool isDis,HTEXTURE t):isShow(isDis),tex(t) { }

			bool isShow;                    // �Ƿ���ʾ��֡
			HTEXTURE tex;                   // ��֡������
		};

		/// ���캯��
		CMolGUIGameAnimator();
		/// �������Ĺ��캯��
		CMolGUIGameAnimator(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);

		/// ���붯��
		bool LoadAnimator(std::string path);
		/// �õ�����·��
		inline std::string GetAnimatorPath(void) { return m_AnimatorPath; }
		/// �õ������ĸ߿�
		inline CMolDimension2d<int> GetAnimSize(void) { return m_AnimSize; }
		/// �õ������ܵ�֡��
		inline int GetFrameCount(void) { return m_AnimFrameCount; }
		/// �õ������Ĳ����ٶ�
		inline int GetSpeed(void) { return m_Speed; }
		/// �����Ƿ�ѭ�����Ŷ���
		inline void SetLoop(bool loop) { m_isLoop = loop; }
		/// �õ��Ƿ�ѭ�����Ŷ���
		inline bool IsLoop(void) { return m_isLoop; }
		/// ���ò��Ŵ���
		inline void SetLoopCount(int count) { m_loopCount = count; }
		/// �õ����Ŵ���
		inline int GetLoopCount(void) { return m_loopCount; }
		/// ���Ŷ���
		inline void Play(void) { m_isPlay = true; m_curPlayCount = 1; }
		/// ֹͣ���Ŷ���
		inline void Stop(void) 
		{ 
			m_isPlay = false; 
			m_CurFrameIndex = 0; 
			m_CurTime = 0;
		}
		/// ��ͣ���Ŷ���
		inline void Pause(void) { m_isPlay = false; }
		/// ���²��Ŷ���
		inline void Restart(void) 
		{ 
			m_CurFrameIndex = 0;
			m_CurTime = 0;
			m_isPlay = true; 
		}
		/// �õ���ǰ��������״̬
		inline bool isPlaying(void) { return m_isPlay; }
		/// �õ���ǰ��������֡����
		inline int GetCurrentFrame(void) { return m_CurFrameIndex; }
		/// ��ն�������
		void Clear(void);

		/// ���ؼ�
		virtual void Draw();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		CMolAnimator m_GameAnimator;                      /**< ���ڶ�ȡ�������� */
		std::string m_AnimatorPath;                       /**< ����·�� */
		CMolDimension2d<s32> m_AnimSize;                  /**< �����߿� */
		int m_AnimFrameCount;                             /**< ����֡�� */
		int m_Speed;                                      /**< ���������ٶ� */
		int m_CurFrameIndex;                            /**< ��ǰ������ʾ֡���� */
		DWORD m_CurTime;                                /**< ���ڿ��ƶ����Ĳ��� */
		bool m_isPlay;                                    /**< �Ƿ񲥷Ŷ��� */
		bool m_isLoop;                                    /**< �Ƿ�ѭ�����Ŷ��� */
		int m_loopCount;                                  /**< ѭ������ */
		int m_curPlayCount;                               /**< ��ǰ���Ŵ��� */

		std::vector<GameFrame> m_FrameList;                /**< ����֡�б� */
	};

	//}
//}

#endif
