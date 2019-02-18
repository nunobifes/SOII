<<<<<<< HEAD
//DLL.h
// o bloco ifdef seguinte é o modo standard de criar macros que tornam a exportação de
// funções e variáveis mais simples. Todos od ficheiros neste projeto DLL são
// compilados com o símbolo DLL_IMP_EXPORTS definido. Este símbolo não deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// ficheiro irá ver as funções e variáveis DLL_IMP_API como sendo importadas de uma DLL.

#include <windows.h>
#include <tchar.h>
// Definir uma constante para facilitar a leitura do protótipo da função
// Este  .h dee ser incluído no projeto que o vai usar (modo implícito)
#define TAM 256
// Esta macro é definida pelo sistema caso estejamos na DLL( <DLL_IMP>_EXPORTS definida)
// ou na app ( <DLL_IMP>_Exports não definida) onde DLL_IMP é o nome deste projeto
#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	// Variável global da DLL
	extern DLL_IMP_API int nDLL;

	// Funções a serem exportadas/importadas
	DLL_IMP_API int UmaString(void);
=======
//DLL.h
// o bloco ifdef seguinte é o modo standard de criar macros que tornam a exportação de
// funções e variáveis mais simples. Todos od ficheiros neste projeto DLL são
// compilados com o símbolo DLL_IMP_EXPORTS definido. Este símbolo não deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// ficheiro irá ver as funções e variáveis DLL_IMP_API como sendo importadas de uma DLL.

#include <windows.h>
#include <tchar.h>
// Definir uma constante para facilitar a leitura do protótipo da função
// Este  .h dee ser incluído no projeto que o vai usar (modo implícito)
#define TAM 256
// Esta macro é definida pelo sistema caso estejamos na DLL( <DLL_IMP>_EXPORTS definida)
// ou na app ( <DLL_IMP>_Exports não definida) onde DLL_IMP é o nome deste projeto
#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	// Variável global da DLL
	extern DLL_IMP_API int nDLL;

	// Funções a serem exportadas/importadas
	DLL_IMP_API int UmaString(void);
>>>>>>> 5deeeb3e98c551fb5dc5a708ab3729962bddb419
}