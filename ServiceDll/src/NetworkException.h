#pragma once
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

