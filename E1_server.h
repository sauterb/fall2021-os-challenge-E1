#ifndef SERVER_E1_H
#define SERVER_E1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>

#include "messages.h"

// structure to keep data obtained from client
 struct Request{
                uint8_t hash[32];
                uint64_t start;
                uint64_t end;
                uint8_t priority;
        };

//declaration of functions needed in server program
void handoff_process( short connfd );
void handle_request(short sockfd);
int find_send_answer( short sockfd, uint64_t start, uint64_t end, uint8_t* hash );
void mycopy(uint8_t destination[],uint8_t source[]);
int compare_uc_arrays(unsigned char * a, unsigned char * b);
void dec_to_hex( uint8_t dec );
void print_array( unsigned char* d, int len );

#endif