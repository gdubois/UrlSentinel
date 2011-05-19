
; declare constants
!define QT_DIR "C:\Qt\4.7.3" 
!define QT_DLL_DIR "${QT_DIR}\bin"


!define COMPANY "Kami Systems"
!define PRODUCT "UrlSentinel"
!define EXE "UrlSentinel.exe"
!define VERSION "1.0" ;Define your own SOFTWARE version here
!define BUILD "Release"
Name "${PRODUCT} ${VERSION}" ;Display name for installer

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"
  
;--------------------------------
;Interface Settings

	!define MUI_ABORTWARNING
	!define VISION_ICON "..\Pictures\AppIcon.ico"                ; icône de l’installateur
	!define MUI_ICON "..\Pictures\AppIcon.ico"                  ; icône d’installation
	!define SPLASHIMAGE "..\Pictures\NoUpdate.png" ; Si vous voulez ajouter un splashscreen au lanceur, commentez (via un point virgule) la ligne si vous ne voulez pas d’image de présentation.
	;!define MUI_WELCOMEFINISHPAGE_BITMAP "win.bmp"     ; bandeau de gauche
	;!define MUI_UNICON "..\AppIcon.ico" 
	!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
	
;--------------------------------
;Pages

	;!insertmacro MUI_PAGE_WELCOME
	!define MUI_LICENSEPAGE_TEXT_TOP ""
	!insertmacro MUI_PAGE_LICENSE "..\Licenses\LICENSE.txt"
	!insertmacro MUI_PAGE_DIRECTORY
	!insertmacro MUI_PAGE_INSTFILES
	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro MUI_UNPAGE_INSTFILES
	!define MUI_FINISHPAGE_RUN "$INSTDIR\${EXE}"
	!insertmacro MUI_PAGE_FINISH
  
;--------------------------------
;Languages
 
  ;!insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;General
	
  ;Name and file
  OutFile "${PRODUCT} ${BUILD} Setup - ${VERSION}.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${COMPANY}\${PRODUCT}"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "SOFTWARE\${COMPANY}\${PRODUCT}" ""
  
  ;Vista redirects $SMPROGRAMS to all users without this
  ;RequestExecutionLevel admin
  
  ; The text to prompt the user to enter a directory
  DirText "This will install ${PRODUCT} on your computer. Choose a directory"
  
;--------------------------------
;Installer Sections

Section "Install" Install

  SetOutPath "$INSTDIR"
  
  File "..\bin\${BUILD}\${EXE}"
  
  ;Use local DLL
  FileOpen $9 "${EXE}.local" w ;Opens a Empty File an fills it
  FileWrite $9 "local dlls"
  FileClose $9 ;Closes the filled file
  
  ;Qt DLL
  ;File "${QT_DLL_DIR}\libgcc_s_dw2-1.dll"
  File "${QT_DLL_DIR}\QtCore4.dll"
  File "${QT_DLL_DIR}\QtGui4.dll"
  File "${QT_DLL_DIR}\QtNetwork4.dll"
  
  
  ;MinGW32 DLL
  File "C:\MinGW\bin\mingwm10.dll"
  ;File "Readme.txt"
  
  ;Language files
  SetOutPath "$INSTDIR\Language"
  File "..\Language\*"
  
  ;Icons
  SetOutPath "$INSTDIR\Pictures"
  File "..\Pictures\*"
  
  ;License files
  SetOutPath "$INSTDIR\Licenses"
  File "..\Licenses\*"
  
   ;Help Files
  ;SetOutPath "$INSTDIR\Help"
  ;File "..\Help\*"
  
  SetOutPath "$INSTDIR"
  
  ;Store installation folder
  WriteRegStr HKCU "SOFTWARE\${COMPANY}\${PRODUCT}" "" $INSTDIR
  
  
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  ;Create StartMenu Entries
  CreateDirectory "$SMPROGRAMS\${COMPANY}"
  CreateShortCut "$SMPROGRAMS\${COMPANY}\${PRODUCT}.lnk" "$INSTDIR\${EXE}"
  CreateShortCut "$SMPROGRAMS\${COMPANY}\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  ; //////// CREATE REGISTRY KEYS TO ADD/REMOVE PROGRAMS IN CONTROL PANEL /////////

WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT} ${VERSION}" "DisplayName"\
"${PRODUCT} (remove only)"

WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT} ${VERSION}" "UninstallString" \
"$INSTDIR\Uninstall.exe"


; //////////////////////// END CREATING REGISTRY KEYS ////////////////////////////

MessageBox MB_OK "Installation of ${PRODUCT} successful."

SectionEnd


;--------------------------------
;Uninstaller Section

Section "Uninstall"

 	
  Delete "$INSTDIR\*"
  
  Delete "$INSTDIR\Language\*"
  RMDir "$INSTDIR\Language"
  
  Delete "$INSTDIR\Pictures\*"
  RMDir "$INSTDIR\Pictures"
  
  Delete "$INSTDIR\Licenses\*"
  RMDir "$INSTDIR\Licenses"
  

  Delete "$INSTDIR\Uninstall.exe"

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "SOFTWARE\${COMPANY}"
  
  ;Delete Control Panel Uninstall String
   DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT} ${VERSION}"
  ; Now remove shortcuts too
Delete "$SMPROGRAMS\${COMPANY}\${PRODUCT}.lnk"
Delete "$SMPROGRAMS\${COMPANY}\Uninstall.lnk"

RMDIR "$SMPROGRAMS\${COMPANY}"

SectionEnd
