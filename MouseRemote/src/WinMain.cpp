#include <Windows.h>
#include <WinUser.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    int i = 0;

    while (i < 10) {
        Sleep(20);
        mouse_event(MOUSEEVENTF_MOVE ,10,10,0,0);
        i++;
    }
    return 0;
}