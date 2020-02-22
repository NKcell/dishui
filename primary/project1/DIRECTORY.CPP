#include <stdio.h>
#include"stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include"PEDEAL.h"
#include"IMPORT.h"
#include"BOUND.h"
#include"EXPORT.h"
#include"RELOCATION.h"
#include"PERESOURCE.h"

extern HINSTANCE happInstance;

void initDir(HWND hwndDlg){
	setDir(hwndDlg);
}

BOOL CALLBACK DialogDir(									
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
			initDir(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{	
			switch (LOWORD (wParam))							
			{							
				case IDC_EXPORT:							
				{							
					setExport(hwndDlg);					
					return TRUE;						
				}
				case IDC_IMPORT:
				{
					setImport(hwndDlg);
					return TRUE;
				}
				case IDC_RESOURCE:							
				{							
					setResource(hwndDlg);						
					return TRUE;						
				}
				case IDC_RELOCATION:
				{
					setRelocation(hwndDlg);
					return TRUE;
				}
				case IDC_BOUNDIMPORT:							
				{							
					setBound(hwndDlg);					
					return TRUE;						
				}
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



void showDir(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_DIRECTORY), hwndDlg, (DLGPROC)DialogDir);
}