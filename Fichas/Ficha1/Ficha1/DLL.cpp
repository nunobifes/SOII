<<<<<<< HEAD
//DLL.cpp
#include <windows.h>
#include "DLL.h"

// Para verificar ao carregar a dll que a aplica��o ir� ocupar mais mem�ria
char ponteiro[40960];

// Defini��o da vari�vel global
int nDLL = 1234;

// Exportar a fun��o para ser utilizada fora da DLL
int UmaString(void)
{
	TCHAR str[TAM];
	_tprintf(TEXT("Dentro da DLL\nIntroduza uma frase:"));
	_fgetts(str, TAM, stdin);
	if (_tcslen(str) > 1)  // Introduzir mais caracteres do que apenas <enter>
		return 1;
	else
		return 0;
}
=======
//DLL.cpp
#include <windows.h>
#include "DLL.h"

// Para verificar ao carregar a dll que a aplica��o ir� ocupar mais mem�ria
char ponteiro[40960];

// Defini��o da vari�vel global
int nDLL = 1234;

// Exportar a fun��o para ser utilizada fora da DLL
int UmaString(void)
{
	TCHAR str[TAM];
	_tprintf(TEXT("Dentro da DLL\nIntroduza uma frase:"));
	_fgetts(str, TAM, stdin);
	if (_tcslen(str) > 1)  // Introduzir mais caracteres do que apenas <enter>
		return 1;
	else
		return 0;
}
>>>>>>> 5deeeb3e98c551fb5dc5a708ab3729962bddb419
