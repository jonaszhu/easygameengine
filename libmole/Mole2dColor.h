#ifndef _MOLE2D_COLOR_H
#define _MOLE2D_COLOR_H

/** 
* Mole2d 图像引擎
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
 * 32位ARGB颜色类
 * 这个颜色值由透明，红色，绿色和蓝色以32位的形式存储。它们的取值
 * 范围在 0 到 255.
 */
class MOLEXPORT CMolColor
{
    public:
        /// 构造函数
        CMolColor() {}
        /// 构造函数
        CMolColor(u32 a,u32 r, u32 g,u32 b)
            : color(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)) {}
        /// 构造函数
        CMolColor(u32 clr)
            : color(clr) {}

        /// 得到颜色值中的透明部分
        u32 getAlpha() const { return color >> 24; }
        /// 得到颜色值中的红色部分
        u32 getRed() const { return (color >> 16) & 0xff; }
        /// 得到颜色值中的绿色部分
        u32 getGreen() const { return (color >> 8) & 0xff; }
        /// 得到颜色值中的蓝色部分
        u32 getBlue() const { return color & 0xff; }
        /// 得到颜色的亮度
        f32 getLuminance() const
        {
            return 0.3f*getRed() + 0.59f*getGreen() + 0.11f*getBlue();
        }
        /// 得到颜色的平均值
        u32 getAverage() const
        {
            return ( getRed() + getGreen() + getBlue() ) / 3;
        }
        /// 设置颜色的透明部分
        void setAlpha(u32 a) { color = ((a & 0xff) << 24) | (color & 0x00ffffff); }
        /// 设置颜色的红色部分
        void setRed(u32 r) { color = ((r & 0xff) << 16) | (color & 0xff00ffff); }
        /// 设置颜色的绿色部分
        void setGreen(u32 g) { color = ((g & 0xff) << 8) | (color & 0xffff00ff); }
        /// 设置颜色的蓝色部分
        void setBlue(u32 b) { color = (b & 0xff) | (color & 0xffffff00); }

        /// 设置颜色
        void set(u32 a,u32 r,u32 g,u32 b)
        {
            color = (((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff));
        }
        /// 设置颜色
        void set(u32 col) { color = col; }

        /// 等于操作
        bool operator==(const CMolColor& other) const { return other.color == color; }
        /// 不等于操作
        bool operator!=(const CMolColor& other) const { return other.color != color; }
        /// 小于操作
        bool operator<(const CMolColor& other) const { return (color < other.color); }

		u32 color;                  /**< A8R8G8B8 格式的颜色 */
};

//}
//}

#endif
