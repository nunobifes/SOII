//#include <windows.h>
//#include <tchar.h>
//#include <io.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <time.h>
//#define LIM 10000
//#define NUM 4
//#define NAMEEV "EVENTO"
//#define NAMEMUT "MUTEX"
//#define FILE_PATH "fich.txt"
//
////includes dos exercícios anteriores
//#define MAX 256
//
//HANDLE hMutex;
//HANDLE hEvent;
//HANDLE hFich;
//TCHAR frase[MAX];
//BOOL nova = 0;
//int _tmain(int argc, LPTSTR argv[]) {
//	hMutex = CreateMutex(NULL, FALSE, NAMEMUT);
//	hEvent = CreateEvent(NULL, TRUE, FALSE, NAMEEV);
//	if (hMutex == NULL) {
//		_tprintf(TEXT("MUTEX ERROR"));
//	}
//	if (hEvent == NULL) {
//		_tprintf(TEXT("EVENT ERROR"));
//	}
//	//UNICODE: Por defeito, a consola Windows não processe caracteres wide.
//	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:
//#ifdef UNICODE
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//#endif
//	TCHAR strLocal[MAX];
//	hFich = CreateFile(FILE_PATH, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	do {
//		WaitForSingleObject(hEvent, INFINITE);
//		WaitForSingleObject(hMutex, INFINITE);
//		
//		ReadFile(hFich, strLocal, MAX, NULL, NULL);
//
//		_tprintf(TEXT("[Consumidor %d]:%s"), GetCurrentThreadId(), strLocal);
//		ReleaseMutex(hMutex);
//
//		//Sleep(1000);
//	} while (_tcsncmp(strLocal, TEXT("fim"), 3));
//
//	return 0;
//} 