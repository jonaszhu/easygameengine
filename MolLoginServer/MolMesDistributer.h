#ifndef _MOL_MES_DISTRIBUTER_H_INCLUDE
#define _MOL_MES_DISTRIBUTER_H_INCLUDE

#include "MolServerCom.h"

/**
 * ���ڴ���������Ϣ
 */
class CMolMesDistributer : public ThreadBase
{
public:
	/// ���캯��
	CMolMesDistributer();
	/// ��������
	~CMolMesDistributer();

	bool run();

private:
	NetMessage myMes;
	//Mutex m_MesLock;
};

#endif
