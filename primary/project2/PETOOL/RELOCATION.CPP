#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"

extern HINSTANCE happInstance;

void initRELOC1(HWND hDlg){
	LV_COLUMN lv;
	HWND hRELOC;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
									
	hRELOC = GetDlgItem(hDlg,IDC_LIST_RELOC1);																
	SendMessage(hRELOC,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Index");								
	lv.cx = 120;							
	lv.iSubItem = 0;
	SendMessage(hRELOC,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	lv.pszText = TEXT("RVA");								
	lv.cx = 120;								
	lv.iSubItem = 1;																
	SendMessage(hRELOC,LVM_INSERTCOLUMN,1,(DWORD)&lv);

	lv.pszText = TEXT("SizeOfBlock");								
	lv.cx = 120;								
	lv.iSubItem = 2;																
	SendMessage(hRELOC,LVM_INSERTCOLUMN,2,(DWORD)&lv);

	EnumRELOCATION1(hRELOC);
}

void initRELOC2(HWND hDlg){
	LV_COLUMN lv;
	HWND hRELOC;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
									
	hRELOC = GetDlgItem(hDlg,IDC_LIST_RELOC2);																
	SendMessage(hRELOC,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
																	
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Index");								
	lv.cx = 120;							
	lv.iSubItem = 0;
	SendMessage(hRELOC,LVM_INSERTCOLUMN,0,(DWORD)&lv);

	lv.pszText = TEXT("RVA");								
	lv.cx = 120;								
	lv.iSubItem = 1;																
	SendMessage(hRELOC,LVM_INSERTCOLUMN,1,(DWORD)&lv);

	lv.pszText = TEXT("Type");								
	lv.cx = 120;								
	lv.iSubItem = 2;																
	SendMessage(hRELOC,LVM_INSERTCOLUMN,2,(DWORD)&lv);

}

BOOL CALLBACK DialogRELOCATION(									
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
			initRELOC1(hwndDlg);
			initRELOC2(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{							
			break;
		}
		case WM_NOTIFY:
		{
			NMHDR*  pNM=(NMHDR*)lParam;
             
            if(pNM->idFrom==IDC_LIST_RELOC1 && pNM->code==NM_CLICK)
            {
                EnumRELOC2(GetDlgItem(hwndDlg, IDC_LIST_RELOC1), wParam, lParam, GetDlgItem(hwndDlg, IDC_LIST_RELOC2));
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

void setRelocation(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_RELOCATION), hwndDlg, (DLGPROC)DialogRELOCATION);
}