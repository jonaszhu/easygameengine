#ifndef MOLE2D_MESSAGE_OUT_H
#define MOLE2D_MESSAGE_OUT_H

/**
 * Mole2D ��Ϸ����
 *
 * ����ļ��������������һ����
 *
 * ���ߣ�akinggw
 * ����ʱ�䣺 2008.6.24
 */

#include <string>

#include "Mole2dCommon.h"

//namespace mole2d
//{
//namespace graphics
//{

#include <iosfwd>

/**
* ���ڽ��������Ϣ
*/
class MOLEXPORT CMolMessageOut
{
public:
	/// ���캯��
	CMolMessageOut();
	/// ����ϢID�Ĺ��캯��
	CMolMessageOut(int id);
	/// ��������
	~CMolMessageOut();

	/// �����ǰ��Ϣ
	void clear();
	/// дһ��BYTE��ȥ
	void writeByte(int value);
	/// дһ��SHORT��ȥ
	void writeShort(int value);
	/// дһ��LONG��ȥ
	void writeLong(unsigned long value);
	/// дһ��FLOAT��ȥ
	void writeFloat(float value);
	/// дһ��DOUBLE��ȥ
	void writeDouble(double value);
	/// дһ���ַ�����ȥ
	void writeString(const std::string &str, int length = -1);
	/// �õ���Ϣ
	char* getData() const { return mData; }
	/// �õ���Ϣ����
	unsigned int getLength() const { return mPos; }

private:
	/// ȷ���������������ܴ�
	void expand(size_t bytes);

	char *mData;
	unsigned int mPos;
	unsigned int mDataSize;
};

//}
//}

#endif
