#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define PORT 27015
#define DATA_BUFSIZE 8192

typedef struct _SOCKET_INFORMATION {
	BOOL RecvPosted;
	CHAR Buffer[DATA_BUFSIZE];
	WSABUF DataBuf;
	SOCKET Socket;
	DWORD BytesSEND;
	DWORD BytesRECV;
	struct _SOCKET_INFORMATION* Next;
	// Ajouter les informations sur le client ici
	struct _CLIENT_INFORMATION* ClientInfo;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

typedef struct _CLIENT_INFORMATION {
	SOCKET Socket;
	// Ajouter d'autres données relatives au client ici si nécessaire
} CLIENT_INFORMATION;

#define WM_SOCKET (WM_USER + 1)

CLIENT_INFORMATION* ClientList = NULL;

// Prototypes de fonctions
void AddClient(SOCKET clientSocket);
CLIENT_INFORMATION* FindClient(SOCKET clientSocket);

// Prototypes de fonctions existantes
void CreateSocketInformation(SOCKET s);
LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);
void FreeSocketInformation(SOCKET s);
HWND MakeWorkerWindow(void);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Variable globale
LPSOCKET_INFORMATION SocketInfoList;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	DWORD Ret;
	SOCKET Listen;
	SOCKADDR_IN InternetAddr;
	HWND Window;
	WSADATA wsaData;

	if ((Window = MakeWorkerWindow()) == NULL) {
		printf("MakeWorkerWindow() failed!\n");
		return 1;
	}
	else
		printf("MakeWorkerWindow() is OK!\n");

	if (WSAStartup((2, 2), &wsaData) != 0) {
		printf("WSAStartup() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("WSAStartup() is OK!\n");

	if ((Listen = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("socket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("socket() is pretty fine!\n");

	if (WSAAsyncSelect(Listen, Window, WM_SOCKET, FD_ACCEPT | FD_CLOSE) == 0)
		printf("WSAAsyncSelect() is OK lol!\n");
	else
		printf("WSAAsyncSelect() failed with error code %d\n", WSAGetLastError());

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(PORT);

	if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR) {
		printf("bind() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("bind() is OK maaa!\n");

	if (listen(Listen, 5)) {
		printf("listen() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("listen() is also OK! I am listening now...\n");

	while (Ret = GetMessage(&msg, NULL, 0, 0)) {
		if (Ret == -1) {
			printf("\nGetMessage() failed with error %d\n", GetLastError());
			return 1;
		}
		else
			printf("\nGetMessage() is pretty fine!\n");

		printf("Translating a message...\n");
		TranslateMessage(&msg);
		printf("Dispatching a message...\n");
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	SOCKET Accept;
	LPSOCKET_INFORMATION SocketInfo;
	DWORD RecvBytes;
	DWORD SendBytes;
	DWORD Flags;

	if (uMsg == WM_SOCKET) {
		if (WSAGETSELECTERROR(lParam)) {
			printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));
			FreeSocketInformation(wParam);
		}
		else {
			printf("Socket looks fine!\n");
			switch (WSAGETSELECTEVENT(lParam)) {
			case FD_ACCEPT:
				if ((Accept = accept(wParam, NULL, NULL)) == INVALID_SOCKET) {
					printf("accept() failed with error %d\n", WSAGetLastError());
					break;
				}
				else
					printf("accept() is OK!\n");
				CreateSocketInformation(Accept); // Crée la structure pour le socket/client
				AddClient(Accept); // Ajoute le client à la liste
				WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
				break;
			case FD_READ:
				// Gérer la lecture des données
				break;
			case FD_CLOSE:
				printf("Closing socket %d\n", wParam);
				FreeSocketInformation(wParam);
				break;
			}
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateSocketInformation(SOCKET s) {
	LPSOCKET_INFORMATION SI;
	if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL) {
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return;
	}
	else
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");

	// Prepare SocketInfo structure for use
	SI->Socket = s;
	SI->RecvPosted = FALSE;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;
	SI->Next = SocketInfoList;
	SocketInfoList = SI;
}

LPSOCKET_INFORMATION GetSocketInformation(SOCKET s) {
	SOCKET_INFORMATION* SI = SocketInfoList;
	while (SI) {
		if (SI->Socket == s)
			return SI;
		SI = SI->Next;
	}
	return NULL;
}

void FreeSocketInformation(SOCKET s) {
	SOCKET_INFORMATION* SI = SocketInfoList;
	SOCKET_INFORMATION* PrevSI = NULL;
	while (SI) {
		if (SI->Socket == s) {
			if (PrevSI)
				PrevSI->Next = SI->Next;
			else
				SocketInfoList = SI->Next;
			closesocket(SI->Socket);
			GlobalFree(SI);
			return;
		}
		PrevSI = SI;
		SI = SI->Next;
	}
}

void AddClient(SOCKET clientSocket) {
	CLIENT_INFORMATION* client = (CLIENT_INFORMATION*)malloc(sizeof(CLIENT_INFORMATION));
	if (client) {
		client->Socket = clientSocket;
		client->Next = ClientList;
		ClientList = client;
	}
	else {
		printf("Failed to allocate memory for client information\n");
	}
}

CLIENT_INFORMATION* FindClient(SOCKET clientSocket) {
	CLIENT_INFORMATION* current = ClientList;
	while (current) {
		if (current->Socket == clientSocket)
			return current;
		current = current->Next;
	}
	return NULL; // Client not found
}

HWND MakeWorkerWindow(void) {
	WNDCLASS wndclass;
	const char* ProviderClass = "AsyncSelect";
	HWND Window;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = (LPCWSTR)ProviderClass;
	if (RegisterClass(&wndclass) == 0) {
		printf("RegisterClass() failed with error %d\n", GetLastError());
		return NULL;
	}
	else
		printf("RegisterClass() is OK!\n");

	// Crée une fenêtre
	if ((Window = CreateWindow(
		(LPCWSTR)ProviderClass,
		L"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL)) == NULL) {
		printf("CreateWindow() failed with error %d\n", GetLastError());
		return NULL;
	}
	else
		printf("CreateWindow() is OK!\n");
	ShowWindow(Window, SW_SHOW);
	return Window;
}
