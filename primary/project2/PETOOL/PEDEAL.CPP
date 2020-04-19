#include <stdio.h>
#include<string.h>
#include"stdafx.h"
#include "resource.h"
#include "windows.h"
#include "PEDEAL.h"
#include <commctrl.h>

extern TCHAR szFile[MAX_PATH];

char* mymem;

PIMAGE_DOS_HEADER dosHead;
PIMAGE_NT_HEADERS NThead;
PIMAGE_FILE_HEADER fileHead;
PIMAGE_OPTIONAL_HEADER opHead;
PIMAGE_SECTION_HEADER section;

LPVOID filetomem(int* rfileLen){
	FILE *fp = NULL;
    fp = fopen(szFile,"rb");
    if (fp == NULL){
        printf("open file error");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); 
	int fileLen = ftell(fp); 
    fseek(fp, 0, SEEK_SET);

	*rfileLen = fileLen;

    char *mem = (char *)malloc(sizeof(int)*fileLen);
    if (mem == NULL){
        printf("malloc failed");
		free(mem);
        return NULL;
    }
    memset(mem, 0, sizeof(int)*fileLen);

	for(unsigned int j=0; j<sizeof(int)*fileLen; j++){
        *(mem+j) = fgetc(fp);
    }

	fclose(fp);
	mymem = mem;
	return mem;
}

LPVOID readfile(int* rfileLen, char* szFile){
	FILE *fp = NULL;
    fp = fopen(szFile,"rb");
    if (fp == NULL){
        printf("open file error");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); 
	int fileLen = ftell(fp); 
    fseek(fp, 0, SEEK_SET);

	*rfileLen = fileLen;

    char *mem = (char *)malloc(sizeof(int)*fileLen);
    if (mem == NULL){
        printf("malloc failed");
		free(mem);
        return NULL;
    }
    memset(mem, 0, sizeof(int)*fileLen);

	for(unsigned int j=0; j<sizeof(int)*fileLen; j++){
        *(mem+j) = fgetc(fp);
    }

	fclose(fp);
	mymem = mem;
	return mem;
}

LPVOID savefile(char* mem, unsigned int lensize, char* savefilename){
	FILE *fp;
	fp = fopen(savefilename, "wb");
	if (fp == NULL){
        printf("open file error");
        return NULL;
    }

	fwrite(mem, sizeof(unsigned char), lensize, fp);
	return fp;
}

void initHead(char* mem){
    dosHead = (PIMAGE_DOS_HEADER)mem;
    mem += dosHead->e_lfanew;
    NThead = (PIMAGE_NT_HEADERS)mem;
    mem += 4;
    fileHead = (PIMAGE_FILE_HEADER)mem;
    mem += 20;
    opHead = (PIMAGE_OPTIONAL_HEADER)mem;
    mem += fileHead->SizeOfOptionalHeader;
    section = (PIMAGE_SECTION_HEADER)mem;
}

void setPEheadValue(HWND hwndDlg){
	char tmp[20];
	HWND hListProcess;

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_ImageBase);
	itoa(opHead->ImageBase, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_EntryPoint);
	itoa(opHead->AddressOfEntryPoint, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SizeOfImage);
	itoa(opHead->SizeOfImage, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SAlignment);
	itoa(opHead->SectionAlignment, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_Subsystem);
	itoa(opHead->Subsystem, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_NumOfSec);
	itoa(fileHead->NumberOfSections, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SizeOfHeader);
	itoa(opHead->SizeOfHeaders, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_CheckSum);
	itoa(opHead->CheckSum, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_OptionHead);
	itoa(fileHead->SizeOfOptionalHeader, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_Character);
	itoa(fileHead->Characteristics, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_BaseOfData);
	itoa(opHead->BaseOfData, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_BaseOfCode);
	itoa(opHead->BaseOfCode, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_TimeStamp);
	itoa(fileHead->TimeDateStamp, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_Machine);
	itoa(fileHead->Machine, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_Magic);
	itoa(opHead->Magic, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_FAlignment);
	itoa(opHead->FileAlignment, tmp, 16);
	SetWindowText(hListProcess, tmp);
}

void setDir(HWND hwndDlg){
	char tmp[20];
	HWND hListProcess;

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_EXPORT_RVA);
	itoa((opHead->DataDirectory)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_EXPORT_SIZE);
	itoa((opHead->DataDirectory)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_IMPORT_RVA);
	itoa((opHead->DataDirectory+1)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_IMPORT_SIZE);
	itoa((opHead->DataDirectory+1)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RESOURCE_RVA);
	itoa((opHead->DataDirectory+2)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RESOURCE_SIZE);
	itoa((opHead->DataDirectory+2)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SECURITY_RVA);
	itoa((opHead->DataDirectory+4)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_SECURITY_SIZE);
	itoa((opHead->DataDirectory+4)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_EXCEPTION_RVA);
	itoa((opHead->DataDirectory+3)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_EXCEPTION_SIZE);
	itoa((opHead->DataDirectory+3)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RELOCATION_RVA);
	itoa((opHead->DataDirectory+5)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RELOCATION_SIZE);
	itoa((opHead->DataDirectory+5)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_DUBUG_RVA);
	itoa((opHead->DataDirectory+6)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_DUBUG_SIZE);
	itoa((opHead->DataDirectory+6)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_COPYRIGHT_RVA);
	itoa((opHead->DataDirectory+7)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_COPYRIGHT_SIZE);
	itoa((opHead->DataDirectory+7)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_GLOBALPTR_RVA);
	itoa((opHead->DataDirectory+8)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_GLOBALPTR_SIZE);
	itoa((opHead->DataDirectory+8)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_TLS_RVA);
	itoa((opHead->DataDirectory+9)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_TLS_SIZE);
	itoa((opHead->DataDirectory+9)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_LOADCONFIG_RVA);
	itoa((opHead->DataDirectory+10)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_LOADCONFIG_SIZE);
	itoa((opHead->DataDirectory+10)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_BOUNDIMPORT_RVA);
	itoa((opHead->DataDirectory+11)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_BOUNDIMPORT_SIZE);
	itoa((opHead->DataDirectory+11)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_IAT_RVA);
	itoa((opHead->DataDirectory+12)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_IAT_SIZE);
	itoa((opHead->DataDirectory+12)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_DELAY_RVA);
	itoa((opHead->DataDirectory+13)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_DELAY_SIZE);
	itoa((opHead->DataDirectory+13)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_COM_RVA);
	itoa((opHead->DataDirectory+14)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_COM_SIZE);
	itoa((opHead->DataDirectory+14)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);

	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RETAIN_RVA);
	itoa((opHead->DataDirectory+15)->VirtualAddress, tmp, 16);
	SetWindowText(hListProcess, tmp);
	hListProcess = GetDlgItem(hwndDlg,IDC_EDIT_RETAIN_SIZE);
	itoa((opHead->DataDirectory+15)->Size, tmp, 16);
	SetWindowText(hListProcess, tmp);	
}

void setSection(HWND hSection){
	LV_ITEM vitem;						
												
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	

    for(DWORD i=0; i<fileHead->NumberOfSections; i++)
    {
        int tmpcount = 0;
		char tmp[20];
		
		vitem.pszText = (char*)((section+i)->Name);						
		vitem.iItem = i;						
		vitem.iSubItem = tmpcount;												
		SendMessage(hSection, LVM_INSERTITEM,0,(DWORD)&vitem);						

		itoa((section+i)->Misc.VirtualSize, tmp, 16);
		vitem.pszText = tmp;						
		vitem.iItem = i;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hSection, &vitem);	

		itoa((section+i)->VirtualAddress, tmp, 16);
		vitem.pszText = tmp;					
		vitem.iItem = i;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hSection, &vitem);	

		itoa((section+i)->SizeOfRawData, tmp, 16);
		vitem.pszText = tmp;					
		vitem.iItem = i;						
		vitem.iSubItem = (++tmpcount);												
		ListView_SetItem(hSection, &vitem);							

		itoa((section+i)->PointerToRawData, tmp, 16);
		vitem.pszText = tmp;						
		vitem.iItem = i;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hSection, &vitem);	

		itoa((section+i)->Characteristics, tmp, 16);
		vitem.pszText = tmp;					
		vitem.iItem = i;						
		vitem.iSubItem = (++tmpcount);						
		ListView_SetItem(hSection, &vitem);	
    }
}

DWORD rvaToFoa(DWORD rva){
	if (rva>=0 && rva<=opHead->SizeOfHeaders){
		return rva;
	}
	if (rva>=opHead->SizeOfImage || (rva>opHead->SizeOfHeaders && rva<section->VirtualAddress)){
		printf("error rva\n");
		return 0;
	}
	for (WORD i=0; i<fileHead->NumberOfSections; i++){
		if ((i == fileHead->NumberOfSections-1)  || (rva>=(section+i)->VirtualAddress && rva<(section+i+1)->VirtualAddress)){
			return rva- (section+i)->VirtualAddress + (section+i)->PointerToRawData;
		}
	}
	return 0;
}

void enumImportDll(HWND hDllName){	
	LV_ITEM vitem;						
												
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	int count = 0;

	PIMAGE_IMPORT_DESCRIPTOR importTable = (PIMAGE_IMPORT_DESCRIPTOR)(rvaToFoa((opHead->DataDirectory+1)->VirtualAddress)+mymem);
	while(importTable->FirstThunk || importTable->ForwarderChain || importTable->Name || importTable->OriginalFirstThunk || importTable->TimeDateStamp){
		vitem.pszText = (char*)(rvaToFoa(importTable->Name)+mymem);						
		vitem.iItem = count;						
		vitem.iSubItem = 0;												
		SendMessage(hDllName, LVM_INSERTITEM,0,(DWORD)&vitem);

		importTable ++;
		count++;
	}
}


void EnumDLLINFO(
		   HWND hListDLLNAME, 			
		   WPARAM wParam,		
		   LPARAM lParam,
		   HWND DLLINFO
		   ){
	char szName[0x20];
	LV_ITEM lv;

	memset(&lv, 0, sizeof(LV_ITEM));
	memset(szName, 0, 0x20);

	DWORD row =  SendMessage(hListDLLNAME, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if(row == -1){
		return;
	}

	lv.iSubItem = 0;
	lv.pszText = szName;
	lv.cchTextMax = 0x20;
	SendMessage(hListDLLNAME, LVM_GETITEMTEXT, row, (DWORD)&lv);

	LV_ITEM vitem;									
	memset(&vitem,0,sizeof(LV_ITEM));			
	vitem.mask = LVIF_TEXT;	
	
	ListView_DeleteAllItems(DLLINFO);
	PIMAGE_IMPORT_DESCRIPTOR importTable = (PIMAGE_IMPORT_DESCRIPTOR)(rvaToFoa((opHead->DataDirectory+1)->VirtualAddress)+mymem);
	while(importTable->FirstThunk || importTable->ForwarderChain || importTable->Name || importTable->OriginalFirstThunk || importTable->TimeDateStamp){	
		if (strcmp(szName, (char*)(rvaToFoa(importTable->Name)+mymem)) == 0){
			PIMAGE_THUNK_DATA INT = (PIMAGE_THUNK_DATA)(rvaToFoa(importTable->OriginalFirstThunk)+mymem);
			int count = 0;
			char tmpstr[20];
			while(INT->u1.Ordinal != 0){
				if (INT->u1.Ordinal & 0x80000000){
					itoa(INT->u1.Ordinal & 0x7FFF, tmpstr, 16);
					vitem.pszText = tmpstr;							
					vitem.iItem = count;						
					vitem.iSubItem = 0;												
					SendMessage(DLLINFO, LVM_INSERTITEM,0,(DWORD)&vitem);	
				}else{
					PIMAGE_IMPORT_BY_NAME hitname = (PIMAGE_IMPORT_BY_NAME)(rvaToFoa(INT->u1.Ordinal)+mymem);
					vitem.pszText = (char*)hitname->Name;						
					vitem.iItem = count;						
					vitem.iSubItem = 0;												
					SendMessage(DLLINFO, LVM_INSERTITEM,0,(DWORD)&vitem);

					itoa((DWORD)hitname->Hint, tmpstr, 16);
					vitem.pszText = tmpstr;						
					vitem.iItem = count;						
					vitem.iSubItem = 1;						
					ListView_SetItem(DLLINFO, &vitem);	
				}
				count++;
				INT = INT+1;
			}
			break;
		}
		importTable ++;
	}
	
}

void enumBound(HWND hListBound){
	LV_ITEM vitem;						
												
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	int count = 0;
	char time[20];
	if ((opHead->DataDirectory+11)->VirtualAddress == 0){
		return;
	}
	PIMAGE_BOUND_IMPORT_DESCRIPTOR bindimportTable = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)(rvaToFoa((opHead->DataDirectory+11)->VirtualAddress)+mymem);
	DWORD first = (DWORD)bindimportTable;
	while(bindimportTable->NumberOfModuleForwarderRefs | bindimportTable->OffsetModuleName | bindimportTable->TimeDateStamp){
		vitem.pszText = (char*)(first+bindimportTable->OffsetModuleName);						
		vitem.iItem = count;						
		vitem.iSubItem = 0;												
		SendMessage(hListBound, LVM_INSERTITEM,0,(DWORD)&vitem);						

		itoa(bindimportTable->TimeDateStamp, time, 16);
		vitem.pszText = time;						
		vitem.iItem = count;						
		vitem.iSubItem = 1;						
		ListView_SetItem(hListBound, &vitem);
		WORD num = bindimportTable->NumberOfModuleForwarderRefs;
		for(WORD i=0; i<num; i++){
			bindimportTable ++;
			vitem.pszText = (char*)(first+bindimportTable->OffsetModuleName);						
			vitem.iItem = count;						
			vitem.iSubItem = 0;												
			SendMessage(hListBound, LVM_INSERTITEM,0,(DWORD)&vitem);						

			itoa(bindimportTable->TimeDateStamp, time, 16);
			vitem.pszText = time;						
			vitem.iItem = count;						
			vitem.iSubItem = 1;						
			ListView_SetItem(hListBound, &vitem);
		}
		bindimportTable++;
	}	
}

void enumTYPEID(HWND hTYPEID){
	LV_ITEM vitem;						
												
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	
	
	int count = 0;

	PIMAGE_RESOURCE_DIRECTORY resource = (PIMAGE_RESOURCE_DIRECTORY)(rvaToFoa((opHead->DataDirectory+2)->VirtualAddress)+mymem);
	PIMAGE_RESOURCE_DIRECTORY_ENTRY entry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((char*)resource+16);
	for(WORD i=0; i<resource->NumberOfNamedEntries+resource->NumberOfIdEntries; i++){
		if((entry+i)->NameIsString){
			PIMAGE_RESOURCE_DIR_STRING_U name = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)resource+(entry+i)->NameOffset);
			WCHAR szStr[MAX_PATH] = { 0 };
            memcpy(szStr, name->NameString, name->Length*sizeof(WCHAR));
			vitem.pszText = (char*)szStr;						
			vitem.iItem = count;						
			vitem.iSubItem = 0;												
			SendMessage(hTYPEID, LVM_INSERTITEM,0,(DWORD)&vitem);
		}else{
			char typeID[20];
			itoa((DWORD)(entry+i)->Id, typeID, 10);
			vitem.pszText = typeID;						
			vitem.iItem = count;						
			vitem.iSubItem = 0;												
			SendMessage(hTYPEID, LVM_INSERTITEM,0,(DWORD)&vitem);
		}
		count++;
	}
}

void EnumSIGN(HWND hListTYPE, WPARAM wParam,LPARAM lParam,HWND hListSIGN){
	char szName[0x20];
	LV_ITEM lv;

	memset(&lv, 0, sizeof(LV_ITEM));
	memset(szName, 0, 0x20);

	DWORD row =  SendMessage(hListTYPE, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if(row == -1){
		return;
	}

	lv.iSubItem = 0;
	lv.pszText = szName;
	lv.cchTextMax = 0x20;
	SendMessage(hListTYPE, LVM_GETITEMTEXT, row, (DWORD)&lv);

	LV_ITEM vitem;									
	memset(&vitem,0,sizeof(LV_ITEM));			
	vitem.mask = LVIF_TEXT;	
	
	ListView_DeleteAllItems(hListSIGN);

	PIMAGE_RESOURCE_DIRECTORY resource = (PIMAGE_RESOURCE_DIRECTORY)(rvaToFoa((opHead->DataDirectory+2)->VirtualAddress)+mymem);
	PIMAGE_RESOURCE_DIRECTORY_ENTRY entry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((char*)resource+16);
	int flag = 0;
	int count = 0;
	for(WORD i=0; i<resource->NumberOfNamedEntries+resource->NumberOfIdEntries; i++){
		if((entry+i)->NameIsString){
			PIMAGE_RESOURCE_DIR_STRING_U name = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)resource+(entry+i)->NameOffset);
			WCHAR szStr[MAX_PATH] = { 0 };
            memcpy(szStr, name->NameString, name->Length*sizeof(WCHAR));
			if (strcmp(szName, (char*)(szStr)) == 0){
				flag = 1;
			}
		}else{
			char typeID[20];
			itoa((DWORD)(entry+i)->Id, typeID, 10);
			if (strcmp(szName, typeID) == 0){
				flag = 1;
			}
		}
		if(flag == 1){
			if ((entry+i)->DataIsDirectory){
				PIMAGE_RESOURCE_DIRECTORY secondRes = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)resource + (entry+i)->OffsetToDirectory);
				PIMAGE_RESOURCE_DIRECTORY_ENTRY secondEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)secondRes+16);
				for(WORD i=0; i<secondRes->NumberOfNamedEntries+secondRes->NumberOfIdEntries; i++){
					if((secondEntry+i)->NameIsString){
						PIMAGE_RESOURCE_DIR_STRING_U sname = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)resource+(secondEntry+i)->NameOffset);
						WCHAR szStr[MAX_PATH] = { 0 };
						memcpy(szStr, sname->NameString, sname->Length*sizeof(WCHAR));
						vitem.pszText = (char*)szStr;						
						vitem.iItem = count;						
						vitem.iSubItem = 0;												
						SendMessage(hListSIGN, LVM_INSERTITEM,0,(DWORD)&vitem);
					}else{
						char typeID[20];
						itoa((DWORD)(secondEntry+i)->Id, typeID, 10);
						vitem.pszText = typeID;						
						vitem.iItem = count;						
						vitem.iSubItem = 0;												
						SendMessage(hListSIGN, LVM_INSERTITEM,0,(DWORD)&vitem);
					}
					PIMAGE_RESOURCE_DIRECTORY thirdRes = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)resource + (secondEntry+i)->OffsetToDirectory);
					PIMAGE_RESOURCE_DIRECTORY_ENTRY thirdEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)thirdRes+16);
					PIMAGE_RESOURCE_DATA_ENTRY data = (PIMAGE_RESOURCE_DATA_ENTRY)((DWORD)resource + thirdEntry->OffsetToDirectory);
					
					char tmpstr[20];
					itoa((DWORD)data->OffsetToData, tmpstr, 16);
					vitem.pszText = tmpstr;						
					vitem.iItem = count;						
					vitem.iSubItem = 1;						
					ListView_SetItem(hListSIGN, &vitem);

					itoa((DWORD)data->Size, tmpstr, 16);
					vitem.pszText = tmpstr;						
					vitem.iItem = count;						
					vitem.iSubItem = 2;						
					ListView_SetItem(hListSIGN, &vitem);

					count++;
				}			
			}

			break;
		}
	}
};


void enumExport(HWND hwndDlg,HWND hListExport){
	PIMAGE_DATA_DIRECTORY export = (PIMAGE_DATA_DIRECTORY)(opHead->DataDirectory);
	PIMAGE_EXPORT_DIRECTORY exportTable = (PIMAGE_EXPORT_DIRECTORY)(rvaToFoa(export->VirtualAddress)+mymem);

	if (export->VirtualAddress==0){
		return;
	}

	char tmp[20];
	HWND hExport;

	hExport = GetDlgItem(hwndDlg,IDC_EDIT_NAME);
	SetWindowText(hExport, (char*)(rvaToFoa(exportTable->Name)+mymem));
	hExport = GetDlgItem(hwndDlg,IDC_EDIT_BASE);
	itoa(exportTable->Base, tmp, 16);
	SetWindowText(hExport, tmp);
	hExport = GetDlgItem(hwndDlg,IDC_EDIT_NUMOFUNC);
	itoa(exportTable->NumberOfFunctions, tmp, 16);
	SetWindowText(hExport, tmp);
	hExport = GetDlgItem(hwndDlg,IDC_EDIT_NUMOFNAME);
	itoa(exportTable->NumberOfNames, tmp, 16);
	SetWindowText(hExport, tmp); 
	
	LV_ITEM vitem;									
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;	

	for(DWORD j=0; j<exportTable->NumberOfNames; j++){
		vitem.pszText = (char *)(rvaToFoa(*((DWORD*)(rvaToFoa(exportTable->AddressOfNames)+mymem)+j))+mymem);						
		vitem.iItem = j;						
		vitem.iSubItem = 0;												
		SendMessage(hListExport, LVM_INSERTITEM,0,(DWORD)&vitem);
		DWORD ord = *((WORD*)(rvaToFoa(exportTable->AddressOfNameOrdinals)+mymem)+j);
		char tmpstr[20];
		itoa(*((WORD*)(rvaToFoa(exportTable->AddressOfNameOrdinals)+mymem)+j), tmpstr, 16);
		vitem.pszText = tmpstr;						
		vitem.iItem = j;						
		vitem.iSubItem = 1;						
		ListView_SetItem(hListExport, &vitem);
		DWORD rva = *((DWORD*)(rvaToFoa(exportTable->AddressOfFunctions)+mymem)+ord);
		itoa(rva, tmpstr, 16);
		vitem.pszText = tmpstr;						
		vitem.iItem = j;						
		vitem.iSubItem = 2;												
		ListView_SetItem(hListExport, &vitem);
	}
};

void EnumRELOCATION1(HWND hRELOC){
	PIMAGE_DATA_DIRECTORY relocation = (opHead->DataDirectory)+5;
	PIMAGE_BASE_RELOCATION relocationTable = (PIMAGE_BASE_RELOCATION)(rvaToFoa(relocation->VirtualAddress)+mymem);
	
	if (relocation->VirtualAddress==0){
		return;
	}

	LV_ITEM vitem;									
	memset(&vitem,0,sizeof(LV_ITEM));						
	vitem.mask = LVIF_TEXT;

	int index = 0;
	while (relocationTable->SizeOfBlock!=0 || relocationTable->VirtualAddress!=0){
		char tmpstr[20];
		
		itoa(index+1, tmpstr, 10);
		vitem.pszText = tmpstr;						
		vitem.iItem = index;						
		vitem.iSubItem = 0;						
		//ListView_InsertItem(hListProcess, &vitem);						
		SendMessage(hRELOC, LVM_INSERTITEM,0,(DWORD)&vitem);
		
		itoa(relocationTable->VirtualAddress, tmpstr, 16);
		vitem.pszText = tmpstr;						
		vitem.iItem = index;						
		vitem.iSubItem = 1;						
		ListView_SetItem(hRELOC, &vitem);											
		
		itoa(relocationTable->SizeOfBlock, tmpstr, 16);
		vitem.pszText = tmpstr;						
		vitem.iItem = index;						
		vitem.iSubItem = 2;						
		ListView_SetItem(hRELOC, &vitem);	

		relocationTable = (PIMAGE_BASE_RELOCATION)((char*)relocationTable+relocationTable->SizeOfBlock);
		index ++;
	}
}

void EnumRELOC2(HWND RELOC1, WPARAM wParam, LPARAM lParam, HWND RELOC2){
	char szName[0x20];
	LV_ITEM lv;

	memset(&lv, 0, sizeof(LV_ITEM));
	memset(szName, 0, 0x20);

	DWORD row =  SendMessage(RELOC1, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if(row == -1){
		return;
	}

	lv.iSubItem = 0;
	lv.pszText = szName;
	lv.cchTextMax = 0x20;
	SendMessage(RELOC1, LVM_GETITEMTEXT, row, (DWORD)&lv);

	LV_ITEM vitem;									
	memset(&vitem,0,sizeof(LV_ITEM));			
	vitem.mask = LVIF_TEXT;	
	
	ListView_DeleteAllItems(RELOC2);

	PIMAGE_DATA_DIRECTORY relocation = (opHead->DataDirectory)+5;
	PIMAGE_BASE_RELOCATION relocationTable = (PIMAGE_BASE_RELOCATION)(rvaToFoa(relocation->VirtualAddress)+mymem);
	
	int index = 0;
	while (relocationTable->SizeOfBlock!=0 || relocationTable->VirtualAddress!=0){
		//printf("**********Index:%d  RVA:%.8x SizeofBlock:%.8x**********\n", index+1, relocationTable->VirtualAddress, relocationTable->SizeOfBlock);
		char tmpstr[20];
		itoa(index+1, tmpstr, 10);
		if (strcmp(szName, tmpstr) == 0){
			WORD* data = (WORD*)relocationTable+4;
			for (DWORD i=0; i< (relocationTable->SizeOfBlock-8)/2; i++){
				if ((*(data+i))>>12 == 0){
					//printf("index: %d, RVA: %s Type: %d\n", i+1, "n/a", 0);
					itoa(i+1, tmpstr, 10);
					vitem.pszText = tmpstr;						
					vitem.iItem = i;						
					vitem.iSubItem = 0;												
					SendMessage(RELOC2, LVM_INSERTITEM,0,(DWORD)&vitem);
					
					vitem.pszText = "n/a";						
					vitem.iItem = i;						
					vitem.iSubItem = 1;						
					ListView_SetItem(RELOC2, &vitem);											
					
					vitem.pszText = "0";						
					vitem.iItem = i;						
					vitem.iSubItem = 2;						
					ListView_SetItem(RELOC2, &vitem);
				}else{
					//printf("index: %d, RVA: %.8x Type: %d\n", i+1, ((*(data+i))&0x0fff)+relocationTable->VirtualAddress, (*(data+i))>>12);
					itoa(i+1, tmpstr, 10);
					vitem.pszText = tmpstr;						
					vitem.iItem = i;						
					vitem.iSubItem = 0;												
					SendMessage(RELOC2, LVM_INSERTITEM,0,(DWORD)&vitem);
					
					itoa(((*(data+i))&0x0fff)+relocationTable->VirtualAddress, tmpstr, 16);
					vitem.pszText = tmpstr;						
					vitem.iItem = i;						
					vitem.iSubItem = 1;						
					ListView_SetItem(RELOC2, &vitem);											
					
					itoa((*(data+i))>>12, tmpstr, 10);
					vitem.pszText = tmpstr;						
					vitem.iItem = i;						
					vitem.iSubItem = 2;						
					ListView_SetItem(RELOC2, &vitem);
				}		
			}
		}
		relocationTable = (PIMAGE_BASE_RELOCATION)((char*)relocationTable+relocationTable->SizeOfBlock);
		index ++;
	}
};