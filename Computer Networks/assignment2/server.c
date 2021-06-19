#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 30
void error_handling(char *message);
void sendToClient(int clnt,int pfd);
void read_childproc(int sig);
int pfd[2][2];

char buf[BUF_SIZE];

int main(int argc, char* argv[]){

    int serv_sock;
    int clnt_sock[2];
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_cnt=0;
    int reuse=1;
    pid_t chilpid[2];
    pid_t pid;
    int flag=0;
    int parentpid;
    socklen_t adr_sz;    
    char str[100]={};
    
    pipe(pfd[0]);
    pipe(pfd[1]);

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof(int));
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi("4000"));

    if(bind(serv_sock,(struct sockaddr*) &serv_adr,sizeof(serv_adr))==-1){
        error_handling("bind() error");
    }

    if(listen(serv_sock,2)==-1){
        error_handling("listen() error");
    }

    for(int i=0; i<2; i++){
        adr_sz = sizeof(clnt_adr);
        clnt_sock[i] = accept(serv_sock,(struct sockaddr*) &clnt_adr, &adr_sz);
        printf("* A client is connected. Socket id: %d\n", clnt_sock[i]);
        clnt_cnt++;
    }

    if(clnt_cnt==2){
        printf("Both clients connected\n");
    }


    for(int i=0; i<2; i++){
        pid = fork();

        if(pid==-1){
            close(clnt_sock[i]);
            continue;
        }
        else if(pid==0){ //child(connect to client socket)
            sendToClient(clnt_sock[i],pfd[i][0]);
            exit(0);
        }
        else{ //parent 
            printf("* Child process %d (pid=%d) created for client with socket id: %d\n", i+1, pid, clnt_sock[i]);
            chilpid[i]=pid;
            
        }
    }

    
    while(1){
        printf("Input message(for sending): ");
        fgets(buf, BUF_SIZE, stdin);
	 	if(!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
		{	for(int i=0; i<2; i++){
                kill(chilpid[i],SIGKILL);
                printf("A client disconneted\n");
            }
			break;
		}
        else{
            for(int i=0; i<2; i++){
               write(pfd[i][1], buf, strlen(buf));
            }
            for(int i=0; i<2; i++){
                printf("* Piping the message to child process %d\n",i+1);
            }
            for(int i=0; i<2; i++){
                printf("* Child process (pid=%d) sending the message\n",chilpid[i]);
            }
        }
    }

   
   for(int i=0; i<2; i++){
        close(clnt_sock[i]);
   }
    close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void sendToClient(int clnt,int pfd){
    while(1){
        int len = read(pfd,buf,BUF_SIZE);
        write(clnt,buf,len);
    }
    exit(0);
}