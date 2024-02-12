#include "OnlineManager.h"



OnlineManager::OnlineManager()
{}



//JSON Manager
json OnlineManager::getData(std::string data)
{
	return json::parse(data);
}

json OnlineManager::getData(std::ifstream file)
{
	return json::parse(file);
}

void OnlineManager::writeJSON(std::string filename, json data)
{
	std::ofstream o(filename + ".json");
	o << std::setw(4) << data << std::endl;
}

void OnlineManager::writeJSON(std::string filename, std::string data)
{
	std::ofstream o(filename + ".json");
	o << std::setw(4) << getData(data) << std::endl;
}

void OnlineManager::sendMessage(const char* message) {

    int iResult = send(ConnectSocket, message, (int)strlen(message), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1); // Vous pouvez modifier la gestion des erreurs selon vos besoins
    }
    printf("Message Sent: %s\n", message);
}



// typedef definition

typedef struct _SOCKET_INFORMATION {

    BOOL RecvPosted;

    CHAR Buffer[DATA_BUFSIZE];

    WSABUF DataBuf;

    SOCKET Socket;

    DWORD BytesSEND;

    DWORD BytesRECV;

    struct _SOCKET_INFORMATION* Next;

} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;



#define WM_SOCKET (WM_USER + 1)



// Prototypes

void CreateSocketInformation(SOCKET s);

LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);

void FreeSocketInformation(SOCKET s);

HWND MakeWorkerWindow(void);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



// Global var

LPSOCKET_INFORMATION SocketInfoList;

bool OnlineManager::connect()
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;

    MSG msg;

    DWORD Ret;

    SOCKET Listen;

    SOCKADDR_IN InternetAddr;

    HWND Window;

    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    if ((Window = MakeWorkerWindow()) == NULL)

    {

        printf("MakeWorkerWindow() failed!\n");

        return 1;

    }

    else

        printf("MakeWorkerWindow() is OK!\n");

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(IP_ADDRESS, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        WSAAsyncSelect(ConnectSocket, Window, WM_SOCKET, FD_READ | FD_CLOSE);
        break;

        freeaddrinfo(result);

        if (ConnectSocket == INVALID_SOCKET) {
            printf("Unable to connect to server!\n");
            WSACleanup();
            return 1;
        }

        printf("Appuyez sur la touche 'Q' pour quitter...\n");

        while (true);

        closesocket(ConnectSocket);
        WSACleanup();


        // Translate and dispatch window messages for the application thread

        while (Ret = GetMessage(&msg, NULL, 0, 0))

        {

            if (Ret == -1)

            {

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

        return true;
}


sf::RenderWindow OnlineManager::createWindow()
{
    //Create  window

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)

    {

        SOCKET Accept;

        LPSOCKET_INFORMATION SocketInfo;

        DWORD RecvBytes;

        DWORD SendBytes;

        DWORD Flags;



        if (uMsg == WM_SOCKET)

        {

            if (WSAGETSELECTERROR(lParam))

            {

                printf("Socket failed with error %d\n", WSAGETSELECTERROR(lParam));

                FreeSocketInformation(wParam);

            }

            else

            {

                printf("Socket looks fine!\n");

                switch (WSAGETSELECTEVENT(lParam))

                {

                case FD_READ:

                    SocketInfo = GetSocketInformation(wParam);

                    // Read data only if the receive buffer is empty

                    if (SocketInfo->BytesRECV != 0)

                    {
                        SocketInfo->RecvPosted = TRUE;


                        return 0;

                    }

                    else

                    {

                        SocketInfo->DataBuf.buf = SocketInfo->Buffer;

                        SocketInfo->DataBuf.len = DATA_BUFSIZE;




                        Flags = 0;

                        if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes,

                            &Flags, NULL, NULL) == SOCKET_ERROR)

                        {

                            if (WSAGetLastError() != WSAEWOULDBLOCK)

                            {

                                printf("WSARecv() failed with error %d\n", WSAGetLastError());

                                FreeSocketInformation(wParam);

                                return 0;

                            }

                        }

                        else // No error so update the byte count

                        {
                            SocketInfo->DataBuf.buf[RecvBytes] = 0;
                            //printf("WSARecv() is OK!\n");
                            //OutputDebugStringA(SocketInfo->DataBuf.buf);
                            printf(SocketInfo->DataBuf.buf);


                            OutputDebugStringA("\n");

                            //SocketInfo->BytesRECV = RecvBytes;


                        }

                    }

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

    void CreateSocketInformation(SOCKET s)

    {

        LPSOCKET_INFORMATION SI;



        if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)

        {

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



    LPSOCKET_INFORMATION GetSocketInformation(SOCKET s)

    {

        SOCKET_INFORMATION* SI = SocketInfoList;



        while (SI)

        {

            if (SI->Socket == s)

                return SI;



            SI = SI->Next;

        }



        return NULL;

    }



    void FreeSocketInformation(SOCKET s)

    {

        SOCKET_INFORMATION* SI = SocketInfoList;

        SOCKET_INFORMATION* PrevSI = NULL;



        while (SI)

        {

            if (SI->Socket == s)

            {

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



    HWND MakeWorkerWindow(void)

    {

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



        if (RegisterClass(&wndclass) == 0)

        {

            printf("RegisterClass() failed with error %d\n", GetLastError());

            return NULL;

        }

        else

            printf("RegisterClass() is OK!\n");



        // Create a window

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

            NULL)) == NULL)

        {

            printf("CreateWindow() failed with error %d\n", GetLastError());

            return NULL;

        }

        else {

            printf("CreateWindow() is OK!\n");
            //ShowWindow(Window, SW_SHOW);
            
        }
        return Window;
}


