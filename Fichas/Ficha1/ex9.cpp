//usaDLL.cpp
// NOTE
// properties -> set as startup project (tem que ficar o nome a BOLD)
// properties -> C/C++ -> General -> Additional Include Directories -> adicionar path do projeto da DLL
// properties -> Linker -> Input -> Additional Dependencies -> (Adicionar nome do .lib do projeto da DLL)
// properties -> General -> Additional Library Directories -> (Adicionar $(OutDir) -> pasta para onde vai o output do build)

#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "Ficha1_Ex8_DLL.h"

int _tmain9(int argc, TCHAR *argv[])
{
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	nDLL += 1;

	// Usar a variável da DLL
	_tprintf(TEXT("Valor da variavel da DLL: %d\n"), nDLL);

	// Chamar a função da DLL
	_tprintf(TEXT("Resultado da funcao da UmaString DLL: %d"), UmaString());
	
	_gettchar();
	return 0;
}