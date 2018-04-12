#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

pthread_t tid[2];
char a[50];

void* runthread(void* arg){




  unsigned long i=0;

pthread_t id=pthread_self();

if (pthread_equal(id,tid[0])){
  while (1) {
    int listenfd = 0, connfd = 0, n = 0;
    char readBuff[1025];
    struct sockaddr_in serv_addr;
    memset(readBuff, '0', sizeof(readBuff));
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);
  while(1){
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    while ( (n = read(connfd, readBuff, sizeof(readBuff)-1)) > 0)
      readBuff[n] = 0;
    printf("%s\n", readBuff);
    close(connfd);
    sleep(1);
    }
  }
}
else{
  while(1){
    int sockfd = 0, n = 0;
    char sendBuff[1025];
    struct sockaddr_in serv_addr; 
    memset(sendBuff, '0', sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, a, &serv_addr.sin_addr);
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    scanf("%s",sendBuff);
    write(sockfd,sendBuff,sizeof(sendBuff));
    return 0;
  }
}

for (i=0;i<(0xFFFFFFFF);i++);
return NULL;
}


int main(int argc, char *argv[])
{
  memset(a, '0', sizeof(a));
  snprintf(a,sizeof(a),"%s",argv[1]);
  int i=0;
  int err;
  while (i<2){
  err = pthread_create(&(tid[i]),NULL,&runthread,NULL);
  i++;
  }

  sleep(10);
  return 0;

}
