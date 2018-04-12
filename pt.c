#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];

void* runthread(void* arg){

unsigned long i=0;
pthread_t id=pthread_self();
if (pthread_equal(id,tid[0])){
while (1) {printf("1st\n");sleep(1);}
}
else{
while (2) {printf("2nd\n");sleep(2);}
}
for (i=0;i<(0xFFFFFFFF);i++);
return NULL;
}


int main(void){
int i=0;
int err;
while (i<2){
err = pthread_create(&(tid[i]),NULL,&runthread,NULL);
i++;
}

sleep(10);
return 0;
}

