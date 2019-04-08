////includes do exercício anterior…
//#include <windows.h>
//#include <tchar.h>
//#include <io.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <time.h>
//#define LIM 10000
//#define NUM 4
//#define MAX 512
//
//typedef struct {
//	int x;
//	int y;
//	int start;
//	int end;
//}values;
//
//HANDLE h;
//DWORD WINAPI Thread(LPVOID param);
//void gotoxy(int x, int y);
//int _tmain(int argc, LPTSTR argv[]) {
//	TCHAR resp;
//	int y;
//	
//	HANDLE *tId; //Id da thread a ser criada no momento
//	HANDLE *hThread;//Array dinâmico de HANDLEs para cada thread a ser criada
//	TCHAR executavel[MAX]; //Nome deste programa executável com args
//	STARTUPINFO si; //Estrutura com dados iniciais para novo processo
//	PROCESS_INFORMATION pi; //A ser preenchida com dados do novo processo
//							//Criação e inicialização do mutex com nome
//	long N;
//	long inicio;
//	long fim;
//	long c;
//
//	//Cópia dos parâmetros passados, para tornar o código mais legível
//	N = _ttoi(argv[1]);
//	inicio = _ttoi(argv[2]);
//	fim = _ttoi(argv[3]);
//	//Cálculo do comprimento de intervalo para cada thread
//	c = (fim - inicio) / N;
//
//	values *v = malloc(sizeof(values) * N);
//
//	//Array dinâmico para guardar N Handles de thread
//	hThread = (HANDLE *)malloc(N * sizeof(HANDLE));
//	tId = (HANDLE *)malloc(N * sizeof(HANDLE));
//
//	h = CreateSemaphore(NULL, 1, 1, "MUTEX");
//
//	if (h == NULL) {
//		_tprintf(TEXT("Cannot Block with mutex... \n EXITING"));
//		return -1;
//	}
//#ifdef UNICODE
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//#endif
//	srand((int)time(NULL));
//	//Lançar um outro processo igual ao actual que dispute pelo mesmo mutex
//	_tprintf(TEXT("[%d]Lançar outro processo igual a mim?(S/N)"), GetCurrentProcessId());
//	_tscanf_s(TEXT("%c"), &resp, 1);
//	if (resp == 'S' || resp == 's') {
//		_stprintf_s(executavel, MAX, TEXT("%s %s %s %s"), argv[0], argv[1], argv[2], argv[3]);
//		ZeroMemory(&si, sizeof(STARTUPINFO));//É equivalente preencher com 0s
//		si.cb = sizeof(STARTUPINFO);
//		_tprintf(TEXT("[%d]Processo a ser lançado:%s\n"), GetCurrentProcessId(), argv[0]);
//		if (CreateProcess(NULL, executavel, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
//			_tprintf(TEXT("[%d]Sucesso\n"), GetCurrentProcessId());
//		else {
//			_tprintf(TEXT("[%d]Erro a criar processo\n"), GetCurrentProcessId());
//			return -1;
//		}
//
//
//	}
//	_tprintf(TEXT("[%d]A Lançar %d threads para percorrer %d-%d ..."), GetCurrentProcessId(), N, inicio, fim);
//
//	for (int i = 0; i < N; i++) {
//		v[i].x = rand() % 40;
//		v[i].y = rand() % 40;;
//		v[i].start = i * (fim / N);
//		v[i].end = (i * (fim / N)) + (fim / N);
//
//		hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&v[i], 0, &
//			tId[i]);
//	}
//	for (int i = 0; i < N; i++) {
//		_tprintf(TEXT("Lancei uma thread com id %d\n"), tId[i]);
//	}
//
//	WaitForMultipleObjects(N, hThread, TRUE, INFINITE);
//
//
//	_tprintf(TEXT("[Thread Principal %d]Vou terminar..."), GetCurrentThreadId());
//	return 0;
//}
///* ----------------------------------------------------- */
///* "Thread" - Funcao associada à Thread */
///* ----------------------------------------------------- */
//
//DWORD WINAPI Thread(LPVOID param) {
//	int i;
//	values *v = ((values*)param);
//	_tprintf(TEXT("[Thread %d]Vou começar a trabalhar\n"), GetCurrentThreadId());
//	Sleep(100);
//	for (i = v->start; i < v->end; i++) {
//		WaitForSingleObject(h, INFINITE);
//		gotoxy(v->x, v->y);
//		_tprintf(TEXT("Thread %5d"), i);
//		ReleaseSemaphore(h, 1, NULL);
//	}
//	return 0;
//}
//
//void gotoxy(int x, int y) {
//	static HANDLE hStdout = NULL;
//	COORD coord;
//	coord.X = x;
//	coord.Y = y;
//	if (!hStdout)
//		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleCursorPosition(hStdout, coord);
//}
