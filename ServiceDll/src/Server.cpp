#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <thread>
#include "NetworkException.h"
#include "Network.h"
#include "UDPSocket.h"




struct SendInput {
	UINT msg;
	LPARAM lParam;
	WPARAM wParam;
};

#define ECHO_PORT 5560
#define SERVER_PORT 5559

void EchoThread();
void ServerThread();
void extractXY(char[50], int&, int&, char&);


void ServerThread() {
	UDPSocket server(SERVER_PORT);
	struct SendInput input;

	INPUT in;

	int X = 0, Y = 0;
	int nRet = 0;
	while (true)
	{

#ifndef NDEBUG
		std::cout << "Waiting for message"<< std::endl;
#endif // !NDEBUG


		nRet = server.Recv(reinterpret_cast<char*>(&input), sizeof(input));
		if (nRet < 0) {
			LOG_ERR;
			throw NetworkException("Failed Receving UDP packet", __FILE__, __LINE__);
			exit(-1);
		}


#ifndef NDEBUG
		std::cout << input.msg << "\t" << input.lParam << "\t" << input.wParam << std::endl;
#endif // !NDEBUG

		in = { 0 ,};
		POINTS pt;
		int delta = 0;
		
		switch (input.msg) {

		case WM_CLOSE:

			break;
		case WM_KILLFOCUS:

			break;
		case WM_ACTIVATE:
			break;

			/*********** KEYBOARD MESSAGES ***********/


		case WM_KEYDOWN:

		case WM_SYSKEYDOWN:
			in.type = INPUT_KEYBOARD;
			in.ki.time = 0;
			in.ki.dwFlags = 0;
			in.ki.wVk = static_cast<unsigned char>(input.wParam);
			break;

		case WM_KEYUP:
		case WM_SYSKEYUP:
			in.type = INPUT_KEYBOARD;
			in.ki.time = 0;
			in.ki.dwFlags = KEYEVENTF_KEYUP;
			in.ki.wVk = static_cast<unsigned char>(input.wParam); 
			break;

		case WM_CHAR:

			break;


			/*********** END KEYBOARD MESSAGES ***********/

			/************* MOUSE MESSAGES ****************/

		case WM_MOUSEMOVE:

			pt = MAKEPOINTS(input.lParam);
			SetCursorPos(pt.x, pt.y);

			break;


		case WM_LBUTTONDOWN:

			pt = MAKEPOINTS(input.lParam);
			in.type = INPUT_MOUSE;
			in.mi.dx = pt.x;
			in.mi.dy = pt.y;
			in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			in.mi.time = 0;
			in.mi.mouseData = 0;

			break;

		case WM_RBUTTONDOWN:
		
			pt = MAKEPOINTS(input.lParam);
			in.type = INPUT_MOUSE;
			in.mi.dx = pt.x;
			in.mi.dy = pt.y;
			in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			in.mi.time = 0;
			in.mi.mouseData = 0;

			break;
		
		case WM_LBUTTONUP:
		
			 pt = MAKEPOINTS(input.lParam);
			in.type = INPUT_MOUSE;
			in.mi.dx = pt.x;
			in.mi.dy = pt.y;
			in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			in.mi.time = 0;
			in.mi.mouseData = 0;

			break;
		
			


		case WM_RBUTTONUP:
			pt = MAKEPOINTS(input.lParam);
			in.type = INPUT_MOUSE;
			in.mi.dx = pt.x;
			in.mi.dy = pt.y;
			in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			in.mi.time = 0;
			in.mi.mouseData = 0;

			break;
		case WM_MOUSEWHEEL:
		

			 pt = MAKEPOINTS(input.lParam);
			delta = GET_WHEEL_DELTA_WPARAM(input.wParam);
			in.type = INPUT_MOUSE;
			in.mi.dx = pt.x;
			in.mi.dy = pt.y;
			in.mi.dwFlags = MOUSEEVENTF_WHEEL;
			in.mi.time = 0;
			in.mi.mouseData = delta;
			break;
		

		/************** END MOUSE MESSAGES **************/

		/************** RAW MOUSE MESSAGES **************/


		case WM_INPUT:

			break;
		default:
			break;
		}

		SendInput(1, &in, sizeof(INPUT));

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
	echo.SetSourcePort(ECHO_PORT);

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
int main(int argc,char** argv)
#endif // NDEBUG

 {
	std::thread echo(EchoThread);
	std::thread server(ServerThread);

	server.join();
	echo.join();
	return 0;
}