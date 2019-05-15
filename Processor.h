#pragma once
#include <string>
#include <map>
#include <functional>
#include<vector>
#include "Encryptor.h"
#include "GammaEncryptor.h"
#include<iostream>
#include"Authentificator.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

struct order {
	std::string price;
	std::string client;
	std::string toDo;
};
using namespace std;
class Processor
{
private:
	
	map<string, string> sessionMap;
	map<string, string> commandMap;
	Encryptor *coder=NULL;
	map<string, string> messageMap;
	//Authentificator *authBase;
	std::vector<order> orders;

public:
	Processor();
	~Processor();
	Processor(Encryptor *c) :Processor() { coder = c; };
	void appendSession(string user, string id);
	void eraseSession(string id);

	//void parseExecute(char* string input, int size);
	void  parse(char extDivider, char intDivider, std::string& flow, int pos, map<string, string>& flowMap);
	void decrypt(string keyName, string& cString);
	//template<class T>
	//static void BubbleSort(vector<T>& arr, std::function<bool(T a, T b)> compare) ;
	template<class T, class Compare>
	void Sort(vector<T>& arr, Compare cmp);
	void ProcessMsg(std::string data);
	void setCoder(Encryptor *coder);
	std::string joinOrders(const vector<order> orders);
	
	static bool compareOrdersByClient(order a, order b) {
		int length;
		if (a.client.length() <= b.client.length()) {
			length = a.client.length();
		}
		else {
			length = b.client.length();
		}
		for (int x = 0; x < length; x++) {
			if (a.client[x] < b.client[x]) {
				return true;
			}
		}
		return false;
	};
	static bool compareOrdersByPrice(order a, order b) {
		int length;
		if (a.price.length() <= b.price.length()) {
			length = a.price.length();
		}
		else {
			length = b.price.length();
		}
		for (int x = 0; x < length; x++) {
			if (a.price[x] < b.price[x]) {
				return true;
			}
		}
		return false;

	};

};


template<class T, class Compare>
inline void Processor::Sort(vector<T>& arr, Compare cmp)
{
	int size = arr.size();
	for (int i = 1; i < size; ++i)
		for (int j = size - 1; j >= i; --j)
			if (cmp(arr[j - 1], arr[j]))
				std::swap(arr[j], arr[j - 1]);
}

