#ifndef _MOLE2D_POSITION2D_H
#define _MOLE2D_POSITION2D_H

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/

#include "Dimension2d.h"

/**
 * 一个简单的存储2D坐标的类
 */
template<class T>
class CMolPosition2d
{
public:
    /// 构造函数
    CMolPosition2d() : X(0),Y(0) {}
    /// 构造函数
    CMolPosition2d(T x, T y) : X(x),Y(y) {}
    /// 构造函数
    CMolPosition2d(const CMolPosition2d<T>& other)
        : X(other.X),Y(other.Y) {}

    /// 等于操作
    bool operator == (const CMolPosition2d<T>& other) const
    {
        return X == other.X && Y == other.Y;
    }
    /// 不等于操作
    bool operator != (const CMolPosition2d<T>& other) const
    {
        return X != other.X && Y != other.Y;
    }
    const CMolPosition2d<T>& operator+=(const CMolPosition2d<T>& other)
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }
    const CMolPosition2d<T>& operator-=(const CMolPosition2d<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }
    const CMolPosition2d<T>& operator+=(const CMolDimension2d<T>& other)
    {
        X += other.Width;
        Y += other.Height;
        return *this;
    }
    const CMolPosition2d<T>& operator-=(const CMolDimension2d<T>& other)
    {
        X -= other.Width;
        Y -= other.Height;
        return *this;
    }
    CMolPosition2d<T> operator-(const CMolPosition2d<T>& other) const
    {
        return CMolPosition2d<T>(X-other.X,Y-other.Y);
    }
    CMolPosition2d<T> operator+(const CMolPosition2d<T>& other) const
    {
        return CMolPosition2d<T>(X+other.X,Y+other.Y);
    }
    CMolPosition2d<T> operator*(const CMolPosition2d<T>& other) const
    {
        return CMolPosition2d<T>(X*other.X,Y*other.Y);
    }
    CMolPosition2d<T> operator+(const CMolDimension2d<T>& other) const
    {
        return CMolPosition2d<T>(X+other.Width,Y+other.Height);
    }
    CMolPosition2d<T> operator-(const CMolDimension2d<T>& other) const
    {
        return CMolPosition2d<T>(X-other.Width,Y-other.Height);
    }
    const CMolPosition2d<T>& operator=(const CMolPosition2d<T>& other)
    {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    T X;                /**< 坐标X */
    T Y;                /**< 坐标Y */
};

#endif
