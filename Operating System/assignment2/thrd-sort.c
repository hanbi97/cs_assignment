#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>


#define MAX_SIZE 1000

int input[MAX_SIZE]={0,};
int first_arr[MAX_SIZE]={0,};
int second_arr[MAX_SIZE]={0,};
int res_arr[MAX_SIZE]={0,};
int thr_id=0;
int last_idx=0;
int first_idx,second_idx;

typedef struct ttwoArg{
    int arr[MAX_SIZE];
    int idx;
}twoArg;


int static compare(const void *first, const void *second){
if(*(int*)first>*(int*)second)
    return 1;
else if(*(int*)first<*(int*)second)
        return -1;
else
        return 0;
}

void *sort(void* p){
    int b[MAX_SIZE]={0,};
    twoArg* pp=(twoArg*)p;
    int a=pp->idx;
    for(int i=0; i<a; i++){
    b[i]=pp->arr[i];
    }

    qsort(pp->arr,a,sizeof(int),compare);
    pthread_exit(0);
}


int main(){

pthread_t tid[2]={0,0};
int thr_id[2]={0,0};
//pthread_attr_t attr;

printf(">thrd-sort\n");
do{
scanf("%d",&input[last_idx]);
last_idx++;
}
while(getchar()!='\n');


if((last_idx%2)==0){
first_idx=last_idx/2;
second_idx=last_idx/2;
}
else{
first_idx=last_idx/2;
second_idx=last_idx-first_idx;
}

for(int i=0; i<first_idx; i++){
    first_arr[i]=input[i];           
}

for(int i=0; i<second_idx; i++){
    second_arr[i]=input[i+first_idx];
}


twoArg fArg;
for(int i=0; i<first_idx; i++){
fArg.arr[i]=first_arr[i];
}
fArg.idx=first_idx;

twoArg sArg;
for(int i=0; i<second_idx; i++){
sArg.arr[i]=second_arr[i];
}
sArg.idx=second_idx;

thr_id[0] = pthread_create(&tid[0],NULL,sort,(void*)&fArg);
       
if(thr_id[0]<0){
perror("thread create error: ");
return -1;
}


thr_id[1] = pthread_create(&tid[1],NULL,sort,(void*)&sArg);
 if(thr_id[1]<0){
 perror("thread create error: ");
 return -1;
 }

for(int i=0; i<2; i++){
pthread_join(tid[i],NULL);
}

int res_idx=first_idx+second_idx;
for(int i=0; i<first_idx; i++){
    res_arr[i]=first_arr[i];
}

for(int i=0; i<second_idx; i++){
res_arr[i+first_idx]=second_arr[i];
}

qsort(res_arr,res_idx,sizeof(int),compare);


for(int i=0; i<res_idx; i++){
    printf("%d ",res_arr[i]);
}
printf("\n");
}
