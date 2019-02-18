#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#define TAM 200

int _tmain(int argc, TCHAR *argv[])
{
	HKEY chave;
	DWORD queAconteceu, versao, tamanho;
	TCHAR str[TAM], autor[TAM];

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	// criar/abrir uma chave em HKEY_CURRENT_USER\Software\MinhaAplicacao
	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\MinhaAplicação"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &chave, &queAconteceu) != ERROR_SUCCESS)
	{
		_tprintf(TEXT("Erro ao criar/abrir chave (%d) \n"), GetLastError());
		return -1;
	}
	else
	{
		// se a chave foi criada, inicializar os valores
		if (queAconteceu == REG_CREATED_NEW_KEY)
		{
			_tprintf(TEXT("Chave: HKEY_CURRENT_USER\\Software\\MinhaAplicação criada\n"));
			// criar valor "Autor" = "Meu Nome"
			RegSetValueEx(chave, TEXT("Autor"), 0, REG_SZ, (LPBYTE)TEXT("Nuno Rocha"), _tcsclen(TEXT("Nuno Rocha")) * sizeof(TCHAR));
			// criar valor "Versao" = 1
			versao = 1;
			RegSetValueEx(chave, TEXT("Versao"), 0, REG_DWORD, (LPBYTE)&versao, sizeof(DWORD));
			_tprintf(TEXT("Valores Autor e Versão guardados.\n"));
		}
		// se a chave foi aberta, ler os valores lá guardados
		else if(queAconteceu == REG_OPENED_EXISTING_KEY)
		{
			_tprintf(TEXT("Chave: HKEY_CURRENT_USER\\Software\\MinhaAplicação aberta\n"));
			tamanho = 20;
			RegQueryValueEx(chave, TEXT("Autor"), NULL, NULL, (LPBYTE)autor, &tamanho);
			autor[tamanho / sizeof(TCHAR)] = '\0';
			tamanho = sizeof(versao);
			RegQueryValueEx(chave, TEXT("Versão"), NULL, NULL, (LPBYTE)&versao, &tamanho);
			versao++;
			RegSetValueEx(chave, TEXT("Versao"), 0, REG_DWORD, (LPBYTE)&versao, sizeof(DWORD));
			_stprintf_s(str, TAM, TEXT("Autor: %s Versão: %d\n"), autor, versao);
		}
		RegCloseKey(chave);
	}
	_getch();
	return 0;
}