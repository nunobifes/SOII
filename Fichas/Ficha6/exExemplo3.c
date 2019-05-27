// Teclas

#include <windows.h>
#include <tchar.h>
#include <winuser.h>
#include "resource.h"


int maxX = 0, maxY = 0, xPos = 0, yPos = 0;
TCHAR c = '?';
void WINAPI invRect(LPVOID param);

LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);
// Nome da classe da janela (para programas de uma só janela, normalmente este nome é
// igual ao do próprio programa) "szprogName" é usado mais abaixo na definição das
// propriedades do objecto janela
TCHAR szProgName[] = TEXT("Base");
// ============================================================================
// FUNÇÃO DE INÍCIO DO PROGRAMA: WinMain()
// ============================================================================
// Em Windows, o programa começa sempre a sua execução na função WinMain()que desempenha
// o papel da função main() do C em modo consola WINAPI indica o "tipo da função" (WINAPI
// para todas as declaradas nos headers do Windows e CALLBACK para as funções de
// processamento da janela)
// Parâmetros:
// hInst: Gerado pelo Windows, é o handle (número) da instância deste programa
// hPrevInst: Gerado pelo Windows, é sempre NULL para o NT (era usado no Windows 3.1)
// lpCmdLine: Gerado pelo Windows, é um ponteiro para uma string terminada por 0
// destinada a conter parâmetros para o programa
// nCmdShow: Parâmetro que especifica o modo de exibição da janela (usado em
// ShowWindow()

HWND global_handle;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd; // hWnd é o handler da janela, gerado mais abaixo por CreateWindow()
	MSG lpMsg; // MSG é uma estrutura definida no Windows para as mensagens
	WNDCLASSEX wcApp; // WNDCLASSEX é uma estrutura cujos membros servem para
					  // definir as características da classe da janela
					  // ============================================================================
					  // 1. Definição das características da janela "wcApp"
					  // (Valores dos elementos da estrutura "wcApp" do tipo WNDCLASSEX)
					  // ============================================================================
	wcApp.cbSize = sizeof(WNDCLASSEX); // Tamanho da estrutura WNDCLASSEX
	wcApp.hInstance = hInst; // Instância da janela actualmente exibida
							 // ("hInst" é parâmetro de WinMain e vem
							 // inicializada daí)
	wcApp.lpszClassName = szProgName; // Nome da janela (neste caso = nome do programa)
	wcApp.lpfnWndProc = TrataEventos; // Endereço da função de processamento da janela
									  // ("TrataEventos" foi declarada no início e
									  // encontra-se mais abaixo)
	wcApp.style = CS_HREDRAW | CS_VREDRAW;// Estilo da janela: Fazer o redraw se for
										  // modificada horizontal ou verticalmente
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);// "hIcon" = handler do ícon normal
												  //"NULL" = Icon definido no Windows
												  // "IDI_AP..." Ícone "aplicação"
	wcApp.hIconSm = LoadIcon(NULL, IDI_ERROR);// "hIconSm" = handler do ícon pequeno
													//"NULL" = Icon definido no Windows
													// "IDI_INF..." Ícon de informação
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW); // "hCursor" = handler do cursor (rato)
												 // "NULL" = Forma definida no Windows
												 // "IDC_ARROW" Aspecto "seta"
	wcApp.lpszMenuName = NULL; // Classe do menu que a janela pode ter
							   // (NULL = não tem menu)
	wcApp.cbClsExtra = 0; // Livre, para uso particular
	wcApp.cbWndExtra = 0; // Livre, para uso particular
	wcApp.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	// "hbrBackground" = handler para "brush" de pintura do fundo da janela. Devolvido por
	// "GetStockObject".Neste caso o fundo será branco
	// ============================================================================
	// 2. Registar a classe "wcApp" no Windows
	// ============================================================================
	if (!RegisterClassEx(&wcApp))
		return(0);
	// ============================================================================
	// 3. Criar a janela
	// ============================================================================
	hWnd = CreateWindow(
		szProgName, // Nome da janela (programa) definido acima
		TEXT("SO2 - Ficha 6 - Exericio 1"),// Texto que figura na barra do título
		WS_OVERLAPPEDWINDOW, // Estilo da janela (WS_OVERLAPPED= normal)
		CW_USEDEFAULT, // Posição x pixels (default=à direita da última)
		CW_USEDEFAULT, // Posição y pixels (default=abaixo da última)
		CW_USEDEFAULT, // Largura da janela (em pixels)
		CW_USEDEFAULT, // Altura da janela (em pixels)
		(HWND)HWND_DESKTOP, // handle da janela pai (se se criar uma a partir de
							// outra) ou HWND_DESKTOP se a janela for a primeira,
							// criada a partir do "desktop"
		(HMENU)NULL, // handle do menu da janela (se tiver menu)
		(HINSTANCE)hInst, // handle da instância do programa actual ("hInst" é
						  // passado num dos parâmetros de WinMain()
		0); // Não há parâmetros adicionais para a janela
			// ============================================================================
			// 4. Mostrar a janela
			// ============================================================================


	ShowWindow(hWnd, nCmdShow); // "hWnd"= handler da janela, devolvido por
								// "CreateWindow"; "nCmdShow"= modo de exibição (p.e.
								// normal/modal); é passado como parâmetro de WinMain()
	UpdateWindow(hWnd); // Refrescar a janela (Windows envia à janela uma

	global_handle = hWnd;



	// mensagem para pintar, mostrar dados, (refrescar)…
	// ============================================================================
	// 5. Loop de Mensagens
	// ============================================================================
	// O Windows envia mensagens às janelas (programas). Estas mensagens ficam numa fila de
	// espera até que GetMessage(...) possa ler "a mensagem seguinte"
	// Parâmetros de "getMessage":
	// 1)"&lpMsg"=Endereço de uma estrutura do tipo MSG ("MSG lpMsg" ja foi declarada no
	// início de WinMain()):
	// HWND hwnd handler da janela a que se destina a mensagem
	// UINT message Identificador da mensagem
	// WPARAM wParam Parâmetro, p.e. código da tecla premida
	// LPARAM lParam Parâmetro, p.e. se ALT também estava premida
	// DWORD time Hora a que a mensagem foi enviada pelo Windows
	// POINT pt Localização do mouse (x, y)
	// 2)handle da window para a qual se pretendem receber mensagens (=NULL se se pretendem
	// receber as mensagens para todas as janelas pertencentes à thread actual)
	// 3)Código limite inferior das mensagens que se pretendem receber
	// 4)Código limite superior das mensagens que se pretendem receber
	// NOTA: GetMessage() devolve 0 quando for recebida a mensagem de fecho da janela,
	// terminando então o loop de recepção de mensagens, e o programa
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg); // Pré-processamento da mensagem (p.e. obter código
								  // ASCII da tecla premida)
		DispatchMessage(&lpMsg); // Enviar a mensagem traduzida de volta ao Windows, que
								 // aguarda até que a possa reenviar à função de
								 // tratamento da janela, CALLBACK TrataEventos (abaixo)
	}
	// ============================================================================
	// 6. Fim do programa
	// ============================================================================

	return((int)lpMsg.wParam); // Retorna sempre o parâmetro wParam da estrutura lpMsg
}
// ============================================================================
// FUNÇÃO DE PROCESSAMENTO DA JANELA
// Esta função pode ter um nome qualquer: Apenas é necesário que na inicialização da
// estrutura "wcApp", feita no início de WinMain(), se identifique essa função. Neste
// caso "wcApp.lpfnWndProc = WndProc"
//
// WndProc recebe as mensagens enviadas pelo Windows (depois de lidas e pré-processadas
// no loop "while" da função WinMain()
//
// Parâmetros:
// hWnd O handler da janela, obtido no CreateWindow()
// messg Ponteiro para a estrutura mensagem (ver estrutura em 5. Loop...
// wParam O parâmetro wParam da estrutura messg (a mensagem)
// lParam O parâmetro lParam desta mesma estrutura
//
// NOTA:Estes parâmetros estão aqui acessíveis o que simplifica o acesso aos seus valores
//
// A função EndProc é sempre do tipo "switch..." com "cases" que descriminam a mensagem
// recebida e a tratar. Estas mensagens são identificadas por constantes (p.e.
// WM_DESTROY, WM_CHAR, WM_KEYDOWN, WM_PAINT...) definidas em windows.h
// ============================================================================
int nClicks = 0;

HDC hdc, memDC, tempDC;
RECT rect;
PAINTSTRUCT ps;
HBRUSH hBrush = NULL;
BITMAP bmp;
HBITMAP hBit, hBmp;
int x = 20, y = 20;

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {


	switch (messg) {

	case WM_KEYDOWN:

		switch((WPARAM)wParam)
		{
		case VK_UP:
			y = y > 0 ? y - 10 : 0;
			break;
		case VK_DOWN:
			y = y < rect.bottom - bmp.bmHeight ? y + 10 : rect.bottom - bmp.bmHeight;
			break;
		case VK_RIGHT:
			x = x < rect.right - bmp.bmWidth ? x + 10 : rect.right - bmp.bmWidth;
			break;
		case VK_LEFT:
			x = x > 0 ? x - 10 : 0;

			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);

	case WM_ERASEBKGND:
		return(1);
		break;
	case WM_CREATE:
		maxX = GetSystemMetrics(SM_CXSCREEN);
		maxY = GetSystemMetrics(SM_CYSCREEN);

		hdc = GetDC(hWnd);
		//######################################################
		// Criação da Replica
		memDC = CreateCompatibleDC(hdc);
		hBit = CreateCompatibleBitmap(hdc, maxX, maxY);
		SelectObject(memDC, hBit);
		DeleteObject(hBit);
		//######################################################
		hBrush = CreateSolidBrush(RGB(70, 150, 70));

		SelectObject(memDC, hBrush);
		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
		ReleaseDC(hWnd, hdc);

		//hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
		hBmp = (HBITMAP)LoadImage(NULL, _T("logo.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		GetObject(hBmp, sizeof(bmp), &bmp);

		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, _T("Pretende mesmo sair?"), _T("sair"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY: // Destruir a janela e terminar o programa
					 // "PostQuitMessage(Exit Status)"
		DeleteDC(memDC);
		DeleteObject(hBrush);
		global_handle = NULL;
		PostQuitMessage(0);
		break;
	case WM_PAINT:

		tempDC = CreateCompatibleDC(memDC);
		SelectObject(tempDC, hBmp);
		PatBlt(memDC, 0, 0, maxX, maxY, PATCOPY);
		BitBlt(memDC, x, y, bmp.bmWidth, bmp.bmHeight, tempDC, 0, 0, SRCCOPY);
		DeleteObject(tempDC);

		GetClientRect(hWnd, &rect);
		SetTextColor(memDC, RGB(255, 255, 255));
		SetBkColor(memDC, TRANSPARENT);
		rect.left = xPos;
		rect.top = yPos;
		DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);

		hdc = BeginPaint(hWnd, &ps);

		BitBlt(hdc, 0, 0, maxX, maxY, memDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar")
		// não é efectuado nenhum processamento, apenas se segue o "default" do Windows
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return(0);
}

