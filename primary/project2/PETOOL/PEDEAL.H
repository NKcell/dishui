#include <stdio.h>
#include<string.h>
#include"stdafx.h"
#include "windows.h"
#include<stdlib.h>

LPVOID filetomem(int* rfileLen);
void initHead(char* mem);
void setPEheadValue(HWND hwndDlg);
void setDir(HWND hwndDlg);
void setSection(HWND hSection);
void enumImportDll(HWND hDllName);
void EnumDLLINFO(HWND hListDLLNAME, WPARAM wParam,LPARAM lParam,HWND hListDLLINFO);
void setBound();
void enumBound(HWND hListBound);
void enumTYPEID(HWND hTYPEID);
void EnumSIGN(HWND hListTYPE, WPARAM wParam,LPARAM lParam,HWND hListSIGN);
void enumExport(HWND hDlg,HWND hListExport);
void EnumRELOCATION1(HWND hRELOC);
void EnumRELOC2(HWND RELOC1, WPARAM wParam,LPARAM lParam, HWND RELOC2);
LPVOID readfile(int* rfileLen, char* szFile);
LPVOID savefile(char* mem, unsigned int lensize, char* savefilename);