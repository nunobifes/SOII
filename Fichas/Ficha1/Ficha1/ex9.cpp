<<<<<<< HEAD
//usaDLL.cpp
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "DLL.h"

int _tmain(int argc, TCHAR *argv[])
{
	// Usar a variável da DLL
	_tprintf(TEXT("Valor da variavel da DLL: %d\n"), nDLL);

	// Chamar a função da DLL
	_tprintf(TEXT("Resultado da funcao da UmaString DLL: %d"), UmaString());
	
	_fgetchar();
	return 0;
=======
//usaDLL.cpp
#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "DLL.h"

int _tmain(int argc, TCHAR *argv[])
{
	// Usar a variável da DLL
	_tprintf(TEXT("Valor da variavel da DLL: %d\n"), nDLL);

	// Chamar a função da DLL
	_tprintf(TEXT("Resultado da funcao da UmaString DLL: %d"), UmaString());
	
	_fgetchar();
	return 0;
>>>>>>> 5deeeb3e98c551fb5dc5a708ab3729962bddb419
}