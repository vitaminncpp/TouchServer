#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <winsock.h>

#define PORT 9909



struct sockaddr_in srv;


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
   
    //Initialize WSA variables
    WSADATA ws;

    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        std::cout << "WSA Failed" << std::endl;
    }
    else {
        std::cout << "WSA succeed"<< std::endl;
    }

    //Initialize socket
    int nSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (nSock < 0) {
        std::cout << "The Socket did not open successfully" << std::endl;

    }
    else {
        std::cout << "The socket opend :" << nSock << std::endl;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = INADDR_ANY;
    memset(srv.sin_zero, 0, 8);


    int i = 0;

    while (i == 10) {
        Sleep(20);
        mouse_event(MOUSEEVENTF_MOVE ,10,10,0,0);
        i++;
    }
    return nSock;
}