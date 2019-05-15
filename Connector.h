#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

#include "GammaEncryptor.h"
#include"Processor.h"


#pragma once
class Connector
{
private:
	Processor proc;
public:
	void rcvData(std::string data);
	 SOCKET Connection;
	
	Connector();
	void SocketCreate();
	void senddata(std::string data);
	~Connector();
};

