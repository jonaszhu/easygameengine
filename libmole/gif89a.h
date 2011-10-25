#if !defined(_GIF89A_)
#define _GIF89A_

#include <fstream>
#include <windows.h>

typedef struct
{	BOOL active;
	UINT disposalMethod;
	BOOL userInputFlag;
	BOOL trsFlag;
	WORD delayTime;
	UINT trsColorIndex;
}GCTRLEXT;

typedef struct 
{	WORD imageLPos;
	WORD imageTPos;
	WORD imageWidth;
	WORD imageHeight;
	BOOL lFlag;
	BOOL interlaceFlag;
	BOOL sortFlag;
	UINT lSize;
	BYTE *pColorTable;
	BYTE *dataBuf;
	GCTRLEXT ctrlExt;
}FRAME;
typedef FRAME *LPFRAME;
typedef const FRAME *LPCFRAME;

typedef struct 
{	UINT frames;
	WORD scrWidth,scrHeight;
	BOOL gFlag;
	UINT colorRes;
	BOOL gSort;
	UINT gSize;
	UINT BKColorIdx;
	UINT pixelAspectRatio;
	BYTE *gColorTable;
}GLOBAL_INFO;
typedef GLOBAL_INFO *LPGLOBAL_INFO;
typedef const GLOBAL_INFO *LPCGLOBAL_INFO;

typedef struct
{	UINT len;
	unsigned char* p;
}STRING_TABLE_ENTRY;

class CGif89a
{
private:
	std::ifstream ifs;
	char version[4];
	BOOL error;
	BOOL opened;
	BOOL inMem;
	BYTE gColorTable[256*3];
	BYTE lColorTable[256*3];
	std::streampos dataStart;
	FRAME *allFrames;
	UINT curIndex;
private:
	UINT checkFrames(std::ifstream&);
	BOOL getAllFrames(std::ifstream&);
	BOOL extractData(FRAME* f,std::ifstream&);
	BOOL initStrTable(STRING_TABLE_ENTRY* strTable,UINT rootSize);
	BOOL addStrTable(STRING_TABLE_ENTRY* strTable,UINT addIdx,UINT idx,unsigned char c);
private:
	GLOBAL_INFO gInfo;
	FRAME curFrame;
	GCTRLEXT ctrlExt;
public:
	int		getNumFrame()		{return gInfo.frames;}
	BYTE*		getColorTable(int index);//		{return gInfo.frames;}
	LPCFRAME getFrame(int index);
	CGif89a();
	CGif89a(LPCSTR fileName,BOOL inMem);
	~CGif89a();
	BOOL operator!();
	BOOL open(LPCSTR fileName,BOOL inMem);
	void close();
	LPCSTR getVer();
	LPCFRAME getNextFrame();
	LPCGLOBAL_INFO getGlobalInfo();
};

#endif