<<<<<<< HEAD
//DLL.h
// o bloco ifdef seguinte � o modo standard de criar macros que tornam a exporta��o de
// fun��es e vari�veis mais simples. Todos od ficheiros neste projeto DLL s�o
// compilados com o s�mbolo DLL_IMP_EXPORTS definido. Este s�mbolo n�o deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// ficheiro ir� ver as fun��es e vari�veis DLL_IMP_API como sendo importadas de uma DLL.

#include <windows.h>
#include <tchar.h>
// Definir uma constante para facilitar a leitura do prot�tipo da fun��o
// Este  .h dee ser inclu�do no projeto que o vai usar (modo impl�cito)
#define TAM 256
// Esta macro � definida pelo sistema caso estejamos na DLL( <DLL_IMP>_EXPORTS definida)
// ou na app ( <DLL_IMP>_Exports n�o definida) onde DLL_IMP � o nome deste projeto
#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	// Vari�vel global da DLL
	extern DLL_IMP_API int nDLL;

	// Fun��es a serem exportadas/importadas
	DLL_IMP_API int UmaString(void);
=======
//DLL.h
// o bloco ifdef seguinte � o modo standard de criar macros que tornam a exporta��o de
// fun��es e vari�veis mais simples. Todos od ficheiros neste projeto DLL s�o
// compilados com o s�mbolo DLL_IMP_EXPORTS definido. Este s�mbolo n�o deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// ficheiro ir� ver as fun��es e vari�veis DLL_IMP_API como sendo importadas de uma DLL.

#include <windows.h>
#include <tchar.h>
// Definir uma constante para facilitar a leitura do prot�tipo da fun��o
// Este  .h dee ser inclu�do no projeto que o vai usar (modo impl�cito)
#define TAM 256
// Esta macro � definida pelo sistema caso estejamos na DLL( <DLL_IMP>_EXPORTS definida)
// ou na app ( <DLL_IMP>_Exports n�o definida) onde DLL_IMP � o nome deste projeto
#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	// Vari�vel global da DLL
	extern DLL_IMP_API int nDLL;

	// Fun��es a serem exportadas/importadas
	DLL_IMP_API int UmaString(void);
>>>>>>> 5deeeb3e98c551fb5dc5a708ab3729962bddb419
}