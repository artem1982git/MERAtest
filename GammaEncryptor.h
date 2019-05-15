#pragma once
#include "Encryptor.h"

class GammaEncryptor :
	public Encryptor
{
public:
	GammaEncryptor();
	~GammaEncryptor();
	void encrypt(string keyName, string& data)  override;
	void decrypt(string keyName, string& data) override;
	
};

