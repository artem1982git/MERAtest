#include "userinterface.h"

UserInterface::UserInterface()
{

}

int UserInterface::mainMenu()
{
 int action;
 std::cout<<"1 Registration"<<std::endl;
 std::cout<<"2 Authorization"<<std::endl;
 std::cout<<"0 Exit"<<std::endl;
 std::cin>>action;
 if (action==0 || action==1 || action==2){
     return action;
 }else {
     std::cout<<"Illegal menu"<<std::endl;
     return -1;
 }

}

int UserInterface::registration(std::string& user,std::string& password)
{
    std::string u;
    std::string tmpPass1;
    std::string tmpPass2;
    std::cout<<"Enter login"<<std::endl;
    std::getline(std::cin,u);
    std::cout<<"Enter password "<<std::endl;
    std::getline(std::cin,tmpPass1);
    std::cout<<"Repeat password "<<std::endl;
    std::getline(std::cin,tmpPass2);
    if (tmpPass1!=tmpPass2){
        std::cout<<"Illegal password"<<std::endl;
        return -1;
    }
    user=u;
    password=tmpPass1;
    return 1;

}

int UserInterface::authentification(std::string& user,std::string& password)
{
    std::string u;
    std::string tmpPass;
    std::cout<<"Enter login "<<std::endl;
    std::getline(std::cin,u);
    std::cout<<"Enter password "<<std::endl;
    std::getline(std::cin,tmpPass);
    user=u;
    password=tmpPass;
    return 1;
}

int UserInterface::actions()
{
    
	//setlocale(LC_ALL, "ru");
		int action;
    std::cout<<"1 Create order"<<std::endl;
    std::cout<<"2 Get order list"<<std::endl;
    std::cout<<"3 Get client sorted order list"<<std::endl;
    std::cout<<"4 Get price sorted order list"<<std::endl;
	std::cout << "0 Exit" << std::endl;
       std::cin>>action;
    if (action>=0 && action<5){
        return action;
    }else {
        std::cout<<"Illegal operation number"<<std::endl;
        return -1;
    }


}

int UserInterface::createOrder(std::string &client, std::string &price, std::string &msg)
{
    std::string tmpClient;
    std::string tmpPrice;
    std::string tmpOrder;
	std::cout << "Enter client name or 0 for cancel" << std::endl;
    while(true){
        std::getline(std::cin, tmpClient);
        if (tmpClient=="0"){
            return 0;

        }
        if (tmpClient.length()){//проверка правильности нужно другую с регулярными выражениями
           break;
        }
    }
	std::cout << "Enter order price or 0 for cancel" << std::endl;
    while(true){
        
        std::getline(std::cin,tmpPrice);
        if (tmpPrice=="0"){//проверка правильности
            return 0;
        }
		boost::regex regEx("(\\D+)");
		boost::smatch results;
		
		boost::regex_search(tmpPrice, results, regEx);
		std::cout << std::string(results[1]);
		if (std::string(results[1]).length()) {
			std::cout << "Digits only! Please try again!" << std::endl;
			continue;
		}
		if (tmpPrice.length()){
            break;
        }
    }
	std::cout << "Enter order description or 0 for cancel" << std::endl;
    while(true){
        
        std::getline(std::cin,tmpOrder);
		if (tmpOrder == "0") {//проверка правильности
			return 0;
		}
        if (tmpOrder.length()){//проверка правильности
			break;
        }
    }
    client=tmpClient;
    price=tmpPrice;
    msg=tmpOrder;
	return 1;

}


