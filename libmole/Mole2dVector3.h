#ifndef _MOLE2D_VECTOR3_H_
#define _MOLE2D_VECTOR3_H_

/** 
* Mole2d 图像引擎
*
* author: akinggw
* date: 2009.11.10
*/

//namespace mole2d
//{
//namespace graphics
//{

class CMolVector3 
{
public:
	double x, y, z;               /**< 向量的三个值 */

	/// 构造函数
	CMolVector3();
	/// 带参数的构造函数
	CMolVector3(double _x, double _y, double _z);
	/// 带参数的构造函数2
	CMolVector3(const CMolVector3& L);

	/// 向量正则化
	void normalize();

	/// 向量乘
	CMolVector3 operator*(const CMolVector3& Rhs);
	/// 向量和常量相乘
	CMolVector3 operator*(const double& Rhs);
	/// 向量减
	CMolVector3 operator-(const CMolVector3& Rhs);
	/// 向量加
	CMolVector3 operator+(const CMolVector3& Rhs);
	/// 向量和常量相加
	CMolVector3 operator+(const double& Rhs);
	/// 向量相除
	double operator%(const CMolVector3& Rhs);
	/// 向量赋值
	CMolVector3 operator=(const CMolVector3& Rhs);

};

//}
//}

#endif
