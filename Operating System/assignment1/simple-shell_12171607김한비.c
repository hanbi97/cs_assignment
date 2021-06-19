#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#define MAX_LINE        80


char* args[10]={};
char buffer[MAX_LINE]={};
char* date="date";
char* who="who";
char* cal="cal";
char* top="top";
char* ls="ls";
char* ps="ps";
char* history="history";
char* pwd="pwd";
char* rm="rm";
char* vi="vi";
char* newptr=NULL;
int n=0;
int length=0;
int w=0;

void func(){
newptr=(char*)malloc(sizeof(char)*(length+1));
strcpy(newptr,buffer);

if(n>=10){
w=9;
for(int j=0; j<=9; j++){
char* tmp = args[j];
char* tmp1 = args[j+1];
args[j]=tmp1;
args[j+1]=tmp;
}

args[9]=newptr;

}

else{
    args[n]=newptr;
    n++;
}

}


int main(){
    int should_run =1;
    int i, upper;
    pid_t pid;

    while(1){
   
        printf("osh>");
        scanf("%s",buffer);
        fflush(stdout);
        length=strlen(buffer);
        pid=fork();

        if(pid<0){
            fprintf(stderr,"Fork Failed");
            return 1;
        }
        else if(pid==0){
        
            if(strcmp(buffer,date)==0){
                 execlp("date","date",NULL);
             }
        
            else if(strcmp(buffer,who)==0){
                  execlp("who","who",NULL);
             }
            else if(strcmp(buffer,cal)==0){
                  execlp("cal","cal",NULL);
             }
            else if(strcmp(buffer,top)==0){
                  execlp("top","top",NULL);
             }
            else if(strcmp(buffer,ls)==0){
                 execlp("ls","ls",NULL);
             }
            else if(strcmp(buffer,ps)==0){
                 execlp("ps","ps",NULL);
             }

            else if(strcmp(buffer,pwd)==0){
                  execlp("pwd","pwd",NULL);
              }
else if(strcmp(buffer,rm)==0){
                  execlp("rm","rm",NULL);
              }
else if(strcmp(buffer,vi)==0){
                  execlp("vi","vi",NULL);
              }

            else if(strcmp(buffer,history)==0){
            
                if(w==9){
                     for(int i=w; i>=0; i--){
                     printf("%d: %s\n",i+1,args[i]);
                     }

                 }
        
                 else{
                    for(int i=n-1;i>=0;i--){
                     printf("%d: %s\n", i+1, args[i]);
                  }
               }
        
               }
            
            
            else{
                printf("There is no such command\n");
            }
            
        }
        else{
        wait(NULL);
        func();
        printf("Child Complete\n");
        }
        }
    
    
    return 0;
}
