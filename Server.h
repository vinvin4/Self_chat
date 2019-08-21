#pragma once
#include <iostream>
#include <conio.h>
#include <sstream> //Работа со строками через интерфейс потоков, std::ostringstream s;
#include <string>

#define _WIN32_WINNT 0x501

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

using std::cerr;

#define host "127.0.0.1"
#define port "8000"

class Server
{
private:
	WSADATA wsaData;
	bool WSA_start();

	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	bool getAddrInfo();

	bool socket_creating();
	int listen_socket;

	bool binding();

	bool correct;

public:
	Server();
	void cleanServ();
	int getListen_socket();
	bool getCorrect();
	//static Server* getInstance();
	~Server();
};

