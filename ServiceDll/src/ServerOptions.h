#pragma once
#include <iostream>

char* GetCmdOption(char** begin, char** end, const std::string& option);
bool CmdOptionExists(char** begin, char** end, const std::string& option);