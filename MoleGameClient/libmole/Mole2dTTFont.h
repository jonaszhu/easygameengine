#ifndef _MOLE2D_TTF_FONT_H_
#define _MOLE2D_TTF_FONT_H_

/**
* Mole2D ��Ϸ����
*
* ����ļ��������������һ����
*
* ���ߣ�akinggw
* ����ʱ�䣺 2008.6.24
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
* ttf����
*/
class CMolGUITTFace
{
public:
	/// ���캯��
	CMolGUITTFace();
	/// ��������
	virtual ~CMolGUITTFace();

	bool              loaded;
	FT_Library        library;
	FT_Face           face;

	/// ���ļ��е���ttf����
	bool load(const c8* filename);
};

/**
* TTFÿ����
*/
class CMolGUITTGlyph
{
public:
	bool cached;
	CMolBaseFrame* Driver;
	FT_Library  library;

	/// ���캯��
	CMolGUITTGlyph();
	/// ��������
	virtual ~CMolGUITTGlyph();
	/// ��ʼ
	void init();
	/// ��������ID�õ���Ӧ����������
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
* TTF����ʵ����
*/
class CMolGUITTFont : public CMolGUIBaseFont
{
public:
	u32 size;

	/// ���캯��
	CMolGUITTFont(CMolBaseFrame *env);
	/// ��������
	virtual ~CMolGUITTFont();

	/// ����һ��TTF����
	bool attach(CMolGUITTFace *Face,u32 size);
	/// ���ַ���
	virtual void draw(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// ���ַ���
	virtual void draw(const wchar_t* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0);
	/// ��ʾ����ַ���
	virtual void drawf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol=CMolColor(255,30,30,30),bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0); 
	/// �õ�ָ���ַ����ĸ߿�
	virtual CMolDimension2d<s32> getDimension(const wchar_t* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30)) const;
	/// �õ�ָ���ַ����ĸ߿�
	virtual CMolDimension2d<s32> getTextDimension(const char* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30));
	/// �õ�ָ���ַ����ַ����е�λ��
	virtual s32 getCharacterFromPos(const wchar_t* text,s32 pixel_x) const;
	/// �����ַ�֮��ļ��
	virtual void setKerningWidth(s32 kerning);
	/// �����ַ�֮��ļ��
	virtual void setKerningHeight(s32 kerning);
	/// �õ�ָ���ַ�����һ��ָ���ַ�֮��Ŀ��
	virtual s32 getKeringWidth(const wchar_t* thisLetter=0,const wchar_t* previousLetter=0) const;
	/// �����ַ�֮��ľ���
	virtual s32 getKerningHeight() const;

	bool AntiAlias;
	bool TransParency;
	bool attached;

private:
	/// ת��char��wchar_t����
	wchar_t *  str2wstrptr(const char *pStr);
	/// ת��wchar_t��char����
	char*  wstr2strptr(const wchar_t *pStr);
	/// �õ��ַ��Ŀ��
	s32 getWidthFromCharacter(const wchar_t c,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,30,30,30)) const;
	/// �����ַ��õ��ַ����ֿ��е�ID
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
