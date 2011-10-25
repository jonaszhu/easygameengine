#include "stdafx.h"

#include "RegisterKey.h"

//////////////////////////////////////////////////////////////////////
//   Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegisterKey::CRegisterKey()
{
	m_hKey   =   NULL;
}

CRegisterKey::~CRegisterKey()
{
	Close();
}

LONG   CRegisterKey::Open(HKEY   hKeyRoot,   CString   pszPath   ,   REGSAM   dwAccess)
{
	DWORD   dw;
	m_sPath   =   pszPath;

	return   RegCreateKeyEx(hKeyRoot   ,   pszPath   ,   0L   ,   NULL   ,   REG_OPTION_NON_VOLATILE   ,  
		dwAccess   ,   NULL   ,   &m_hKey   ,   &dw);
}

void   CRegisterKey::Close()
{
	if(m_hKey)
	{
		RegCloseKey(m_hKey);
		m_hKey   =   NULL;
	}
}

LONG   CRegisterKey::Write(LPCTSTR   pszKey,   DWORD   dwVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	return   RegSetValueEx(m_hKey   ,   pszKey   ,   0L   ,   REG_DWORD   ,   (LPBYTE)   &dwVal   ,
		sizeof(DWORD));
}

LONG   CRegisterKey::Write(LPCTSTR   pszKey,   CString   pszVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);
	ASSERT(pszVal);
	ASSERT(AfxIsValidAddress(pszVal   ,   pszVal.GetLength()   ,   FALSE));

	return   RegSetValueEx(m_hKey   ,   pszKey   ,   0L   ,   REG_SZ   ,   (LPBYTE)   pszVal.GetBuffer()   ,  
		pszVal.GetLength()*sizeof(TCHAR)+1);
}

LONG   CRegisterKey::Write(LPCTSTR   pszKey,   const   BYTE   *pData,   DWORD   dwLength)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);
	ASSERT(pData   &&   dwLength> 0);
	ASSERT(AfxIsValidAddress(pData   ,   dwLength   ,   FALSE));

	return   RegSetValueEx(m_hKey   ,   pszKey   ,   0L   ,   REG_BINARY   ,   (LPBYTE)pData   ,   dwLength);
}

LONG   CRegisterKey::Read(LPCTSTR   pszKey,   DWORD   &dwVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD   dwType;
	DWORD   dwSize   =   sizeof(DWORD);
	DWORD   dwDest;

	LONG   lRet   =   RegQueryValueEx(m_hKey   ,   pszKey   ,   NULL   ,   &dwType   ,   (LPBYTE)   &dwDest   ,   &dwSize);

	if(lRet   ==   ERROR_SUCCESS)
		dwVal   =   dwDest;

	return   lRet;
}

LONG   CRegisterKey::Read(LPCTSTR   pszKey,   CString   &sVal)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD   dwType;
	DWORD   dwSize   =   512;
	TCHAR  string[512];

	LONG   lRet   =   RegQueryValueEx(m_hKey   ,   pszKey   ,   NULL   ,   &dwType   ,   (LPBYTE)   string   ,   &dwSize);

	if(lRet   ==   ERROR_SUCCESS)
		sVal   =   string;

	return   lRet;
}

LONG   CRegisterKey::Read(LPCTSTR   pszKey,   BYTE   *pData,   DWORD   &dwLength)
{
	ASSERT(m_hKey);
	ASSERT(pszKey);

	DWORD   dwType;

	return   RegQueryValueEx(m_hKey   ,   pszKey   ,   NULL   ,   &dwType   ,   pData   ,   &dwLength);
} 