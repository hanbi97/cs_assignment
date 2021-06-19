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
	// 1. CREATES A TCP SERVER SOCKET
	int server_socket = socket(PF_INET,SOCK_STREAM,0);
	FILE* file = fopen("data.txt", "rb");
	const int BUFFER_SIZE = 20;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in server_address;

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port=htons(atoi("1234"));

	
	// 2. BINDS THE SERVER SOCKET TO PORT 1234
	if(bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address))==-1)
		error_handling("bind() error\n");
	// 2. LISTENS TO CONNECTION REQUESTS
	if(listen(server_socket,2))
		error_handling("listen() error\n");
	
	// 3. ITERATIVE APPROACH
	int n;
	for(n=0; n<2; n++)
	{
		struct sockaddr_in clnt_adr;
		socklen_t clnt_adr_sz = sizeof(clnt_adr);
		
		// 3. ACCEPTS A CONNECTION REQUEST FROM CLIENT
		int client_socket = accept(server_socket,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
		
		if(client_socket==-1)
			error_handling("accpet() error\n");

		// 4.1. LOADS THE FILE CONTENT TO A BUFFER, AND NOTES THE LENGTH OF THE FILE
		rewind(file);
		fseek(file,0,SEEK_END);
		int filelength = ftell(file);
		rewind(file);
        fread(buffer,filelength,1,file);

		// 4.2. SENDS THE LENGTH OF THE FILE (DATA) TO CLIENT
		if((send(client_socket,&filelength,sizeof(filelength),0)) == -1)
        	error_handling("File size SYNC error\n");

		// 4.3. SENDS THE CONTENT OF THE FILE
		write(client_socket,buffer,filelength);

		// 4.4. TERMINATES ITS OUTPUT (TCP HALF-CLOSE)
		shutdown(client_socket,SHUT_WR);

		// 4.5. RECEIVES A NUMBER (A BYTE) FROM CLIENT
		int rcvnum=recv(client_socket,buffer,sizeof(buffer)-1, 0);
		
		// 4.5. PRINTS OUT THE RECEIVED NUMBER
		printf("recieved number:%d\n",rcvnum);
		
		// 4.6. CLOSES THE CLIENT SOCKET
		close(client_socket);
	}
	
	// 5. CLOSES THE FILE AND SERVER SOCKET
	fclose(file);
	close(server_socket);

	return 0;
}
