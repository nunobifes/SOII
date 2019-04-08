#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>


HANDLE hTimer;

int _tmain(int argc, LPSTR argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif


	SYSTEMTIME st;
	FILETIME ft, ftUTC;
	LARGE_INTEGER li;
	unsigned intervalo;

	ZeroMemory(&st, sizeof(SYSTEMTIME));
	GetSystemTime(&st);
	if(_stscanf_s(argv[1], _T("%hd:%hd:%hd"), &st.wHour, &st.wMinute, &st.wSecond))
	{
		_tprintf(_T("Erro no 1º argumento: formato esperado HH:MM:SS\n"));
	}

	intervalo = _ttoi(argv[2]);

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

	SystemTimeToFileTime(&st, &ft);
	LocalFileTimeToFileTime(&ft, &ftUTC);

	li.HighPart = ftUTC.dwHighDateTime;
	li.LowPart = ftUTC.dwLowDateTime;

	if (!SetWaitableTimer(hTimer, &li, 0, NULL, NULL, TRUE))
	{
		_tprintf(_T("Erro na programação do timer.\n"));
		return -1;
	}

}
