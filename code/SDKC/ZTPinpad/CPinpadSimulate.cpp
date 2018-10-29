/*****************************************************************************
* Copyright(C) 1993-2012,ZT Corporation.
*
* File Name:   CPinpadSimulate.cpp
* Description: the base class of simulate pinpad device       
*
* Author:      liuguoxun
* Date:        2012-05-28
* History 1: 
*
*****************************************************************************/


#include "CPinpadSimulate.h"


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
CPinpadSimulate::CPinpadSimulate(EPORT ePort, EExchange eType, EPIN_EXTEND eExtend)
	: CPinpadBase(ePort, eType, eExtend)
{
	memset(&m_stCap, 0, sizeof(m_stCap));
	m_stCap.wClass = 4; //WFS_SERVICE_CLASS_PIN
	m_stCap.fwType = eHW_EPP | eHW_EDM | eHW_HSM;
	m_stCap.bCompound = FALSE;

	m_stCap.fwAlgorithms = CRYPT_DESECB | CRYPT_DESCBC | CRYPT_DESCFB | CRYPT_RSA | CRYPT_DESMAC 
		| CRYPT_TRIDESECB | CRYPT_TRIDESCBC | CRYPT_TRIDESCFB | CRYPT_TRIDESMAC
		| CRYPT_SM4ECB | CRYPT_SM4CBC;
	m_stCap.fwPinFormats = FORMAT_IBM3624 | FORMAT_ANSI | FORMAT_ISO0 | FORMAT_ISO1 | FORMAT_ISO3 | FORMAT_VISA | FORMAT_VISA3 
							| FORMAT_DIEBOLD | FORMAT_DIEBOLDCO | FORMAT_ECI2 | FORMAT_ECI3 | FORMAT_BANKSYS;
	m_stCap.fwDerivationAlgorithms = 0; //not support WFS_PIN_CHIP_ZKA
	m_stCap.fwPresentationAlgorithms = 0; //not support WFS_PIN_PRESENT_CLEAR
	m_stCap.fwDisplay = 1; //WFS_PIN_DISPNONE

	m_stCap.bIDConnect = FALSE;
	m_stCap.fwIDKey = 0; //don't support
	m_stCap.fwValidationAlgorithms = VA_DES | VA_DES_OFFSET | VA_VISA;
	m_stCap.fwKeyCheckModes = KCVSELF | KCVZERO;

	m_stCap.bPINCanPersistAfterUse = FALSE;
	m_stCap.fwAutoBeep = 2; //WFS_PIN_BEEP_ACTIVE_SELECTABLE
	m_stCap.bHSMJournaling = FALSE;

	m_stCap.dwRSAAuthenticationScheme = 3; //WFS_PIN_RSA_AUTH_2PARTY_SIG | WFS_PIN_RSA_AUTH_3PARTY_CERT
	m_stCap.dwRSASignatureAlgorithm = SIGN_RSASSA_V15;
	m_stCap.dwRSACryptAlgorithm = 1; //WFS_PIN_CRYPT_RSAES_PKCS1_V1_5
	m_stCap.dwRSAKeyCheckMode = HASH_SHA1;
	m_stCap.dwSignatureScheme = 15; //WFS_PIN_SIG_GEN_RSA_KEY_PAIR | WFS_PIN_SIG_RANDOM_NUMBER | WFS_PIN_SIG_EXPORT_EPP_ID | WFS_PIN_SIG_ENHANCED_RKL
	
	m_stCap.lpwEMVImportSchemes = m_wEMVImportSchemes;
	m_stCap.fwEMVHashAlgorithm = HASH_SHA1;
	m_stCap.bKeyImportThroughParts = TRUE;
	m_stCap.fwENCIOProtocols = 0;
	m_stCap.bTypeCombined = FALSE;

	m_stCap.bSetPinblockDataRequired = FALSE;
	m_stCap.fwKeyBlockImportFormats = 0;
	m_stCap.bPowerSaveControl = FALSE;
	m_stCap.wDESKeyLength = 7; //WFS_PIN_KEYSINGLE | WFS_PIN_KEYDOUBLE | WFS_PIN_KEYTRIPLE

	m_stCap.dwCapsSize = sizeof(m_stCap);
	m_stCap.dwAlgorithms = m_stCap.fwAlgorithms | CRYPT_SM2;
	m_stCap.dwRSAHashAlg = HASH_SHA1;
	m_stCap.ucKCVL = 0x03;
	m_stCap.wUserKeyOffset = MAX_ART_KEY;
	m_stCap.bSplitBankSysMAC = TRUE;
	m_stCap.dwRIMode = RIM_PSW;
	

	REG_KEY_NUM();
}


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
CPinpadSimulate::~CPinpadSimulate()
{
}


/*****************************************************************************
 * ����˵��: �Զ����EPP������
 * ��������: ��
 * �� �� ֵ: EPP���� 
 *****************************************************************************/
EPIN_TYPE CPinpadSimulate::IsMyself(WORD &wSubType, IPort *pPort)
{
	wSubType = SUBVER_NONE;

	return ePIN_UNKNOWN;
}


/*****************************************************************************
 * ����˵��: ע���Լ�������
 * ��������: 
 * �� �� ֵ: 
 *****************************************************************************/
long CPinpadSimulate::RegisterMyFeatures(BOOL bAll)
{
	return 0;
}

long CPinpadSimulate::GetHardwareVersion(char *pcVersion)
{
	if(NULL == pcVersion)
	{
		return EC_POINTER_NULL;
	}

	strcpy(pcVersion, "Simulate Pinpad V3.00");

	return 0;
}

long CPinpadSimulate::OpenKeyboardAndSound(ESOUND eSound, ENTRYMODE eMode, DWORD dwActiveKey, DWORD dwActiveFDK)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: �豸��ʼ��(ͬʱ�����������Կ��������λ)
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_Init(long nMode)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: �豸��λ(�൱�������ϵ�)
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_Reset(void)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: �豸�����Լ�
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_SelfTest(long iComponent)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: Loader�汾��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_GetLoaderVersion(char *pcVersion)
{
	if(NULL != pcVersion)
	{
		strcpy(pcVersion, "V3.6");
	}

	return 0;
}

long CPinpadSimulate::Inner_ChipCommunicate(BYTE Mode, char *pChipInfo)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: ���ع̼�����
 * ��������: Mode: see define in enum ECHIP
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_DownProgram(LPCSTR pcFileData, long nFileLen, BYTE Mode, void *hWnd)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: ECHO����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::ECHO(void)
{
	return EC_SUCCESS;
}

 /*****************************************************************************
 * ����˵��: ȡ�����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RandomData(DWORD &dwInOutLen, char *pRandom)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: ���ð���ģʽ
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::SetEntryMode(ENTRYMODE eMode, DWORD dwActiveKey, DWORD dwActiveFDK)
{
	return EC_SUCCESS;
}

long CPinpadSimulate::Inner_SetKeyboardCode(LPCSTR lpKeyboardCodes, long nLen, ENTRYMODE eMode)
{	
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: ��ȡ������
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_GetKeyboardCode(char *lpKeyboardCodes, long &nOutLen, ENTRYMODE eMode)	
{
	nOutLen = 0;
	if(NULL == lpKeyboardCodes || NULL == m_pPort)
	{
		return EC_POINTER_NULL;
	}

	RLog2(LOG_LEVEL_COMMON, "eMode=0x%X", eMode);

	long nRet = 0;
	char szPara[512] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(eMode == ENTRY_MODE_CLOSE)
	{
		return EC_INVALID_PARA;
	}
	else
	{
		if(eMode < 0x30)
		{
			szPara[0] = eMode + 0x30;
		}
		else
		{
			szPara[0] = eMode;
		}
		
		nRet = Execute(INX_GET_KEYBOARD_CODES, szPara, iBufOrRetLen);
		if(nRet == EC_SUCCESS)
		{
			memcpy(lpKeyboardCodes, szPara, 16); //16 FK
			memcpy(lpKeyboardCodes + 16, szPara + 32, 8);//8 FDK

			nOutLen = 24;
			return EC_SUCCESS;
		}
		else
		{
			long nOnce = 1; //��8�޸ĳ�1��������0x00�����������
			DWORD dwRead = 0;
			char cKeyCode[512] = {0};
			char cTable[] = {"\x0\x1\x2\x3\x4\x5\x6\x7\x8\x9\xA\xB\xC\xD\xE\xF\x10\x11\x12\x13\x14\x15\x16\x17"};

			if(eMode == ENTRY_MODE_TEXT)
			{
				FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_CLOSE, ENTRY_MODE_CLOSE));
				FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_CLOSE, ENTRY_MODE_TEXT));

				for(int i = 0; i < (24 / nOnce); i++)
				{
					FAIL_RET(nRet, this, VirtualPress(cTable + i * nOnce, nOnce));
					nRet = ReadText(cKeyCode, dwRead, 1000);
					if(dwRead > 0)
					{
						memcpy(lpKeyboardCodes + i * nOnce, cKeyCode, nOnce);
						nOutLen += nOnce;
					}
					else if(i >= 16 / nOnce)
					{
						break;
					}
					else
					{
						memset(lpKeyboardCodes + i * nOnce, 0x00, nOnce);
						nOutLen += nOnce;
					}
				}

				return 0;
			}
			else
			{
				return EC_UNSUPPORT;
			}
		}
	}
}

/*****************************************************************************
 * ����˵��: ��ȡ�����
 * ��������: 
             wKeyId: ������Կ1
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_GetPinBlock(WORD wKeyId, BYTE PinLen, EPINFORMAT ePinFormat, LPCSTR lpCardNo, char *pPinBlock, WORD &wOutLen, BYTE Padding, WORD wKeyId2, WORD wVI, WORD wVI2)
{
	wOutLen = 0;
	long iRet = 0;
	char szPara[128] = {0};
	long iBufOrRetLen = sizeof(szPara);
	char szInitialPinPatern[64] = {0};
	char szCustomerData[64] = {0};
	BYTE PinOffset = 0;
	BYTE PinPostion = 0;

	RLog2(LOG_LEVEL_COMMON, "wKeyId=0x%X, EPINFORMAT=0x%X, PinLen=%d, Padding=0x%X.", wKeyId, ePinFormat, PinLen, Padding);

	if(wKeyId > MAX_CMM_KEY || NULL == pPinBlock)
	{
		return PIN_INVALID_COMMAND_PARA;
	}

	FAIL_RET(iRet, this, OpenKeyboardAndSound(SOUND_CLOSE, ENTRY_MODE_CLOSE));

	FAIL_RET(iRet, this, PinFillFormat(ePinFormat, PinLen, Padding, lpCardNo, PinOffset, PinPostion, szInitialPinPatern, szCustomerData));

	FAIL_RET(iRet, this, Authentication(wKeyId, USE_KEY));

	if(wKeyId2 == KEY_INVALID)
	{
		szPara[4] = 0x01; //single
		szPara[6] = LOBYTE(wKeyId);
		szPara[7] = HIBYTE(wKeyId);
	}
	else
	{
		szPara[4] = 0x02; //double
		szPara[6] = LOBYTE(wKeyId2);
		szPara[7] = HIBYTE(wKeyId2);
		szPara[8] = LOBYTE(wVI2);
		szPara[9] = HIBYTE(wVI2);
	}

	szPara[0] = LOBYTE(wKeyId);
	szPara[1] = HIBYTE(wKeyId);
	szPara[2] = LOBYTE(wVI);
	szPara[3] = HIBYTE(wVI);
	szPara[5] = ConvertFormat(ePinFormat);	
	memcpy(szPara + 10, szInitialPinPatern, 8);
	szPara[18] = PinPostion;//PinOffset;
	szPara[19] = PinLen;
	memcpy(szPara + 20, szCustomerData, 8);
	
	iRet = Execute(INX_READ_PIN_BLOCK, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS && iBufOrRetLen > 0) 
	{
		memcpy(pPinBlock, szPara, iBufOrRetLen);
		wOutLen = iBufOrRetLen;
	}

 	return iRet; 
}

/*****************************************************************************
 * ����˵��: �ֶ�������Կ
 * ��������: wKeyId : 			
			 dwKeyAttr:
			 eMode : 	
			 lpKCVRet: У�鷵��
			 eKCV : 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_StoreKey(WORD wKeyId, DWORD dwKeyAttr, EKEYMODE eMode, long iKeyLen, EKCVMODE eKCV, char *lpKCVRet)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: ������Կ(��������)
 * ��������: wKeyId : ��Կ��	             
			 dwKeyAttr: ��Կ����
			 lpKey : ��Կ,���ȱ���Ϊ8�ı���(��8�ֽڵ�����0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF)
			 iKeyLen : ��Կ����
			 wEnKey: ������Կ��,ΪKEY_INVALIDʱ������������
			 eMode : ����ģʽ
			 wVI : Variation Index
			 lpKCVRet: У�鷵��
			 eKCV : 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_LoadKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpKey, long iKeyLen, WORD wEnKey, EKEYMODE eMode, EKCVMODE eKCV, char *lpKCVRet)
{
	WORD wEnVI = 0;
	WORD wRealEnKey = wEnKey;
	WORD wEnKeyLen = 0;
	long iRet = 0;
	char cKey[64] = {0};
    DWORD wKeyAttr = 0;

	RLog2(LOG_LEVEL_DATA, "wKeyId=0x%X, dwKeyAttr=0x%X, wKeyLen=%d, wEnKey=0x%X, EKEYMODE=0x%X, EKCVMODE=0x%X.", 
			wKeyId, dwKeyAttr, iKeyLen, wEnKey, eMode, eKCV);
	
	if(NULL == lpKey)
	{
		return EC_POINTER_NULL;
	}

	if((dwKeyAttr & ATTR_ANSTR31)) //��������������ANSTR31��
	{
		return PIN_INVALID_KEY_ATTRIBUTES;
	}

	if(iKeyLen % 8 != 0)
	{
		return PIN_INVALID_COMMAND_PARA;
	}
	memcpy(cKey, lpKey, iKeyLen);

	CHECK_MAP_ID(wKeyId);

	if(PIN_KEY_NOT_EXIST == Inner_ReadKeyAttr(KEYID_MPK, &wKeyAttr) && EC_SUCCESS == Inner_ReadKeyAttr(KEYID_MK, &wKeyAttr))//��������Կ��;�Ƿ�����=>��
	{
		m_stArtKey[wKeyId].wAppId    = wKeyId;
		m_stArtKey[wKeyId].wKeyLen   = iKeyLen;
		m_stArtKey[wKeyId].dwKeyAttr = dwKeyAttr;
		m_stArtKey[wKeyId].wEnKeyId  = wRealEnKey;
		m_stArtKey[wKeyId].wEnKeyLen = wEnKeyLen;
		STRCPY_S(m_stArtKey[wKeyId].szKeyName, MAX_KEY_NAME + 1, m_szKeyNameBuf[wKeyId]);
		MEMCPY_S(m_stArtKey[wKeyId].szKeyValue, sizeof(m_stArtKey[wKeyId].szKeyValue), lpKey, iKeyLen);
		SaveEnlargeKey();
	}
	
	return iRet;
}

/*****************************************************************************
 * ����˵��: �ڲ�ɾ����Կ
 * ��������: wKeyId : ��ԿID
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_DeleteKey(WORD wKeyId)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: ��ȡ��Կ����
 * ��������: wKeyId : ��ԿID
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_ReadKeyAttr(WORD wKeyId, LPDWORD lpKeyAttr, EKCVMODE eKCV, char *lpKCVRet, WORD wVI)
{
	return EC_SUCCESS;
}

long CPinpadSimulate::Inner_Crypt(WORD wKeyId, ECRYPT eMode, LPCSTR lpDataIn, DWORD &dwInOutLen, char *lpOut, bool bEncrypt, LPCSTR lpIVdata, WORD wIVid, WORD wVI)
{
	long iRet = 0;
	char lpIV[16] = {0};
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);
	
	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, eMode=0x%X, dwInOutLen=%d, bEncrypt=%d, wIVid=0x%X.", wKeyId, eMode, dwInOutLen, bEncrypt, wIVid);

	if(NULL == lpDataIn || NULL == lpOut || (dwInOutLen % 8 != 0) || dwInOutLen == 0)
	{
		return (PIN_INVALID_DATA);
	}

	if(wKeyId > MAX_CMM_KEY) 
	{
		return PIN_INVALID_KEYID;
	}
	
	char cDesMode = 0;
	if(eMode == CRYPT_DESECB || eMode == CRYPT_TRIDESECB) 
	{
		if(bEncrypt)
		{
			cDesMode = 0x31;
		}
		else
		{
			cDesMode = 0x41;
		}
	}
	else if(eMode == CRYPT_DESCBC || eMode == CRYPT_TRIDESCBC) 
	{
		if(bEncrypt)
		{
			cDesMode = 0x32;
		}
		else
		{
			cDesMode = 0x42;
		}
	}
	else if(eMode == CRYPT_DESCFB || eMode == CRYPT_TRIDESCFB)
	{
		if(bEncrypt)
		{
			cDesMode = 0x33;
		}
		else
		{
			cDesMode = 0x43;
		}
	}
	else 
	{
		return EC_UNSUPPORT;
	}

	if(NULL != lpIVdata)
	{
		memcpy(lpIV, lpIVdata, 8);
	}

	DWORD nSend = 0; //�ѷ��͵ĳ���	
	LPCSTR pDataBegin = lpDataIn; //����λ��ָ��
	char *pCopyPos = lpOut; //����λ��ָ��
	long nOffset = 19;

	while(nSend < dwInOutLen)
	{
		FAIL_RET(iRet, this, Authentication(wKeyId));

		szPara[2] = LOBYTE(wKeyId);
		szPara[3] = HIBYTE(wKeyId);
		szPara[4] = LOBYTE(wVI);
		szPara[5] = HIBYTE(wVI);

		if((pCopyPos != lpOut) && (eMode == CRYPT_DESCBC || eMode == CRYPT_TRIDESCBC))
		{
			if(bEncrypt) //�����CBC����,��һ�μ��ܽ�������8�ֽڲ�����һ�ε�IV
			{
				memcpy(lpIV, pCopyPos - 8, 8);
			}
			else //�����CBC����,��һ�����ݵ����8�ֽڲ�����һ�ε�IV
			{
				memcpy(lpIV, pDataBegin + nSend - 8, 8);
			}
		}

		if(wIVid == KEY_INVALID)
		{
			szPara[6] = LOBYTE(wKeyId);
			szPara[7] = HIBYTE(wKeyId);
			memcpy(szPara + 8, lpIV, 8);
			szPara[16] = 0x31; //IV data as IV
		}
		else if(NULL != lpIVdata)
		{
			FAIL_RET(iRet, this, Authentication(wIVid));

			szPara[6] = LOBYTE(wIVid);
			szPara[7] = HIBYTE(wIVid);
			memcpy(szPara + 8, lpIV, 8);
			szPara[16] = 0x32; //Decrypt(IV Data ,IV key ID) AS IV

			wIVid = KEY_INVALID; //��һ�ֶ�ֻ����ģʽIV data as IV
		}	
		else
		{
			FAIL_RET(iRet, this, Authentication(wIVid));

			szPara[6] = LOBYTE(wIVid);
			szPara[7] = HIBYTE(wIVid);
			szPara[16] = 0x30; //IV key as IV

			wIVid = KEY_INVALID; //��һ�ֶ�ֻ����ģʽIV data as IV
		}

		szPara[17] = cDesMode;
		if(eMode == CRYPT_DESECB || eMode == CRYPT_DESCBC)
		{
			szPara[18] = 0x31; //DES
		}
		else
		{
			szPara[18] = 0x32; //TDES
		}

		if(dwInOutLen - nSend > ONCE_LEN) //Ӳ��һ����������ֽ�
		{
			szPara[0] = LOBYTE(17 + ONCE_LEN); //ǰ2�ֽڷŲ�������
			szPara[1] = HIBYTE(17 + ONCE_LEN);
			memcpy(szPara + nOffset, pDataBegin + nSend, ONCE_LEN);
			nSend += ONCE_LEN;
		}
		else   //��������ݲ�����ONCE_LEN ���� ���������һ��
		{
			szPara[0] = LOBYTE(17 + dwInOutLen - nSend);
			szPara[1] = HIBYTE(17 + dwInOutLen - nSend);
			memcpy(szPara + nOffset, pDataBegin + nSend, dwInOutLen - nSend);
			nSend = dwInOutLen;
		}
		
		iBufOrRetLen = sizeof(szPara);
		iRet = Execute(INX_DES_ENCRYPT, szPara, iBufOrRetLen); //�ӽ���Ϊͬһ������
		if(iRet == EC_SUCCESS) 
		{
			memcpy(pCopyPos, szPara, iBufOrRetLen);
			pCopyPos += iBufOrRetLen;
		}
		else
		{
			*lpOut = 0;
			break;
		}
	}

	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = nSend;
	}
	else
	{
		dwInOutLen = 0;
	}

	return iRet;
}

/*****************************************************************************
 * ����˵��: MAC����
 * ��������: wKeyId: ����MAC����ԿID             
			 eMac : �鿴����
			 lpDataIn : ����MAC���������,���ȱ�����8�ı���
			 wInLen : ���볤��
			 lpOutData : ����8�ֽڵ�MAC������
			 lpIVdata: IV data
			 wIVid: IV id			 
 * �� �� ֵ: 0Ϊ�ɹ� 
 *****************************************************************************/
long CPinpadSimulate::Inner_MAC(WORD wKeyId, EMAC eMac, LPCSTR lpDataIn, DWORD &dwInOutLen, char *lpOut, LPCSTR lpIVdata, WORD wIVid, WORD wVI)
{
	long iRet = 0;
	char lpIV[16] = {0};
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, eMac=0x%X, dwInOutLen=%d, wIVid=0x%X.", wKeyId, eMac, dwInOutLen, wIVid);

	BYTE MacMode = 0;
	if(eMac == MAC_X9)
	{	
		MacMode = 0x41;
	}
	else if(eMac == MAC_X919 || eMac == MAC_PBOC)
	{	
		MacMode = 0x42;
	}
	else if(eMac == MAC_CBC) //CBC�㷨
	{
		MacMode = 0x43;
	}
	else if(eMac == MAC_BANKSYS) //�й�����
	{
		MacMode = 0x45;
	}
	else
	{
		return EC_UNSUPPORT;
	}

	if(NULL != lpIVdata)
	{
		memcpy(lpIV, lpIVdata, 8);
	}

	long nSend = 0; //�ѷ��͵ĳ���	
	LPCSTR pDataBegin = (char*)lpDataIn; //����λ��ָ��
	char *pCopyPos = NULL; //����λ��ָ��
	long nOffset = 19;

	while(nSend < dwInOutLen)
	{
		iRet = Authentication(wKeyId);
		if(iRet != 0)
		{
			break;
		}

		szPara[2] = LOBYTE(wKeyId);
		szPara[3] = HIBYTE(wKeyId);
		szPara[4] = LOBYTE(wVI);
		szPara[5] = HIBYTE(wVI);
		szPara[17] = MacMode;

		if(NULL != pCopyPos)
		{
			//��һ�μ��ܽ�������8�ֽڲ�����һ�ε�IV
			memcpy(lpIV, pCopyPos, 8);
		}

		if(wIVid == KEY_INVALID)
		{
			szPara[6] = LOBYTE(wKeyId);
			szPara[7] = HIBYTE(wKeyId);
			szPara[16] = 0x31; //IV data as IV
			szPara[18] = 0x32; //with IV

			memcpy(szPara + 8, lpIV, 8);
		}
		else
		{
			iRet = Authentication(wIVid);
			if(iRet != 0)
			{
				break;
			}

			szPara[6] = LOBYTE(wIVid);
			szPara[7] = HIBYTE(wIVid);
			szPara[18] = 0x32; //with IV
			if(NULL != lpIVdata)
			{
				memcpy(szPara + 8, lpIVdata, 8);
				szPara[16] = 0x32; //Decrypt(IV Data ,IV key ID) AS IV	
			}
			else
			{				
				szPara[16] = 0x30; //IV key as IV	
			}

			wIVid = KEY_INVALID; //��һ�ֶ�ֻ����ģʽIV data as IV
		}

		if(dwInOutLen - nSend > ONCE_LEN) //Ӳ��һ����������ֽ�
		{
			szPara[0] = LOBYTE(17 + ONCE_LEN); //ǰ2�ֽڷŲ�������
			szPara[1] = HIBYTE(17 + ONCE_LEN);
			memcpy(szPara + nOffset, pDataBegin + nSend, ONCE_LEN);
			nSend += ONCE_LEN;
		}
		else   //��������ݲ�����ONCE_LEN ���� ���������һ��
		{
			szPara[0] = LOBYTE(17 + dwInOutLen - nSend);
			szPara[1] = HIBYTE(17 + dwInOutLen - nSend);
			memcpy(szPara + nOffset, pDataBegin + nSend, dwInOutLen - nSend);		
			nSend = dwInOutLen;
		}
		
		iBufOrRetLen = sizeof(szPara);
		iRet = Execute(INX_MAC_CALC, szPara, iBufOrRetLen);
		if(iRet == EC_SUCCESS) 
		{
			memcpy(lpOut, szPara, iBufOrRetLen);
			pCopyPos = lpOut;
		}
		else
		{
			*lpOut = 0;
			break;
		}
	}

	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = 8;
		if(m_stCap.bSplitBankSysMAC && eMac == MAC_BANKSYS)
		{
			Bin2Hex(szPara, sizeof(szPara), lpOut, dwInOutLen);
			memcpy(lpOut, szPara, dwInOutLen);
		}
	}
	else
	{
		dwInOutLen = 0;
	}

    return iRet;
}

/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_Crypt_DES(ECRYPT eMode, LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpIV, WORD wIVLen, char *lpOut, bool bEncrypt)
{
	if(NULL == lpDataIn || NULL == lpOut || dwInOutLen == 0 || wKeyLen % 8 != 0)
	{
		return PIN_INVALID_DATA;
	}

	long iRet = 0;
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(dwInOutLen > MAX_DATA_LEN)
	{
		return PIN_DATA_TOOLONG;
	}

	char cDesMode = 0;
	if(eMode == CRYPT_DESECB || eMode == CRYPT_TRIDESECB) 
	{
		if(wKeyLen == 8)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x31;
			}
			else  //����
			{
				cDesMode = 0x41;
			}
		}
		else if(wKeyLen == 16)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x32;
			}
			else  //����
			{
				cDesMode = 0x42;
			}
		}
		else if(wKeyLen == 24)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x33;
			}
			else  //����
			{
				cDesMode = 0x43;
			}
		}
		else
		{
			return PIN_INVALID_KEY_LENGTH;
		}
	}
	else if(eMode == CRYPT_DESCBC || eMode == CRYPT_TRIDESCBC) 
	{
		if(wKeyLen == 8)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x34;
			}
			else  //����
			{
				cDesMode = 0x44;
			}
		}
		else if(wKeyLen == 16)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x35;
			}
			else  //����
			{
				cDesMode = 0x45;
			}
		}
		else if(wKeyLen == 24)
		{
			if(bEncrypt) //����
			{
				cDesMode = 0x36;
			}
			else  //����
			{
				cDesMode = 0x46;
			}
		}
		else
		{
			return PIN_INVALID_KEY_LENGTH;
		}
	}
	else 
	{
		return EC_UNSUPPORT;
	}

	if(wIVLen != 8)
	{
		wIVLen = 8;
	}

	szPara[0] = LOBYTE(1 + wKeyLen + wIVLen + dwInOutLen); //ǰ2�ֽڷŲ�������
	szPara[1] = HIBYTE(1 + wKeyLen + wIVLen + dwInOutLen);

	if(NULL != lpIV)
	{
		memcpy(szPara + 2, lpIV, wIVLen);
	}

	szPara[2 + wIVLen] = cDesMode;
	memcpy(szPara + 3 + wIVLen, lpKey, wKeyLen);
	memcpy(szPara + 3 + wIVLen + wKeyLen, lpDataIn, dwInOutLen);

	dwInOutLen = 0;
	iRet = Execute(INX_DES_RAW_ENCRYPT, szPara, iBufOrRetLen); //�ӽ���Ϊͬһ������
	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = iBufOrRetLen;
		memcpy(lpOut, szPara, iBufOrRetLen);
	}
	
	return iRet;
}

long CPinpadSimulate::RAW_MAC_DES(EMAC eMac, LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpIV, WORD wIVLen, char *lpOut)
{
	if(NULL == lpDataIn || NULL == lpOut || dwInOutLen == 0 || wKeyLen % 8 != 0)
	{
		return PIN_INVALID_DATA;
	}

	long iRet = 0;			
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(dwInOutLen > MAX_DATA_LEN)
	{
		return PIN_DATA_TOOLONG;
	}

	BYTE cMACMode = 0;
	if(eMac == MAC_X9) 
	{
		cMACMode = 0x41;
	}
	else if(eMac == MAC_X919) 
	{
		cMACMode = 0x42;
	}
	else if(eMac == MAC_CBC) 
	{
		cMACMode = 0x43;
	}
	else 
	{
		return EC_UNSUPPORT;
	}

	szPara[0] = LOBYTE(10 + wKeyLen + dwInOutLen);
	szPara[1] = HIBYTE(10 + wKeyLen + dwInOutLen);

	if(NULL != lpIV)
	{
		memcpy(szPara + 2, lpIV, 8);
	}

	szPara[10] = cMACMode;
	szPara[11] = LOBYTE(wKeyLen);
	memcpy(szPara + 12, lpKey, wKeyLen);
	memcpy(szPara + 12 + wKeyLen, lpDataIn, dwInOutLen);

	dwInOutLen = 0;
	iRet = Execute(INX_MAC_CRYPT_RAW, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = iBufOrRetLen;
		memcpy(lpOut, szPara, iBufOrRetLen);
	}
	
	return iRet;
}

/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_GenSig_RSA(LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpModulus, WORD wModulusLen, LPCSTR lpExponent, WORD wExponentLen, char *lpOut)
{
	if(NULL == lpDataIn || NULL == lpModulus || NULL == lpExponent)
	{
		return EC_POINTER_NULL;
	}

	if(wModulusLen > 512 || wExponentLen > 512)
	{
		return PIN_DATA_TOOLONG;
	}

	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	szPara[0] = LOBYTE(6 + wModulusLen + wExponentLen + dwInOutLen);
	szPara[1] = HIBYTE(6 + wModulusLen + wExponentLen + dwInOutLen);

	szPara[2] = LOBYTE(wModulusLen);
	szPara[3] = HIBYTE(wModulusLen);
	memcpy(szPara + 4, lpModulus, wModulusLen);

	szPara[4 + wModulusLen] = LOBYTE(wExponentLen);
	szPara[5 + wModulusLen] = HIBYTE(wExponentLen);
	memcpy(szPara + 6 + wModulusLen, lpExponent, wExponentLen);

	szPara[6 + wModulusLen + wExponentLen] = LOBYTE(dwInOutLen);
	szPara[7 + wModulusLen + wExponentLen] = HIBYTE(dwInOutLen);
	memcpy(szPara + 8 + wModulusLen + wExponentLen, lpDataIn, dwInOutLen);

	dwInOutLen = 0;
	long iRet = Execute(INX_RSA_SIG_RAW, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS)
	{
		dwInOutLen = iBufOrRetLen;
		if(NULL != lpOut)
		{
			memcpy(lpOut, szPara, iBufOrRetLen);
		}
	}

	return iRet;
}


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_VerifySig_RSA(LPCSTR lpDataIn, DWORD dwInLen, LPCSTR lpModulus, WORD wModulusLen, LPCSTR lpExponent, WORD wExponentLen, LPCSTR lpSigIn, WORD wSigLen)
{
	if(NULL == lpDataIn || NULL == lpModulus || NULL == lpExponent)
	{
		return EC_POINTER_NULL;
	}

	if(wModulusLen > 512 || wExponentLen > 512 || dwInLen > 512)
	{
		return PIN_DATA_TOOLONG;
	}

	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	szPara[0] = LOBYTE(6 + wModulusLen + wExponentLen + dwInLen + wSigLen); //ǰ2�ֽڷŲ�������
	szPara[1] = HIBYTE(6 + wModulusLen + wExponentLen + dwInLen + wSigLen);

	szPara[2] = LOBYTE(wModulusLen);
	szPara[3] = HIBYTE(wModulusLen);
	memcpy(szPara + 4, lpModulus, wModulusLen);

	szPara[4 + wModulusLen] = LOBYTE(wExponentLen);
	szPara[5 + wModulusLen] = HIBYTE(wExponentLen);
	memcpy(szPara + 6 + wModulusLen, lpExponent, wExponentLen);

	szPara[6 + wModulusLen + wExponentLen] = LOBYTE(dwInLen);
	szPara[7 + wModulusLen + wExponentLen] = HIBYTE(dwInLen);
	memcpy(szPara + 8 + wModulusLen + wExponentLen, lpDataIn, dwInLen);

	memcpy(szPara + 8 + wModulusLen + wExponentLen + dwInLen, lpSigIn, wSigLen);

	long iRet = Execute(INX_RSA_SIG_CHECK_RAW, szPara, iBufOrRetLen);

	return iRet;
}


/*****************************************************************************
 * ����˵��: RSAԭʼ����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_Crypt_RSA(LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpModulus, WORD wModulusLen, LPCSTR lpExponent, WORD wExponentLen, char *lpOut)
{
	if(NULL == lpDataIn || NULL == lpModulus || NULL == lpExponent)
	{
		return EC_POINTER_NULL;
	}

	if(wModulusLen > 512 || wExponentLen > 512 || dwInOutLen > 512)
	{
		return PIN_DATA_TOOLONG;
	}

	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	szPara[0] = LOBYTE(6 + wModulusLen + wExponentLen + dwInOutLen); //ǰ2�ֽڷŲ�������
	szPara[1] = HIBYTE(6 + wModulusLen + wExponentLen + dwInOutLen);

	szPara[2] = LOBYTE(wModulusLen);
	szPara[3] = HIBYTE(wModulusLen);
	memcpy(szPara + 4, lpModulus, wModulusLen);

	szPara[4 + wModulusLen] = LOBYTE(wExponentLen);
	szPara[5 + wModulusLen] = HIBYTE(wExponentLen);
	memcpy(szPara + 6 + wModulusLen, lpExponent, wExponentLen);

	szPara[6 + wModulusLen + wExponentLen] = LOBYTE(dwInOutLen);
	szPara[7 + wModulusLen + wExponentLen] = HIBYTE(dwInOutLen);
	memcpy(szPara + 8 + wModulusLen + wExponentLen, lpDataIn, dwInOutLen);

	dwInOutLen = 0;
	long iRet = Execute(INX_RSA_RAW_ENCRYPT, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS)
	{
		dwInOutLen = iBufOrRetLen;
		if(NULL != lpOut)
		{
			memcpy(lpOut, szPara, iBufOrRetLen);
		}
	}

	return iRet;
}


/***********************************************************************
 * ˵  ��: RSA���̳�ʼ�������ظ���������Կ
 * ��  ��: 
 * ��  ��: 
 **********************************************************************/
long CPinpadSimulate::Inner_RSAVendorInit(bool bSoftGenKeyPair, long nBits, LPCSTR SKOtherVendor, WORD wSKLen, LPCSTR PKOtherVendor, WORD wPKLen)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: 
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_ImpRSAKey(WORD wKeyId, LPCSTR lpDer, WORD wDerLen, LPCSTR lpSig, WORD wSigLen, ESIG_ALGORITHM eSig, WORD wSigId, LPDWORD pKCVMode, char *lpKCVRet, LPDWORD pKCVL)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: RSA����DES��Կ
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_RSAImpDESKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpTag, WORD wTagLen, bool bRandom, ESIG_ALGORITHM eSig, WORD wHostPK, WORD wDecryptId, EKCVMODE eKCV, char *lpKCVRet, WORD *lpDesKeyLen)
{
	return EC_SUCCESS;
}

long CPinpadSimulate::Cmd_RemoveInstallBySig(EINSTALL_AUTH eMode, LPCSTR lpTag, DWORD dwTagLen, WORD wKeyID)
{
	return EC_SUCCESS;
}

long CPinpadSimulate::Inner_RemoveInstallBySig(EINSTALL_AUTH eMode, LPCSTR lpKey, WORD wKeyLen, WORD wKeyID)
{
	return EC_SUCCESS;
}

/*****************************************************************************
 * ����˵��: �����ֶ�������Կ�ڲ����д���
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::Inner_VirtualBankKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpKey, long nLen, LPCSTR lpPSW, LPCSTR lpKeyboardCodes, EKCVMODE eKCV, char *lpKCVRet)
{
	return EC_SUCCESS;
}


/*****************************************************************************
 * ����˵��: �����ֶ�������Կ�ڲ���ɢ����
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::VirtualBankKeyGo(WORD wKeyId, DWORD dwKeyAttr, LPCSTR cKeyTable, long nLen, LPCSTR cPSWTable, long nPSWLen, LPCSTR cZeros, EKCVMODE eKCV, char *lpKCVRet)
{
	long nRet = 0;

	FAIL_RET(nRet, this, StartPswInput(SOUND_KEEP, PSW_ID1, PSW_OLD));
	FAIL_RET(nRet, this, VirtualPress(cPSWTable, nPSWLen));
	FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_CLOSE));
	FAIL_RET(nRet, this, StartKeyInput(SOUND_KEEP, nLen));
	FAIL_RET(nRet, this, VirtualPress(cKeyTable, nLen));
	FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_CLOSE));
	FAIL_RET(nRet, this, StoreKey(wKeyId, dwKeyAttr, KEY_SET, nLen, lpKCVRet, eKCV));
	
	FAIL_RET(nRet, this, StartPswInput(SOUND_KEEP, PSW_ID2, PSW_OLD));
	FAIL_RET(nRet, this, VirtualPress(cPSWTable + nPSWLen, nPSWLen));
	FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_CLOSE));
	FAIL_RET(nRet, this, StartKeyInput(SOUND_KEEP, nLen));
	FAIL_RET(nRet, this, VirtualPress(cZeros, nLen));
	FAIL_RET(nRet, this, OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_CLOSE));
	FAIL_RET(nRet, this, StoreKey(wKeyId, dwKeyAttr, KEY_XOR, nLen));

	//Clean text buffer
	OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_TEXT);
	OpenKeyboardAndSound(SOUND_KEEP, ENTRY_MODE_CLOSE); 

	return 0;
}

//SM2.SM3.SM4
/*****************************************************************************
 * ����˵��: ����������Կ����ǰSM4��������һ�ξ���Ч���������
 * ��������: wKeyId : ��Կ��	
			 dwKeyAttr: ��Կ����
			 iKeyLen : ��Կ����
			 eMode : ����ģʽ 
			 lpKCVRet: У�鷵��
			 eKCV : 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::SM4_StoreKey(WORD wKeyId, DWORD dwKeyAttr, EKEYMODE eMode, long iKeyLen, EKCVMODE eKCV, char *lpKCVRet)
{
	long iNum = 0;
	long iRet = 0;	
	char szPara[256] = {0};
	long iBufOrRetLen = sizeof(szPara);

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	iRet = Authentication(wKeyId, USE_KEY);
	if(EC_SUCCESS != iRet && PIN_KEY_NOT_EXIST != iRet)	//exist flag
	{
		return iRet;
	}

	DWORD wKeyAttr = ConverKeyAttr(dwKeyAttr);

	//���������а���MAC������MAC�ں���ͳһ���
	iNum = 2;//Ԥ��ǰ2�ֽڴ洢����
	szPara[iNum++] = LOBYTE(wKeyId);
	szPara[iNum++] = HIBYTE(wKeyId);
	szPara[iNum++] = eMode-0x30;
	szPara[iNum++] = LOBYTE(wKeyAttr);
	szPara[iNum++] = HIBYTE(wKeyAttr);
	szPara[iNum++] = 0x30;
	if(KCVSELF == eKCV)
	{
		szPara[iNum++] = 0x30;
	}
	else
	{
		szPara[iNum++] = 0x31;
	}
	iNum += m_stCap.ucKCVL; 

	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);


	iRet = Execute(INX_SM4_STORE_KEY, szPara, iBufOrRetLen);
	if(EC_SUCCESS == iRet)
	{
		if(NULL != lpKCVRet && eKCV != KCVNONE)
		{
			memcpy(lpKCVRet, szPara, (m_stCap.ucKCVL < iBufOrRetLen) ? m_stCap.ucKCVL : iBufOrRetLen);
		}
	}

	RLog2(LOG_LEVEL_COMMON, "iRet=%d, wKeyId=0x%X, dwKeyAttr=0x%X, eMode=0x%X", iRet, wKeyId, dwKeyAttr, eMode);

	return iRet;
}

/*****************************************************************************
 * ����˵��: ����������Կ����ǰSM4��������һ�ξ���Ч���������
 * ��������: wKeyId : ��Կ��	
			 dwKeyAttr: ��Կ����
			 lpKey : ��Կ,���ȱ���Ϊ16�ı���
			 iKeyLen : ��Կ����
			 eMode : ����ģʽ 
			 lpKCVRet: У�鷵��
			 eKCV : 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::SM4_LoadTextKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpKey, long iKeyLen, EKEYMODE eMode, EKCVMODE eKCV, char *lpKCVRet)
{	
	long iNum = 0;
	long iRet = 0;	
	char szPara[256] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(NULL == lpKey)
	{
		return EC_POINTER_NULL;
	}

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	if(IS_SM4(wKeyId, 0))
	{
		iRet = Authentication(wKeyId, USE_KEY);
		if(EC_SUCCESS != iRet && PIN_KEY_NOT_EXIST != iRet)	//exist flag
		{
			return iRet;
		}
	}
	
	DWORD wKeyAttr = ConverKeyAttr(dwKeyAttr);

	//���������а���MAC������MAC�ں���ͳһ���
	iNum = 2;//Ԥ��ǰ2�ֽڴ洢����
	szPara[iNum++] = LOBYTE(wKeyId);
	szPara[iNum++] = HIBYTE(wKeyId);
	szPara[iNum++] = eMode-0x30;
	memcpy(szPara + iNum, lpKey, iKeyLen); iNum += iKeyLen;
	szPara[iNum++] = LOBYTE(wKeyAttr);
	szPara[iNum++] = HIBYTE(wKeyAttr);

	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);

	
	iRet = Execute(INX_SM4_LOAD_TEXT_KEY, szPara, iBufOrRetLen);
	if(EC_SUCCESS == iRet)
	{
		//if(eMode == KEY_SET)
		//{
			//if(wKeyId == KEY_KBPK || wKeyId == KEY_UAK || (wKeyId <= MAX_CMM_KEY))
			//{
			//	FAIL_RET(iRet, this, SM4_LoadTextKey(wKeyId, dwKeyAttr, "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0", iKeyLen, KEY_XOR));
			//}
		//}

		if(NULL != lpKCVRet && eKCV != KCVNONE)
		{
			memcpy(lpKCVRet, szPara, (m_stCap.ucKCVL < iBufOrRetLen) ? m_stCap.ucKCVL : iBufOrRetLen);
		}
	}

	RLog2(LOG_LEVEL_COMMON, "iRet=%d, wKeyId=0x%X, dwKeyAttr=0x%X, eMode=0x%X", iRet, wKeyId, dwKeyAttr, eMode);

	return iRet;
}

long CPinpadSimulate::SM4_ExchangeKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpKey, long iKeyLen, WORD wEnKey, WORD wVI, EKEYMODE eMode, EKCVMODE eKCV, char *lpKCVRet)
{
	long iNum = 0;
	long iRet = 0;
	char szPara[256] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(NULL == lpKey)
	{
		return EC_POINTER_NULL;
	}

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	OFFSET_BASE_RIGHT(wEnKey, MIN_SM4_KEY);

	if(IS_SM4(wKeyId, 0))
	{
		iRet = Authentication(wKeyId, USE_KEY);
		if(EC_SUCCESS != iRet && PIN_KEY_NOT_EXIST != iRet)	//exist flag
		{
			return iRet;
		}
	}
	else
	{
		return PIN_INVALID_KEYID;
	}
	
	if(IS_SM4(wEnKey, 0) && wKeyId != wEnKey)
	{
		FAIL_RET(iRet, this, Authentication(wEnKey));
	}


	DWORD wKeyAttr = ConverKeyAttr(dwKeyAttr);

	//���������а���MAC������MAC�ں���ͳһ���
	iNum = 2;//Ԥ��ǰ2�ֽڴ洢����
	szPara[iNum++] = LOBYTE(wKeyId);
	szPara[iNum++] = HIBYTE(wKeyId);
	szPara[iNum++] = LOBYTE(wEnKey);
	szPara[iNum++] = HIBYTE(wEnKey);
	memcpy(szPara + iNum, lpKey, iKeyLen); iNum += iKeyLen;
	szPara[iNum++] = LOBYTE(wKeyAttr);
	szPara[iNum++] = HIBYTE(wKeyAttr);

	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);
	
	iRet = Execute(INX_SM4_EXCHANGE_KEY, szPara, iBufOrRetLen);
	if(EC_SUCCESS == iRet)
	{
		if(NULL != lpKCVRet && eKCV != KCVNONE)
		{
			memcpy(lpKCVRet, szPara, (m_stCap.ucKCVL < iBufOrRetLen) ? m_stCap.ucKCVL : iBufOrRetLen);
		}
	} 

	RLog2(LOG_LEVEL_COMMON, "iRet=%d, wEnKey=0x%X, wEnVI=0x%X, wKeyId=0x%X, dwKeyAttr=0x%X, eMode=0x%X", iRet, wEnKey, wVI, wKeyId, dwKeyAttr, eMode);
	
	return iRet;
}

/*****************************************************************************
 * ����˵��: ����SM4��Կ(��������)
 * ��������: wKeyId : ��Կ��	             
			 dwKeyAttr: ��Կ����
			 lpKey : ��Կ,���ȱ���Ϊ8�ı���(��8�ֽڵ�����0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF)
			 iKeyLen : ��Կ����
			 wEnKey: ������Կ��,ΪKEY_INVALIDʱ������������
			 eMode : ����ģʽ
			 wVI : Variation Index
			 lpKCVRet: У�鷵��
			 eKCV : KCV����ģʽ
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::SM4_LoadKey(WORD wKeyId, DWORD dwKeyAttr, LPCSTR lpKey, WORD iKeyLen, WORD wEnKey, EKEYMODE eMode, EKCVMODE eKCV, char *lpKCVRet)
{
	WORD wRealKeyId = wKeyId;
	WORD wRealEnKey = wEnKey;
	WORD wEnKeyLen = 0;
	WORD wKeyIndex = 0;
	WORD wEnVI = 0;
	long iRet = 0;
	char cKey[64] = {0};

	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, dwKeyAttr=0x%X, wKeyLen=%d, wEnKey=0x%X, EKEYMODE=0x%X, EKCVMODE=0x%X.", 
			wKeyId, dwKeyAttr, iKeyLen, wEnKey, eMode, eKCV);
	
	if(NULL == lpKey)
	{
		return EC_POINTER_NULL;
	}

	if(16 != iKeyLen)
	{
		return PIN_INVALID_COMMAND_PARA;
	}
	memcpy(cKey, lpKey, iKeyLen);

	if(m_eExtend & eEX_ENLARGE_KEY)
	{
		CHECK_MAP_ID(wKeyId);

		if(wKeyId == wRealEnKey) //����֮ǰ��key��Ϣ���ø�����Ϊmk��mk��־
		{
			m_stArtKey[wKeyId].wAppId = FLAG_DOWNSELF;

			RLog2(LOG_LEVEL_COMMON, "wKeyId=0x%X, wEnKey=0x%X, set downself flag.", wKeyId, wRealEnKey);
		}
		else
		{
			memset(&m_stArtKey[wKeyId], 0, sizeof(ARTKEY)); //�����������֤������ȷ�����
		}

		ARTKEY stArtKey;
		AELKEY stAelKey;
		iRet = GetEnlargeKeyInfo(wEnKey, ATTR_MK, stAelKey, &stArtKey);
		wEnVI = stAelKey.wVI;
		wRealEnKey = stAelKey.wEnlargeId;
		wEnKeyLen = stArtKey.wKeyLen;

		if(dwKeyAttr & ATTR_PK)
		{
			AllotEnlargeKeyId(wKeyId, dwKeyAttr, wRealKeyId, wKeyIndex);

			m_stArtKey[wKeyId].stKey[wKeyIndex].wEnlargeId = wRealKeyId;
			m_stArtKey[wKeyId].stKey[wKeyIndex].dwKeyAttr  = ATTR_PK;
			m_stArtKey[wKeyId].stKey[wKeyIndex].wVI        = 0;

			if(wRealEnKey == KEY_INVALID)
			{
				iRet = SM4_LoadTextKey(wRealKeyId, ATTR_PK, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
			}
			else
			{
				iRet = SM4_ExchangeKey(wRealKeyId, ATTR_PK, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
			}
		}

		if(dwKeyAttr & ATTR_AK)
		{
			AllotEnlargeKeyId(wKeyId, dwKeyAttr, wRealKeyId, wKeyIndex);

			m_stArtKey[wKeyId].stKey[wKeyIndex].wEnlargeId = wRealKeyId;
			m_stArtKey[wKeyId].stKey[wKeyIndex].dwKeyAttr  = ATTR_AK;
			m_stArtKey[wKeyId].stKey[wKeyIndex].wVI        = 0;

			if(wRealEnKey == KEY_INVALID)
			{
				iRet = SM4_LoadTextKey(wRealKeyId, ATTR_AK, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
			}
			else
			{
				iRet = SM4_ExchangeKey(wRealKeyId, ATTR_AK, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
			}
		}

		//��������ATTR_DK��Կ������Ӧ�ò���������ȴ���Լ�����KCV
		//if(dwKeyAttr & ATTR_DK)
		{
			AllotEnlargeKeyId(wKeyId, dwKeyAttr, wRealKeyId, wKeyIndex);

			m_stArtKey[wKeyId].stKey[wKeyIndex].wEnlargeId = wRealKeyId;
			m_stArtKey[wKeyId].stKey[wKeyIndex].dwKeyAttr  = ATTR_DK;
			m_stArtKey[wKeyId].stKey[wKeyIndex].wVI        = 0;

			if(wRealEnKey == KEY_INVALID)
			{
				iRet = SM4_LoadTextKey(wRealKeyId, ATTR_DK, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
			}
			else
			{
				iRet = SM4_ExchangeKey(wRealKeyId, ATTR_DK, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
			}
		}

		if(dwKeyAttr & ATTR_IV)
		{
			AllotEnlargeKeyId(wKeyId, dwKeyAttr, wRealKeyId, wKeyIndex);

			m_stArtKey[wKeyId].stKey[wKeyIndex].wEnlargeId = wRealKeyId;
			m_stArtKey[wKeyId].stKey[wKeyIndex].dwKeyAttr  = ATTR_IV;
			m_stArtKey[wKeyId].stKey[wKeyIndex].wVI        = 0;

			if(wRealEnKey == KEY_INVALID)
			{
				iRet = SM4_LoadTextKey(wRealKeyId, ATTR_IV, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
			}
			else
			{
				iRet = SM4_ExchangeKey(wRealKeyId, ATTR_IV, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
			}
		}

		if(dwKeyAttr & ATTR_MK)
		{
			AllotEnlargeKeyId(wKeyId, dwKeyAttr, wRealKeyId, wKeyIndex);

			m_stArtKey[wKeyId].stKey[wKeyIndex].wEnlargeId = wRealKeyId;
			m_stArtKey[wKeyId].stKey[wKeyIndex].dwKeyAttr  = ATTR_MK;
			m_stArtKey[wKeyId].stKey[wKeyIndex].wVI        = 0;

			if(wRealEnKey == KEY_INVALID)
			{
				iRet = SM4_LoadTextKey(wRealKeyId, ATTR_MK, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
			}
			else
			{
				iRet = SM4_ExchangeKey(wRealKeyId, ATTR_MK, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
			}
		}

		m_stArtKey[wKeyId].wAppId    = wKeyId;
		m_stArtKey[wKeyId].wKeyLen   = iKeyLen;
		m_stArtKey[wKeyId].dwKeyAttr = dwKeyAttr;
		m_stArtKey[wKeyId].wEnKeyId  = wRealEnKey;
		m_stArtKey[wKeyId].wEnKeyLen = wEnKeyLen;
		STRCPY_S(m_stArtKey[wKeyId].szKeyName, MAX_KEY_NAME + 1, m_szKeyNameBuf[wKeyId]);
		SaveEnlargeKey();
	}
	else
	{
		WORD dwUse = dwKeyAttr & ATTR_MWK;
		if(wEnKey == KEY_INVALID)
		{
			iRet = SM4_LoadTextKey(wKeyId, dwUse, cKey, iKeyLen, eMode, eKCV, lpKCVRet);
		}
		else
		{
			iRet = SM4_ExchangeKey(wKeyId, dwUse, cKey, iKeyLen, wRealEnKey, wEnVI, eMode, eKCV, lpKCVRet);
		}
	}
	
	return iRet;
}

/*****************************************************************************
 * ����˵��: SM4���ݼӽ��ܲ���
 * ��������: wKeyId: ������Կ��             
			 eMode :  �鿴����
			 lpDataIn : ��ӽ��ܵ�����,���ȱ�����8�ı���
			 wInLen : ����(Ҳ�����)����
			 lpOutData : �õ��ļӽ��ܽ��,�����봫�������ݳ���һ��			 
			 bEncrypt  : trueΪ���ܣ�falseΪ����
			 lpIVdata: IV data
			 wIVid: IV id			 
 * �� �� ֵ: �ɹ�Ϊ0
 *****************************************************************************/
long CPinpadSimulate::SM4_Crypt(WORD wKeyId, ECRYPT eMode, LPCSTR lpDataIn, DWORD &dwInOutLen, char *lpOut, bool bEncrypt, LPCSTR lpIVdata, WORD wIVid, WORD wVI)
{
	int iNum=0;
	long iRet = 0;
	char lpIV[16] = {0};
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, ECRYPT=0x%X, dwInOutLen=%d, bEncrypt=%d.", wKeyId, eMode, dwInOutLen, bEncrypt);

	if(NULL == lpDataIn || NULL == lpOut || (dwInOutLen % 16 != 0) || dwInOutLen == 0)
	{
		return PIN_INVALID_DATA;
	}

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	OFFSET_BASE_RIGHT(wIVid, MIN_SM4_KEY);

	if(wKeyId < MIN_SM4_KEY || wKeyId > MAX_SM4_KEY) 
	{
		return PIN_INVALID_KEYID;
	}
	
	char cAlgorithm = 0; 
	char cBlockMode = 0; 
	if(bEncrypt)
	{
		cAlgorithm = 0x31;
	}
	else
	{
		cAlgorithm = 0x32;
	}
	if(eMode == CRYPT_SM4ECB) 
	{
		cBlockMode = 0x41;
	}
	else if(CRYPT_SM4CBC == eMode)
	{
		cBlockMode = 0x42;
	}
	else 
	{
		return EC_UNSUPPORT;
	}

	if(NULL != lpIVdata)
	{
		memcpy(lpIV, lpIVdata, 16);
	}

	long nSend = 0; //�ѷ��͵ĳ���	
	const char *pDataBegin = lpDataIn; //����λ��ָ��
	char *pCopyPos = lpOut; //����λ��ָ��

	while(nSend < dwInOutLen)
	{
		FAIL_RET(iRet, this, Authentication(wKeyId));

		iNum = 2;//ǰ2�ֽ�Ԥ���洢����
		szPara[iNum++] = LOBYTE(wKeyId);
		szPara[iNum++] = HIBYTE(wKeyId);
		szPara[iNum++] = cAlgorithm;
		szPara[iNum++] = cBlockMode;

		if((pCopyPos != lpOut) && eMode == CRYPT_SM4CBC)
		{
			if(bEncrypt) //�����CBC����,��һ�μ��ܽ�������16�ֽڲ�����һ�ε�IV
			{
				memcpy(lpIV, pCopyPos - 16, 16);
			}
			else //�����CBC����,��һ�����ݵ����16�ֽڲ�����һ�ε�IV
			{
				memcpy(lpIV, pDataBegin + nSend - 16, 16);
			}
		}

		if(wIVid == KEY_INVALID)
		{		
			memcpy(szPara + iNum, lpIV, 16);
			iNum += 16;
		}
		else 
		{
			return EC_UNSUPPORT;
		}

		if(dwInOutLen - nSend > ONCE_LEN) //Ӳ��һ����������ֽ�
		{
			memcpy(szPara + iNum, pDataBegin + nSend, ONCE_LEN); 
			iNum += ONCE_LEN;
			nSend += ONCE_LEN;
			szPara[0] = LOBYTE(iNum-2); //ǰ2�ֽڷŲ�������
			szPara[1] = HIBYTE(iNum-2);			
		}
		else   //��������ݲ�����ONCE_LEN ���� ���������һ��
		{
			memcpy(szPara + iNum, pDataBegin + nSend, dwInOutLen - nSend); 
			iNum += dwInOutLen - nSend;
			nSend = dwInOutLen;
			szPara[0] = LOBYTE(iNum-2);
			szPara[1] = HIBYTE(iNum-2);	
		}
		
		iBufOrRetLen = sizeof(szPara);
		iRet = Execute(INX_SM4_CRYPT, szPara, iBufOrRetLen); //�ӽ���Ϊͬһ������
		if(iRet == EC_SUCCESS) 
		{
			memcpy(pCopyPos, szPara, iBufOrRetLen);
			pCopyPos += iBufOrRetLen;
		}
		else
		{
			*lpOut = 0;
			break;
		}
	}

	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = nSend;
	}
	else
	{
		dwInOutLen = 0;
	}

	return iRet;
}

/*****************************************************************************
 * ����˵��: SM4 MAC����
 * ��������: wKeyId: ����MAC����ԿID             
			 eMac : �鿴����
			 lpDataIn : ����MAC���������,���ȱ�����8�ı���
			 wInLen : ���볤��
			 lpOutData : ����16�ֽڵ�MAC������
			 lpIVdata: IV data
			 wIVid: IV id			 
 * �� �� ֵ: 0Ϊ�ɹ� 
 *****************************************************************************/
long CPinpadSimulate::SM4_MAC(WORD wKeyId, EMAC eMac, LPCSTR lpDataIn, DWORD &dwInOutLen, char *lpOut, LPCSTR lpIVdata, WORD wIVid, WORD wVI)
{
	int iNum = 0;
	long iRet = 0;
	char lpIV[64] = {0};
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, EMAC=0x%X, wInLen=%d.", wKeyId, eMac, dwInOutLen);

	if(NULL == lpDataIn || NULL == lpOut || dwInOutLen == 0)
	{
		return PIN_INVALID_DATA;
	}

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	OFFSET_BASE_RIGHT(wIVid, MIN_SM4_KEY);

	BYTE MacMode = 0;
	if(eMac == SM4MAC_CBC)
	{	
		MacMode = 0x40;
	}
	else if(eMac == SM4MAC_PBOC)
	{	
		MacMode = 0x43;
	}
	else
	{
		return EC_UNSUPPORT;
	}

	if(NULL != lpIVdata)
	{
		memcpy(lpIV, lpIVdata, 16);
	}

	long nSend = 0; //�ѷ��͵ĳ���	
	LPCSTR pDataBegin = (char*)lpDataIn; //����λ��ָ��
	char *pCopyPos = NULL; //����λ��ָ��
//	long nOffset = 19;

	while(nSend < dwInOutLen)
	{
		iRet = Authentication(wKeyId);
		if(iRet != 0)
		{
			break;
		}
		iNum=2;//Ԥ��2�ֽڳ���

		szPara[iNum++] = LOBYTE(wKeyId);
		szPara[iNum++] = HIBYTE(wKeyId);

		if(NULL != pCopyPos)
		{
			//��һ�μ��ܽ�������16�ֽڲ�����һ�ε�IV
			memcpy(lpIV, pCopyPos, 16);
		}

		if(wIVid == KEY_INVALID)
		{
			memcpy(szPara + iNum, lpIV, 16);
			iNum +=16;
		}
		else
		{
			return EC_UNSUPPORT;
		}
		szPara[iNum++] = MacMode;	

		if(dwInOutLen - nSend > ONCE_LEN) //Ӳ��һ����������ֽ�
		{
			memcpy(szPara + iNum, pDataBegin + nSend, ONCE_LEN); 
			iNum += ONCE_LEN;
			nSend += ONCE_LEN;
			szPara[0] = LOBYTE(iNum-2); //ǰ2�ֽڷŲ�������
			szPara[1] = HIBYTE(iNum-2);
		}
		else   //��������ݲ�����ONCE_LEN ���� ���������һ��
		{
			memcpy(szPara + iNum, pDataBegin + nSend, dwInOutLen - nSend); 
			iNum += dwInOutLen - nSend;	
			nSend = dwInOutLen;
			szPara[0] = LOBYTE(iNum-2);
			szPara[1] = HIBYTE(iNum-2);			
		}
		
		iBufOrRetLen = sizeof(szPara);
		iRet = Execute(INX_SM4_MAC, szPara, iBufOrRetLen);
		if(iRet == EC_SUCCESS) 
		{
			memcpy(lpOut, szPara, iBufOrRetLen);
			pCopyPos = lpOut;
		}
		else
		{
			*lpOut = 0;
			break;
		}
	}

	if(iRet == 0)
	{
		dwInOutLen = 16;
	}
	else
	{
		dwInOutLen = 0;
	}

    return iRet;
}

/*****************************************************************************
 * ����˵��: ��ȡ�����(SM4����)
 * ��������: 
             wKeyId: ������Կ1
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::SM4_GetPinBlock(WORD wKeyId, BYTE PinLen, EPINFORMAT ePinFormat, LPCSTR lpCardNo, char *pPinBlock, WORD &wOutLen, BYTE Padding, WORD wKeyId2, WORD wVI, WORD wVI2)
{
	wOutLen = 0;
	int iNum = 0;
	long iRet = 0;
	char szPara[128] = {0};
	long iBufOrRetLen = sizeof(szPara);
	char szInitialPinPatern[64] = {0};
	char szCustomerData[64] = {0};
	BYTE PinOffset = 0;
	BYTE PinPostion = 0;

	RLog2(LOG_LEVEL_DEBUG, "wKeyId=0x%X, EPINFORMAT=0x%X, PinLen=%d, Padding=0x%X.", wKeyId, ePinFormat, PinLen, Padding);

	OFFSET_BASE_RIGHT(wKeyId, MIN_SM4_KEY);

	OFFSET_BASE_RIGHT(wKeyId2, MIN_SM4_KEY);

	if(wKeyId < MIN_SM4_KEY || wKeyId > MAX_SM4_KEY || NULL == pPinBlock)
	{
		return PIN_INVALID_COMMAND_PARA;
	}

	FAIL_RET(iRet, this, OpenKeyboardAndSound(SOUND_CLOSE, ENTRY_MODE_CLOSE));

	FAIL_RET(iRet, this, PinFillFormat(ePinFormat, PinLen, Padding, lpCardNo, PinOffset, PinPostion, szInitialPinPatern, szCustomerData));	

	FAIL_RET(iRet, this, Authentication(wKeyId, USE_KEY));


	szPara[iNum++] = LOBYTE(wKeyId);
	szPara[iNum++] = HIBYTE(wKeyId);

	if(wKeyId2 == KEY_INVALID)
	{
		szPara[iNum++] = 0x01; //single
		szPara[iNum++] = LOBYTE(wKeyId);
		szPara[iNum++] = HIBYTE(wKeyId);
	}
	else
	{
		szPara[iNum++] = 0x02; //double
		szPara[iNum++] = LOBYTE(wKeyId2);
		szPara[iNum++] = HIBYTE(wKeyId2);
	}

	if(m_stCap.ePinpadType == ePIN_PCI_3X)
	{
		szPara[iNum++] = FORMAT_FREE;
	}
	else
	{
		szPara[iNum++] = ConvertFormat(ePinFormat);
	}
	
	memcpy(szPara + iNum, szInitialPinPatern, 16); 
	iNum += 16;
	szPara[iNum++] = PinPostion;//PinOffset
	szPara[iNum++] = PinLen;
	memcpy(szPara + iNum + 8, szCustomerData, 8);
	iNum += 16;
	iNum += 16;//XORData2, set to 16's 0x00
	
	iRet = Execute(INX_SM4_GET_PIN_BLOCK, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS) 
	{
		wOutLen = iBufOrRetLen;
		memcpy(pPinBlock, szPara, iBufOrRetLen);
	}

 	return iRet; 
}

long CPinpadSimulate::Inner_SM2VendorInit(bool bSoftGenKeyPair, LPCSTR lpIDa, WORD wIDLen, LPCSTR SKOtherVendor, WORD wSKLen, LPCSTR PKOtherVendor, WORD wPKLen)
{
	return EC_SUCCESS;
}


long CPinpadSimulate::SM2_Encrypt(WORD wKeyId, LPCSTR lpDataIn, DWORD &dwInOutLen, char *lpOut)
{
	if(NULL == lpDataIn)
	{
		return EC_POINTER_NULL;
	}

	if(dwInOutLen > (2048 - 97 - 2))
	{
		return PIN_DATA_TOOLONG;
	}

	long iRet = 0;
	WORD wRealHostPK = wKeyId;
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	OFFSET_BASE_RIGHT(wRealHostPK, _EPP_SM2_CRYPT_PK);

	RLog2(LOG_LEVEL_COMMON, "wKeyId=%d, wRealHostPK=%d, dwInLen=%d", wKeyId, wRealHostPK, dwInOutLen);

	szPara[0] = LOBYTE(2 + dwInOutLen); //ǰ2�ֽڷŲ�������
	szPara[1] = HIBYTE(2 + dwInOutLen);

	szPara[2] = LOBYTE(wRealHostPK);
	szPara[3] = HIBYTE(wRealHostPK);
	memcpy(szPara + 4, lpDataIn, dwInOutLen);

	iRet = Execute(INX_SM2_ENCRYPT, szPara, iBufOrRetLen);
	if(iRet == EC_SUCCESS)
	{
		if(NULL != lpOut && iBufOrRetLen > 1)
		{
			if(iBufOrRetLen == dwInOutLen + 32 + 64 + 1) //ȥ��04
			{
				dwInOutLen = iBufOrRetLen - 1;
				memcpy(lpOut, szPara + 1, dwInOutLen);
			}
			else
			{
				dwInOutLen = iBufOrRetLen;
				memcpy(lpOut, szPara, iBufOrRetLen);
			}
		}
	}
	else
	{
		dwInOutLen = 0;
	}

	return iRet;
}

/*****************************************************************************
 * ����˵��: SM2 RAW������Կ��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_SM2_GenKeys(char *lpSK, WORD &wSKLen, char *lpPK, WORD &wPKLen)
{
	RLog2(LOG_LEVEL_DATA, "Enter");
	  
	long iNum = 0;
	long iRet = 0;	
	char szPara[1024] = {0};
	long iBufOrRetLen = sizeof(szPara);
	
	iRet = Execute(INX_SM2_GENERATE_KEY_PAIR_RAW, szPara, iBufOrRetLen);
	if(EC_SUCCESS == iRet)
	{
		if( 96 > iBufOrRetLen)
		{
			return EC_INVALID_PARA;
		}
		else
		{
			if(ePIN_VISA & m_stCap.ePinpadType)
			{
				Hex2Bin(lpSK, 32, szPara, 64);
				Hex2Bin(lpPK, 64, szPara, 128);
			}
			else
			{
				memcpy(lpSK, szPara, 32);
				memcpy(lpPK, szPara, 64);
			}

			wSKLen = 32;
			wPKLen = 64;
		}
	}
	RLog2(LOG_LEVEL_COMMON, "iRet=%d", iRet);

	return iRet;
}

/*****************************************************************************
 * ����˵��: SM2 RAW�ӽ���
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_Crypt_SM2(LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpIV, WORD wIVLen, char *lpOut, bool bEncrypt)
{
	RLog2(LOG_LEVEL_DATA, "dwInOutLen=%d, wKeyLen=%d", dwInOutLen, wKeyLen);
	
	long iRet = 0;	
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	long iNum = 2;
	memcpy(szPara+iNum, lpKey, wKeyLen); 
	iNum += wKeyLen;
	memcpy(szPara+iNum, lpDataIn, dwInOutLen); 
	iNum += dwInOutLen;

	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);

	if(bEncrypt)
	{
		iRet = Execute(INX_SM2_ENCRYPT_RAW, szPara, iBufOrRetLen);
	}
	else
	{
		iRet = Execute(INX_SM2_DECRYPT_RAW, szPara, iBufOrRetLen);
	}

	if(EC_SUCCESS == iRet)
	{
		if(1 > iBufOrRetLen)
		{
			return EC_INVALID_PARA;
		}
		else
		{
			if(iBufOrRetLen == dwInOutLen + 32 + 64 + 1) //ȥ��04
			{
				dwInOutLen = iBufOrRetLen - 1;
				memcpy(lpOut, szPara + 1, dwInOutLen);
			}
			else
			{
				dwInOutLen = iBufOrRetLen;
				memcpy(lpOut, szPara, iBufOrRetLen);
			}
		}
	}
	else
	{
		dwInOutLen = 0;
	}

	RLog2(LOG_LEVEL_DEBUG, "iRet=%d OutLen=%d", iRet, dwInOutLen);
	return iRet;
}

/*****************************************************************************
 * ����˵��: SM2 RAWǩ��
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_GenSig_SM2(LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpEx, WORD wExLen, char *lpOut)
{
	RLog2(LOG_LEVEL_DATA, "dwInOutLen=%d, wKeyLen=%d, nZLen=%d", dwInOutLen, wKeyLen, wExLen);

	long iRet = 0;	
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	long iNum = 2;
	memcpy(szPara+iNum, lpKey, wKeyLen); 
	iNum += wKeyLen;
	memcpy(szPara+iNum, lpEx, wExLen); 
	iNum += wExLen;
	memcpy(szPara+iNum, lpDataIn, dwInOutLen); 
	iNum += dwInOutLen;
	
	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);

	iRet = Execute(INX_SM2_SIGN_RAW, szPara, iBufOrRetLen);

	dwInOutLen = 0;
	if(EC_SUCCESS == iRet)
	{
		if( 64 != iBufOrRetLen)
		{
			return EC_INVALID_PARA;
		}
		else
		{
			dwInOutLen = iBufOrRetLen;
			memcpy(lpOut, szPara, iBufOrRetLen);
		}
	}

	RLog2(LOG_LEVEL_DEBUG, "iRet=%d", iRet);

	return iRet;
}

/*****************************************************************************
 * ����˵��: SM2 RAW��ǩ
 * ��������: 
 * �� �� ֵ:  
 *****************************************************************************/
long CPinpadSimulate::RAW_VerifySig_SM2(LPCSTR lpDataIn, DWORD dwInLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpEx, WORD wExLen, LPCSTR lpSigIn, WORD wSigLen)
{
	RLog2(LOG_LEVEL_DATA, "dwInLen=%d, wKeyLen=%d, nZLen=%d, wSigLen=%d", dwInLen, wKeyLen, wExLen, wSigLen);

	if(NULL == lpDataIn || NULL == lpKey || NULL == lpEx || NULL == lpSigIn)
	{
		return EC_POINTER_NULL;
	}
	
	long iRet = 0;	
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	long iNum = 2;
	memcpy(szPara+iNum, lpKey, wKeyLen); 
	iNum += wKeyLen;
	memcpy(szPara+iNum, lpEx, wExLen); 
	iNum += wExLen;
	memcpy(szPara+iNum, lpDataIn, dwInLen); 
	iNum += dwInLen;
	memcpy(szPara+iNum, lpSigIn, wSigLen);
	iNum += wSigLen;
	
	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);

	iRet = Execute(INX_SM2_VERIFY_SIGNATURE_RAW, szPara, iBufOrRetLen);

	RLog2(LOG_LEVEL_DEBUG, "iRet=%d", iRet);

	return iRet;
}

long CPinpadSimulate::RAW_Crypt_SM4(ECRYPT eMode, LPCSTR lpDataIn, DWORD &dwInOutLen, LPCSTR lpKey, WORD wKeyLen, LPCSTR lpIV, WORD wIVLen, char *lpOut, bool bEncrypt)
{
	if(NULL == lpDataIn || NULL == lpOut || dwInOutLen == 0 || wKeyLen % 16 != 0)
	{
		return PIN_INVALID_DATA;
	}

	long iRet = 0, iNum = 0;
	BYTE lpIVData[16] = {0};
	char szPara[MAX_PACKET_LEN] = {0};
	long iBufOrRetLen = sizeof(szPara);

	if(dwInOutLen > MAX_DATA_LEN)
	{
		return PIN_DATA_TOOLONG;
	}

	BYTE bMode = 0;
	if(eMode == CRYPT_SM4ECB) 
	{
		if(bEncrypt) 
			bMode = 0x31;	
		else 
			bMode = 0x41;	
	}
	else if(eMode == CRYPT_SM4CBC) 
	{
		if(bEncrypt) 
			bMode = 0x32;	
		else 
			bMode = 0x42;	

		if(wIVLen == 16)
		{
			memcpy(lpIVData,lpIV,16);
		}
		else if(0 != wIVLen)
		{
			return PIN_INVALID_DATA;
		}
	}
	else 
	{
		return EC_UNSUPPORT;
	}

	//���������а���MAC������MAC�ں���ͳһ���
	iNum = 2;//Ԥ��ǰ2�ֽڴ洢����
	szPara[iNum++] = bMode;
	memcpy(szPara + iNum, lpKey, wKeyLen); iNum += wKeyLen;
	if(eMode == CRYPT_SM4CBC) 
	{
		memcpy(szPara + iNum, lpIVData, 16); iNum += 16;
	}
	memcpy(szPara + iNum, lpDataIn, dwInOutLen); iNum += dwInOutLen;

	szPara[0] = LOBYTE(iNum-2); //ǰ2���ֽڷų���
	szPara[1] = HIBYTE(iNum-2);

	iRet = Execute(INX_SM4_CYRPT_RAW, szPara, iBufOrRetLen); //�ӽ���Ϊͬһ������
	if(iRet == EC_SUCCESS) 
	{
		dwInOutLen = iBufOrRetLen;
		memcpy(lpOut, szPara, iBufOrRetLen);
	}

	return iRet;
}

long CPinpadSimulate::RI_RandomData(DWORD &dwInOutLen, char *pRandom)
{
	return EC_SUCCESS;
}
