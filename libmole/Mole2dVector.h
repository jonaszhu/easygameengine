#ifndef _MOLE2D_VECTOR_H_INCLUDE
#define _MOLE2D_VECTOR_H_INCLUDE

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.10
*/

#include <assert.h>

#include <vector>
#include <algorithm> 

//namespace mole2d
//{

template<class T>
class CMolVector
{
public:
	/// ���캯��
	CMolVector() {}
	/// ��������
	~CMolVector() {}

	/// ���һ������������
	void push_back(T d)
	{
		m_data.push_back(d);
	}
	/// �������
	void clear(void)
	{
		m_data.clear();
	}
	/// ��������Ƿ�Ϊ��
	bool empty(void)
	{
		return m_data.empty();
	}
	/// ��С�����������
	void sort(void)
	{
		std::sort(m_data.begin(),m_data.end(),sort1);
	}
	/// �õ�����ĳ���
	int size(void)
	{
		return (int)m_data.size();
	}
	/// �����Ƿ���ָ��������
	int find(T data)
	{
		if(m_data.empty()) return -1;

		for(int i=0;i<(int)m_data.size();i++)
			if(m_data[i] == data) return i;

		return -1;
	}
	/// ɾ��ָ��λ�õ�����
	void del(int pos)
	{
		if(m_data.empty() || pos < 0) return;

		std::vector<T>::iterator iter = m_data.begin();
		for(int i=0;iter != m_data.end();iter++,i++)
			if(i=pos) { m_data.erase(iter); break; }
	}
	/// �õ�ָ��������
	T& operator[](int index)
	{
		assert( index < size() );
		return m_data[index];
	}

private:
	/// ��С��������
	static bool sort1(const T &t1,const T &t2)
	{
		return t1 < t2;
	}

	std::vector<T> m_data;                /**< ���ڴ洢���� */
};

//}

#endif