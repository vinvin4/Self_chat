#include "Server.h"

Server::Server()
{
	correct = binding();
}


bool Server::WSA_start()
{
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);//MAKEWORD(2,2) == 0000 0010 0000 0010

	if (result != 0)
	{
		cerr << "WSAStartup failed: " << result << std::endl;
		return false;
	}
	else
	{
		cerr << "WSAStartup completed" << std::endl;
		return true;
	}
	
}

bool Server::getAddrInfo()
{
	if (this->WSA_start())
	{
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		if (int result = getaddrinfo(host, port, &hints, &addr) != 0)
		{
			cerr << "getaddrinfo failed:  " << result << std::endl;
			WSACleanup();
			return false;
		}
		else
		{
			cerr << "getaddrinfo completed" << std::endl;
			return true;
		}
	}
	else
	{
		return false;
	}	
}

bool Server::socket_creating()
{
	if (this->getAddrInfo())
	{
		listen_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

		if (listen_socket == INVALID_SOCKET)
		{
			cerr << "Error at socket: " << WSAGetLastError() << std::endl;
			freeaddrinfo(addr);
			WSACleanup();
			return false;
		}
		else
		{
			cerr << "Good at socket" << std::endl;
			return true;
		}
	}
	else
		return false;
}

bool Server::binding()
{
	if (this->socket_creating())
	{
		if (bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen) == SOCKET_ERROR)
		{
			cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
			freeaddrinfo(addr);
			closesocket(listen_socket);
			WSACleanup();
			return false;
		}
		else
		{
			cerr << "Bind was completed;" << std::endl;
			return true;
		}
	}
	else
		return false;
}






void Server::cleanServ()
{
	closesocket(listen_socket);
	freeaddrinfo(addr);
	WSACleanup();
}

int Server::getListen_socket()
{
	return listen_socket;
}

bool Server::getCorrect()
{
	return correct;
}

Server::~Server()
{
	cleanServ();
}
