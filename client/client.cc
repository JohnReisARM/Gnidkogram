#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>

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

void send_massage_to_server (sf::Packet & pac, sf::TcpSocket & socket, const std::string & name) {
    std::string msg;

    std::cout << "Now you can, write and send massege:" << std::endl;
    while(1) {
	std::getline(std::cin, msg);

	if(msg != "") {
	    pac.clear();
	    pac << name << msg;
	    
	    socket.send(pac);
	    msg = "";
	}
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    sf::TcpSocket socket;


    /* Выбираем айпишник, если впадлу писать, то дефолтным будет адрес компа.
     * Чтобы подкобчится к дефолту, то нужно просто на
     * ентер нажать, когда попросят.
     */
    sf::IpAddress ip;
    std::string ip_str;
    std::cout << "Write ip address to connect, local address - "
	      << sf::IpAddress::getLocalAddress()
	      << ", or addres that you want"
	      << std::endl;
    std::getline(std::cin, ip_str);
    if (ip_str.size() == 0) {
	ip = sf::IpAddress::getLocalAddress();
    } else {
	ip = ip_str;
    }
    
    // Тут выбираем порт, чтобы подключится.
    int port_num;
    std::cout << "Write port number to connect: ";
    std::cin >> port_num;


    // Соединяемся, ну и проверяем че как
    if(socket.connect(ip, port_num) != sf::Socket::Done) {
	std::cout << "ERROR: cant connet to socekt\n"
		  << "stopping program..."<< std::endl;
	return -1;
    } else {
	std::cout << "connected to server" << std::endl;
    }


    /* Заранее выбираем ник, ибо потом будет потом будем постоянно проверять 
     * введенный тект, чтобы отправить сообщения, и не понятно куда пойдет текст.
     */
    std::string username;
    std::cout << "Write your nickname: ";
    std::cin >> username;
    std::cout << "Your nickname is \"" << username << "\"" << std::endl;
    
    // Делаем, чтобы сокет ничего нам не блочил во время работы.
    socket.setBlocking(false);


    // Запускаем всё отдельными потоками
    sf::Packet pac;
    std::thread check_new_msg(check_new_massage, std::ref(pac), std::ref(socket));
    std::thread send_msg(send_massage_to_server, std::ref(pac), std::ref(socket), std::ref(username));
    check_new_msg.join(); 
    send_msg.join();

    
    
    return 0;   
}
