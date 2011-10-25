#ifndef _REGISTER_KEY_H_INCLUDE_
#define _REGISTER_KEY_H_INCLUDE_

#include   <winreg.h>

class CRegisterKey    
{
public:
	LONG   Read(LPCTSTR   pszKey   ,   BYTE   *pData   ,   DWORD   &   dwLength);
	LONG   Read(LPCTSTR   pszKey,   CString   &sVal);
	LONG   Read(LPCTSTR   pszKey   ,   DWORD   &   dwVal);
	LONG   Write(LPCTSTR   pszKey   ,   const   BYTE   *pData   ,   DWORD   dwLength);
	LONG   Write(LPCTSTR   pszKey   ,   CString   pszVal);
	LONG   Write(LPCTSTR   pszKey   ,   DWORD   dwVal);
	void   Close();
	LONG   Open(HKEY   hKeyRoot   ,   CString   pszPath   ,   REGSAM   dwAccess   =   KEY_ALL_ACCESS);
	CRegisterKey();
	virtual   ~CRegisterKey();

protected:
	CString   m_sPath;
	HKEY   m_hKey;
}; 

#endif