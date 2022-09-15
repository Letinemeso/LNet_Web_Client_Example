#include <iostream>
#include <thread>
#include <chrono>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Linux_Socket_Implementation.h"

/*
#ifdef LNET_ASSERT
	#undef LNET_ASSERT
#endif
#define LNET_ASSERT(condition) if(!condition) { int a = 1; a /= 0; } 1 == 1

void error(const char *msg)
{
	if(msg)
		std::cout << msg << "\n";
	LNET_ASSERT(false);
}

int main()
{
	int sockfd, portno, n;
	sockaddr_in serv_addr;
	hostent *server;

	char buffer[256];

	portno = 25565;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("127.0.0.1");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	printf("Please enter the message: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0)
		 error("ERROR writing to socket");
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0)
		 error("ERROR reading from socket");
	printf("%s\n",buffer);
	close(sockfd);
	return 0;
}
*/

int main()
{
	std::cout << "trying to create socket and connect to server!\n";

//	while(true)
//	{
//		LNet::Client_Socket_Ptr socket = LNet::Client_Socket_Impl::create("127.0.0.1", 25565);
//		if(socket.extract_pointer())
//			break;
//		else
//			std::cout << "failure! retrying after 2 seconds\n";

//		std::this_thread::sleep_for(std::chrono::seconds(2));
//	}

	LNet::Client_Socket_Ptr socket_obj = LNet::Client_Socket_Impl::create("127.0.0.1", 25565);
	if(socket_obj)
		std::cout << "successfuly connected!\n";
	else
		std::cout << "error code: " << errno << "\nerror: " << strerror(errno) << "\n";

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

	return 0;
}
