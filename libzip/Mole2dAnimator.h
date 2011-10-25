#ifndef MOLE2D_ANIMATOR_H_INCLUDE
#define MOLE2D_ANIMATOR_H_INCLUDE

/**
 * Mole2d ��Ϸ����
 *
 * ��������ڲ�������ϵͳ�����еĶ���
 */

#include <string>
#include <vector>

#define CHUNK 16384

typedef unsigned char FAR MBytef;

/** 
 * ����������
 */
class CMolAnimator
{
public:
	/** 
	 * ����ʹ�õĶ���ṹ
	 */
	struct Point 
	{
		Point():x(0),y(0) {}
		Point(int _x,int _y):x(_x),y(_y) {}

		int x,y;                                // ��������
	};

	/**
	* ѹ����ͷ�ṹ
	*/
	struct FileHeader
	{
		char marker[3];                         // �ļ���ʶ "S","P","R"
		int files_count;                        // �ļ�����

		int width,height;                       // �����߿�
		int speed;                              // �������ŵ��ٶ�
	};

	/**
	* ����֡�ṹ
	*/
	struct FrameStruct
	{
		char  filename[256];                            // �ļ���������
		int startx,starty;                              // ��֡ͼ��Ŀ�ʼ��ʾλ��
		bool isDisplay;                                 // �Ƿ�Ҫ��ʾ��֡ͼ��

		unsigned long startposition;                    // �ļ�������ѹ�����еĿ�ʼλ��

		unsigned long uncompressed_size;                // �������ļ�����
		unsigned long compressed_size;                  // ѹ������ļ�����
	};

	/// ���캯��
	CMolAnimator();
	/// ��������
	~CMolAnimator();

	/// �õ���ǰ����·��
	inline std::string GetCurrentPath(void) { return m_CurrentPath + "\\"; }
	/// ���õ�ǰ����·��
	inline void SetCurrentPath(std::string path) { m_CurrentPath = path; }
	/// ��ָ��·���Ķ����ļ�(�򿪵Ķ���·�������Ǿ���·��)
	bool OpenAnimator(std::string filepath);
	/// ���浱ǰ�����ļ�(����Ķ���·�������Ǿ���·��)
	bool SaveAnimator(std::string filepath);
	/// ���ָ����ͼƬ��������(�򿪵�ͼƬ·�������Ǿ���·��)
	bool AddImage(std::string filepath);
	/// �ر��ļ�
	void CloseAnimator();

	/// ��ѹ�����ļ���Ŀ¼��
	bool UncompressAllFilesToDirection(std::string path);
	/// �õ�ָ��֡��ͼ������
	unsigned char* GetFrame(int index,unsigned long* length);
	/// ���ö����ĸ߿�
	void SetAnimWidthAndHeight(int w,int h);
	/// ���ö������ŵ��ٶ�
	inline void SetSpeed(int s) { m_Header.speed = s; }
	/// �õ��������ŵ��ٶ�
	inline int GetSpeed(void) { return m_Header.speed; }
	/// �õ������Ŀ��
	inline int GetAnimWidth(void) { return m_Header.width; }
	/// �õ������ĸ߶�
	inline int GetAnimHeight(void) { return m_Header.height; }
	/// ����ָ������֡����ʾλ��
	void SetFrameStartPos(int index,CMolAnimator::Point pos);
	/// �õ�ָ������֡����ʾλ��
	CMolAnimator::Point GetFrameStartPos(int index);
	/// �õ�ָ��֡������
	CMolAnimator::FrameStruct* GetFrameInfo(int index);
	/// �õ���ǰ����֡��
	inline int GetFrameCount(void) { return (int)m_FrameList.size(); }
	/// �����ǰ���������е�֡
	inline void ClearAllFrames(void) { m_FrameList.clear(); }

private:
	/// ����ѹ���ƶ����ļ����ƶ��İ��ļ���
	int def(FILE *source, FILE *dest,unsigned long *size,int level,bool iswrite=true);
	/// ���ڽ�ѹѹ�����е����е��ļ�
	int inf(FILE *source, FILE *dest,unsigned long length,unsigned long *clength);
	/// ���ڽ�ѹѹ�����е��ƶ��ļ����ڴ���
	int inf(FILE *source, unsigned char *dest,unsigned long length,unsigned long *clength);
	/// �����ƶ���С���ڴ����ݵ�ָ���ڴ���
	void CopyDataToMemory(MBytef *dest,MBytef *src,unsigned long pos,unsigned long size);
	/// ����ļ�ͷ���ļ��ṹ�鵽�ļ���
	bool AddFileHeaderAndFileStructs(void);
	/// �����ļ�·����������Ӧ��Ŀ¼
	void CreateDirectionByPath(std::string path,std::string filename);
	/// ѹ�����е�ǰϵͳ��ӵ�е������ļ���ѹ������
	bool CompressAllFileInSystem(void);

	/// �Զ����ļ�д�뺯��
	size_t mfwrite(void *data, size_t size,size_t count,FILE *file);
	/// �Զ����ļ���ȡ����
	size_t mfread(void *data,size_t size,size_t count,FILE *file);
	/// ��������
	void Encrypto(unsigned char *data,unsigned long length);
	/// ��������
	void Decrypto(unsigned char *data,unsigned long length);

private:
	std::string                             m_FileName;     // �����ļ��������ļ���
	std::string                             m_CurrentPath;  // ��ǰ�����·��

	FileHeader                              m_Header;       // ѹ������ͷ
	std::vector<FrameStruct>                m_FrameList;    // ����֡�б�

	FILE*                                   m_File;         // �ļ���д
};

#endif