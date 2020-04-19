#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"

extern HINSTANCE happInstance;

void initEXPORTLVM(HWND hDlg){
	LV_COLUMN lv;
	HWND hListExport;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
								
	hListExport = GetDlgItem(hDlg,IDC_LIST_EXPORT);																
	SendMessage(hListExport,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Name");			
	lv.cx = 220;
	lv.iSubItem = 0;																
	SendMessage(hListExport,LVM_INSERTCOLUMN,0,(DWORD)&lv);
	
	lv.pszText = TEXT("Ordinal");								
	lv.cx = 100;								
	lv.iSubItem = 1;																
	SendMessage(hListExport,LVM_INSERTCOLUMN,1,(DWORD)&lv);

	lv.pszText = TEXT("RVA");								
	lv.cx = 100;								
	lv.iSubItem = 2;																
	SendMessage(hListExport,LVM_INSERTCOLUMN,2,(DWORD)&lv);

	enumExport(hDlg,hListExport);
}

BOOL CALLBACK DialogEXPORT(									
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
			initEXPORTLVM(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{							
			break;
		}
		case WM_NOTIFY:
		{
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

void setExport(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_EXPORT), hwndDlg, (DLGPROC)DialogEXPORT);
}