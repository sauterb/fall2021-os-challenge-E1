all: E1_server_main_v0.c E1_server_functions_v0.c E1_util_functions_v0.c
	gcc -o server E1_server_main_v0.c E1_server_functions_v0.c E1_util_functions_v0.c -lssl -lcrypto
clean:
	$(RM) server