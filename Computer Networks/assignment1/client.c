#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main()
{
	// 1. CREATES A TCP SOCKET
	int client_socket = socket(PF_INET,SOCK_STREAM,0);
	const int BUFFER_SIZE = 20;
	char buffer[BUFFER_SIZE];
	
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(atoi("1234"));

	// 2. CONNECTS TO TCP LOCAL SERVER (BY ADDRESS: ip=127.0.0.1, port=1234)
	if(connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address))==-1)
		error_handling("connect() error\n");	
	
	// 3. RECEIVES (A BYTE) A LENGTH OF THE INCOMING DATA
	int expected_data_length;

	recv(client_socket,&expected_data_length,sizeof(expected_data_length),0);
    buffer[expected_data_length]='\0';
	
	// 4. RECEIVES THE INCOMING DATA
	char received_length;
    received_length = read(client_socket, buffer, expected_data_length);
    buffer[received_length] = '\0';

	if(received_length != expected_data_length)
	{
		printf("Mismatch in data length! Expected data length: %d, received data length: %d\n", expected_data_length, received_length);
	}

	// 5. PRINTS OUT THE RECEIVED DATA
	printf("%s\n",buffer);
	
	// SEND A NUMBER (A BYTE) VALUE 0 TO SERVER
	send(client_socket,'0',1,0);

	// CLOSES THE SOCKET
	close(client_socket);

	return 0;
}
