





all:
	g++ -c server.cc
	g++ server.o -o server -lsfml-network -lsfml-system
	g++ -c client.cc
	g++ client.o -o client -lsfml-network -lsfml-system
