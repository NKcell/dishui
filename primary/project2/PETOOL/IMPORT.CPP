#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"

extern HINSTANCE happInstance;

void initDLLNAME(HWND hDlg){
	LV_COLUMN lv;
	HWND hDllName;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
									
	hDllName = GetDlgItem(hDlg,IDC_LIST_DLLNAME);																
	SendMessage(hDllName,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("NAME");								
	lv.cx = 300;							
	lv.iSubItem = 0;
	SendMessage(hDllName,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	enumImportDll(hDllName);
}

void initDLLINFO(HWND hDlg){
	LV_COLUMN lv;
	HWND hDllInfo;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
								
	hDllInfo = GetDlgItem(hDlg,IDC_LIST_DLLINFO);																
	SendMessage(hDllInfo,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("NAME");				
	lv.cx = 180;
	lv.iSubItem = 0;																
	SendMessage(hDllInfo,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
								
	lv.pszText = TEXT("HIT");								
	lv.cx = 120;								
	lv.iSubItem = 1;																
	SendMessage(hDllInfo,LVM_INSERTCOLUMN,1,(DWORD)&lv);								
}

BOOL CALLBACK DialogIMPORT(									
						 HWND hwndDlg,  // handle to dialog box			
						 UINT uMsg,     // message			
						 WPARAM wParam, // first message parameter			
						 LPARAM lParam  // second message parameter			
						 )			
{									
									
	switch(uMsg)								
	{								
		case  WM_INITDIALOG :
		{	
			HICON hMyIcon = LoadIcon(happInstance, MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (DWORD)hMyIcon);
			SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (DWORD)hMyIcon);
			initDLLNAME(hwndDlg);
			initDLLINFO(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{							
			break;
		}
		case WM_NOTIFY:
		{
			NMHDR*  pNM=(NMHDR*)lParam;
             
            if(pNM->idFrom==IDC_LIST_DLLNAME && pNM->code==NM_CLICK)
            {
                EnumDLLINFO(GetDlgItem(hwndDlg, IDC_LIST_DLLNAME), wParam, lParam, GetDlgItem(hwndDlg, IDC_LIST_DLLINFO));
                return TRUE;        
            }
			break;
		}
		case WM_CLOSE:
		{
			EndDialog(hwndDlg, wParam);
			return TRUE;
		}								
    }																		
	return FALSE ;								
}

void setImport(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_IMPORT), hwndDlg, (DLGPROC)DialogIMPORT);
}