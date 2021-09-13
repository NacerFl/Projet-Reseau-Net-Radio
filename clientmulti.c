#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 2727
#define MAXLINE 1024

int main(int argc, char **argv)
{
    int socketsama;
    char buff[MAXLINE];
    struct sockaddr_in address_sock;
    int ok=1;
    socketsama = socket(AF_INET, SOCK_DGRAM, 0); //j'ai changer SOCK D_GRAM EN SOCK_STREAM
   // bzero(buff, MAXLINE); //initialise à 0 buff
   int multisocket=setsockopt(socketsama,SOL_SOCKET,SO_REUSEPORT,&ok,sizeof(ok));

    if (socketsama == -1)
    {
        printf("Erreur dans l'ouverture de la socket");
        exit(1);
    }
    else
    {
        printf("Socket créée\n");
    }

    memset(&address_sock, 0, sizeof(address_sock));
    //memset(&client, 0, sizeof(client));

    address_sock.sin_family = AF_INET;
    address_sock.sin_addr.s_addr = INADDR_ANY;
    address_sock.sin_port = htons(2727);

    multisocket=bind(socketsama,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
    if(multisocket == -1){
        printf("error bind");
    }else{
        printf("nice bind");
    }

    printf("Waiting...\n");

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr=inet_addr("225.1.2.4");
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    multisocket=setsockopt(socketsama,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

    int reception;

    //char *hello = "STOP";
    while (1){
    printf("je suis dans la boucle");
    reception = recv(socketsama, buff, sizeof(buff), 0);
    buff[reception] = '\0';
    printf("Réponse 1 du Server : %s\n ",buff);
  
    }
    close(socketsama);
    return 0;
}