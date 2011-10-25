#ifndef _MOLE2D_BASE_FONT_H_
#define _MOLE2D_BASE_FONT_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/

#include "Mole2d.h"

//namespace mole2d
//{
//namespace graphics
//{

/**
 * 基本字体实现类
 */
class CMolGUIBaseFont
{
public:
	/// 画字符串
	virtual void draw(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0) = 0;
	/// 显示描边字符串
	virtual void drawf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0) = 0; 
	/// 得到指定字符串的高宽
	virtual CMolDimension2d<s32> getDimension(const wchar_t* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,255,255,255)) const  = 0;
	/// 得到指定字符串的高宽
	virtual CMolDimension2d<s32> getTextDimension(const char* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,255,255,255)) = 0;
	/// 得到指定字符在字符串中的位置
	virtual s32 getCharacterFromPos(const wchar_t* text,s32 pixel_x) const  = 0;
	/// 设置字符之间的间距
	virtual void setKerningWidth(s32 kerning) = 0;
	/// 设置字符之间的间距
	virtual void setKerningHeight(s32 kerning) = 0;
	/// 得到指定字符到另一个指定字符之间的宽度
	virtual s32 getKeringWidth(const wchar_t* thisLetter=0,const wchar_t* previousLetter=0) const = 0;
	/// 返回字符之间的距离
	virtual s32 getKerningHeight() const = 0;
};

////}
//}

#endif