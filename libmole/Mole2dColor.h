#ifndef _MOLE2D_COLOR_H
#define _MOLE2D_COLOR_H

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.10
*/

#include "Mole2dCommon.h"

//namespace mole2d
//{
//namespace graphics
//{

/**
 * 32λARGB��ɫ��
 * �����ɫֵ��͸������ɫ����ɫ����ɫ��32λ����ʽ�洢�����ǵ�ȡֵ
 * ��Χ�� 0 �� 255.
 */
class MOLEXPORT CMolColor
{
    public:
        /// ���캯��
        CMolColor() {}
        /// ���캯��
        CMolColor(u32 a,u32 r, u32 g,u32 b)
            : color(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)) {}
        /// ���캯��
        CMolColor(u32 clr)
            : color(clr) {}

        /// �õ���ɫֵ�е�͸������
        u32 getAlpha() const { return color >> 24; }
        /// �õ���ɫֵ�еĺ�ɫ����
        u32 getRed() const { return (color >> 16) & 0xff; }
        /// �õ���ɫֵ�е���ɫ����
        u32 getGreen() const { return (color >> 8) & 0xff; }
        /// �õ���ɫֵ�е���ɫ����
        u32 getBlue() const { return color & 0xff; }
        /// �õ���ɫ������
        f32 getLuminance() const
        {
            return 0.3f*getRed() + 0.59f*getGreen() + 0.11f*getBlue();
        }
        /// �õ���ɫ��ƽ��ֵ
        u32 getAverage() const
        {
            return ( getRed() + getGreen() + getBlue() ) / 3;
        }
        /// ������ɫ��͸������
        void setAlpha(u32 a) { color = ((a & 0xff) << 24) | (color & 0x00ffffff); }
        /// ������ɫ�ĺ�ɫ����
        void setRed(u32 r) { color = ((r & 0xff) << 16) | (color & 0xff00ffff); }
        /// ������ɫ����ɫ����
        void setGreen(u32 g) { color = ((g & 0xff) << 8) | (color & 0xffff00ff); }
        /// ������ɫ����ɫ����
        void setBlue(u32 b) { color = (b & 0xff) | (color & 0xffffff00); }

        /// ������ɫ
        void set(u32 a,u32 r,u32 g,u32 b)
        {
            color = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
        }
        /// ������ɫ
        void set(u32 col) { color = col; }

        /// ���ڲ���
        bool operator==(const CMolColor& other) const { return other.color == color; }
        /// �����ڲ���
        bool operator!=(const CMolColor& other) const { return other.color != color; }
        /// С�ڲ���
        bool operator<(const CMolColor& other) const { return (color < other.color); }

		u32 color;                  /**< A8R8G8B8 ��ʽ����ɫ */
};

//}
//}

#endif
