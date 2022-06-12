#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>



struct IPv4
{
    unsigned char s_b1, s_b2, s_b3, s_b4;
};

bool GetMyIP(struct IPv4& myIP);