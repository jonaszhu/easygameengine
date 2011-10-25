; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "mole������Ϸƽ̨"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "mole���������"
!define PRODUCT_WEB_SITE "http://www.mole2d.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\MolGameClient.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ���Э��ҳ��
!insertmacro MUI_PAGE_LICENSE "LICENSE.TXT"
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\MolGameClient.exe"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "MoleGameSetup.exe"
InstallDir "$PROGRAMFILES\mole������Ϸƽ̨"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "MolGameClient.exe"
  CreateDirectory "$SMPROGRAMS\mole������Ϸƽ̨"
  CreateShortCut "$SMPROGRAMS\mole������Ϸƽ̨\mole������Ϸƽ̨.lnk" "$INSTDIR\MolGameClient.exe"
  CreateShortCut "$DESKTOP\mole������Ϸƽ̨.lnk" "$INSTDIR\MolGameClient.exe"
  File "Mole2d.dll"
  File "MolCrashRptSender.exe"
  File "MolCrashRpt.dll"
  File "dbghelp.dll"
  File "clientconfig.ini"
  File "bass.dll"
  File "LICENSE.TXT"
  File "MFC71.dll"
  File "msvcp71.dll"
  File "msvcr71.dll"  
  File /r "gameroomconfig"
  File /r "Avatars"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\mole������Ϸƽ̨\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\mole������Ϸƽ̨\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\MolGameClient.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\MolGameClient.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\MolGameClient.exe"
  Delete "$INSTDIR\bass.dll"
  Delete "$INSTDIR\dbghelp.dll"
  Delete "$INSTDIR\LICENSE.TXT"
  Delete "$INSTDIR\MFC71.dll"
  Delete "$INSTDIR\MolCrashRpt.dll"
  Delete "$INSTDIR\clientconfig.ini"  
  Delete "$INSTDIR\mole2d.log"  
  Delete "$INSTDIR\MolCrashRptSender.exe"
  Delete "$INSTDIR\Mole2d.dll"
  Delete "$INSTDIR\msvcp71.dll"
  Delete "$INSTDIR\msvcr71.dll"

  Delete "$SMPROGRAMS\mole������Ϸƽ̨\Uninstall.lnk"
  Delete "$SMPROGRAMS\mole������Ϸƽ̨\Website.lnk"
  Delete "$DESKTOP\mole������Ϸƽ̨.lnk"
  Delete "$SMPROGRAMS\mole������Ϸƽ̨\mole������Ϸƽ̨.lnk"
  
  RMDir "$SMPROGRAMS\mole������Ϸƽ̨"

  RMDir /r "$INSTDIR\Avatars"
  RMDir /r "$INSTDIR\gameroomconfig"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd
