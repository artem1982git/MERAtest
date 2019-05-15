#include "Encryptor.h"
#include <iostream>


Encryptor::Encryptor()
{
}


Encryptor::~Encryptor()
{
}

void Encryptor::setKey(string keyName, string key)
{

    keyMap[keyName] = key;
}

int Encryptor::getKey(std::string keyName, std::string& key)
{

    if (keyMap.count(keyName)) {
		key.clear();
		key = keyMap[keyName];
        
        return 1;
	}

	return 0;
}

void Encryptor::delKey(string keyName)
{
	keyMap.erase(keyName);
}
