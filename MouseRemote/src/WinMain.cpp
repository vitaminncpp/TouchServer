#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <winsock.h>
#include <string>

#define PORT 5559

void extractXY(char[1024], int& , int&);


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

    char buff[1024]{ ' '};

	int X=0, Y = 0;
    while (true) {
       
        nRet = recv(nClient, buff,1024, 0);
		extractXY(buff,X,Y);
		std::cout << "--->"<<X << "    " << Y << std::endl;
        //std::cout <<"--->"<< buff << std::endl;
    }
    return nRet;
}

void extractXY(char buff[1024], int& X, int& Y) {
	int i = 0;
	char ch = buff[i];
	int state = 0;
	X = 0;
	Y = 0;


	while (ch) {

		switch (state)
		{
		case 0:
			if (ch == ' ') {
				i++;
			}
			else if (ch == '-') {
				state = 4;
				i++;
			}
			else {
				state = 1;
			}
			break;
		case 1:
			if (ch >= 48 && ch <= 57) {
				X *= 10;
				X += ch - 48;
				i++;
			}
			else if (ch == ' ') {
				
				state = 2;
			}

			break;
		case 2:
			if (ch == ' ') {
				i++;
			}
			else if (ch >= 48 && ch <= 57) {
				state = 3;
			}
			else if (ch == '-') {
				state = 5;
				i++;
			}
			break;
		case 3:
			if (ch >= 48 && ch <= 57) {
				Y *= 10;
				Y += ch - 48;
				i++;
			}
			else {
				state = 6;
			}
			break;
		case 4:
			if (ch >= 48 && ch <= 57) {
				X *= 10;
				X += ch - 48;
				i++;
			}
			else {
				X *= -1;
				state = 2;
			}
			break;
		case 5:
			if (ch <= 57 && ch >= 48) {
				Y *= 10;
				Y -= ch - 48;
				i++;
			}
			else {
				
				state = 6;
			}
			break;
		case 6:

			break;
		default:
			break;
		}
		ch = buff[i];
	}
}