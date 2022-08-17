#include "NetworkException.h"
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "Util.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <thread>
#include <cmath>


void GetDesktopResolution(int& horizontal, int& vertical);


#define ECHO_PORT 5560
#define SERVER_PORT 5559

void EchoThread();
void ServerThread();

void ServerThread() {
	UDPReceiver server(SERVER_PORT);

	INPUT in;
	char buff[1024];
	std::string json;
	std::unordered_map<std::string, std::string> map;

	int X = 0, Y = 0;
	int nRet = 0;
	while (true)
	{

#ifndef NDEBUG
		std::cout << "Waiting for message" << std::endl;
#endif // !NDEBUG


		nRet = server.Recv(buff, 1024);
		if (nRet < 0) {
			LOG_ERR;
			throw NetworkException("Failed Receving UDP packet", __FILE__, __LINE__);
			exit(-1);
		}
		json = std::string(buff, 1024);
		ReadJSON(json, map);

#ifndef NDEBUG
		std::cout << json << std::endl;
#endif // !NDEBUG

		in.type = std::stoi(map["type"]);
		if (in.type == INPUT_MOUSE) {
			in.mi.dx = std::stoi(map["dx"]);
			in.mi.dy = std::stoi(map["dy"]);
			in.mi.mouseData = std::stoi(map["mouseData"]);
			in.mi.time = std::stoi(map["time"]);
			in.mi.dwExtraInfo = std::stoi(map["dwExtraInfo"]);
			in.mi.dwFlags = std::stoi(map["dwFlags"]);
		}
		else if (in.type == INPUT_KEYBOARD) {
			in.ki.wVk = std::stoi(map["wVk"]);
			in.ki.wScan = std::stoi(map["wScan"]);
			in.ki.dwFlags = std::stoi(map["dwFlags"]);
			in.ki.time = std::stoi(map["time"]);
			in.ki.dwExtraInfo = std::stoi(map["dwExtraInfo"]);
		}
		else if (in.type == INPUT_HARDWARE) {
			//For Future
		}
		else {
			LOG_ERR;
		}
		SendInput(1, &in, sizeof(INPUT));

	}
}

void EchoThread() {
	struct IPv4 ip;
	if (!GetMyIP(ip)) {
		//LOG_ERR;
		throw NetworkException("Failed to get Local IP", __FILE__, __LINE__);
	}

	IPv4 broadCast = ip;
	broadCast.s_b4 = 255;

	UDPSender echo(broadCast, ECHO_PORT);

	while (true)
	{
		echo.Send((const char*)&ip, 4);
		Sleep(2000);
		std::cout << ip.s_b1 << " " << ip.s_b2 << " " << ip.s_b3 << " " << ip.s_b4 << std::endl;
	}

}

#ifdef NDEBUG
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif // NDEBUG

{
	std::thread echo(EchoThread);
	std::thread server(ServerThread);

	server.join();
	echo.join();
	return 0;
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}