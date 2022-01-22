#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <winsock.h>

#define PORT 5559



struct sockaddr_in srv;


int main(int argc, char** argv)
{

    //Initialize WSA variables
    WSADATA ws;

    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        std::cout << "WSA Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "WSA succeed" << std::endl;
    }

    //Initialize socket
    int nSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (nSock < 0) {
        std::cout << "The Socket did not open successfully" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "The socket opend :" << nSock << std::endl;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = inet_addr(argv[1]);
    memset(srv.sin_zero, 0, 8);

    int nRet = connect(nSock, (sockaddr*)&srv, sizeof(sockaddr));

    if (nRet < 0) {
        std::cout << "Failed to connect to remote server" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "Successfully connected to  remote server" << std::endl;
    }


    char buff[1024] { 0, };
    while (true) {
        std::cout << "--->";
        std::cin.getline(buff, 1024);
        send(nSock, buff,1024,0);
    }

    return nRet;
}