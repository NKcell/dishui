#include "PE.h"
#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include <Commdlg.h>
#include"PEDEAL.h"
#include"SECTION.h"
#include"DIRECTORY.h"

extern HINSTANCE happInstance;

TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。

void initPE(HWND hwndDlg){
	int rfileLen = 0;
	char* mem = (char*)filetomem(&rfileLen);
	initHead(mem);
	setPEheadValue(hwndDlg);
}	

BOOL CALLBACK DialogPE(									
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
			initPE(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{						
			switch (LOWORD (wParam))							
			{
				case IDC_BUTTON_H_CLOSE:							
				{							
					EndDialog(hwndDlg, wParam);												
					return TRUE;						
				}
				case IDC_BUTTON_SECTION:							
				{							
					showSection(hwndDlg);												
					return TRUE;						
				}
				case IDC_BUTTON_H_DIRECTORY:							
				{							
					showDir(hwndDlg);												
					return TRUE;						
				}
			}
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

void PETool(HWND hwndDlg){
	OPENFILENAME ofn;      // 公共对话框结构。     
                   
    // 初始化选择文件对话框。     
    ZeroMemory(&ofn, sizeof(OPENFILENAME));    
    ofn.lStructSize = sizeof(OPENFILENAME);    
    ofn.hwndOwner = NULL;    
    ofn.lpstrFile = szFile;    
    ofn.lpstrFile[0] = '\0';   
    ofn.nMaxFile = sizeof(szFile);    
    ofn.lpstrFilter = (const char *)"Executable files (*.exe)\0*.exe\0Dynamic Link Libraries (*.dll)\0*.dll\0OLE-ActiveX Controls (*.ocx)\0*.ocx\0Screen Savers (*.scr)\0*.scr\0\0";    
    ofn.nFilterIndex = 1;    
    ofn.lpstrFileTitle = NULL;    
    ofn.nMaxFileTitle = 0;    
    ofn.lpstrInitialDir = NULL;    
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;    
    //ofn.lpTemplateName =  MAKEINTRESOURCE(ID_TEMP_DIALOG);    
    // 显示打开选择文件对话框。
    if ( GetOpenFileName(&ofn) )    
    {    
        DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_PE), hwndDlg, (DLGPROC)DialogPE);
    }else{
		return;
	}
}