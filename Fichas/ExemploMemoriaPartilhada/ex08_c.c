#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX 256

#define FILE_PATH TEXT("FicheiroPartilhado.txt")

int _tmain(int argc, LPTSTR argv[]) 
{
	HANDLE hMutex, hEvento, /*hFicheiro,*/hShared;
	TCHAR frase[MAX];
	DWORD n, res;
	TCHAR* ptrMemoria;

	hShared = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, 0, sizeof(frase), _T("SharedMem"));

	//hFicheiro = CreateFile(FILE_PATH, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	hMutex = CreateMutex(NULL, FALSE, TEXT("MeuMutex"));

	hEvento = CreateEvent(NULL, TRUE, FALSE, TEXT("MeuEvento"));

	if (hShared == NULL || hMutex == NULL || hEvento == NULL) 
	{
		_tprintf(TEXT("Erro a abrir recursos de comunicação e/ou sincronização.\n"));
		return -1;
	}

	ptrMemoria = (TCHAR*)MapViewOfFile(hShared, FILE_MAP_READ, 0, 0, sizeof(frase));
	if (ptrMemoria == NULL)
	{
		_tprintf(TEXT("Erro a mapear memoria partilhada.\n"));
		return -1;

	}


	#ifdef UNICODE
		_setmode(_fileno(stdin), _O_WTEXT);
		_setmode(_fileno(stdout), _O_WTEXT);
	#endif

	_tprintf(TEXT("[Processo Consumidor %d] Vou começar a trabalhar...\n Prima \'fim\' para terminar...\n"), GetCurrentProcessId());
	
	do 
	{		
		WaitForSingleObject(hEvento, INFINITE);
		
		WaitForSingleObject(hMutex, INFINITE);
		
		//res = ReadFile(hShared, frase, MAX * sizeof(TCHAR), &n, NULL);

		
		_tcscpy_s(frase, (_tcslen(ptrMemoria) + 1) * sizeof(TCHAR), ptrMemoria);

		_tprintf(TEXT("[Consumidor]: %s"), frase);

		ReleaseMutex(hMutex);
	} 
	while (_tcsncmp(frase, TEXT("fim"), 3) && n > 0 && res != 0);

	_tprintf(TEXT("[Processo Consumidor %d] Finalmente vou terminar..."), GetCurrentProcessId());

	CloseHandle(hMutex);
	CloseHandle(hEvento);
	CloseHandle(hShared);

	return 0;
}
