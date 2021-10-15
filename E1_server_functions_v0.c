#include "E1_server.h"

void handoff_process( short connfd ){

	// Test that accept was successful
	if(connfd < 0){
		printf("server accept failed connfd:%d\n", connfd);
		exit(0);
	}
	else{
		printf("server accepted the client\n");
	}

	pid_t pid = fork();

	if( pid == 0 ){
		//Child process handles request
		handle_request(connfd);

		//close(server_socket);
		close(connfd);

		//Kill child process
		exit(0);
		printf("I'm not dead");

	}else if (pid == -1) { // error checking
		printf("fork fail\n");
		exit(1); // exit with exit code 1

		}else{
			// Parent process continues listening
			close(connfd);
	}
}

void handle_request(short sockfd){
	unsigned char request_packet[PACKET_REQUEST_SIZE];
	unsigned char response_packet[PACKET_RESPONSE_SIZE];

	bzero(request_packet,PACKET_REQUEST_SIZE);
	read(sockfd,request_packet,sizeof(request_packet));

	//initializing a structure reqest given from client
	struct Request request;

	uint64_t *st = malloc(sizeof(uint64_t));
	memcpy(st,&request_packet[PACKET_REQUEST_START_OFFSET],8);
	request.start = htobe64(*st);
	free(st);

	uint64_t *en = malloc(sizeof(uint64_t));
	memcpy(en,&request_packet[PACKET_REQUEST_END_OFFSET],8);
	request.end = htobe64(*en);
	free(en);

	mycopy(request.hash,&request_packet[PACKET_REQUEST_HASH_OFFSET]) ;
	request.priority = request_packet[PACKET_REQUEST_PRIO_OFFSET] ;

	if( request.start != 0 ){

		printf("Looking for answer --- Start: %lu\nEnd: %lu\nPriority:%u\n",request.start,request.end,request.priority);

		if(!find_send_answer( sockfd, request.start, request.end, request.hash )){return;}

		else{ printf("Error, could not reverse hash");}
	}
}

int find_send_answer( short sockfd, uint64_t start, uint64_t end, uint8_t* hash ){

	uint8_t d[32];

	for(uint64_t i = start; i<end; i++){

		SHA256_CTX sha256;
		SHA256_Init(&sha256);
		uint64_t hashnumb = htole64(i);
		SHA256_Update(&sha256,&hashnumb,sizeof(uint64_t));
		SHA256_Final(d,&sha256);				

	        if(compare_uc_arrays(d,hash)==0){

	                //at this point we have value i which was encrypted
			uint64_t response_in_uint64t = htobe64(i);
	                
		       	write(sockfd,&response_in_uint64t,PACKET_RESPONSE_SIZE);

		       	printf("[server] %lu\n", i);
			
			return 0;
	        }
	}
	return 1;
}
