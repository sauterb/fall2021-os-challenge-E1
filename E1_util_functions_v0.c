#include "E1_server.h"

//mycopy copy the uint8_t array in reversed order
void mycopy(uint8_t destination[], uint8_t source[]){
	int length = 32;
	for(int i = length-1;i>=0; i--){
		destination[i] = source[i];
	}
}

int compare_uc_arrays(unsigned char * a, unsigned char * b){

	for(int i = 0; i<32 ; i++){

		if(a[i] != b[i]){
			return 1;
		}
	}
	return 0;
}

void dec_to_hex( uint8_t dec ){
	int n = (int)dec;
	char hexaDec[100];
	int i =0;
	while(n != 0){
		int temp = 0;
		temp = n%16;
		if(temp < 10){
			hexaDec[i] = temp + 48;
			i++;
		}else{
			hexaDec[i] = temp + 55;
			i++;
		}
		n = n/16;
	}
	for(int j = i-1; j>=0; j--){
		printf("%c",hexaDec[j]);
	}
}

void print_array( uint8_t* d, int len ){

	for( int i = 0; i < len; i++ ){

		printf("%d", d[i]);
	}
	printf("\n");
}
