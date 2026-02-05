#include <SFML/Network.hpp>
#include <iostream>
#include <string>


int main() {
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    if(socket.connect(ip,58223) != sf::Socket::Done) {
	std::cout << "sosi hui" << std::endl;
    }
    socket.setBlocking(false);

    std::string msg;
    sf::Packet pac;

     while(1) {
	 std::getline(std::cin, msg);
	 //	 std::cin >> msg;
	 if(msg != "") {
	     pac.clear();
	     pac << "mr.bipka: " << msg;

	    socket.send(pac);
	    msg = "";
	 }
	 if(socket.receive(pac) == sf::Socket::Done ) {
	     std::string name;
	     std::string awnser;
	     pac >> name >> awnser;
	     std::cout << name << " : " << awnser << std::endl;
	     
	 }
	 
    }
    
    
    
    return 0;   
}
