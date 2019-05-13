#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#define PIPE_NAME TEXT("\\\\.\\pipe\\teste")
#define TAM 256
#define N 10

DWORD WINAPI ThreadConsola(LPVOID param);

HANDLE hPipes[N];
int numClientes = 0;
HANDLE hMutex;
int terminar = 0;

TCHAR buf[TAM];
DWORD n;
int i;

HANDLE hPipeTemp;
HANDLE hT;

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	// mutex
	hMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		TEXT("ex3-escritor"));      // unnamed mutex
	if (hMutex == NULL)
	{
		_tprintf(TEXT("CreateMutex error: %d\n"), GetLastError());
		return 1;
	}

	hT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadConsola, NULL, 0, NULL);
	if (hT != NULL)
		_tprintf(TEXT("Lancei uma thread...\n"));
	else
		_tprintf(TEXT("Erro ao criar Thread\n"));


	while (!terminar) {

		_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);
		hPipeTemp = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_OUTBOUND, PIPE_WAIT |
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, 1, sizeof(TCHAR), TAM * sizeof(TCHAR), 1000, NULL);
		if (hPipeTemp == INVALID_HANDLE_VALUE) {
			_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe)\n"));
			exit(-1);
		}

		_tprintf(TEXT("[ESCRITOR] Criar uma cópia do pipe...\n"));

		_tprintf(TEXT("[ESCRITOR] Esperar ligação de um leitor...(ConnectNamedPipe)\n"));
		if (!ConnectNamedPipe(hPipeTemp, NULL)) {
			_tprintf(TEXT("[ERRO] Ligação ao leitor! (ConnectNamedPipe\n"));
			exit(-1);
		}

		WaitForSingleObject(hMutex, INFINITE);

		if (numClientes < N) {
			hPipes[numClientes] = hPipeTemp;
			numClientes++;
		}

		ReleaseMutex(hMutex);
	}

	WaitForSingleObject(hT, INFINITE);
	_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));
	for (i = 0; i > numClientes; i++) {
		if (!DisconnectNamedPipe(hPipes[i])) {
			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)\n"));
			exit(-1);
		}
		CloseHandle(hPipes[i]);
	}

	Sleep(2000);
	CloseHandle(hPipeTemp);
	exit(0);
}

DWORD WINAPI ThreadConsola(LPVOID param) {
	int i;
	DWORD n;
	do {
		_tprintf(TEXT("[ESCRITOR] Frase: "));
		_fgetts(buf, 256, stdin);

		WaitForSingleObject(hMutex, INFINITE);

		buf[_tcslen(buf) - 1] = '\0';

		for (i = 0; i < numClientes; i++) {
			if (!WriteFile(hPipes[i], buf, _tcslen(buf) * sizeof(TCHAR), &n, NULL)) {
				_tprintf(TEXT("[ERRO] Escrever no pipe! (WriteFile)\n"));
				exit(-1);
			}
		}
		_tprintf(TEXT("[ESCRITOR] Enviei %d bytes ao leitor...(WriteFile)\n"), n);
	} while (_tcscmp(buf, TEXT("fim")));

	terminar = 1;

	CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return 0;
}

