#ifndef _MOLE2D_BASE_FONT_H_
#define _MOLE2D_BASE_FONT_H_

/** 
* Mole2d ͼ������
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
 * ��������ʵ����
 */
class CMolGUIBaseFont
{
public:
	/// ���ַ���
	virtual void draw(const char* text,const CMolRect<s32>& position,
		CMolColor color,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0) = 0;
	/// ��ʾ����ַ���
	virtual void drawf(const char* text,const CMolRect<s32>& position,
		CMolColor textcol,CMolColor figurecol,bool hcenter=false,bool vcenter=false,
		const CMolRect<s32>* clip=0) = 0; 
	/// �õ�ָ���ַ����ĸ߿�
	virtual CMolDimension2d<s32> getDimension(const wchar_t* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,255,255,255)) const  = 0;
	/// �õ�ָ���ַ����ĸ߿�
	virtual CMolDimension2d<s32> getTextDimension(const char* text,bool isFigure=false,CMolColor textcol=CMolColor(255,255,255,255),CMolColor figurecol=CMolColor(255,255,255,255)) = 0;
	/// �õ�ָ���ַ����ַ����е�λ��
	virtual s32 getCharacterFromPos(const wchar_t* text,s32 pixel_x) const  = 0;
	/// �����ַ�֮��ļ��
	virtual void setKerningWidth(s32 kerning) = 0;
	/// �����ַ�֮��ļ��
	virtual void setKerningHeight(s32 kerning) = 0;
	/// �õ�ָ���ַ�����һ��ָ���ַ�֮��Ŀ��
	virtual s32 getKeringWidth(const wchar_t* thisLetter=0,const wchar_t* previousLetter=0) const = 0;
	/// �����ַ�֮��ľ���
	virtual s32 getKerningHeight() const = 0;
};

////}
//}

#endif