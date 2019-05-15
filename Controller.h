#pragma once
#include "userinterface.h"
#include "Encryptor.h"
#include "GammaEncryptor.h"
#include "Connector.h"

class Controller
{
private:
	std::string id;
	std::string password;
	std::string user;
	UserInterface ui;
	Encryptor *coder;
	Connector connection;
public:
	Controller();
	~Controller();
	void process();
    void senddata(std::string data);
};

