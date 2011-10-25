#include "stdafx.h"

#include "MolMesDistributer.h"

#include "GameFrameManager.h"

/**
 * 构造函数
 */
CMolMesDistributer::CMolMesDistributer()
{

}

/**
 * 析构函数
 */
CMolMesDistributer::~CMolMesDistributer()
{

}

bool CMolMesDistributer::run()
{
	while(IsConnected())
	{
		//m_MesLock.Acquire();
		int count = GetNetMessage(myMes);
		for(int i=0;i<count;i++)
		{
			MessageStru *mes = myMes.GetMesById(i);
			if(mes==NULL) continue;

			switch(mes->GetType())
			{
			case MES_TYPE_ON_CONNECTED:
				{
					ServerGameFrameManager.OnProcessConnectedNetMes(mes->GetSocket());
				}
				break;
			case MES_TYPE_ON_DISCONNECTED:
				{
					ServerGameFrameManager.OnProcessDisconnectNetMes(mes->GetSocket());
				}
				break;
			case MES_TYPE_ON_READ:
				{
					ServerGameFrameManager.OnProcessNetMes(mes->GetSocket(),mes->GetMes());	
				}
				break;
			default:
				break;
			}			
		}
		//if(count > 0) 
		//	myMes.Clear();	
		//m_MesLock.Release();

		Sleep(10);
	}

	return false;
}
