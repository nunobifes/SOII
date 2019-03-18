//#include <windows.h>
//#include <tchar.h>
//#include <io.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <time.h>
//
//#define LIM 10000
//
//DWORD WINAPI Thread(LPVOID param);
//void gotoxy(int x, int y);
//
//
//typedef struct
//{
//	int y;
//	int lim1;
//	int lim2;
//} strct;
//
//int _tmain2(int argc, LPSTR argv[])
//{
//#ifdef UNICODE
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stderr), _O_WTEXT);
//#endif
//
//	TCHAR resp;
//	DWORD threadId[4];  // Id da thread a ser criada
//	HANDLE hT[4];  // HANDLE/Ponteiro para a thread a ser criada
//	strct *stct = malloc(4 * sizeof(strct));
//	srand((int)time(NULL));
//	_tprintf(_T("Lançar Thread (S/N)?"));
//	_tscanf_s(_T("%c"), &resp, 1);
//	int aux = 0;
//	if (resp == 'S' || resp == 's')
//	{
//
//		for(int i = 0; i< 4; i++){
//			stct[i].lim1 = aux;
//			stct[i].lim2 = stct[i].lim1 + (LIM / 4) - 1;
//			stct[i].y = rand() % 40;
//			hT[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&stct[i], 0, &threadId[i]);
//			if (hT[i] != NULL)
//			{
//				_tprintf(_T("Lancei thread com o Id: %d\n"), threadId[i]);
//				//WaitForSingleObject(hT, INFINITE);
//			}
//			else
//			{
//				_tprintf(_T("Erro ao criar Thread\nVou Terminar..."));
//				_gettchar();
//				_gettchar();
//				return 0;
//			}
//			aux = stct[i].lim2 + 1;
//		}
//
//	}
//	else
//	{
//		_tprintf(_T("Adeus."));
//		_gettchar();
//
//		return 0;
//	}
//	WaitForMultipleObjects(4, hT, TRUE, INFINITE);
//	_tprintf(_T("[Thread Principal %d] Vou Terminar..."), GetCurrentThreadId());
//	free(stct);
//	_gettchar();
//	_gettchar();
//	return 0;
//
//}
//
//// -------------------------------------------------------------
//// "Thread" - Função associada à Thread
//// -------------------------------------------------------------
////
////DWORD WINAPI Thread(LPVOID param)
////{
////	int i;
////	strct *stct = ((strct*)param);
////	_tprintf(_T("[Thread %d] Vou começar a trabalhar\n"), GetCurrentThreadId());
////	Sleep(100);
////	for (i = stct->lim1; i < stct->lim2; i++)
////	{
////		gotoxy(40, 10 + (stct->lim1/1000));
////		_tprintf(_T("[Thread %d] -> %5d   "), GetCurrentThreadId(), i);
////	}
////	return 0;
////}
////
////void gotoxy(int x, int y)
////{
////	static HANDLE hStdout = NULL;
////	COORD coord;
////	coord.X = x;
////	coord.Y = y;
////	if (!hStdout)
////		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
////	SetConsoleCursorPosition(hStdout, coord);
////}