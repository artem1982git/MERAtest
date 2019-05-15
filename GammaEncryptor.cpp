#include "GammaEncryptor.h"
#include<iostream>


GammaEncryptor::GammaEncryptor()
{
}


GammaEncryptor::~GammaEncryptor()
{
}

void GammaEncryptor::encrypt(string keyName, string& data)
{
    std::string key;
    getKey(keyName, key);
    int keySize=key.length();
    for (int i=0;i<data.length();i++){
        data[i]=data[i] xor key[i%keySize];
    }
}

void GammaEncryptor::decrypt(string keyName, string& data)
{
    std::string key;
    getKey(keyName, key);
    int keySize=key.length();
    for (int i=0;i<data.length();i++){
        data[i]=data[i] xor key[i%keySize];
    }


}
