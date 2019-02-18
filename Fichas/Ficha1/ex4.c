#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <minwinbase.h>
#define MAX 256

int _tmain4(int argc, LPSTR argv[])
{
	TCHAR executavel[MAX], resp;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	_tprintf(TEXT("Lançar outra aplicação igual a mim (S/N)?"));
	_tscanf_s(TEXT("%c"), &resp, 1);
	if(resp == 'S' || resp == 's')
	{
		ZeroMemory(&si, sizeof(STARTUPINFO)); // equivalente a preencher com 0s
		si.cb = sizeof(STARTUPINFO);
		//GetModuleFileName(NULL, executavel, MAX);
		_tcscpy_s(executavel, MAX, TEXT("notepad.exe")); // stringcopy
		_tprintf(TEXT("Processo a ser lançando: %s\n"), executavel);
		if (CreateProcess(NULL, executavel, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
		{
			_tprintf(TEXT("Sucesso\n"));
			_tprintf(TEXT("ID = %d \n"), pi.dwProcessId);
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess); // boa pratica
			CloseHandle(pi.hThread);
			_tprintf(TEXT("Terminou \n"));
		}
			
		else
			_tprintf(TEXT("Erro\n"));
	}
	
	_fgetchar();
	
	return 0;
}