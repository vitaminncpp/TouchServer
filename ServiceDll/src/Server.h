#pragma once
#include <iostream>
#include <thread>
#include <cmath>
#include <Windows.h>
#include <WinUser.h>

constexpr unsigned short int ECHO_PORT = 5560;
constexpr unsigned short int SERVER_PORT = 5559;

void EchoThread();
void EchoThreadA(IPv4 ip);
void ServerThread();