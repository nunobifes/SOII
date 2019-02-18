#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>

using namespace std;

#ifdef UNICODE
#define tcout wcout
#define tcin wcin
#define tstring wstring
#else
#define tcout cout
#define tcin cin
#define tstring string
#endif

int _tmain3(int argc, LPSTR argv[])
{
	tstring str = TEXT("Olá! Este programa é para aceitar UNICODE. Insira \'fim\' para sair\n");
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	tcout << str;
	do
	{
		getline(tcin, str);
		for (unsigned int i = 0; i < str.length(); i++)
			str[i] = _totupper(str[i]);
		tcout << TEXT("Frase: ") << str << TEXT("Tamanho: ") << str.length() << endl;
	} while (str != TEXT("FIM"));
	return 0;
}