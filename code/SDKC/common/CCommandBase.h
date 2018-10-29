/*****************************************************************************
* Copyright(C) 1993-2012,ZT Corporation.
*
* File Name:   CCommandBase.h
* Description: the base class of all the command device
*
* Author:      liuguoxun
* Date:        2012-04-18
* History 1: 
*
*****************************************************************************/


#ifndef COMMANDBASE_H_20140513
#define COMMANDBASE_H_20140513


#include "IBasePort.h"
#include "IBaseLog.h"


#define   MAX_CMD_NUM    256 //0x0 - 0xFF
#define   MAX_CMD_DES     64 //command remarks


extern TCHAR g_cRunPath[MAX_PATH];


class CCommandBase
{
public:
	//ͨѶ���ƺ���
	virtual long Open(LPTSTR lpDesc);
	virtual long ReOpen(DWORD dwAfterTime = 0);
	virtual bool IsOpen(void) const;
	virtual long Close(void);
	virtual long SetBaudrate(DWORD dwBaudrate, BOOL bOnlyPort = 0);
	virtual DWORD GetCurBaudrate(void);
	virtual long SendData(const char *pData, DWORD dwDataLen, DWORD dwTimeout);
	virtual long ReadData(char *pData, DWORD &dwInOutLen, DWORD dwTimeout);
	virtual long Cancel(void);
	virtual void *GetPortPointer(void) { return m_pPort; }


	//�̼�����
	virtual DWORD OpenFile(char *pOutBuf, LPCTSTR lpFileName, LPCSTR lpDecryptKey = 0, WORD wKeyLen = 0); 
	virtual long ChipCommunicate(BYTE Mode, char *pChipInfo = 0);
	virtual long DownProgram(LPCSTR pcFileData, long nFileLen, BYTE Mode, void *hWnd = 0);



	//��������
	virtual long Init(long nMode = 0);										  //�豸��ʼ��(�������)
	virtual long Reset(void);											      //�豸��λ
	virtual long SelfTest(long iComponent = 0);							      //�豸�����Լ�
	virtual long GetStatus(void);										      //��ȡ�豸״̬
	virtual long GetCapabilities(void *lpvCap);							      //��ȡ�豸����
	virtual long Execute(long iCmdIndex, char *pcBuffer, long &iBufOrRetLen); //ִ������
	virtual long GetLastErrorCode(void);	    					          //��ȡ�����뼰���������
	virtual char *GetErrorInfo(long iCode);				                      //ȡ���������
	virtual long GetHardwareID(char *pcModelId);						      //��Ӳ��ID
	virtual long GetHardwareSN(char *pcSn);						              //��Ӳ���������к�	
	virtual long GetHardwareVersion(char *pcVersion);				          //��Ӳ���汾��
	virtual long GetLoaderVersion(char *pcVersion);
	virtual long GetSoftVersion(char *pcSoftVersion, void *hModule = 0);      //������汾��



public:
	CCommandBase(EPORT ePort, EExchange eType);
    virtual ~CCommandBase();



protected:
	typedef enum
	{
		  F_NORMAL        = 0x0   //����
	    , FS_NO_HEAD      = 0x1	  //�����ޱ���ͷ
		, FS_NO_END       = 0x2	  //�����ޱ���β
		, FS_NO_CHECK     = 0x4	  //���ͱ�����У����
		, FS_ADD_MAC_KBPK = 0x8	  //���ͱ�������KBPKΪ��Կ��MACУ��
		, FS_ADD_MAC_UAK  = 0x10  //���ͱ�������UAKΪ��Կ��MACУ��

		, FR_NO_HEAD      = 0x100 //�����ޱ���ͷ
		, FR_NO_END       = 0x200 //�����ޱ���β
		, FR_NO_CHECK     = 0x400 //���ձ�����У����
	}EFORMAT;

	typedef struct stCommand
	{
		BYTE    ucIndex;          // ��������(��ƿ)
		BYTE    ucCommand;        // ������
		WORD    wParaLen;         // �������ȣ�0xFFFF��ʾ�Ƕ���(��ʱ�����ڲ�����ǰ2���ֽڣ���λ��ǰ)			
		DWORD   dwTimeOut;        // ���ʱʱ��	
		BYTE    ucMaxCnt;         // �������ִ�д���
		EFORMAT eFormat;          // �����ʽ
		char    cDes[MAX_CMD_DES];// ��������
	}STCOMMAND, *PSTCOMMAND;
   

	//ע������
	long RegisterCommand(BYTE  ucIndex, BYTE ucCommand, WORD  wParaLen, DWORD dwTimeOut, BYTE ucMaxCnt, EFORMAT eFormat, LPCSTR pDes = NULL);
	void UnRegisterAllCommand(void);


protected:
	virtual long PackData(PSTCOMMAND pstCmd, LPCSTR pcData, WORD wDataLen, char *pcPackData);//�������(HEX��ʽ���ǲ���ַ�����ʽ����)
	virtual long UnPackData(PSTCOMMAND pstCmd, LPCSTR pcData, WORD wDataLen, char *pcRetData, long &iBufOrRetLen); //���ݽ��(HEX��ʽ���ǲ���ַ�����ʽ���)


protected:
	BYTE   m_CmdSeq;	  //������ˮ��
    BOOL   m_bCmdSeqAdd;  //������ˮ���Ƿ�����
	long   m_iErrorCode;  //������

	IPort *m_pPort;
    PSTCOMMAND m_apCommand[MAX_CMD_NUM]; //������ָ���ָ������
};


#endif //COMMANDBASE_H_20140513

