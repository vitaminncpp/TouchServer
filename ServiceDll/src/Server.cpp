#include "NetworkException.h"
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "Util.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <thread>


void GetDesktopResolution(int& horizontal, int& vertical);

struct SendInput {
	UINT msg;
	LPARAM lParam;
	WPARAM wParam;
};

#define ECHO_PORT 5560
#define SERVER_PORT 5559

void EchoThread();
void ServerThread();

void ServerThread() {
	UDPReceiver server(SERVER_PORT);
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
int main(int argc,char** argv)
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