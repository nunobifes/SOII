//#include <windows.h>
//#include <tchar.h>
//#include <io.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <time.h>
//#define LIM 10000
//#define NUM 4
//#define NAME "EVENTO"
////includes dos exercícios anteriores
//#define MAX 256
//DWORD WINAPI ThreadProdutor(LPVOID param);
//DWORD WINAPI ThreadConsumidor(LPVOID param); 
//
//HANDLE hMutex;
//HANDLE hEvent;
//TCHAR frase[MAX];
//BOOL nova = 0;
//int _tmain(int argc, LPTSTR argv[]) {
//	TCHAR resp;
//	DWORD threadId;
//	HANDLE hThreadProd, hThreadCons;
//	hMutex = CreateMutex(NULL, FALSE, NULL);
//	hEvent = CreateEvent(NULL, FALSE, FALSE, NAME);
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
//	_tprintf(TEXT("Lançar threads produtor-consumidor?"));
//	_tscanf_s(TEXT("%c"), &resp, 1);   if (resp == 'S' || resp == 's'){
//		hThreadProd = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProdutor, NULL, 0, &threadId);
//		if (hThreadProd != NULL)
//			_tprintf(TEXT("Lancei uma thread com id %d\n"), threadId);
//		else{
//			_tprintf(TEXT("Erro ao criar Thread\n"));
//			return -1;
//		} 
//			hThreadCons = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadConsumidor, NULL, 0, &threadId);
//			if (hThreadCons != NULL)
//				_tprintf(TEXT("Lancei uma thread com id %d\n"), threadId);
//			else{    
//				_tprintf(TEXT("Erro ao criar Thread\n"));
//				return -1;
//			}
//		WaitForSingleObject(hThreadProd, INFINITE);  
//		WaitForSingleObject(hThreadCons, INFINITE);
//	} 
//	_tprintf(TEXT("[Thread Principal %d]Finalmente vou terminar..."), GetCurrentThreadId());
//	return 0;
//} 
//
//	DWORD WINAPI ThreadProdutor(LPVOID param) {
//		TCHAR strLocal[MAX];
//
//		_tprintf(TEXT("[Produtor]Sou a thread %d e vou começar a trabalhar ...\n Prima \'fim\' para terminar...\n"), GetCurrentThreadId()); 
//		Sleep(100); 
//		do {
//			_fgetts(strLocal, MAX, stdin); 
//			fflush(stdin);
//			SetEvent(hEvent);
//			WaitForSingleObject(hMutex, INFINITE); 
//			_tcscpy_s(frase, MAX, strLocal);
//			ReleaseMutex(hMutex);
//		} while (_tcsncmp(strLocal, TEXT("fim"), 3));
//		return 0;
//	}
//	DWORD WINAPI ThreadConsumidor(LPVOID param) {
//		TCHAR strLocal[MAX];
//
//		_tprintf(TEXT("[Consumidor]Sou a thread %d e vou começar a trabalhar ...\n"), GetCurrentThreadId());
//		Sleep(100);  
//		do { 
//			WaitForSingleObject(hEvent, INFINITE);
//			WaitForSingleObject(hMutex, INFINITE); 
//			_tcscpy_s(strLocal, MAX, frase);
//			_tprintf(TEXT("[Consumidor %d]:%s"), GetCurrentThreadId(), strLocal);
//			ReleaseMutex(hMutex);
//			
//			//Sleep(1000);
//		} while (_tcsncmp(strLocal, TEXT("fim"), 3));
//		return 0;
//	}