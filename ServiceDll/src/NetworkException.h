#pragma once
#include <string>
#include <exception>



#ifndef NDEBUG
#include <iostream>
#define LOG_ERR std::cerr << "Error At : " << __FILE__ << " : " << __LINE__ << std::endl
#else
#define LOG_ERR
#endif


class NetworkException:public std::exception
{
private:
	std::string message;
	std::string file;
	int line;
public:
	NetworkException(std::string message,std::string file,int line);
	~NetworkException();

public:
	const char* what()noexcept ;
	std::string getFileName();
	int getLine();
};

