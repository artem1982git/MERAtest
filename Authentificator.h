#pragma once
#include <string>
#include <map>
#include<time.h>
#include<iostream>
#include <functional>

//должен быть синглтон

//using namespace std;

class Authentificator
{
private:
	static std::map<std::string, size_t> passwordBase;
public:
	
	Authentificator();
	~Authentificator();
	static int authenticate(std::string userName, std::string password,std::function<void (std::string)> out );
	static int regist(std::string userName, std::string password, std::function<void(std::string)> out);
};

