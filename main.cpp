
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "Controller.h"
#include"Connector.h"

struct ord {
	std::string price;
	std::string client;
	std::string toDo;
};

int main(int argc, char* argv[]) {
	
	    
    Controller ctrl;
    ctrl.process();

	return 1;

}
