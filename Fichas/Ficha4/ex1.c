#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <stdio.h>
int _tmain(int argc, TCHAR * argv[])
{
	HANDLE objMap1, objMap2, f1, f2;
	LARGE_INTEGER tam;
	char * map1, * map2, * posActual1, * posActual2;
	
	if (argc != 3)
	{
		_tprintf(TEXT("[Erro]Sintaxe: %s ficheiro_origem ficheiro_destino\n"), argv[0]);return -1;
	}
	
	//Tentar abrir/criar os ficheiros passados pela linha de comandos
	f1=CreateFile(argv[1],GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
	f2=CreateFile(argv[2],GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
	
	if (f1== INVALID_HANDLE_VALUE || f2 == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("[Erro] Abrir ficheiros (%d)\n"), GetLastError());return -1;
	}
	
	//Saber o tamanho do ficheiro 1 em bytes
	GetFileSizeEx(f1, &tam);
	
	//Criar um objecto para o mapeamento para cada ficheiro aberto 
	objMap1=CreateFileMapping(f1, NULL, PAGE_READONLY, 0, 0, NULL);
	objMap2=CreateFileMapping(f2, NULL, PAGE_READWRITE,tam.HighPart,tam.LowPart,NULL);
	
	if (objMap1 == NULL || objMap2 == NULL)
	{
		_tprintf(TEXT("[Erro]Criar objectos mapeamentos(%d)\n"), GetLastError());return -1;
	}

	//Mapear efectivamente o ficheiro em memória
	map1 = (char*)MapViewOfFile(objMap1, FILE_MAP_READ, 0, 0, 0);
	map2 = (char*)MapViewOfFile(objMap2, FILE_MAP_WRITE, 0, 0, tam.QuadPart);
	
	if (map1 == NULL || map2 == NULL)
	{
		_tprintf(TEXT("[Erro]Mapear para memória(%d)\n"), GetLastError()); return -1;
	}
	
	posActual1 = map1;
	posActual2 = map2;//Percorrer o primeiro mapeamento e copiar para o segundo mapeamento
	
	while (posActual1 <map1 + tam.QuadPart)
	{
		*posActual2 = *posActual1;posActual1++;posActual2++;
	}

	UnmapViewOfFile(map1);
	UnmapViewOfFile(map2);
	CloseHandle(objMap1);
	CloseHandle(objMap2);
	CloseHandle(f1);
	CloseHandle(f2);
	return 0;
}
