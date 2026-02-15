#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void check_new_massage(sf::Packet & pac, sf::TcpSocket & socket) {
    std::string name;
    std::string awnser;

    while(1) {

	 if(socket.receive(pac) == sf::Socket::Done ) {
	     pac >> name >> awnser;
	     std::cout << name << ": " << awnser << std::endl;
	     
	 }
	 
	 std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void send_massage_to_client (sf::Packet & pac, sf::TcpSocket & socket) {
    std::string msg;

    std::cout << "Now you ready to send massage:" << std::endl;
    while(1) {
	std::getline(std::cin, msg);

	if(msg != "") {
	    pac.clear();
	    pac << "SERVER" << msg;
	    
	    socket.send(pac);
	    msg = "";
	}
    }
}



int main() {
    setlocale(LC_ALL, "Russian");
    sf::TcpSocket socket;
    sf::TcpListener listener;

    // Выборы порта, который будем слушать
    int port_num;
    do {
    std::cout << "Write port number to listen (49152-65535): ";
    std::cin >> port_num;
    } while((port_num > 65535) || (port_num < 49152));

    // Слушаем порт, если нет, то судьба против
    listener.listen(port_num);
    if(listener.accept(socket) != sf::Socket::Done) {
	std::cout << "Cant listen socket, stopping program" << std::endl;
	return -1;
    } else {
	std::cout << "User connected" << std::endl;
    }
    
    // Вот эта вот лабуда, чтобы у нас сокет при работе остальную прогу не блокал
    socket.setBlocking(false);
    
    /* Тут просто запускаем в два потока проверку сообщений и отправку, чтобы
     * они друг другу не мешали
     */
    sf::Packet pac;
    std::thread check_new_msg(check_new_massage, std::ref(pac), std::ref(socket));
    std::thread send_msg(send_massage_to_client, std::ref(pac), std::ref(socket));
    check_new_msg.join(); 
    send_msg.join();
   
    return 0;   
}
