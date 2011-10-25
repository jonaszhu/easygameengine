#ifndef MOLE2D_ANIMATOR_H_INCLUDE
#define MOLE2D_ANIMATOR_H_INCLUDE

/**
 * Mole2d 游戏引擎
 *
 * 这个类用于操作我们系统中所有的动画
 */

#include <string>
#include <vector>

#define CHUNK 16384

typedef unsigned char FAR MBytef;

/** 
 * 动画操作类
 */
class CMolAnimator
{
public:
	/** 
	 * 动画使用的顶点结构
	 */
	struct Point 
	{
		Point():x(0),y(0) {}
		Point(int _x,int _y):x(_x),y(_y) {}

		int x,y;                                // 顶点坐标
	};

	/**
	* 压缩包头结构
	*/
	struct FileHeader
	{
		char marker[3];                         // 文件标识 "S","P","R"
		int files_count;                        // 文件数量

		int width,height;                       // 动画高宽
		int speed;                              // 动画播放的速度
	};

	/**
	* 动画帧结构
	*/
	struct FrameStruct
	{
		char  filename[256];                            // 文件完整名称
		int startx,starty;                              // 这帧图像的开始显示位置
		bool isDisplay;                                 // 是否要显示这帧图像

		unsigned long startposition;                    // 文件在整个压缩包中的开始位置

		unsigned long uncompressed_size;                // 正常的文件长度
		unsigned long compressed_size;                  // 压缩后的文件长度
	};

	/// 构造函数
	CMolAnimator();
	/// 析构函数
	~CMolAnimator();

	/// 得到当前程序路径
	inline std::string GetCurrentPath(void) { return m_CurrentPath + "\\"; }
	/// 设置当前程序路径
	inline void SetCurrentPath(std::string path) { m_CurrentPath = path; }
	/// 打开指定路径的动画文件(打开的动画路径必须是绝对路径)
	bool OpenAnimator(std::string filepath);
	/// 保存当前动画文件(保存的动画路径必须是绝对路径)
	bool SaveAnimator(std::string filepath);
	/// 添加指定的图片到动画中(打开的图片路径必须是绝对路径)
	bool AddImage(std::string filepath);
	/// 关闭文件
	void CloseAnimator();

	/// 解压所有文件到目录中
	bool UncompressAllFilesToDirection(std::string path);
	/// 得到指定帧的图像数据
	unsigned char* GetFrame(int index,unsigned long* length);
	/// 设置动画的高宽
	void SetAnimWidthAndHeight(int w,int h);
	/// 设置动画播放的速度
	inline void SetSpeed(int s) { m_Header.speed = s; }
	/// 得到动画播放的速度
	inline int GetSpeed(void) { return m_Header.speed; }
	/// 得到动画的宽度
	inline int GetAnimWidth(void) { return m_Header.width; }
	/// 得到动画的高度
	inline int GetAnimHeight(void) { return m_Header.height; }
	/// 设置指定动画帧的显示位置
	void SetFrameStartPos(int index,CMolAnimator::Point pos);
	/// 得到指定动画帧的显示位置
	CMolAnimator::Point GetFrameStartPos(int index);
	/// 得到指定帧的数据
	CMolAnimator::FrameStruct* GetFrameInfo(int index);
	/// 得到当前动画帧数
	inline int GetFrameCount(void) { return (int)m_FrameList.size(); }
	/// 清除当前动画中所有的帧
	inline void ClearAllFrames(void) { m_FrameList.clear(); }

private:
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
	/// 压缩所有当前系统中拥有的所有文件到压缩包中
	bool CompressAllFileInSystem(void);

	/// 自定义文件写入函数
	size_t mfwrite(void *data, size_t size,size_t count,FILE *file);
	/// 自定义文件读取函数
	size_t mfread(void *data,size_t size,size_t count,FILE *file);
	/// 加密数据
	void Encrypto(unsigned char *data,unsigned long length);
	/// 解密数据
	void Decrypto(unsigned char *data,unsigned long length);

private:
	std::string                             m_FileName;     // 动画文件的完整文件名
	std::string                             m_CurrentPath;  // 当前程序的路径

	FileHeader                              m_Header;       // 压缩包的头
	std::vector<FrameStruct>                m_FrameList;    // 动画帧列表

	FILE*                                   m_File;         // 文件读写
};

#endif