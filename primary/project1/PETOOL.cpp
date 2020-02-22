// PETOOL.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>	
#include "PE.h"
#pragma comment(lib,"comctl32.lib")	

HINSTANCE happInstance;

void enumProcess(HWND hListProcess){
	LV_ITEM vitem;						
						
	//��ʼ��						
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	int countProcess=0;                                    //��ǰ����������������
	
    PROCESSENTRY32 currentProcess;                        //��ſ��ս�����Ϣ��һ���ṹ��
    currentProcess.dwSize = sizeof(currentProcess);        //��ʹ������ṹ֮ǰ�����������Ĵ�С
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//��ϵͳ�ڵ����н�����һ������
    
    if (hProcess == INVALID_HANDLE_VALUE)
    {
        return;
    }
    
    bool bMore=Process32First(hProcess,&currentProcess);    //��ȡ��һ��������Ϣ
	int count = 0;
    while(bMore)
    {
		if (currentProcess.th32ProcessID == 0){
			bMore=Process32Next(hProcess,&currentProcess); 
			continue;
		}
		
		HANDLE hTmp=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, currentProcess.th32ProcessID);
		//OutputDebugStringF("%d", GetLastError());
		if (hTmp == INVALID_HANDLE_VALUE)
		{
			//OutputDebugStringF("error: %d", GetLastError());
			char errorcode[20];
			itoa(GetLastError(), errorcode, 20);
			//MessageBox(NULL, errorcode,TEXT("INIT"),MB_OK);
			bMore=Process32Next(hProcess,&currentProcess);
			
			continue;
		}
		MODULEENTRY32 me32;
		me32.dwSize = sizeof(MODULEENTRY32);
		if (!Module32First(hTmp, &me32))
		{
			//OutputDebugStringF("%d", GetLastError());
			return;
		}
		
        //printf("PID=%5u    PName= %s\n",currentProcess.th32ProcessID,currentProcess.szExeFile);    //�������̿��գ�������ʾÿ��������Ϣ
        int tmpcount = 0;
		char pid[10];
		char imagesize[20];
		char imageaddr[20];

		vitem.pszText = currentProcess.szExeFile;						
		vitem.iItem = count;						
		vitem.iSubItem = tmpcount;						
		//ListView_InsertItem(hListProcess, &vitem);						
		SendMessage(hListProcess, LVM_INSERTITEM,0,(DWORD)&vitem);
		
		itoa(currentProcess.th32ProcessID, pid, 10);
		vitem.pszText = pid;						
		vitem.iItem = count;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hListProcess, &vitem);											
		
		itoa((DWORD)me32.modBaseAddr, imageaddr, 16);
		vitem.pszText = imageaddr;						
		vitem.iItem = count;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hListProcess, &vitem);	

		itoa(me32.modBaseSize, imagesize, 10);
		vitem.pszText = imagesize;					
		vitem.iItem = count;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hListProcess, &vitem);	
		
		bMore=Process32Next(hProcess,&currentProcess);    //������һ��
        countProcess++;
		count++;
    }
    
    CloseHandle(hProcess);				
}

void initDialogPro(HWND hDlg){
	LV_COLUMN lv;
	HWND hListProcess;								
									
	//��ʼ��								
	memset(&lv,0,sizeof(LV_COLUMN));
	
	//��ȡIDC_LIST_PROCESS���								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_PRO);								
	//��������ѡ��								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//��һ��								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("����");				//�б���				
	lv.cx = 180;								//�п�
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
	//�ڶ���								
	lv.pszText = TEXT("PID");								
	lv.cx = 80;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);								
	//������								
	lv.pszText = TEXT("�����ַ");								
	lv.cx = 100;								
	lv.iSubItem = 2;								
	ListView_InsertColumn(hListProcess, 2, &lv);								
	//������								
	lv.pszText = TEXT("�����С");								
	lv.cx = 100;								
	lv.iSubItem = 3;								
	ListView_InsertColumn(hListProcess, 3, &lv);								
	
	enumProcess(hListProcess);
}

void initDialogMod(HWND hDlg){
	LV_COLUMN lv;
	HWND hListProcess;								
																	
	memset(&lv,0,sizeof(LV_COLUMN));
								
	hListProcess = GetDlgItem(hDlg,IDC_LIST_MOD);								
	//��������ѡ��								
	SendMessage(hListProcess,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);								
									
	//��һ��								
	lv.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;								
	lv.pszText = TEXT("Module");				//�б���				
	lv.cx = 200;								//�п�
	lv.iSubItem = 0;								
	//ListView_InsertColumn(hListProcess, 0, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,0,(DWORD)&lv);								
	//�ڶ���								
	lv.pszText = TEXT("ImageBase");								
	lv.cx = 100;								
	lv.iSubItem = 1;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,1,(DWORD)&lv);

	lv.pszText = TEXT("ImageSize");								
	lv.cx = 100;								
	lv.iSubItem = 2;								
	//ListView_InsertColumn(hListProcess, 1, &lv);								
	SendMessage(hListProcess,LVM_INSERTCOLUMN,2,(DWORD)&lv);
}		


void EnumModule(
		   HWND hListPro, 			
		   WPARAM wParam,		
		   LPARAM lParam,
		   HWND hListMod
		   ){
	TCHAR szPid[0x20];
	LV_ITEM lv;

	memset(&lv, 0, sizeof(LV_ITEM));
	memset(szPid, 0, 0x20);

	DWORD row =  SendMessage(hListPro, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if(row == -1){
		return;
	}

	lv.iSubItem = 1;
	lv.pszText = szPid;
	lv.cchTextMax = 0x20;
	SendMessage(hListPro, LVM_GETITEMTEXT, row, (DWORD)&lv);
	//MessageBox(NULL, szPid, TEXT("PID"), MB_OK);
	int pid;
	sscanf(szPid, "%d", &pid);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, (DWORD)pid);
	if (hProcess == INVALID_HANDLE_VALUE || !hProcess){
		return;
	}

	LV_ITEM vitem;						
	//��ʼ��			
	memset(&vitem,0,sizeof(LV_ITEM));			
	vitem.mask = LVIF_TEXT;
	
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,(DWORD)pid);
    if (INVALID_HANDLE_VALUE == hSnapshot)
    {
        return;
    }

    MODULEENTRY32 mi; 
    mi.dwSize = sizeof(MODULEENTRY32); 
    BOOL bRet = Module32First(hSnapshot,&mi);
	int count = 0;
	ListView_DeleteAllItems(hListMod);
    while (bRet)
    {
        int tmpcount = 0;
		char imagesize[20];
		char imageaddr[20];
		
		vitem.pszText = mi.szModule;						
		vitem.iItem = count;						
		vitem.iSubItem = tmpcount;						
		//ListView_InsertItem(hListProcess, &vitem);						
		SendMessage(hListMod, LVM_INSERTITEM,0,(DWORD)&vitem);						

		itoa((DWORD)mi.modBaseAddr, imageaddr, 16);
		vitem.pszText = imageaddr;						
		vitem.iItem = count;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hListMod, &vitem);	

		itoa(mi.modBaseSize, imagesize, 10);
		vitem.pszText = imagesize;					
		vitem.iItem = count;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hListMod, &vitem);	

		count++;
		bRet = Module32Next(hSnapshot,&mi);
    }
    CloseHandle(hSnapshot);
}



BOOL CALLBACK DialogMain(									
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
			initDialogPro(hwndDlg);
			initDialogMod(hwndDlg);
			HICON hMyIcon = LoadIcon(happInstance, MAKEINTRESOURCE(IDI_ICON));
			SendMessage(hwndDlg, WM_SETICON, ICON_SMALL, (DWORD)hMyIcon);
			SendMessage(hwndDlg, WM_SETICON, ICON_BIG, (DWORD)hMyIcon);
			return TRUE ;
		}
		case  WM_COMMAND :								
		{						
			switch (LOWORD (wParam))							
			{							
				case IDC_BUTTON_QUIT:							
				{							
					EndDialog(hwndDlg, wParam);												
					return TRUE;						
				}
				case IDC_BUTTON_PE:
				{
					PETool(hwndDlg);
					return TRUE;
				}
			}
			break;
		}
		case WM_NOTIFY:
		{
			NMHDR*  pNM=(NMHDR*)lParam;
             
            if(pNM->idFrom==IDC_LIST_PRO && pNM->code==NM_CLICK)
            {
                EnumModule(GetDlgItem(hwndDlg, IDC_LIST_PRO), wParam, lParam, GetDlgItem(hwndDlg, IDC_LIST_MOD));
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


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	INITCOMMONCONTROLSEX icex;				
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);				
	icex.dwICC = ICC_WIN95_CLASSES;				
	InitCommonControlsEx(&icex);	
	
	happInstance = hInstance;
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DialogMain);

	return 0;
}



