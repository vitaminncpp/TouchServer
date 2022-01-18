#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <winsock.h>
#include <string>

#define PORT 9909



struct sockaddr_in srv;


int main(int argc,int argv){
   
    //Initialize WSA variables
    WSADATA ws;

    if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
        std::cout << "WSA Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "WSA succeed"<< std::endl;
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
    srv.sin_addr.s_addr = INADDR_ANY;
    memset(srv.sin_zero, 0, 8);

    int nRet = bind(nSock, (sockaddr*)&srv, sizeof(sockaddr));

    if (nRet < 0) {
        std::cout << "Failed to bind to local port" << std::endl;
        exit(EXIT_FAILURE);
    } else{
        std::cout << "Successfully bound to local port" << std::endl;
    }

    int i = 0;

    nRet = listen(nSock, 5);

    if (nRet < 0) {
        std::cout << "Failed to start listen to local port" << std::endl;
        exit(EXIT_FAILURE);

    }
    else {
        std::cout << "started listening to local port" << std::endl;
    }


    int nClient = 0;
    int addrlen = sizeof(srv);
    nClient = accept(nSock, (struct sockaddr*)&srv,&addrlen);

    char buff[1024]{ 0 };

    while (true) {
        /*/Sleep(20);
        mouse_event(MOUSEEVENTF_MOVE ,10,10,0,0);
        i++;*/
        nRet = recv(nClient, buff,1024, 0);
        std::cout <<"--->"<< buff << std::endl;
    }
    return nRet;
}