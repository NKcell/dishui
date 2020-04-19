#include <stdio.h>
#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#include <Commdlg.h>
#include"PEDEAL.h"
#include<stdlib.h>
#include<windows.h>

extern HINSTANCE happInstance;

void myEncryption(char* srcFileContent, int fileLen){
	for(int i=0; i<fileLen; i++){
		*(srcFileContent+i) ^= 1;
	}
}

void getPath(HWND hListProcess){
	OPENFILENAME ofn;      // 公共对话框结构。     
    TCHAR szFile[MAX_PATH];

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
	GetOpenFileName(&ofn);

	SetWindowText(hListProcess, szFile);
}

DWORD toFileAlignment(DWORD len, DWORD FileAlignment){
	if (len%FileAlignment == 0){
		return len;
	}
	return ((len/FileAlignment)+1)*FileAlignment;
}

DWORD toSectionAlignment(DWORD len, DWORD SectionAlignment){
	if (len%SectionAlignment == 0){
		return len;
	}
	return ((len/SectionAlignment)+1)*SectionAlignment;
}

void addSectionToShell(HWND hwndDlg, char* shellFileContent, int shellFileLen, char* srcFileContent, int srcFileLen){
    char* mem2;
    mem2 = shellFileContent;

    PIMAGE_DOS_HEADER dos_head = (PIMAGE_DOS_HEADER)shellFileContent;
	shellFileContent += dos_head->e_lfanew;
	shellFileContent += 4;
	PIMAGE_FILE_HEADER pe_head = (PIMAGE_FILE_HEADER)shellFileContent;
	shellFileContent += 20;
    PIMAGE_OPTIONAL_HEADER pe_optionhead = pe_optionhead = (PIMAGE_OPTIONAL_HEADER)shellFileContent;
	shellFileContent += pe_head->SizeOfOptionalHeader;
	PIMAGE_SECTION_HEADER section = (PIMAGE_SECTION_HEADER)shellFileContent;

    unsigned int headrawsize;
    headrawsize = dos_head->e_lfanew + 0x18 + pe_head->SizeOfOptionalHeader + (pe_head->NumberOfSections*0x28);
    if (section->SizeOfRawData-headrawsize<2*0x18){
		MessageBox(hwndDlg, "add section failed, not enough space!", 0, 0);
        return;
    }
    for (int i=0; i<2*0x18; i++){
        if (*(((char*)section+headrawsize)+i)!=0){
            printf("the space already has data\n");
			MessageBox(hwndDlg, "add section failed, the space already has data!", 0, 0);
            return;
        }
    }

    memcpy((section+(pe_head->NumberOfSections)),(section+(pe_head->NumberOfSections-1)), 0x28);
    char newname[7] = {'.', 's', 'h', 'e', 'l', 'l', 0};
    memcpy((char*)(section+(pe_head->NumberOfSections)), newname, 7);
	(section+(pe_head->NumberOfSections))->VirtualAddress = pe_optionhead->SizeOfImage;
	(section+(pe_head->NumberOfSections))->Misc.VirtualSize = (DWORD)srcFileLen;
	(section+(pe_head->NumberOfSections))->SizeOfRawData = toFileAlignment((DWORD)srcFileLen, pe_optionhead->FileAlignment);
	(section+(pe_head->NumberOfSections))->Characteristics = 0xc0000020;
	(section+(pe_head->NumberOfSections))->PointerToRawData = (DWORD)shellFileLen;
	pe_optionhead->SizeOfImage += toSectionAlignment((DWORD)srcFileLen, pe_optionhead->SectionAlignment);

    pe_head->NumberOfSections++;

    char* newfile = (char*)malloc(srcFileLen+shellFileLen);

    memcpy(newfile, mem2, shellFileLen);
    memcpy(newfile+(shellFileLen), srcFileContent, srcFileLen);

    LPVOID savef = savefile(newfile, srcFileLen+shellFileLen, "exp.exe");
	if (savef == NULL){
		MessageBox(hwndDlg, "error SaveFile!", 0, 0);
	}else{
		MessageBox(hwndDlg, "shell success!", "success", MB_ICONINFORMATION);
	}
	free(savef);
	free(newfile);
}

void addShell(HWND hwndDlg){
	TCHAR szSoruceFile[MAX_PATH];
	memset(szSoruceFile, 0, MAX_PATH);
	HWND hSource = GetDlgItem(hwndDlg,IDC_EDIT_SOURCEPATH);
	GetWindowText(hSource, szSoruceFile, MAX_PATH);
	if(lstrlen(szSoruceFile) == 0){
		MessageBox(hwndDlg, "error SourceFile!", 0, 0);
		return;
	}
	int sourceFilelen;
	char* sourcemem = (char*)readfile(&sourceFilelen, szSoruceFile);
	if (sourcemem == NULL){
		MessageBox(hwndDlg, "error SourceFile!", 0, 0);
		return;
	}

	TCHAR szShellFile[MAX_PATH];
	memset(szShellFile, 0, MAX_PATH);
	HWND hShell = GetDlgItem(hwndDlg,IDC_EDIT_SHELLPATH);
	GetWindowText(hShell, szShellFile, MAX_PATH);
	if(lstrlen(szShellFile) == 0){
		MessageBox(hwndDlg, "error ShellFile!", 0, 0);
		return;
	}
	int shellFilelen;
	char* shellmem = (char*)readfile(&shellFilelen, szShellFile);
	if (shellmem == NULL){
		MessageBox(hwndDlg, "error ShellFile!", 0, 0);
		return;
	}

	myEncryption(sourcemem, sourceFilelen);

	addSectionToShell(hwndDlg, shellmem, shellFilelen, sourcemem, sourceFilelen);
	
	free(sourcemem);
	free(shellmem);
}

BOOL CALLBACK DialogShell(									
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
			//initDialogSec(hwndDlg);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{						
			switch (LOWORD (wParam))							
			{
				case IDC_BUTTON_SOURCEPATH:
				{
					//EndDialog(hwndDlg, wParam);
					HWND hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SOURCEPATH);
					getPath(hListProcess);
					return TRUE;
				}
				case IDC_BUTTON_SHELLPATH:
				{
					HWND hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SHELLPATH);
					getPath(hListProcess);
					return TRUE;						  
				}
				case IDC_BUTTON_ADDSHELL:
				{
					addShell(hwndDlg);
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



void showShell(HWND hwndDlg){
	DialogBox(happInstance, MAKEINTRESOURCE(IDD_DIALOG_SHELL), hwndDlg, (DLGPROC)DialogShell);
}