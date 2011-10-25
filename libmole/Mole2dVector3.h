#ifndef _MOLE2D_VECTOR3_H_
#define _MOLE2D_VECTOR3_H_

/** 
* Mole2d ͼ������
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
	double x, y, z;               /**< ����������ֵ */

	/// ���캯��
	CMolVector3();
	/// �������Ĺ��캯��
	CMolVector3(double _x, double _y, double _z);
	/// �������Ĺ��캯��2
	CMolVector3(const CMolVector3& L);

	/// ��������
	void normalize();

	/// ������
	CMolVector3 operator*(const CMolVector3& Rhs);
	/// �����ͳ������
	CMolVector3 operator*(const double& Rhs);
	/// ������
	CMolVector3 operator-(const CMolVector3& Rhs);
	/// ������
	CMolVector3 operator+(const CMolVector3& Rhs);
	/// �����ͳ������
	CMolVector3 operator+(const double& Rhs);
	/// �������
	double operator%(const CMolVector3& Rhs);
	/// ������ֵ
	CMolVector3 operator=(const CMolVector3& Rhs);

};

//}
//}

#endif
