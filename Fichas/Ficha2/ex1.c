//#include <windows.h>
//#include <tchar.h>
//#include <io.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <time.h>
//
//#define LIM 1000
//
//DWORD WINAPI Thread(LPVOID param);
//void gotoxy(int x, int y);
//
//int _tmain1(int argc, LPSTR argv[])
//{
//#ifdef UNICODE
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//	_setmode(_fileno(stderr), _O_WTEXT);
//#endif
//
//	TCHAR resp;
//	int y;
//	DWORD threadId;  // Id da thread a ser criada
//	HANDLE hT;  // HANDLE/Ponteiro para a thread a ser criada
//
//	srand((int)time(NULL));
//	_tprintf(_T("Lançar Thread (S/N)?"));
//	_tscanf_s(_T("%c"), &resp, 1);
//	if(resp == 'S' || resp == 's')
//	{
//		y = rand() % 40;
//		hT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)y, 0, &threadId);
//		if(hT != NULL)
//		{
//			_tprintf(_T("Lancei thread com o Id: %d\n"), threadId);
//			WaitForSingleObject(hT, INFINITE);
//		}
//		else
//		{
//			_tprintf(_T("Erro ao criar Thread\nVou Terminar..."));
//			_gettchar();
//			_gettchar();
//			return 0;
//		}
//			
//	}else
//	{
//		_tprintf(_T("Adeus."));
//		_gettchar();
//		_gettchar();
//		return 0;
//	}
//	
//		_tprintf(_T("[Thread Principal %d] Vou Terminar..."), GetCurrentThreadId());
//		_gettchar();
//		_gettchar();
//		return 0;
//
//
//}
//
//// -------------------------------------------------------------
//// "Thread" - Função associada à Thread
//// -------------------------------------------------------------
//
////DWORD WINAPI Thread(LPVOID param)
////{
////	int i;
////	int y = ((int)param);
////	_tprintf(_T("[Thread %d] Vou começar a trabalhar\n"), GetCurrentThreadId());
////	Sleep(100);
////	for (i = 0; i<LIM; i++)
////	{
////		gotoxy(y, y);
////		_tprintf(_T("Thread %5d   "), i);
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