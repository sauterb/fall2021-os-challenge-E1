#include "E1_server.h"

int main(int argc,char *argv[]){
	
	//check if the number of input arguments is correct
	if(argc != 2){
		printf("Usage: ./server port\n");
		return 0;
	}
	int server_port = atoi(argv[1]);

	short server_socket;

	printf("server_port: %i\n", server_port);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	struct sockaddr_in client;
	int len;
	short clientLen;

	//creating the server socket 
	//function socket(int family, int type, int protocol)
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	//bind the socket to our specified IP and port
	//function bind( socketdescriptor, const struct sockaddr *addr, locklen_t addrlen)
	bind(server_socket,(struct sockaddr*)&server_address , sizeof(server_address));

	printf("Server is now listening for a client message\n");
	listen(server_socket, 100);
	
	while(1){
		// Accept the client request
		short connfd = accept(server_socket,(struct sockaddr*)&client,&len);

		handoff_process( connfd );
	}
	return 0;
}

