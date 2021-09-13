#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAXLINE 1024

void display_msg(char content[MAXLINE]){                                    //Affiche la chaîne de caractère suivant la structure demandée des messages

  for(int i=0; i<MAXLINE; i++){                                                   //On lit le message caractère par caractère
    if((content[i] == '\r') && (i<139))                                     //Si on tombe sur un \r puis un \n, on stoppe l'affichage puisqu'on terminé le message
      if(content[i+1] =='\n')
    break;
    printf("%c", content[i]);                                               //Sinon on affiche le caractère
  }
  write(STDOUT_FILENO, "\n",1);                                               //Et quand on a fini, on revient à la ligne

}

int main(int argc, char **argv)
{
    int socketsama;
    struct sockaddr_in serveraddr;
    FILE *fptr;
    char * buffer="";
    char gest_ip[15], gest_port[5];

    int port = 1111;
    printf("%d\n", argc);
    if(argc == 2) port = atoi(argv[1]);
    if(port < 0 || port > 9999){
        write(STDERR_FILENO, "Port invalide\n",14);     
        exit(EXIT_FAILURE);
    }

  while ((fptr = fopen("./config.txt", "r")) == NULL)
  {
    printf("Fichier de Gestionnaire inexistant. Entrez quelque chose pour reessayer\n");
    scanf("%s\n", buffer);
  }
  fgets(gest_ip,sizeof(char)*15,fptr);
  fgets(gest_port,sizeof(char)*5,fptr);
  int port_gest = (gest_port[0]-'0')*1000 + (gest_port[1]-'0')*100 + (gest_port[2]-'0')*10 + (gest_port[3]-'0');

  char id[9] = "#Cholera\0";
  char buff[256];
  memset(buff, 0, 256);
 /* printf("Voulez vous redéfinir votre identifiant? (o/n)\n");
  scanf("%s", buff);
  while(strcmp("o",buff) != 0 && strcmp("O",buff) != 0 && strcmp("n",buff) != 0 && strcmp("N",buff) != 0){
    printf("Entrée incorrecte\n");
    memset(buff, 0, 256);
    printf("Voulez vous redéfinir votre identifiant? (o/n)\n");
    scanf("%s", buff);
  }
  if(strcmp("o",buff) == 0 || strcmp("O",buff) == 0){
    memset(buff, 0, 256);
    memset(id, '#', 8);
    printf("Entrez le nouvel identifiant :\n");
    scanf("%s", buff);
    memcpy(id, buff, 8);
  } */
  printf("INFO UTILISATEUR\n");
  printf("Port: %d\n",port_gest);
  gest_ip[10] = '\0';
  printf("Addresse : %s\n",gest_ip);

  socketsama = socket(AF_INET, SOCK_STREAM, 0);
  if (socketsama == -1){
      printf("erreur socket register \n");
      exit(0);
  }
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port_gest);
  inet_aton(gest_ip, &serveraddr.sin_addr);
  int r = connect(socketsama,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr_in));
  printf("Waiting...\n");
  
  if (r!=-1){
      while (1){
          memset(buff, 0, 256);
          printf("Que voulez vous faire? (MESS/LAST/EXIT)\n");
          scanf("%s", buff);
          while(strcmp("MESS",buff) != 0 && strcmp("LAST",buff) != 0 && strcmp("EXIT",buff) != 0){
            printf("Entrée incorrecte\n");
            memset(buff, 0, 256);
            printf("Que voulez vous faire? (MESS/LAST/EXIT)\n");
            scanf("%s", buff);
          }
          if(strcmp("EXIT",buff) == 0){
            close(socketsama);
            exit(EXIT_SUCCESS);
          }
          
          char tosend[155];
          memset(tosend,0,155);
          
          if(strcmp("MESS",buff) == 0){
            memset(tosend, '#', 154);
            memcpy(tosend, "MESS ", 5);
            memcpy(tosend+5, id, 8);
            tosend[13] = ' ';
            memset(buff, 0, 256);
            printf("Entrez votre message (Ctrl+D lorsque vous avez fini) \n");
            read(STDOUT_FILENO, buff, 140);
            if(strlen(buff)<139){
              memcpy(tosend+14, buff, strlen(buff));
              memcpy(tosend+strlen(buff)+14, "\r\n", 2);
            } else {
              memcpy(tosend+14, buff, 138);
              tosend[152] = '\r';
              tosend[153] = '\n';
            }
            //printf("%s\n",tosend);
            send(socketsama, tosend, strlen(tosend), 0);

          }

          if(strcmp("LAST",buff) == 0){
            printf("Combien de messages voulez vous récupérer? (1-1000)\n");
            scanf("%s", buff);
            int n = atoi(buff);
            while( n<0 || n>1000 ){
              printf("Entrée incorrecte\n");
              memset(buff, 0, 256);
              printf("Combien de messages voulez vous récupérer? (1-1000)\n");
              scanf("%s", buff);
              n = atoi(buff);
            }
            int no = n;
            memcpy(tosend, "LAST ", 5);
            tosend[5] = '0'+n/100;
            n = n%100;
            tosend[6] = '0'+n/10;
            n = n%10;
            tosend[7] = '0'+n;
          //  printf("LAST %s\n",tosend);
            memcpy(tosend+8, "\r\n", 2);
            send(socketsama, tosend, strlen(tosend), 0);
            printf("Message envoyé \n");
            for (int i = 0; i < no; i++)
            {
                char buffer[MAXLINE];
                int reception = recv(socketsama, buffer, sizeof(buffer), 0);
                printf("%d : ",no - i);
                write(STDOUT_FILENO, (const char *)buffer, reception);
                printf("\n");

            }
          }

          memset(buff, 0, 256);
          memset(tosend, 0, 154);

    }
    close(socketsama);
    return 0;
  }
}