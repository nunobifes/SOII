//#include <windows.h>
//#include <tchar.h>
//#include <fcntl.h>
//#include <io.h>
//#include <stdio.h>
//includes do exercício anterior…
//#include <time.h>
//#define LIM 10000
//
//typedef struct {
//	int posI, posF;
//}dado;
//TCHAR *palavra, *ficheiro;
//DWORD WINAPI Thread(LPVOID param);
//void gotoxy(int x, int y);
//int _tmain(int argc, LPTSTR argv[]) { //Sintaxe: programa N_threads
//	int inicio = GetTickCount();
//	TCHAR resp;
//	int y, N_threads;
//	DWORD threadId; //Id da thread a ser criada
//	HANDLE * hT; //HANDLE/ponteiro para cada thread a ser criada
//	dado * arrayDados;
//	FILE * fp = NULL;
//	int n_bytes, n_bytes_t;
//#ifdef UNICODE
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//#endif
//	if (argc != 4) {
//		_tprintf(TEXT("Erro no nº de argumentos: %s N_threads\n"), argv[0]);
//		return -1;
//	}
//	N_threads = _ttoi(argv[1]);
//	palavra = argv[2];
//	ficheiro = argv[3];
//	if(_tfopen_s(&fp, ficheiro, _T("rt")) != 0)
//	{
//		_tprintf(TEXT("Erro ao abrir o ficheiro\n"));
//		return -1;
//	}
//
//
//	arrayDados = (dado *)malloc(N_threads * sizeof(dado));
//	
//	hT = (HANDLE *)malloc(N_threads * sizeof(HANDLE));
//
//	if(fseek(fp, 0, SEEK_END) !=0)
//	{
//		_tprintf(TEXT("Erro ao mover ponteiro\n"));
//		return -1;
//	}
//	n_bytes = ftell(fp);
//	fclose(fp);
//
//	n_bytes_t = n_bytes / N_threads;
//	int aux = 0;
//	_tprintf(TEXT("Lançar thread (S/N)?"));
//	_tscanf_s(TEXT("%c"), &resp, 1);
//	if (resp == 'S' || resp == 's') {
//		Criar as N threads
//		for (int i = 0; i < N_threads; i++) {
//			
//
//			arrayDados[i].posI = aux;
//			arrayDados[i].posF = arrayDados[i].posI + (n_bytes_t - 1);
//			hT[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)&arrayDados[i],
//				0, &threadId);
//			if (hT[i] != NULL)
//				_tprintf(TEXT("Lancei uma thread[%d] com id %d\n Prima qq tecla para começar..."),
//					i, threadId);
//			_tscanf_s(TEXT(" %c"), &resp, 1); //Esperar até o utilizador desejar iniciar a thread
//			ResumeThread(hT); 
//			else
//				_tprintf(TEXT("Erro ao criar Thread\n"));
//
//			aux = arrayDados[i].posF + 1;
//		}
//		
//		WaitForMultipleObjects(N_threads, hT, 1, INFINITE);
//		_tprintf(TEXT("Todas as threads terminaram\ndemoraram :%d miliseg\n"), GetTickCount() - inicio);
//		for (int i = 0; i < N_threads; i++)
//			CloseHandle(hT[i]);
//	}
//	Libertar arrays dinâmicos
//	free(arrayDados);
//	free(hT);
//	_tprintf(TEXT("[Thread Principal %d]Vou terminar..."), GetCurrentThreadId());
//	_gettchar();
//	_gettchar();
//	return 0;
//}
///* ----------------------------------------------------- */
///* "Thread" - Funcao associada à Thread */
///* ----------------------------------------------------- */
//DWORD WINAPI Thread(LPVOID param) {
//	dado * ptrDado = (dado *)param;
//	TCHAR str[100];
//
//	FILE * fp = NULL;
//	if (_tfopen_s(&fp, ficheiro, _T("rt")) != 0)
//	{
//		_tprintf(TEXT("Erro ao abrir o ficheiro\n"));
//		return -1;
//	}
//
//	_tprintf(TEXT("[Thread %d]Vou começar a trabalhar, ordem:%d\n"), GetCurrentThreadId(), ptrDado->posI);
//	
//	if (fseek(fp, ptrDado->posI, SEEK_SET) != 0)
//	{
//		_tprintf(TEXT("Erro ao mover ponteiro\n"));
//		return -1;
//	}
//	
//	
//	while(_fgetts(str, 100, fp) != NULL)
//	{
//		if(_tcsstr(str, palavra) != NULL)
//		{
//			_tprintf(TEXT("[Thread %d] Encontrou na linha: %s"), GetCurrentThreadId(), str);
//		}
//		if (ftell(fp) >= ptrDado->posF)
//			break;
//	}
//	return 0;
//}
