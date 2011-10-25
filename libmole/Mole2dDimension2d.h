#ifndef _MOLE2D_DIMENSION2D_H
#define _MOLE2D_DIMENSION2D_H

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

template<class T>
class CMolDimension2d
{
public:
	/// ���캯��
	CMolDimension2d() : Width(0),Height(0) {}
	/// ���캯��
	CMolDimension2d(const T& width,const T& height)
		: Width(width),Height(height) {}

	/// ���ڲ���
	bool operator==(const CMolDimension2d<T>& other) const
	{
		return Width == other.Width && Height == other.Height;
	}
	/// �����ڲ���
	bool operator!=(const CMolDimension2d<T>& other) const
	{
		return !(*this == other);
	}
	/// �����µĲ���
	CMolDimension2d<T>& set(const T& width,const T& height)
	{
		Width = width;
		Height = height;
		return *this;
	}
	/// ���Բ���
	CMolDimension2d<T>& operator/=(const T& scale)
	{
		Width /= scale;
		Height /= scale;
		return *this;
	}
	/// ������
	CMolDimension2d<T> operator/(const T& scale) const
	{
		return CMolDimension2d<T>(Width/scale,Height/scale);
	}
	/// ���Բ���
	CMolDimension2d<T> operator*(const T& scale) const
	{
		return CMolDimension2d<T>(Width/scale,Height*scale);
	}
	/// �õ���Χֵ
	T getArea() const
	{
		return Width*Height;
	}

	T Width;           /**< ����Ŀ�� */
	T Height;          /**< ����ĸ߶� */
};

//}
//}

#endif
