#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"

extern HINSTANCE happInstance;

void initBOUNDLVM(HWND hDlg){
	LV_COLUMN lv;
	HWND hListBound;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
								
	hListBound = GetDlgItem(hDlg,IDC_LIST_BOUND);																
	SendMessage(hListBound,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Name");			
	lv.cx = 180;
	lv.iSubItem = 0;																
	SendMessage(hListBound,LVM_INSERTCOLUMN,0,(DWORD)&lv);
	
	lv.pszText = TEXT("TimeDataStamp");								
	lv.cx = 150;								
	lv.iSubItem = 1;																
	SendMessage(hListBound,LVM_INSERTCOLUMN,1,(DWORD)&lv);
	
	enumBound(hListBound);
}

BOOL CALLBACK DialogBOUND(									
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
			initBOUNDLVM(hwndDlg);
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

void setBound(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_BOUND), hwndDlg, (DLGPROC)DialogBOUND);
}