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
////includes dos exercícios anteriores
//#define MAX 256
//
//HANDLE hMutex;
//HANDLE hEvent;
//HANDLE hFich;
//TCHAR frase[MAX];
//
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
//
//	hFich = CreateFile(FILE_PATH, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
// 
//	do {
//		_fgetts(strLocal, MAX, stdin);
//		fflush(stdin);
//		WaitForSingleObject(hMutex, INFINITE);
//		WriteFile(hFich, strLocal, MAX, NULL, NULL);
//		SetEvent(hEvent);
//		ReleaseMutex(hMutex);
//		ResetEvent(hEvent);
//	} while (_tcsncmp(strLocal, TEXT("fim"), 3));
//	return 0;
//} 