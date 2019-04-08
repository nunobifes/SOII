#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

#define LIM 10000

DWORD WINAPI Thread(LPVOID param);
void gotoxy(int x, int y);

HANDLE h;

typedef struct
{
	int y;
	int lim1;
	int lim2;
} strct;

int _tmain(int argc, LPSTR argv[])
{
	TCHAR resp;
	int y;
	DWORD threadId;//Id da thread a ser criada no momento
	HANDLE *hT;//Array dinâmico de HANDLEs para cada thread a ser criada
	TCHAR executavel[MAX_PATH];//Nome deste programa executávelcom args
	STARTUPINFO si;//Estrutura com dados iniciais para novo processo
	PROCESS_INFORMATION pi;//A ser preenchida com dados do novo processo



	N = _ttoi(argv[1]);
	inicio = _ttoi(argv[2]);
	fim = _ttoi(argv[3]);
	//Cálculo do comprimento de intervalo para cada thread
	c = (fim -inicio) / N;
	//Array dinâmico para guardar N Handles de threadh
	Threade = (HANDLE *)malloc(N * sizeof(HANDLE));

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	
	strct *stct = malloc(4 * sizeof(strct));
	srand((int)time(NULL));
	_tprintf(_T("Lançar Thread (S/N)?"));
	_tscanf_s(_T("%c"), &resp, 1);
	h = CreateMutex(NULL, FALSE, NULL);
	int aux = 0;
	int aux2 = THREAD_PRIORITY_LOWEST;
	if (resp == 'S' || resp == 's')
	{

		for (int i = 0; i < 4; i++) {
			stct[i].lim1 = aux;
			stct[i].lim2 = stct[i].lim1 + (LIM / 4) - 1;
			stct[i].y = rand() % 40;
			hT[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&stct[i], 0, &threadId[i]);
			SetThreadPriority(hT[i], aux2);
			if (aux2 != THREAD_PRIORITY_LOWEST)
				aux2 = THREAD_PRIORITY_HIGHEST;
			if (hT[i] != NULL)
			{
				_tprintf(_T("Lancei thread com o Id: %d\n"), threadId[i]);
				//WaitForSingleObject(hT, INFINITE);
			}
			else
			{
				_tprintf(_T("Erro ao criar Thread\nVou Terminar..."));
				_gettchar();
				_gettchar();
				return 0;
			}
			aux = stct[i].lim2 + 1;
		}

	}
	else
	{
		_tprintf(_T("Adeus."));
		_gettchar();

		return 0;
	}
	WaitForMultipleObjects(4, hT, TRUE, INFINITE);
	_tprintf(_T("[Thread Principal %d] Vou Terminar..."), GetCurrentThreadId());
	free(stct);
	CloseHandle(h);
	_gettchar();
	_gettchar();
	return 0;

}

// -------------------------------------------------------------
// "Thread" - Função associada à Thread
// -------------------------------------------------------------

DWORD WINAPI Thread(LPVOID param)
{
	int i;
	strct *stct = ((strct*)param);
	_tprintf(_T("[Thread %d] Vou começar a trabalhar\n"), GetCurrentThreadId());
	Sleep(100);
	for (i = stct->lim1; i < stct->lim2; i++)
	{
		WaitForSingleObject(h, INFINITE);
		gotoxy(40, 10 + (stct->lim1 / 1000));
		_tprintf(_T("[Thread %d] -> %5d   "), GetCurrentThreadId(), i);
		ReleaseMutex(h);
	}
	return 0;
}

void gotoxy(int x, int y)
{
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if (!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, coord);
}