#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

int _tmain(int argc, TCHAR *argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	HINSTANCE hLib;
	FARPROC varAdd, procAdd;

	
	hLib = LoadLibrary(_T("Ficha1_Ex8_DLL.dll"));
	if (hLib != NULL) {

		varAdd = (FARPROC)GetProcAddress(hLib, "nDLL");
		
		procAdd = (FARPROC)GetProcAddress(hLib, "UmaString");

		if (varAdd != NULL && procAdd != NULL) {

			(*((int *)varAdd)) += 1;

			// Usar a variável da DLL
			_tprintf(TEXT("Valor da variavel da DLL: %d\n"), *((int *)varAdd));

			// Chamar a função da DLL
			_tprintf(TEXT("Resultado da funcao da UmaString DLL: %d"), procAdd());
		}
		FreeLibrary(hLib);
	}

	_gettchar();
	return 0;
}