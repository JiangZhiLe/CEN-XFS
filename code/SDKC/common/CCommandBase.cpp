/*****************************************************************************
* Copyright(C) 1993-2012,ZT Corporation.
*
* File Name:   CCommandBase.cpp
* Description: the base class of all the command device       
*
* Author:      liuguoxun
* Date:        2012-04-18
* History 1: 
*
*****************************************************************************/


#include "CCommandBase.h"


TCHAR g_cRunPath[MAX_PATH] = {0};



/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
CCommandBase::CCommandBase(EPORT ePort, EExchange eType)
{
	m_CmdSeq     = 0;	
	m_iErrorCode = 0;
	m_bCmdSeqAdd = FALSE;

	for(int i = MAX_CMD_NUM - 1; i >= 0; i--)
	{
		m_apCommand[i] = NULL;
	}

	m_pPort   = InstanceIPort(ePort, eType, NULL);
}


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
CCommandBase::~CCommandBase()
{
	UnRegisterAllCommand();

	if(NULL != m_pPort)
	{
		ReleaseIPort(m_pPort);
		m_pPort = NULL;
	}
}


/*****************************************************************************
 * ����˵��: ע������
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::RegisterCommand(BYTE  ucIndex, BYTE ucCommand, WORD  wParaLen, DWORD dwTimeOut, BYTE ucMaxCnt, EFORMAT eFormat, LPCSTR pDes)
{
	if(ucIndex >= MAX_CMD_NUM) //����Ƿ񳬳�����ע���������
	{
		return EC_FULL_NOW;
	}

	stCommand* pCommand = new stCommand();
	if(NULL != pCommand)
	{
		pCommand->ucIndex        = ucIndex;
		pCommand->ucCommand      = ucCommand;
		pCommand->wParaLen       = wParaLen;
		pCommand->dwTimeOut      = dwTimeOut;
		pCommand->ucMaxCnt       = ucMaxCnt;
		pCommand->eFormat        = eFormat;
		if(NULL != pDes)
		{
			STRCPY_S(pCommand->cDes, MAX_CMD_DES - 1, pDes);
		}

		if(NULL != m_apCommand[ucIndex])
		{
			DELETE_P(m_apCommand[ucIndex]);
		}

		m_apCommand[ucIndex]     = pCommand;
		return EC_SUCCESS;
	}
	else
	{
		return EC_ALLOC_FAILED;
	}	
}


/*****************************************************************************
 * ����˵��: ע����������
 * ��������: ��
 * �� �� ֵ: �� 
 *****************************************************************************/
void CCommandBase::UnRegisterAllCommand(void)
{
	for(int i = MAX_CMD_NUM - 1; i >= 0; i--)
	{
		DELETE_P(m_apCommand[i]);
	}
}


/*****************************************************************************
 * ����˵��: ���ݴ��
 * ��������: pstCmd:����ṹָ�룬pcData:���������iDataLen���������ȣ�pcPackData������Ĵ������
 * �� �� ֵ: ���ݰ����� 
 *****************************************************************************/
long CCommandBase::PackData(PSTCOMMAND pstCmd, LPCSTR pcData, WORD wDataLen, char *pcPackData)
{
	return 0;
}


/*****************************************************************************
 * ����˵��: ���ݽ��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::UnPackData(PSTCOMMAND pstCmd, LPCSTR pcData, WORD wDataLen, char *pcRetData, long &iBufOrRetLen)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ: ������ 
 *****************************************************************************/
long CCommandBase::Open(LPTSTR lpDesc)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ȡ��ǰ���ڲ�����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
DWORD CCommandBase::GetCurBaudrate()
{
	if(NULL == m_pPort || (!m_pPort->IsOpen()))
	{
		return 0;
	}

    return (m_pPort->GetBaudrate());
}


/*****************************************************************************
 * ����˵��: ���´򿪴��ڣ�����Ϊ��ǰ����
 * ��������: dwAfterTime: �رմ��ں���ٺ��������´�
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::ReOpen(DWORD dwAfterTime)
{
	if(NULL == m_pPort)
	{
		return EC_POINTER_NULL;
	}

    return m_pPort->ReOpen(dwAfterTime);
}


/*****************************************************************************
 * ����˵��: ��⴮���Ƿ��
 * ��������: ��
 * �� �� ֵ:  
 *****************************************************************************/
bool CCommandBase::IsOpen(void) const
{
	if(NULL == m_pPort)
	{
		return false;
	}

    return m_pPort->IsOpen();
}


/*****************************************************************************
 * ����˵��: �رմ���
 * ��������: ��
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::Close(void)
{
	if(NULL == m_pPort)
	{
		return EC_POINTER_NULL;
	}

	return m_pPort->Close();
}


/*****************************************************************************
 * ����˵��: ȡ����������
 * ��������: ��
 * �� �� ֵ: �鿴������� 
 *****************************************************************************/
long CCommandBase::Cancel(void)
{
	if(NULL == m_pPort)
	{
		return EC_POINTER_NULL;
	}

	return m_pPort->Cancel();
}


/*****************************************************************************
 * ����˵��:
 * ��������:
 * �� �� ֵ:
 *****************************************************************************/
long CCommandBase::SendData(const char *pData, DWORD dwDataLen, DWORD dwTimeout)
{
	if(NULL == m_pPort || NULL == pData)
	{
		return EC_POINTER_NULL;
	}

	return m_pPort->SendData(pData, dwDataLen, dwTimeout);
}


/*****************************************************************************
 * ����˵��: �Ӵ��ڽ�������
 * ��������: dwTimeOut����ʱʱ�䣨���룩
 * �� �� ֵ: �鿴������� 
 *****************************************************************************/
long CCommandBase::ReadData(char *pData, DWORD &dwInOutLen, DWORD dwTimeout)
{
	if(NULL == m_pPort || NULL == pData)
	{
		return EC_POINTER_NULL;
	}

	long iRet = 0;
	DWORD dwRead = 0;
	char szPara[MAX_PACKET_LEN] = {0};

	iRet = m_pPort->ReceiveData(szPara, dwInOutLen, &dwRead, dwTimeout);
	if(dwRead > 0)
	{
		memcpy(pData, szPara, dwRead);
	}

	dwInOutLen = dwRead;
	return iRet;
}


/*****************************************************************************
 * ����˵��: ���ò�����(Ӳ��������)
 * ��������: dwBaudrate: �²�����
 * �� �� ֵ: �鿴������� 
 *****************************************************************************/
long CCommandBase::SetBaudrate(DWORD dwBaudrate, BOOL bOnlyPort)
{
	if(NULL == m_pPort)
	{
		return EC_POINTER_NULL;
	}

	long iRet = 0;

	if(bOnlyPort)
	{
		iRet = m_pPort->SetBaudrate(dwBaudrate);
	}
	else
	{
		iRet = EC_UNSUPPORT;
	}

	return iRet;
}


/*****************************************************************************
 * ����˵��: ��ȡ�̼��ļ�����(�����ļ�����)
 * ��������: 
 * �� �� ֵ: �ļ����� 
 *****************************************************************************/
DWORD CCommandBase::OpenFile(char *pOutBuf, LPCTSTR lpFileName, LPCSTR lpDecryptKey, WORD wKeyLen)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ���оƬ/��оƬ����
 * ��������: 
 * �� �� ֵ: 
 *****************************************************************************/
long CCommandBase::ChipCommunicate(BYTE Mode, char *pChipInfo)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ���ع̼�����
 * ��������:
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::DownProgram(LPCSTR pcFileData, long nFileLen, BYTE Mode, void *hWnd)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: �豸��ʼ��(ͬʱ�����������Կ��������λ)
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::Init(long nMode)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: �豸��λ(�൱�������ϵ�)
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::Reset(void)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: �豸�����Լ�
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::SelfTest(long iComponent)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��ȡ�豸״̬
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetStatus(void)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��ȡ�豸����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetCapabilities(void *lpvCap)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��Ӳ��ID
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetHardwareID(char *pcModelId)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��Ӳ���������к�
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetHardwareSN(char *pcSn)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��Ӳ���汾��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetHardwareVersion(char *pcVersion)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: Loader(STM)�汾��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetLoaderVersion(char *pcVersion)
{
	return EC_UNSUPPORT;
}

	
/*****************************************************************************
 * ����˵��: ������汾��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetSoftVersion(char *pcSoftVersion, void *hModule)
{
	TCHAR cFileName[MAX_PATH] = {0};

	#ifdef __ms_windows__
	GetModuleFileName((HMODULE)hModule, cFileName, sizeof(cFileName));
	#endif

	return GetFileVersion(cFileName, pcSoftVersion);
}


/*****************************************************************************************
 * ����˵��: ִ������
 * ��������: iCmdIndex:���������ţ�pcBuffer��[IN]������� [OUT]��������
 *           iBufOrRetLen��[IN]���������� [OUT]�������ݳ���
 * �� �� ֵ:  
 *****************************************************************************************/
long CCommandBase::Execute(long iCmdIndex, char *pcBuffer, long &iBufOrRetLen)
{
	return EC_UNSUPPORT;
}


/*****************************************************************************
 * ����˵��: ��ȡ�����뼰���������
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CCommandBase::GetLastErrorCode(void)
{
	return m_iErrorCode;
}


/*****************************************************************************
 * ����˵��: ȡ���������
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
char * CCommandBase::GetErrorInfo(long iCode)
{
	switch(iCode)
	{
		case EC_SUCCESS:
		{
			return("Success.");
		}
		case EC_OPEN_FAILED:
		{
			return("Open port failed.");
		}
		case EC_INVALID_PORT:
		{
			return("Invalid port.");
		}
		case EC_INVALID_PARA:
		{
			return("Invalid parameter.");
		}
		case EC_INVALID_DATA:
		{
			return("Invalid data.");
		}
		case EC_SEND_FAILED:
		{
			return("Send data failed.");
		}
		case EC_RECEIVED_FAILED:
		{
			return("Received data failed.");
		}
		case EC_USER_CANCEL:
		{
			return("User cancel all operate.");
		}
		case EC_DATA_TOOLONG:
		{
			return("Data is too long.");
		}
		case EC_NAK_RECEIVED:
		{
			return("Received NAK.");
		}
		case EC_READ_TIMEOUT:
		{
			return("Read data timeout.");
		}
		case EC_WRITE_TIMEOUT:
		{
			return("Write data timeout.");
		}
		case EC_WAITEVENT_FAILED:
		{
			return("Wait event failed.");
		}
		case EC_SET_FAILED:
		{
			return("Set parameter failed.");
		}
		case EC_STEP_ERROR:
		{
			return("Step error.");
		}
		case EC_POINTER_NULL:
		{
			return("Pointer is NULL.");
		}
		case EC_FULL_NOW:
		{
			return("Queue or space or other full now.");
		}
		case EC_NET_ERROR:
		{
			return("Net error.");
		}
		case EC_INVALID_FILE:
		{
			return("Invalid file.");
		}
		case EC_TEST_MODE:
		{
			return("Test mode.");
		}
		case EC_EXIT:
		{
			return("Process or thread exit.");
		}
		case EC_ALLOC_FAILED:
		{
			return("Alloc failed.");
		}
		case EC_TYPE_UNMATCH:
		{
			return("Type unmatch.");
		}
		case EC_RETURN_FAILED:
		{
			return("Return failed.");
		}
		case EC_SERIOUS_ERROR:
		{
			return("Serious error.");
		}	
		case EC_UNSUPPORT:
		{
			return("Unsupport.");
		}
		default:
		{
			return("Undefined error code.");
		}
	}

	return EC_SUCCESS;
}

