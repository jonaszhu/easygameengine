#ifndef _MOLE2D_RECT_H
#define _MOLE2D_RECT_H

/** 
* Mole2d ͼ������
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
 * ����ģ����
 */
template<class T>
class CMolRect
{
    public:
        /// ���캯��
        CMolRect() : UpperLeftCorner(0,0),LowerRightCorner(0,0) {}
        /// ���캯��
        CMolRect(T x,T y,T x2,T y2)
        : UpperLeftCorner(x,y),LowerRightCorner(x2,y2) {}
        /// ���캯��
        CMolRect(const CMolPosition2d<T>& upperLeft,const CMolPosition2d<T>& lowerRight)
        : UpperLeftCorner(upperLeft),LowerRightCorner(lowerRight) {}
        /// ���캯��
        CMolRect(const CMolPosition2d<T>& pos,const CMolDimension2d<T>& size)
        : UpperLeftCorner(pos),LowerRightCorner(pos.X + size.Width,pos.Y + size.Height) {}

        /// ������
        CMolRect<T> operator+(const CMolPosition2d<T>& pos) const
        {
            CMolRect<T> ret(*this);
            return ret += pos;
        }
        /// ��������
        CMolRect<T>& operator+=(const CMolPosition2d<T>& pos)
        {
            UpperLeftCorner += pos;
            LowerRightCorner += pos;
            return *this;
        }
        /// ������
        CMolRect<T>& operator-(const CMolPosition2d<T>& pos) const
        {
            CMolRect<T> ret(*this);
            return ret-=pos;
        }
        /// ��ȥ����
        CMolRect<T>& operator-=(const CMolPosition2d<T>& pos)
        {
            UpperLeftCorner -= pos;
            LowerRightCorner -= pos;
            return *this;
        }
        /// �������
        bool operator==(const CMolRect<T>& other) const
        {
            return (UpperLeftCorner == other.UpperLeftCorner &&
                LowerRightCorner == other.LowerRightCorner);
        }

        /// ���������
        bool operator!=(const CMolRect<T>& other) const
        {
            return (UpperLeftCorner != other.UpperLeftCorner ||
                LowerRightCorner != other.LowerRightCorner);
        }
        /// С������
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

        /// ���ؾ��εĴ�С
        T getArea() const
        {
            return getWidth() * getWidth();
        }
        /// ���һ�����Ƿ��ھ��η�Χ��
        bool isPointInside(const CMolPosition2d<T>& pos) const
        {
            return (UpperLeftCorner.X <= pos.X &&
                    UpperLeftCorner.Y <= pos.Y &&
                    LowerRightCorner.X >= pos.X &&
                    LowerRightCorner.Y >= pos.Y);
        }
        /// ����Ƿ����һ�������ཻ
        bool isRectCollided(const CMolRect<T>& other) const
        {
			return (LowerRightCorner.Y > other.UpperLeftCorner.Y &&
				    UpperLeftCorner.Y < other.LowerRightCorner.Y &&
				    LowerRightCorner.X > other.UpperLeftCorner.X &&
				    UpperLeftCorner.X < other.LowerRightCorner.X);
        }
        /// �غ���������
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
        /// �ƶ����ε�ָ��������
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
		/// �õ����εĿ��
		T getWidth() const
		{
		    return LowerRightCorner.X - UpperLeftCorner.X;
		}
		/// �õ����εĸ߶�
		T getHeight() const
		{
		    return LowerRightCorner.Y - UpperLeftCorner.Y;
		}
		/// �޸�����
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
		/// �����Ƿ����
		bool isValid() const
		{
		    return ((LowerRightCorner.X >= UpperLeftCorner.X) &&
                    (LowerRightCorner.Y >= UpperLeftCorner.Y));
		}
		/// ���ؾ��ε����ĵ�
		CMolPosition2d<T> getCenter() const
		{
		    return CMolPosition2d<T>((UpperLeftCorner.X + LowerRightCorner.X) / 2,
		                (UpperLeftCorner.Y + LowerRightCorner.Y) / 2);
		}
		/// �õ����εĸ߿�
		CMolDimension2d<T> getSize() const
		{
		    return CMolDimension2d<T>(getWidth(),getHeight());
		}
		/// ���һ���㵽�����У��Ա������ı��С
		void addInternalPoint(const CMolPosition2d<T>& p)
		{
		    addInternalPoint(p.X,p.Y);
		}
		/// ���ݾ������ڲ���һ����ı���εĴ�С
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
