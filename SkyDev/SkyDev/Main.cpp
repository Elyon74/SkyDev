#include <windows.h> // Les programmes windows bureau en c++ necessite toujours d' inclure ces deux fonctions
#include <stdlib.h>	// Les programmes windows bureau en c++ necessite toujours d' inclure ces deux fonctions
#include <string.h>	// Pour utiliser des variables tchar/string
#include <tchar.h> // Pour utiliser des variables tchar

// Le nom de la classe de fenetre principale
static TCHAR szWindowClass[] = _T("DesktopApp");

// Le nom de l' application 
static TCHAR szTitle[] = _T("SkyDev");
HINSTANCE hInst;	// On cree une variable d' instance

// WndProc pour la creation d' une fenetre
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Chaque programme C/C++ window non console necessite obligatoirement de creer une fonction WinMain pour la creation du projet
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
// Debut de la fonction Winmain
{
		WNDCLASSEX wcex;	// WNDCLASSEX Contient les informations de la fenetre principale
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

		if (!RegisterClassEx(&wcex))	// Detection de la fenetre
		{
			MessageBox(NULL,
				_T("Call to RegisterClassEx failed!"),	// On utilise _T car on utilise les variables tchar
				_T("Windows Desktop Guided Tour"),
				NULL);

			return 1;
		}

		hInst = hInstance;		// On dit que la variable hInst est egal a hInstance (argument de creation d' instance)

		HWND hWnd = CreateWindow(	// On cree la fenetre principale du programme
			szWindowClass,	// On inclus la classe de fenetre
			szTitle,	// Le nom du projet
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			500, 100,	// Sa taillle 500 sur l' axe x horizontale et 100 sur l' axe y vertical
			NULL,
			NULL,
			hInstance,	// on l' instance
			NULL
		);
		if (!hWnd)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Windows Desktop Guided Tour"),
				NULL);

			return 1;
		}
		ShowWindow(hWnd,	// On affiche la fenetre apres l' avoir instancer
			nCmdShow);
		UpdateWindow(hWnd);	// On recupere les parametres de WinMain
		MSG msg;	// On récupere le message principal
		// On Gere les messages
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return (int)msg.wParam;
}		// Fin de la fonction WinMain

		// On gere maintenant le contenue de notre fenetre principal grace a WndProc
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
			// Debut fonction WndProc
		{
			PAINTSTRUCT ps;	// On paint un contenue ici message
			HDC hdc;	// On creer une variable HDC positionement du message
			TCHAR greeting[] = _T("Bienvenue !");	// On creer une variable tchar qui s' apelle greeting et le message afficher dans la fenetre

			switch (message)
			{
			case WM_PAINT:
				hdc = BeginPaint(hWnd, &ps);	// On paint le message en haut a gauche de la fenetre
				TextOut(hdc,
					5, 5,
					greeting, _tcslen(greeting));
				EndPaint(hWnd, &ps);
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}
			return 0;
		}	// Fin de la fonction WndProc