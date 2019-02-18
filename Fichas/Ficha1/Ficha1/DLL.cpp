<<<<<<< HEAD
//DLL.cpp
#include <windows.h>
#include "DLL.h"

// Para verificar ao carregar a dll que a aplicação irá ocupar mais memória
char ponteiro[40960];

// Definição da variável global
int nDLL = 1234;

// Exportar a função para ser utilizada fora da DLL
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

// Para verificar ao carregar a dll que a aplicação irá ocupar mais memória
char ponteiro[40960];

// Definição da variável global
int nDLL = 1234;

// Exportar a função para ser utilizada fora da DLL
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
