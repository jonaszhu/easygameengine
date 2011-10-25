#ifndef _MOLE2D_RECT_H
#define _MOLE2D_RECT_H

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/

#include "Mole2dDimension2d.h"
#include "Mole2dPosition2d.h"

//namespace mole2d
//{
//namespace graphics
//{

/**
 * 矩形模板类
 */
template<class T>
class CMolRect
{
    public:
        /// 构造函数
        CMolRect() : UpperLeftCorner(0,0),LowerRightCorner(0,0) {}
        /// 构造函数
        CMolRect(T x,T y,T x2,T y2)
        : UpperLeftCorner(x,y),LowerRightCorner(x2,y2) {}
        /// 构造函数
        CMolRect(const CMolPosition2d<T>& upperLeft,const CMolPosition2d<T>& lowerRight)
        : UpperLeftCorner(upperLeft),LowerRightCorner(lowerRight) {}
        /// 构造函数
        CMolRect(const CMolPosition2d<T>& pos,const CMolDimension2d<T>& size)
        : UpperLeftCorner(pos),LowerRightCorner(pos.X + size.Width,pos.Y + size.Height) {}

        /// 加运算
        CMolRect<T> operator+(const CMolPosition2d<T>& pos) const
        {
            CMolRect<T> ret(*this);
            return ret += pos;
        }
        /// 加上运算
        CMolRect<T>& operator+=(const CMolPosition2d<T>& pos)
        {
            UpperLeftCorner += pos;
            LowerRightCorner += pos;
            return *this;
        }
        /// 减运算
        CMolRect<T>& operator-(const CMolPosition2d<T>& pos) const
        {
            CMolRect<T> ret(*this);
            return ret-=pos;
        }
        /// 减去运算
        CMolRect<T>& operator-=(const CMolPosition2d<T>& pos)
        {
            UpperLeftCorner -= pos;
            LowerRightCorner -= pos;
            return *this;
        }
        /// 相等运算
        bool operator==(const CMolRect<T>& other) const
        {
            return (UpperLeftCorner == other.UpperLeftCorner &&
                LowerRightCorner == other.LowerRightCorner);
        }

        /// 不相等运算
        bool operator!=(const CMolRect<T>& other) const
        {
            return (UpperLeftCorner != other.UpperLeftCorner ||
                LowerRightCorner != other.LowerRightCorner);
        }
        /// 小于运算
        bool operator<(const CMolRect<T>& other) const
        {
            return getArea() < other.getArea();
        }

		//const NMRect<T>& operator=(const NMRect<T>& other) const
		//{
		//	 UpperLeftCorner = other.UpperLeftCorner;
		//	 LowerRightCorner = other.LowerRightCorner;
		//	 return *this;
		//}

        /// 返回矩形的大小
        T getArea() const
        {
            return getWidth() * getWidth();
        }
        /// 检测一个点是否在矩形范围内
        bool isPointInside(const CMolPosition2d<T>& pos) const
        {
            return (UpperLeftCorner.X <= pos.X &&
                    UpperLeftCorner.Y <= pos.Y &&
                    LowerRightCorner.X >= pos.X &&
                    LowerRightCorner.Y >= pos.Y);
        }
        /// 检测是否和另一个矩形相交
        bool isRectCollided(const CMolRect<T>& other) const
        {
			return (LowerRightCorner.Y > other.UpperLeftCorner.Y &&
				    UpperLeftCorner.Y < other.LowerRightCorner.Y &&
				    LowerRightCorner.X > other.UpperLeftCorner.X &&
				    UpperLeftCorner.X < other.LowerRightCorner.X);
        }
        /// 重合两个矩形
        void clipAgainst(const CMolRect<T>& other)
        {
			if (other.LowerRightCorner.X < LowerRightCorner.X)
				LowerRightCorner.X = other.LowerRightCorner.X;
			if (other.LowerRightCorner.Y < LowerRightCorner.Y)
				LowerRightCorner.Y = other.LowerRightCorner.Y;

			if (other.UpperLeftCorner.X > UpperLeftCorner.X)
				UpperLeftCorner.X = other.UpperLeftCorner.X;
			if (other.UpperLeftCorner.Y > UpperLeftCorner.Y)
				UpperLeftCorner.Y = other.UpperLeftCorner.Y;

			if (UpperLeftCorner.Y > LowerRightCorner.Y)
				UpperLeftCorner.Y = LowerRightCorner.Y;
			if (UpperLeftCorner.X > LowerRightCorner.X)
				UpperLeftCorner.X = LowerRightCorner.X;
        }
        /// 移动矩形到指定矩形中
     	bool constrainTo(const CMolRect<T>& other)
		{
			if (other.getWidth() < getWidth() || other.getHeight() < getHeight())
				return false;

			T diff = other.LowerRightCorner.X - LowerRightCorner.X;
			if (diff < 0)
			{
				LowerRightCorner.X += diff;
				UpperLeftCorner.X  += diff;
			}

			diff = other.LowerRightCorner.Y - LowerRightCorner.Y;
			if (diff < 0)
			{
				LowerRightCorner.Y += diff;
				UpperLeftCorner.Y  += diff;
			}

			diff = UpperLeftCorner.X - other.UpperLeftCorner.X;
			if (diff < 0)
			{
				UpperLeftCorner.X  -= diff;
				LowerRightCorner.X -= diff;
			}

			diff = UpperLeftCorner.Y - other.UpperLeftCorner.Y;
			if (diff < 0)
			{
				UpperLeftCorner.Y  -= diff;
				LowerRightCorner.Y -= diff;
			}

			return true;
		}
		/// 得到矩形的宽度
		T getWidth() const
		{
		    return LowerRightCorner.X - UpperLeftCorner.X;
		}
		/// 得到矩形的高度
		T getHeight() const
		{
		    return LowerRightCorner.Y - UpperLeftCorner.Y;
		}
		/// 修复矩形
		void repair()
		{
			if (LowerRightCorner.X < UpperLeftCorner.X)
			{
				T t = LowerRightCorner.X;
				LowerRightCorner.X = UpperLeftCorner.X;
				UpperLeftCorner.X = t;
			}

			if (LowerRightCorner.Y < UpperLeftCorner.Y)
			{
				T t = LowerRightCorner.Y;
				LowerRightCorner.Y = UpperLeftCorner.Y;
				UpperLeftCorner.Y = t;
			}
		}
		/// 矩形是否可用
		bool isValid() const
		{
		    return ((LowerRightCorner.X >= UpperLeftCorner.X) &&
                    (LowerRightCorner.Y >= UpperLeftCorner.Y));
		}
		/// 返回矩形的中心点
		CMolPosition2d<T> getCenter() const
		{
		    return CMolPosition2d<T>((UpperLeftCorner.X + LowerRightCorner.X) / 2,
		                (UpperLeftCorner.Y + LowerRightCorner.Y) / 2);
		}
		/// 得到矩形的高宽
		CMolDimension2d<T> getSize() const
		{
		    return CMolDimension2d<T>(getWidth(),getHeight());
		}
		/// 添加一个点到矩形中，以便让它改变大小
		void addInternalPoint(const CMolPosition2d<T>& p)
		{
		    addInternalPoint(p.X,p.Y);
		}
		/// 根据矩形中内部的一个点改变矩形的大小
		void addInternalPoint(T x,T y)
		{
			if (x>LowerRightCorner.X)
			LowerRightCorner.X = x;
			if (y>LowerRightCorner.Y)
			LowerRightCorner.Y = y;

			if (x<UpperLeftCorner.X)
			UpperLeftCorner.X = x;
			if (y<UpperLeftCorner.Y)
			UpperLeftCorner.Y = y;
		}

	CMolPosition2d<T> UpperLeftCorner;
	CMolPosition2d<T> LowerRightCorner;
};

////}
//}

#endif
