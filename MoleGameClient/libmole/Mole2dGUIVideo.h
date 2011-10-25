#ifndef _MOLE2D_GUI_VIDEO_H_INCLUDE
#define _MOLE2D_GUI_VIDEO_H_INCLUDE

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2010.5.3
*/

#include "Mole2dBaseGUIElement.h"

//#include "libvideo/TheoraPlayer.h"
//#include "libvideo/TheoraDataSource.h"


//namespace mole2d
//{
	//namespace graphics
	//{

	class MOLEXPORT CMolGUIVideo : public CMolBaseGUIElement
	{
	public:
		/// ���캯��
		CMolGUIVideo();
		/// �������Ĺ��캯��
		CMolGUIVideo(CMolBaseFrame* driver,CMolBaseGUIElement* parent,
			int id,std::string caption,CMolRect<int> rect);
		/// ��������
		virtual ~CMolGUIVideo();

		///// ������Ƶ��·��
		//void LoadVideo(std::string path,bool isPlay=false);
		///// �õ���Ƶ��·��
		//inline std::string GetVideoPath(void) { return m_videpath; }
		///// ������Ƶ
		//void Play();
		///// ��ͣ��Ƶ����
		//void Pause();
		///// ֹͣ��Ƶ����
		//void Stop();
		///// ���¿�ʼ������Ƶ
		//void Restart();

		/// ���ؼ�
		virtual void Draw();
		/// ����֮ǰ����
		virtual bool OnProcessPostUpdate();
		/// ���ڴ�����յ����¼�
		virtual bool OnProcessEvent(const CMolEvent& event);
		/// ����ʧ������¼�
		virtual void OnProcessLostFocusEvent(const CMolEvent& event);

	private:
		//HTEXTURE m_FrameTex;                  /**< ֡���� */
		//std::string m_videpath;

		//TheoraVideoClip* clip;                  /**< ��Ƶ���� */
		//TheoraMemoryFileDataSource *mTheoraDataSource;     /**< ���ڴ洢��Ƶ���� */
	};

	//}
//}

#endif
