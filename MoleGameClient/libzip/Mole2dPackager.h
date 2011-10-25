#ifndef PACKAGER_H_INCLUDED
#define PACKAGER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

/**
 * Mole2d ��Ϸ����
 *
 * ����ļ����������е�ѹ�����֣���ʹ����stl�е�map������
 * ���е�ѹ���ļ���Ŀ¼���ݲ�֪�����ֹ���ʽ����Դ��ȡ���ٶȵ�Ӱ��
 */
//namespace mole2d
//{
//namespace comp
//{

#define CHUNK 16384

typedef unsigned char FAR MBytef;

/**
 * ѹ���ඨ��
 */
class CMolPackager
{
public:
	/**
	 * ��ǰѹ������ʹ����;
	 */
	enum UseType
	{
	   COMPRESS = 0,
	   UNCOMPRESS
	};

    /**
     * �ļ��ṹ
     */
    struct FileStruct
    {
       char  filename[512];               // �ļ���������

       unsigned long startposition;                    // �ļ�������ѹ�����еĿ�ʼλ��

       unsigned long uncompressed_size;                // �������ļ�����
       unsigned long compressed_size;                  // ѹ������ļ�����
    };

    /**
     * ѹ����ͷ�ṹ
     */
    struct FileHeader
    {
       char marker[3];                         // �ļ���ʶ "P","A","K"
       int files_count;                        // �ļ�����
    };

    /// �������Ĺ��캯��
    CMolPackager(UseType type=UNCOMPRESS);
    /// ��������
    ~CMolPackager();

	/// �ر��ļ�
	void Close(void);

	/// �õ�ѹ�����ߵ�ʹ�÷�ʽ
	UseType GetUseType();

	/// ��������Ҫ��ѹ��ѹ�������ļ���
	bool CreateNewPakFile(std::string inputfile,std::string outputfile);
	/// ѹ�����е�ǰϵͳ��ӵ�е����е������ļ���ѹ������
	bool CompressAllFileInSystem(void);
	/// ѹ��ϵͳ���ƶ����ļ���ѹ�����У����ﺯ����Ҫ��ѹ��������ʹ�ã�
	bool CompressFileByNameToSystem(std::string filename);

    /// ��һ��ѹ�����ļ����ڽ�ѹ
    bool OpenCompressedFile(std::string filename);
	/// ��ѹ�ƶ��ļ���Ŀ¼��
	bool UncompressFileToDirection(std::string path,std::string filename);
	/// �õ��ƶ��ļ���ѹ������
	unsigned char* UncompressFileToMemory(std::string filename,unsigned long* length);
	/// ��ѹ�����ļ���Ŀ¼��
	bool UncompressAllFilesToDirection(std::string path);
	/// ����ƶ��ļ��Ƿ����
	bool IsExist(std::string filename);

	/// �õ���ǰѹ�����е������ļ���Ϣ
	std::map<std::string,CMolPackager::FileStruct> getFilesInfo() { return m_FileList; }
	/// �õ���ǰϵͳ�ܵ��ļ�����
	int GetFilesCount() { return (int)m_FileList.size(); }

private:
	/// ��������Ҫѹ�����ļ����ļ��У���Ҫ�õ����ǵ��ļ����Ⱥ��ļ�����
	void AnalyseFileOrFileCurrent(std::string path,std::string relativepath,std::string file);
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

	/// �Զ����ļ�д�뺯��
	size_t mfwrite(void *data, size_t size,size_t count,FILE *file);
	/// �Զ����ļ���ȡ����
	size_t mfread(void *data,size_t size,size_t count,FILE *file);
	/// ��������
	void Encrypto(unsigned char *data,unsigned long length);
	/// ��������
	void Decrypto(unsigned char *data,unsigned long length);

private:
    std::string                             m_FileName;     // Ҫѹ�����ļ����ļ���
	std::string                             m_CurrentPath;  // ��ǰѹ�������·��
	std::string                             m_CompressPath; // ��ǰ��ѹ��·��
	UseType                                 m_UseType;      // ʹ�÷�ʽ

    FileHeader                              m_Header;       // ѹ������ͷ
    std::map<std::string,FileStruct>        m_FileList;     // �ļ��б�

	FILE*                                   m_File;         // �ļ���д
};

//}
//}

#endif // PACKAGER_H_INCLUDED
