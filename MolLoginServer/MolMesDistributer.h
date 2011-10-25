#ifndef _MOL_MES_DISTRIBUTER_H_INCLUDE
#define _MOL_MES_DISTRIBUTER_H_INCLUDE

#include "MolServerCom.h"

/**
 * 用于处理网络消息
 */
class CMolMesDistributer : public ThreadBase
{
public:
	/// 构造函数
	CMolMesDistributer();
	/// 析构函数
	~CMolMesDistributer();

	bool run();

private:
	NetMessage myMes;
	//Mutex m_MesLock;
};

#endif
