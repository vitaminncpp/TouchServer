#include <iostream>
#include <string>
#include <mutex>
#include <Windows.h>
#include <WinUser.h>
#include "NetworkException.h"
#include "Network.h"
#include "UDPSocket.h"
#define DLL_EXPORT __declspec(dllexport)



bool running = false;

void EchoThread();
void ServerThread();
void extractXY(char[50], int&, int&, char&);

std::mutex mu;




void EchoThread() {
	struct IPv4 ip;
	if (!getMyIP(ip)) {
		LOG_ERR;
		throw NetworkException("Failed to get Local IP", __FILE__, __LINE__);
	}

	struct IPv4 broadcastIP = ip;
	broadcastIP.s_b4 = 255; //for broadcast shit

	UDPSocket echo(broadcastIP, 5560);
	echo.SetSourcePort(5560);
	while (true)
	{

		mu.lock();
		if (running) {
			mu.unlock();
			break;
		}
		mu.unlock();

		echo.Send((const char*)&ip, 4);
		Sleep(3000);
	}
}

void ServerThread() {
	UDPSocket server(5559);
	char msg = 0;
	char buff[50]{ ' ' };

	int X = 0, Y = 0;
	int nRet = 0;
	while (true)
	{
		mu.lock();
		if (running) {
			mu.unlock();
			break;
		}
		mu.unlock();


		nRet = server.Recv(buff,50);
		if (nRet <= 0) {
			LOG_ERR;
			throw NetworkException("Failed Receving UDP packet",__FILE__,__LINE__);
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
		default:
			LOG_ERR;
			throw NetworkException("Unknown code", __FILE__, __LINE__);
			break;
		}
	
	}
}






extern "C" {


	DLL_EXPORT std::string Start() {
		mu.lock();
		if (!running) {
			mu.unlock();
			try {
				std::thread echo(EchoThread);
				std::thread server(ServerThread);

				echo.detach();
				echo.detach();
				running = true;
				mu.unlock();
				return std::string("Server Started Successfully");
				
			}
			catch (NetworkException ex) {
				mu.unlock();
				std::cout << ex.what() << std::endl;
				return std::string("Server Failed to start with an exception:").append(ex.what());
			}
		}
		else {
			mu.unlock();
			std::cout << "Server is already Started" << std::endl;
			return std::string("Server is already Started");
		}
	}

	DLL_EXPORT std::string Stop() {
		mu.lock();
		if (running) {
			try {
				running = false;
				mu.unlock();
			}
			catch (NetworkException ex) {
				mu.unlock();
				std::cout << ex.what() << std::endl;
				return std::string("Server Failed to stop with an Exception:").append(ex.what());
			}
		}
		else {
			mu.unlock();
			std::cout << "Server is not Started" << std::endl;
			return std::string("Server is not started");
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