#include "Authentificator.h"

std::map<std::string, size_t> Authentificator::passwordBase;

Authentificator::Authentificator()
{
}


Authentificator::~Authentificator()
{
}
int Authentificator::authenticate(std::string userName, std::string password, std::function<void(std::string)> out)
{

	if (!passwordBase.count(userName)) {
		out ("no such user!!!");
		return 0;
	}
	std::hash<std::string> sHash;
	size_t dSign = sHash(password);
	
	if (dSign != passwordBase.at(userName)) {
		out ("no such user!!!");
		return -1;
	}
	
	srand(time(NULL));
	return rand();
}

int Authentificator::regist(std::string userName, std::string password, std::function<void(std::string)> out)
{
	if (passwordBase.count(userName))
		return 0;
	std::hash<std::string> sHash;
	size_t dSign = sHash(password);
	passwordBase[userName] = dSign;
	srand(time(NULL));
	return rand();
	
}
