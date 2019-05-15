#pragma once

#include <vector>
#include <map>
#include<string>

using namespace std;

class Encryptor
{
private:
	map<string,string> keyMap; //keys should be multiple 8 bits 
	
public:
	Encryptor();
	~Encryptor();
	virtual void encrypt(string keyName,string& data) = 0;
	virtual void decrypt(string keyName,string& data ) = 0;
	void setKey(string keyName, string key);
    int getKey(string keyName, string & key);
	void delKey(string keyName);
};

