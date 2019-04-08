//ex3_leitor.c
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define BufferSize 100
#define Buffers 10

TCHAR NomeMemoria[] =TEXT("Nome da Memória Partilhada");
TCHAR(* PtrMemoria)[Buffers][BufferSize];

TCHAR NomeSemaforoPodeEscrever[]= TEXT("Semáforo Pode Escrever");
TCHAR NomeSemaforoPodeLer[]= TEXT("Semáforo Pode Ler");

HANDLE PodeEscrever;
HANDLE PodeLer;
HANDLE hMemoria;

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
	hMemoria = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(DADOS), NomeMemoria);
	
	if (PodeEscrever == NULL || PodeLer == NULL || hMemoria == NULL)
	{
		_tprintf(TEXT("[Erro]Criação de objectos do Windows(%d)\n"),GetLastError());
		return -1;
	}
	
	shm = (DADOS*)MapViewOfFile(hMemoria, FILE_MAP_WRITE, 0, 0, sizeof(DADOS));
	
	if (PtrMemoria == NULL)
	{
		_tprintf(TEXT("[Erro]Mapeamento da memória partilhada(%d)\n"), GetLastError());
		return -1;
	}
	
	for (int i = 0;; ++i){
		WaitForSingleObject(PodeLer, INFINITE);
		pos = shm->Out;
		shm->Out = (shm->Out + 1) % Buffers;
		_tprintf((*PtrMemoria)[i % 10]); // Reader reads data
		ReleaseSemaphore(PodeEscrever, 1, NULL);
	}

	UnmapViewOfFile(shm);
	CloseHandle(PodeEscrever);
	CloseHandle(PodeLer);
	CloseHandle(hMemoria);
	
	return 0;
}