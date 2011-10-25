#ifndef PACKAGER_H_INCLUDED
#define PACKAGER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

/**
 * Mole2d 游戏引擎
 *
 * 这个文件属于引擎中的压缩部分，我使用了stl中的map来管理
 * 所有的压缩文件和目录，暂不知道这种管理方式对资源读取的速度的影响
 */
//namespace mole2d
//{
//namespace comp
//{

#define CHUNK 16384

typedef unsigned char FAR MBytef;

/**
 * 压缩类定义
 */
class CMolPackager
{
public:
	/**
	 * 当前压缩包的使用用途
	 */
	enum UseType
	{
	   COMPRESS = 0,
	   UNCOMPRESS
	};

    /**
     * 文件结构
     */
    struct FileStruct
    {
       char  filename[512];               // 文件完整名称

       unsigned long startposition;                    // 文件在整个压缩包中的开始位置

       unsigned long uncompressed_size;                // 正常的文件长度
       unsigned long compressed_size;                  // 压缩后的文件长度
    };

    /**
     * 压缩包头结构
     */
    struct FileHeader
    {
       char marker[3];                         // 文件标识 "P","A","K"
       int files_count;                        // 文件数量
    };

    /// 带参数的构造函数
    CMolPackager(UseType type=UNCOMPRESS);
    /// 析构函数
    ~CMolPackager();

	/// 关闭文件
	void Close(void);

	/// 得到压缩工具的使用方式
	UseType GetUseType();

	/// 设置我们要解压的压缩包的文件名
	bool CreateNewPakFile(std::string inputfile,std::string outputfile);
	/// 压缩所有当前系统中拥有的所有的所有文件到压缩包中
	bool CompressAllFileInSystem(void);
	/// 压缩系统中制定的文件到压缩包中（这里函数主要在压缩工具中使用）
	bool CompressFileByNameToSystem(std::string filename);

    /// 打开一个压缩包文件用于解压
    bool OpenCompressedFile(std::string filename);
	/// 解压制定文件到目录中
	bool UncompressFileToDirection(std::string path,std::string filename);
	/// 得到制定文件的压缩数据
	unsigned char* UncompressFileToMemory(std::string filename,unsigned long* length);
	/// 解压所有文件到目录中
	bool UncompressAllFilesToDirection(std::string path);
	/// 检测制定文件是否存在
	bool IsExist(std::string filename);

	/// 得到当前压缩包中的所有文件信息
	std::map<std::string,CMolPackager::FileStruct> getFilesInfo() { return m_FileList; }
	/// 得到当前系统总的文件数量
	int GetFilesCount() { return (int)m_FileList.size(); }

private:
	/// 分析我们要压缩的文件或文件夹，主要得到它们的文件长度和文件个数
	void AnalyseFileOrFileCurrent(std::string path,std::string relativepath,std::string file);
    /// 用于压缩制定的文件到制定的包文件中
    int def(FILE *source, FILE *dest,unsigned long *size,int level,bool iswrite=true);
    /// 用于解压压缩包中的所有的文件
    int inf(FILE *source, FILE *dest,unsigned long length,unsigned long *clength);
	/// 用于解压压缩包中的制定文件到内存中
	int inf(FILE *source, unsigned char *dest,unsigned long length,unsigned long *clength);
    /// 拷贝制定大小的内存数据到指定内存中
    void CopyDataToMemory(MBytef *dest,MBytef *src,unsigned long pos,unsigned long size);
	/// 添加文件头和文件结构组到文件中
	bool AddFileHeaderAndFileStructs(void);
	/// 根据文件路径名建立相应的目录
	void CreateDirectionByPath(std::string path,std::string filename);

	/// 自定义文件写入函数
	size_t mfwrite(void *data, size_t size,size_t count,FILE *file);
	/// 自定义文件读取函数
	size_t mfread(void *data,size_t size,size_t count,FILE *file);
	/// 加密数据
	void Encrypto(unsigned char *data,unsigned long length);
	/// 解密数据
	void Decrypto(unsigned char *data,unsigned long length);

private:
    std::string                             m_FileName;     // 要压缩的文件或文件包
	std::string                             m_CurrentPath;  // 当前压缩程序的路径
	std::string                             m_CompressPath; // 当前的压缩路径
	UseType                                 m_UseType;      // 使用方式

    FileHeader                              m_Header;       // 压缩包的头
    std::map<std::string,FileStruct>        m_FileList;     // 文件列表

	FILE*                                   m_File;         // 文件读写
};

//}
//}

#endif // PACKAGER_H_INCLUDED
