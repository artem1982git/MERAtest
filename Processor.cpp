#include "Processor.h"

void  out(std::string str) {
	std::cout << str << endl;
}






Processor::Processor()
{
	std::string key = "wewdteertdfdfdfdfdfdgtdfgdfdfdgdf";
	coder = new GammaEncryptor();
	coder->setKey("transportuser", key);
	appendSession("transportuser", "111111");
	//con.SocketCreate();
}


Processor::~Processor()
{
}

void Processor::appendSession(string user, string id)
{
	sessionMap[id] = user;
}

void Processor::eraseSession(string id)
{
	sessionMap.erase(id);
}



void  Processor::parse(char extDivider, char intDivider, std::string& flow, int pos, map<string, string>& flowMap) {

	string name;
	string val;
	bool m = true;
	while (pos < flow.length() && flow[pos] != extDivider) {
		if (m && flow[pos] != intDivider) {
			name += flow[pos];
		}
		if (flow[pos] == intDivider)
			m = false;
		if (!m && flow[pos] != intDivider) {
			val += flow[pos];
		}
		pos++;
	}
	if (!m)
		flowMap[name] = val;
	pos++;
	if (pos < flow.length())
		parse(extDivider, intDivider, flow, pos, flowMap);
}

void Processor::decrypt(string keyName,string & cString)
{
	coder->decrypt(keyName,cString);
}

void Processor::ProcessMsg(std::string data)

{
	coder->decrypt("transportuser", data);

	map<string, string> msgMap;
	parse(';', ':', data, 0, msgMap);
	
	std::function<void(std::string)> prnt;
	prnt =out;
	
	if (!msgMap.count("id") || !msgMap.count("command")){
		cout << "Illegal; message: no id or command!!!";
		return;
	}
	
	enum commands { registration, auth, push, get };
	map<string, int> comMap;
	comMap["registration"] = commands::registration;
	comMap["auth"] = commands::auth;
	comMap["push"] = commands::push;
	comMap["get"] = commands::get;
	int id;
	
	boost::regex regEx("user=(\\w+|\\d+)&password=(\\w+|\\d+)");
	boost::smatch results;
	order newOrder;
	std::function<bool(order,order)> cmp;


	switch (comMap[msgMap["command"]]) {
		case commands::registration:
			if (!msgMap.count("data")) {
				out("illegal register data!!!");
				return;
			}

			boost::regex_search(msgMap["data"], results, regEx);
						
			if (!std::string(results[1]).size() && !std::string(results[2]).size()) {
				out("illegal register data!!!");
				return;
			}
			id = Authentificator::regist(std::string(results[1]), std::string(results[2]),prnt);
			if (!id) {
				out("user exists!!!");
				return;
			}
			
			appendSession(std::to_string(id), std::string(results[1])); //допустим что не будет коллизий;
			//возврат айди клиенту

		break;
		case commands::auth:
			if (!msgMap.count("data")) {
				out("illegal auth data!!!");
				return;
			}
			boost::regex_search(msgMap["data"], results, regEx);
			
			if (!std::string(results[1]).size() && !std::string(results[2]).size()) {
				out("illegal register data!!!");
				return;
			}
			id = Authentificator::regist(std::string(results[1]), std::string(results[2]), prnt);
			if (!id) {
				out("user exists!!!");
				return;
			}
			id = Authentificator::authenticate(std::string(results[1]), std::string(results[2]),prnt);
			if (id>0) {
				appendSession(std::to_string(id), std::string(results[1]));
				
			}
			//возврат айди клиенту
			break;
			/*case commands::push{
				if (!msgMap.count("data")) {
					out("illegal auth data!!!");
					return;
				}
				

			*/

		case commands::push:

			if (!msgMap.count("data")) {
				out("illegal data!!!");
				return;
			}
			
			regEx=("client=(\\w+)&price=(\\d+)&order=(\\w+)");
			boost::regex_search(msgMap["data"], results, regEx);

			if (!std::string(results[1]).size() && !std::string(results[2]).size() && !std::string(results[3]).size()) {
				out("illegal order data!!!");
				return;
			}
			newOrder.client = std::string(results[1]);
			newOrder.price = std::string(results[2]);
			newOrder.toDo = std::string(results[3]);
			orders.push_back(newOrder);
			//возврат айди клиенту
			break;
		case commands::get:
			if (!msgMap.count("data")) {
				out("illegal data!!!");
				return;
			}
			regEx = ("sort_by=(\\w+)");
			boost::regex_search(msgMap["data"], results, regEx);

			if (!std::string(results[1]).size()) {
				out("illegal get data!!!");
				return;
			}
			if (std::string(results[1])=="client") {
				cmp = compareOrdersByClient;
				Sort(orders, cmp);
				out(joinOrders(orders));
				
				//отправить клиенту
			}
			if (std::string(results[1]) == "price") {
				//cmp = compareOrdersByPrice;
				Sort(orders, [](order a, order b) {
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

				});
				std::string str;
				out("Orders:\n\n"+joinOrders(orders));
				//отправить клиенту
			}
			if (std::string(results[1]) == "nosort") {
								
				out("Orders:\n\n"+joinOrders(orders));
				//отправить клиенту
			}
			break;
	}


}

void Processor::setCoder(Encryptor *coder)
{
	this->coder = coder;
}

std::string Processor::joinOrders(const vector<order> orders)
{
	std::string str;
	int i = 1;
	for (auto& t : orders) {
		str = str + std::to_string(i) + ": " + t.client + "\n" + "  " + t.price + "\n" + "  " + t.toDo + "\n";
		i++;
	}
	return str;
}






