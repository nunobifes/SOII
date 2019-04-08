//ex3_escritor.c
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BufferSize 100
#define Buffers 10

TCHAR NomeMemoria[] = TEXT("Nome da Memória Partilhada");
TCHAR(*PtrMemoria)[Buffers][BufferSize];

TCHAR NomeSemaforoPodeEscrever[]= TEXT("Semáforo Pode Escrever");
TCHAR NomeSemaforoPodeLer[]= TEXT("Semáforo Pode Ler");

HANDLE PodeEscrever;
HANDLE PodeLer;
HANDLE hMemoria;
HANDLE hFile;

typedef struct
{
	TCHAR buffer[Buffers][BufferSize];
	int In, Out;
}DADOS;

int _tmain(void)
{

	DADOS* shm;
	char init = 0;
	int pos;
	PodeEscrever = CreateSemaphore(NULL, Buffers, Buffers, NomeSemaforoPodeEscrever);
	PodeLer = CreateSemaphore(NULL, 0, Buffers, NomeSemaforoPodeLer);

	hFile = CreateFile(_T("ex3.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
		init = 1;


	hMemoria = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, sizeof(DADOS), NomeMemoria);

	if (PodeEscrever == NULL || PodeLer == NULL || hMemoria == NULL)
	{
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	shm = (DADOS*)MapViewOfFile(hMemoria, FILE_MAP_WRITE, 0, 0, sizeof(DADOS));

	if (shm == NULL)
	{
		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
		return -1;
	}

	if(init)
	{
		_tprintf(_T("Init...\n"));
		shm->In = 0;
		shm->Out = 0;
		ReleaseSemaphore(PodeEscrever, Buffers, NULL);
	}
	else
	{
		_tprintf(_T("Continua a execução anterior..\n"));
		ReleaseSemaphore(PodeEscrever, Buffers - shm->In, NULL);
		ReleaseSemaphore(PodeLer, Buffers - shm->Out, NULL);
	}

	for (int i = 0; i < 100; i++){

		WaitForSingleObject(PodeEscrever, INFINITE);
		pos = shm->In;
		shm->In = (shm->In + 1) % Buffers;  // Incrementar SHM
		_tprintf(TEXT("Escrever para buffer %i\n"), i);
		_stprintf_s(shm->buffer[pos], BufferSize, TEXT("Escritor-%i\n"), i);
		Sleep(1000);
		ReleaseSemaphore(PodeLer, 1, NULL);
	}

	UnmapViewOfFile(shm);
	CloseHandle(PodeEscrever);
	CloseHandle(PodeLer);
	CloseHandle(hMemoria);

	return 0;
}