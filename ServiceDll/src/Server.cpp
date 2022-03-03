#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <thread>
#include "NetworkException.h"
#include "Network.h"
#include "UDPSocket.h"


#define ECHO_PORT 5560
#define SERVER_PORT 5559

void EchoThread();
void ServerThread();
void extractXY(char[50], int&, int&, char&);


void ServerThread() {
	UDPSocket server(SERVER_PORT);
	char msg = 0;
	char buff[50]{ ' ', };

	int X = 0, Y = 0;
	int nRet = 0;
	while (true)
	{
		nRet = server.Recv(buff, 50);
		if (nRet < 0) {
			LOG_ERR;
			throw NetworkException("Failed Receving UDP packet", __FILE__, __LINE__);
			exit(-1);
		}

		extractXY(buff, X, Y, msg);


		switch (msg) {
		case 'L':
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			break;
		case 'l':
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			break;
		case 'R':
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			break;
		case 'r':
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			break;
		case 'W':

			mouse_event(MOUSEEVENTF_WHEEL, 0, 0, X, 0);
			break;
		case 'M':

			mouse_event(MOUSEEVENTF_MOVE, X, Y, 0, 0);
			break;

		case 'C':
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(1);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			break;
		case 'D':
			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			Sleep(1);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			break;
		default:
			LOG_ERR;
			throw NetworkException("Unknown code", __FILE__, __LINE__);
			break;
		}

	}
}



void extractXY(char buff[50], int& X, int& Y, char& msg) {
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
			else {
				return;
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
			else {
				return;
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
			while (true) {
				ch = buff[i++];
				if (ch != ' ') {
					msg = ch;
					return;
				}
			}
			break;
		default:
			break;
		}
		ch = buff[i];
	}
}



void EchoThread() {
	struct IPv4 ip;
	if (!GetMyIP(ip)) {
		LOG_ERR;
		throw NetworkException("Failed to get Local IP", __FILE__, __LINE__);
	}

	IPv4 broadCast = ip;
	broadCast.s_b4 = 255;

	UDPSocket echo(broadCast, ECHO_PORT);
	echo.SetSourcePort(5560);

	while (true)
	{
		echo.Send((const char*)&ip, 4);
		Sleep(2000);
	}

}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	std::thread echo(EchoThread);
	std::thread server(ServerThread);

	server.join();
	echo.join();
	return 0;
}