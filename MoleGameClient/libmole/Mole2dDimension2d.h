#ifndef _MOLE2D_DIMENSION2D_H
#define _MOLE2D_DIMENSION2D_H

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

template<class T>
class CMolDimension2d
{
public:
	/// 构造函数
	CMolDimension2d() : Width(0),Height(0) {}
	/// 构造函数
	CMolDimension2d(const T& width,const T& height)
		: Width(width),Height(height) {}

	/// 等于操作
	bool operator==(const CMolDimension2d<T>& other) const
	{
		return Width == other.Width && Height == other.Height;
	}
	/// 不等于操作
	bool operator!=(const CMolDimension2d<T>& other) const
	{
		return !(*this == other);
	}
	/// 设置新的参数
	CMolDimension2d<T>& set(const T& width,const T& height)
	{
		Width = width;
		Height = height;
		return *this;
	}
	/// 除以操作
	CMolDimension2d<T>& operator/=(const T& scale)
	{
		Width /= scale;
		Height /= scale;
		return *this;
	}
	/// 除操作
	CMolDimension2d<T> operator/(const T& scale) const
	{
		return CMolDimension2d<T>(Width/scale,Height/scale);
	}
	/// 乘以操作
	CMolDimension2d<T> operator*(const T& scale) const
	{
		return CMolDimension2d<T>(Width/scale,Height*scale);
	}
	/// 得到范围值
	T getArea() const
	{
		return Width*Height;
	}

	T Width;           /**< 区域的宽度 */
	T Height;          /**< 区域的高度 */
};

//}
//}

#endif
