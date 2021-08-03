#include "windows.h" // Les programmes windows bureau en c++ necessite toujours d' inclure ces deux fonctions
#include "stdlib.h"	// Les programmes windows bureau en c++ necessite toujours d' inclure ces deux fonctions
#include "string.h" // Pour utiliser des variables tchar/string
#include "tchar.h" // Pour utiliser des variables tchar
#include <chrono> // Pour utiliser chrono_literals
#include <iostream> // Pour enregistrer et lire un fichier
#include <fstream> // Pour enregistrer et lire un fichier
#include <sstream> ///Pour faire des chaines de fichiers
using namespace std::chrono_literals;

#define FILE_MENU_EXIT 1
#define FILE_MENU_SUB 2
#define FILE_MENU_SUB2 3
#define FILE_APROPOS 4

// Code principal
int notewrite()
{
	for (unsigned int i = 0; i < 999; i++)
	{
		std::ostringstream flux;
		flux << "note_" << i << ".txt";
		std::ofstream ofs(flux.str().c_str());
		ofs << i;
		return 0;
	}
}
int noteopen()
{
	std::ifstream flux ("note_0.txt");
	if (flux) ("note_0.txt");
	{
		notewrite();
		flux.close();
		return 0;
	}
}
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
				_T("Impossible d' enregistrer la classe !"),	// On utilise _T car on utilise les variables tchar
				_T("Windows Desktop"),
				NULL);
			return 1;
		}

		hInst = hInstance;		// On dit que la variable hInst est egal a hInstance (argument de creation d' instance)

		HWND hWnd = CreateWindow(	// On cree la fenetre principale du programme
			szWindowClass,	// On inclus la classe de fenetre
			szTitle,	// Le nom du projet
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			800, 600,	// Sa taillle 500 sur l' axe x horizontale et 100 sur l' axe y vertical
			NULL,
			NULL,
			hInstance,	// on l' instance
			NULL
		);
		if (!hWnd)
		{
			MessageBox(NULL,
				_T("Impossible d' initialiser la fenetre !"),
				_T("Windows Desktop"),
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
			TCHAR greeting[] = _T("");	// On creer une variable tchar qui s' apelle greeting et le message afficher dans la fenetre

			switch (message)
			{
			case WM_CREATE:
			{
				HMENU MenuBar = CreateMenu();
				HMENU hFiles = CreateMenu();
				HMENU hSubMenu = CreateMenu();
				HMENU hSubMenu2 = CreateMenu();

				AppendMenu(hSubMenu, MF_STRING, FILE_MENU_SUB, "Note");
				AppendMenu(hSubMenu2, MF_STRING, FILE_MENU_SUB2, "Note");
				AppendMenu(MenuBar, MF_POPUP, (UINT_PTR)hFiles, "Fichiers");
				AppendMenu(MenuBar, MF_POPUP, FILE_APROPOS, "A propos");
				AppendMenu(hFiles, MF_POPUP, (UINT_PTR)hSubMenu, "Nouveau fichier");
				AppendMenu(hFiles, MF_POPUP, (UINT_PTR)hSubMenu2, "Ouvrir un fichier");
				AppendMenu(hFiles, MF_SEPARATOR, NULL, NULL);
				AppendMenu(hFiles, MF_STRING, FILE_MENU_EXIT, "Quitter");
				SetMenu(hWnd, MenuBar);
				break;
			}
			case WM_COMMAND:
				switch (wParam)
				{
				case FILE_MENU_EXIT:
					DestroyWindow(hWnd);
					break;
				case FILE_MENU_SUB:
					MessageBeep(MB_ICONINFORMATION);
					notewrite();
					MessageBox(hWnd, "Un fichier de note a eter creer .", "Info", MB_ICONINFORMATION);
					break;
				case FILE_MENU_SUB2:
					MessageBeep(MB_ICONINFORMATION);
					noteopen();
					MessageBox(hWnd, "Pas de fichier de note a ouvrir .", "Erreur", MB_ICONINFORMATION);
					break;
				case FILE_APROPOS:
					MessageBox(hWnd, "SkyDev Version 1.11 Copyright 2021", "A propos", MB_ICONINFORMATION);
					break;
				}
			case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);	// On paint le message en haut a gauche de la fenetre
				TextOut(hdc,
					50, 50,	// Emplacement en x horizontale, en y vertical
					greeting, _tcslen(greeting));
				EndPaint(hWnd, &ps);
				break;
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}
			return 0;
		}// Fin de la fonction WndProc