#include <iostream>
#include <conio.h>
#include <sstream> 
#include <string>

#define _WIN32_WINNT 0x501

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

using std::cerr;

#include "Server.h"

int main()
{
	Server *serv = new Server();
	if (serv->getCorrect() == false)
	{
		return 1;
	}
	else
	{
		system("start http://127.0.0.1:8000/");
		int listenSocket = serv->getListenSocket();

		if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
			serv->cleanServ();
			return 1;
		}
		else
		{
			cerr << "Listening correct" << std::endl;
		}
		/////
		int client_socket = accept(listenSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
		{
			cerr << "Accept failed: " << std::endl;
			serv->cleanServ();
			return 1;
		}
		else
		{
			cerr << "Accept was good" << std::endl;
		}
		/////
		const int maxClientBufferSize = 1024;
		char buf[maxClientBufferSize];

		int result = recv(client_socket, buf, maxClientBufferSize, 0);
			   		
		if (result == SOCKET_ERROR)
			{
				cerr << "Recv failed: " << std::endl;
			}
		else
			if (result == 0)
				{
					cerr << "Connection closed" << std::endl;
				}
			else
				if (result > 0)
				{
					buf[result] = '\0';					
					//////
					std::stringstream response;
					std::stringstream response_body;
					std::stringstream sample;

					response_body
						<< "<title>Test C++ HTTP Chat Server</title>" << std::endl
						<< "<h1>Hello Page</h1>" << std::endl
						<< "<p> </p>" << std::endl
						<< "<h2>Chat area: </h2>" << std::endl;
					response
						<< "HTTP/1.1 200 OK\r" << std::endl
						<< "Version: HTTP/1.1\r" << std::endl
						<< "Content-Type: text/html; charset=utf-8\r" << std::endl
						<< "Content-Length" << response_body.str().length()
						<< "\r\n\r\n"
						<< response_body.str();
					result = send(client_socket, response.str().c_str(), response.str().length(), 0);
					//////
					
						for (int j = 0; j < 2; j++)
						{
							std::stringstream message;
							cerr << "Press line: " << std::endl;
							char sample_buf[maxClientBufferSize];
							std::cin.getline(sample_buf, 1024);
							message
								<< "<pre>" << sample_buf << "</pre>" << std::endl;

							result = send(client_socket, message.str().c_str(), message.str().length(), 0);

							if (result == SOCKET_ERROR)
							{
								cerr << "Send failed: " << WSAGetLastError() << std::endl;
							}
						}
						closesocket(client_socket);
					}
			_getch();
	}	
	serv->cleanServ();
	return 0;
}