#pragma once
#include <string>
#include <unordered_map>


int ReadJSON(const std::string& buff, std::unordered_map<std::string, std::string>& input);
