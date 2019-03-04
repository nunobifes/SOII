// Ficha1_Ex8_DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <windows.h>
#include "Ficha1_Ex8_DLL.h"

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
	if (_tcslen(str) > 1) { // Introduzir mais caracteres do que apenas <enter>
		_tprintf(str);  // exercicio 10
		return 1;
	}
	else {
		_tprintf(TEXT("Não escreveu nada.\n"));  // exercicio 10
		return 0;
	}
}


