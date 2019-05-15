#include "Controller.h"
#include <Windows.h>


Controller::Controller()
{
    std::string key = "wewdteertdfdfdfdfdfdgtdfgdfdfdgdf";
    user = "user1";
    coder = new GammaEncryptor();
    coder->setKey(user, key);
    id="111111";
	//connection.SocketCreate();

}



Controller::~Controller()
{


}

void Controller::process()
{

    enum commands {close,push, get, get_sorted_by_client,get_sorted_by_price};
	int command;
    command=ui.actions();
    while (command!=commands::close){

        if (command == commands::push) {
            std::string client;
            std::string price;
            std::string msg;
            if (!ui.createOrder(client, price, msg)) {
               command=ui.actions();
               continue;

                
            }
        std::string data = "id:" + id +";"+"command:push;"+"data:client=" + client + "&" + "price=" + price + "&" + "order=" + msg + ";";
            senddata(data);

        }
        if (command == commands::get) {
            std::string data = "id:" + id +";"+"command:get;data:sort_by=nosort;";
            senddata(data);
        }

        if (command == commands::get_sorted_by_client) {
            std::string data = "id:" + id +";"+"command:get;data:sort_by=client;";
            senddata(data);

        }
        if (command == commands::get_sorted_by_price) {
            std::string data = "id:" + id +";"+"command:get;data:sort_by=price;";
            senddata(data);

        }
         command=ui.actions();
    }
    delete coder;
    std::cout<<"Bye!";
    exit(0);
}

void Controller::senddata(std::string data)
{
   coder->encrypt(user,data);
   connection.senddata(data);

}
