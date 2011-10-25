#ifndef _MOLE2D_TTF_FONT_H_
#define _MOLE2D_TTF_FONT_H_

/**
* Mole2D 游戏引擎
*
* 这个文件属于整个引擎的一部分
*
* 作者：akinggw
* 建立时间： 2008.6.24
*/

#include "ft2build.h"
#include "freetype/freetype.h"

#include <vector>

#include "Mole2d.h"

#include "Mole2dBaseFont.h"

#define xmalloc(s) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (s))
#define xfree(p)   HeapFree (GetProcessHeap(), 0, (p))

//namespace mole2d
//{
//namespace graphics
//{

class CMolBaseFrame;

/**
* ttf面类
*/
class CMolGUITTFace
{
public:
	/// 构造函数
	CMolGUITTFace();
	/// 析够函数
	virtual ~CMolGUITTFace();

	bool              loaded;
	FT_Library        library;
	FT_Face           face;

	/// 从文件中导入ttf字体
	bool load(const c8* filename);
};

/**
* TTF每个字
*/
class CMolGUITTGlyph
{
public:
	bool cached;
	CMolBaseFrame* Driver;
	FT_Library  library;

	/// 构造函数
	CMolGUITTGlyph();
	/// 析够函数
	virtual ~CMolGUITTGlyph();
	/// 初始
	void init();
	/// 根据文字ID得到相应的纹理数据
	void cache(u32 idx,bool isFigure,CMolColor textcol,CMolColor figurecol);
	FT_Face *face;
	u32 size;
	u32 top;
	u32 left;
	u32 texw;
	u32 texh;
	u32 imgw;
	u32 imgh;
	HTEXTURE tex;
	u32 top16;
	u32 left16;
	u32 texw16;
	u32 texh16;
	u32 imgw16;
	u32 imgh16;
	HTEXTURE tex16;
	s32 offset;
	u8 *image;
};

/**
* TTF字体实现类
*/
class CMolGUITTFont : public CMolGUIBaseFont
{
public:
	u32 size;

	/// 构造函数
	CMolGUITTFont(CMolBaseFrame *env);
	/// 析够函数
	virtual ~CMolGUITTFont();

	/// 导入一个TTF字体
	bool attach(CMolGUITTFace *Face,u32 size);
	/// 画字符串
	virtual void draw(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// 画字符串
	virtual void draw(const wchar_t* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// 显示描边字符串
	virtual void drawf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol=CMolColor(255,30,30,30),bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0); 
	/// 得到指定字符串的高宽
	virtual CMolDimension2d<s32> getDimension(const wchar_t* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30)) const;
	/// 得到指定字符串的高宽
	virtual CMolDimension2d<s32> getTextDimension(const char* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30));
	/// 得到指定字符在字符串中的位置
	virtual s32 getCharacterFromPos(const wchar_t* text,s32 pixel_x) const;
	/// 设置字符之间的间距
	virtual void setKerningWidth(s32 kerning);
	/// 设置字符之间的间距
	virtual void setKerningHeight(s32 kerning);
	/// 得到指定字符到另一个指定字符之间的宽度
	virtual s32 getKeringWidth(const wchar_t* thisLetter=0,const wchar_t* previousLetter=0) const;
	/// 返回字符之间的距离
	virtual s32 getKerningHeight() const;

	bool AntiAlias;
	bool TransParency;
	bool attached;

private:
	/// 转换char到wchar_t类型
	wchar_t *  str2wstrptr(const char *pStr);
	/// 转换wchar_t到char类型
	char*  wstr2strptr(const wchar_t *pStr);
	/// 得到字符的宽度
	s32 getWidthFromCharacter(const wchar_t c,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30)) const;
	/// 根据字符得到字符在字库中的ID
	u32 getGlyphByChar(const wchar_t c,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30)) const;
	CMolBaseFrame* Driver;
	mutable std::vector< CMolGUITTGlyph > Glyphs,GlyphsFigure;
	CMolGUITTFace *tt_face;

	s32 GlobalKerningWidth,GlobalKerningHeight;
	wchar_t pWideCharStr[102400];
};

//}
//}

#endif
