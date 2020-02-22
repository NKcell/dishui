#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"

extern HINSTANCE happInstance;

void initTYPEID(HWND hDlg){
	LV_COLUMN lv;
	HWND hTYPEID;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
									
	hTYPEID = GetDlgItem(hDlg,IDC_LIST_TYPEID);																
	SendMessage(hTYPEID,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Type");								
	lv.cx = 300;							
	lv.iSubItem = 0;
	SendMessage(hTYPEID,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	enumTYPEID(hTYPEID);
}

void initSIGNID(HWND hDlg){
	LV_COLUMN lv;
	HWND hSIGNID;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
								
	hSIGNID = GetDlgItem(hDlg,IDC_LIST_SIGN);																
	SendMessage(hSIGNID,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("SIGN");				
	lv.cx = 180;
	lv.iSubItem = 0;																
	SendMessage(hSIGNID,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
								
	lv.pszText = TEXT("RVA");								
	lv.cx = 120;								
	lv.iSubItem = 1;																
	SendMessage(hSIGNID,LVM_INSERTCOLUMN,1,(DWORD)&lv);
	
	lv.pszText = TEXT("SIZE");								
	lv.cx = 120;								
	lv.iSubItem = 2;																
	SendMessage(hSIGNID,LVM_INSERTCOLUMN,2,(DWORD)&lv);	
}

BOOL CALLBACK DialogRESOURCE(									
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
			initTYPEID(hwndDlg);
			initSIGNID(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{							
			break;
		}
		case WM_NOTIFY:
		{
			NMHDR*  pNM=(NMHDR*)lParam;
             
            if(pNM->idFrom==IDC_LIST_TYPEID && pNM->code==NM_CLICK)
            {
                EnumSIGN(GetDlgItem(hwndDlg, IDC_LIST_TYPEID), wParam, lParam, GetDlgItem(hwndDlg, IDC_LIST_SIGN));
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

void setResource(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_RESOURCE), hwndDlg, (DLGPROC)DialogRESOURCE);
}