#include "Connector.h"



void Connector::rcvData(std::string data)
{
	proc.ProcessMsg(data);
}

Connector::Connector()
{
}

void Connector::SocketCreate()
{
   

}

void Connector::senddata(std::string data)
{
	
	rcvData(data);

}
Connector::~Connector()
{
}
