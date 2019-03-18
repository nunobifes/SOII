#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
//includes do exercício anterior…
#include <time.h>
#define LIM 10000

typedef struct {
	int pos, ordem;
}dado;

HANDLE h;

DWORD WINAPI Thread(LPVOID param);
void gotoxy(int x, int y);
int _tmain(int argc, LPTSTR argv[]) { //Sintaxe: programa N_threads
	TCHAR resp;
	int y, N_threads;
	DWORD threadId; //Id da thread a ser criada
	HANDLE * hT; //HANDLE/ponteiro para cada thread a ser criada
	dado * arrayDados;
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	if (argc != 2) {
		_tprintf(TEXT("Erro no nº de argumentos: %s N_threads\n"), argv[0]);
		return -1;
	}

	h = CreateMutex(NULL, FALSE, NULL);

	N_threads = _ttoi(argv[1]);
	arrayDados = (dado *)malloc(N_threads * sizeof(dado));
	hT = (HANDLE *)malloc(N_threads * sizeof(HANDLE));
	srand((int)time(NULL));
	_tprintf(TEXT("Lançar thread (S/N)?"));
	_tscanf_s(TEXT("%c"), &resp, 1);
	if (resp == 'S' || resp == 's') {
		//Criar as N threads
		for (int i = 0; i < N_threads; i++) {
			y = rand() % 40;
			arrayDados[i].pos = y;
			arrayDados[i].ordem = i + 1;
			hT[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&arrayDados[i],
				0, &threadId);
			if (hT[i] != NULL)
				_tprintf(TEXT("Lancei uma thread[%d] com id %d\n Prima qq tecla para começar..."),
					i, threadId);
			//_tscanf_s(TEXT(" %c"), &resp, 1); //Esperar até o utilizador desejar iniciar a thread
			//ResumeThread(hT); 
			else
				_tprintf(TEXT("Erro ao criar Thread\n"));
		}
		_tscanf_s(TEXT(" %c"), &resp, 1); //Esperar até o utilizador desejar iniciar a thread
		for (int i = 0; i < N_threads; i++)
			SuspendThread(hT[i]);
		_tscanf_s(TEXT(" %c"), &resp, 1);
		for (int i = 0; i < N_threads; i++)
			ResumeThread(hT[i]);
		WaitForMultipleObjects(N_threads, hT, 1, INFINITE);
		_tprintf(TEXT("Todas as threads terminaram\n"));
		for (int i = 0; i < N_threads; i++)
			CloseHandle(hT[i]);
	}
	//Libertar arrays dinâmicos
	free(arrayDados);
	free(hT);
	_tprintf(TEXT("[Thread Principal %d]Vou terminar..."), GetCurrentThreadId());
	return 0;
}
/* ----------------------------------------------------- */
/* "Thread" - Funcao associada à Thread */
/* ----------------------------------------------------- */
DWORD WINAPI Thread(LPVOID param) {
	int i;
	dado * ptrDado = (dado *)param;
	_tprintf(TEXT("[Thread %d]Vou começar a trabalhar, ordem:%d\n"), GetCurrentThreadId(), ptrDado->ordem);
	Sleep(100);

	for (i = 0; i < LIM; i++) {
		WaitForSingleObject(h, INFINITE);
		gotoxy(ptrDado->pos, ptrDado->pos);
		_tprintf(TEXT("Thread %5d "), i);
		ReleaseMutex(h);
	}
	return 0;
}
void gotoxy(int x, int y) {
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if (!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, coord);
}