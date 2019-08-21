#pragma once
#include <iostream>
#include <conio.h>
#include <sstream> 
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
	/**
	Prepare initial information
	Return: true - WSAStartup was correct; false - there were troubles
	*/
	bool wsaStart();

	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	/**
	Fill initial information
	Return: true - getaddrinfo was correct; false - there were troubles
	*/
	bool getAddrinfo();
	/**
	Create socket
	Return: true - socket was created; false - returned INVALID_SOCKET
	*/
	bool socketCreating();
	int listenSocket;
	/**
	Bind the socket
	Return: true - binding was correct; false - returned SOCKET_ERROR
	*/
	bool binding();

	bool correct; 

public:
	Server(); //binding()<-socketCreating()<-getAddrinfo()<-wsaStart()
	void cleanServ(); //Clean working area
	int getListenSocket();
	bool getCorrect();//Returns true, if all stages of building were completed
	
	~Server();
};

