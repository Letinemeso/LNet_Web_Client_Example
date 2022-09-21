#include <iostream>
#include <thread>
#include <chrono>

#include <string.h>

#include "Socket_Implementation.h"


int main()
{
	LNET_CREATE_LOG_LEVEL("WINDOWS_SOCKET_LOG_LEVEL");

	std::cout << "trying to create socket and connect to server!\n";

	WSADATA wsaData;
	int error = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (error != 0) {
		std::cout << "WSAStartup failed: " << error << "\n";
		return 1;
	}

	LNet::Client_Socket_Ptr socket_obj = LNet::Client_Socket_Impl::create("127.0.0.1", 25565);
	if(socket_obj)
		std::cout << "successfuly connected!\n";
	else
	{
		int error = WSAGetLastError();
		std::cout << "error code: " << error << "\nerror: " << strerror(error) << "\n";
	}

	if(socket_obj)
	{
		while(true)
		{
			std::string msg;
			std::cin >> msg;

			if(msg == "//") return 0;
			socket_obj->send_message(msg);
		}
	}

	WSACleanup();

	return 0;
}
