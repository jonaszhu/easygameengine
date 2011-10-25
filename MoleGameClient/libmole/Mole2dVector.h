#ifndef _MOLE2D_VECTOR_H_INCLUDE
#define _MOLE2D_VECTOR_H_INCLUDE

/** 
* Mole2d 图像引擎
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
	/// 构造函数
	CMolVector() {}
	/// 析构函数
	~CMolVector() {}

	/// 添加一个数到数组中
	void push_back(T d)
	{
		m_data.push_back(d);
	}
	/// 清空数组
	void clear(void)
	{
		m_data.clear();
	}
	/// 检测数组是否为空
	bool empty(void)
	{
		return m_data.empty();
	}
	/// 从小到大进行排序
	void sort(void)
	{
		std::sort(m_data.begin(),m_data.end(),sort1);
	}
	/// 得到数组的长度
	int size(void)
	{
		return (int)m_data.size();
	}
	/// 查找是否有指定的数据
	int find(T data)
	{
		if(m_data.empty()) return -1;

		for(int i=0;i<(int)m_data.size();i++)
			if(m_data[i] == data) return i;

		return -1;
	}
	/// 删除指定位置的数据
	void del(int pos)
	{
		if(m_data.empty() || pos < 0) return;

		std::vector<T>::iterator iter = m_data.begin();
		for(int i=0;iter != m_data.end();iter++,i++)
			if(i=pos) { m_data.erase(iter); break; }
	}
	/// 得到指定的数组
	T& operator[](int index)
	{
		assert( index < size() );
		return m_data[index];
	}

private:
	/// 从小到大排序
	static bool sort1(const T &t1,const T &t2)
	{
		return t1 < t2;
	}

	std::vector<T> m_data;                /**< 用于存储数据 */
};

//}

#endif