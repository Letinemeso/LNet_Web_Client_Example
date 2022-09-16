#include <iostream>
#include <thread>
#include <chrono>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Linux_Implementation/Socket_Implementation.h"

#include "Debug.h"

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

#include "Function_Wrapper.h"

struct kostyl_placeholder_class
{

};

class cl
{
public:
	void dosmth(int arg)
	{
		std::cout << "ass\n";
	}

	void dosmth(int arg, bool agr)
	{
		std::cout << "ass\n";
	}

};

template <typename objtype, typename ftype, typename... argtypes>
struct wrapper2
{
	objtype* obj = nullptr;
	ftype(objtype::*func)(argtypes...) = nullptr;

	void operator=(wrapper2<objtype, ftype, argtypes...>&& _other)
	{
		obj = _other.obj;
		func = _other.func;
	}

	wrapper2() { }

	wrapper2(wrapper2<objtype, ftype, argtypes...>&& _other)
	{
		obj = _other.obj;
		func = _other.func;
	}

	void operator()(argtypes... _args)
	{
		if(obj != nullptr)
			(obj->*func)(_args...);
		else
			func(_args...);
	}
};

template <typename objtype, typename ftype, typename... argtypes>
wrapper2<objtype, ftype, argtypes...> create_func_ptr(objtype* _obj, ftype(objtype::*_func)(argtypes...))
{
	wrapper2<objtype, ftype, argtypes...> w;

	w.obj = _obj;
	w.func = _func;

	return w;
}

template <typename ftype, typename... argtypes>
wrapper2<kostyl_placeholder_class, ftype, argtypes...> create_func_ptr(ftype(*_func)(argtypes...))
{
	wrapper2<kostyl_placeholder_class, ftype, argtypes...> w;

	w.obj = nullptr;
	w.func = _func;

	return w;
}

int main()
{
	cl c;

	wrapper2<cl, void, int> w = create_func_ptr<cl, void, int>(&c, &cl::dosmth);
	w(1);

//	wrapper w = create_func_ptr(&c, &cl::dosmth);

//	name = &cl::dosmth;
//	(c.*name)();

//	call(&c, &cl::dosmth);


//	LNET_CREATE_LOG_LEVEL("LINUX_SOCKET_LOG_LEVEL");

//	std::cout << "trying to create socket and connect to server!\n";

//	LNet::Client_Socket_Ptr socket_obj = LNet::Client_Socket_Impl::create("127.0.0.1", 25565);
//	if(socket_obj)
//		std::cout << "successfuly connected!\n";

//	if(socket_obj)
//	{
//		while(true)
//		{
//			std::string msg;
//			std::cin >> msg;

//			if(msg == "//") return 0;
//			socket_obj->send_message(msg);
//		}
//	}

	return 0;
}
