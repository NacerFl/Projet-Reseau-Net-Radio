#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <netdb.h>


#define SOCKETERROR (-1)
#define BUFSIZE 1024
#define SERVER_BACKLOG 1

typedef struct sockaddr_in SA;
typedef struct sockaddr SE;

char * msg_list[1000] = {"IDENTIF# MESSAGE1#R\rnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"message spécial",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"message spécial",
"IDENTIF# MESSAGE1#R\tnfzueof\nJe vous aime\r\n###########################################################################################################"};
int last_msg = 0;

int modulo(int tomod, int mod){
  while(tomod <0)
    tomod+=mod;
  return tomod%mod;
}

int power(int a, int b){
  int c = 1;
  for(int i=0; i<b; i++)
    c = c*a;
  return c;
}

void * flee(void *useless){
    char command[64];
    char * lecture = malloc(64);
    printf("HELLO\n");

    while(1){

        printf("Commande :\n");
        scanf("%s", lecture);
        memcpy(command, lecture, 64);
        //write(STDOUT_FILENO, command, 64);
        if(strcmp(command, "exit") ==0||strcmp(command, "Exit") == 0)
            exit(EXIT_SUCCESS);
    }
    return NULL;
}

void int_to_char(int i,char s[4]){
  s[0] = '0' + ((int) i/1000);
  s[1] = '0' + ((int)(i%1000)/100);
  s[2] = '0' + ((int)(i%100)/10);
  s[3] = '0' + (i%10);


}

void handle_connection(int Clientsocket);
void *multi_msg(void * useless);
int handle_msg(char message[BUFSIZE]);
int checkerror(int exp, const char *msg);
void *chatting(void *arg);
void getlastmsg(int n);
void *handle_register(void *arg);

char *idMaster = "# Peste#";
int main(int argc, char **argv){

    //memset(id,'#',sizeof(char)*8);
    if(argc == 2) memcpy(idMaster,argv[1],sizeof(char)*strlen(argv[1]));

    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;

    gethostname(hostbuffer, sizeof(hostbuffer));

    host_entry = gethostbyname(hostbuffer);

    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));

    printf("*********************************\n");
    printf("Hostname: %s\n", hostbuffer);
    printf("Addresse machine: %s\n", IPbuffer);

    int portdifu = 2727;
    int portaffficher = 1717;
    char *adressedifu = "225.1.2.4";
    char portbis[4];
    char port1[4];

    int_to_char(portdifu,portbis);
    int_to_char(portaffficher,port1);



    printf("my port d'ecoute %s \n", port1);
    printf("addresse de diffusion : %s\n",adressedifu);
    printf("Mon port de diffusion: %d\n",portdifu);
    printf("*********************************\n");


    pthread_t th, th0, th1, th2;
    pthread_create(&th2,NULL,handle_register,NULL);
    pthread_create(&th,NULL,multi_msg,NULL);
    pthread_create(&th0,NULL,flee,NULL);
    pthread_create(&th1,NULL,chatting,NULL);

    pthread_join(th, NULL);
    pthread_join(th0, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2,NULL);

}

//S'occupe du Gestionnaire
void* handle_register(void* args){
  FILE *fptr;
  char * buff="";
  char gest_ip[15], gest_port[5]; // variables du gestionnaire
  char *adressedifu2 = "225.001.002.004";
  char *portbis = "1234";
  char *port1 = "5555";
  char info [58];
  memset(info,0,58 * sizeof(char));
  memcpy(info,"REGI ",sizeof(char)*5);
  memcpy(info + 5,idMaster,sizeof(char)*8);
  memcpy(info + 13, " ", sizeof(char));
  memcpy(info + 14 ,adressedifu2,sizeof(char) * 15);
  memcpy(info + 29, " ", sizeof(char));
  memcpy(info + 30,portbis,sizeof(char) *4);
  memcpy(info + 34, " ", sizeof(char));
  memcpy(info + 35,"127.000.000.001",sizeof(char) * 15);
  memcpy(info + 50, " ", sizeof(char));
  memcpy(info + 51,port1,sizeof(char) * 4);
  info[55] = '\r';
  info[56] = '\n';
  printf("%s\n",info);

  int Mastersocket ;
  struct sockaddr_in  serveraddr;

  while ((fptr = fopen("./gestionnaire.txt", "r")) == NULL)
  {
    printf("Fichier de Gestionnaire inexistant. Veuillez lancer Gestionnaire.java avant\n");
    scanf("%s\n", buff);
  }
  fgets(gest_ip,sizeof(char)*15,fptr);
  fgets(gest_port,sizeof(char)*5,fptr);
  int port_gest = (gest_port[0]-'0')*1000 + (gest_port[1]-'0')*100 + (gest_port[2]-'0')*10 + (gest_port[3]-'0');
  printf("INFO GESTIONNAIRE RECUP\n");
  printf("Port du gestionnaire: %d\n",port_gest);
  gest_ip[10] = '\0';
  printf("Addresse du Gestionnaire : %s\n",gest_ip);

  //int option = 1;
  Mastersocket = socket(AF_INET, SOCK_STREAM, 0);
  //setsockopt(Mastersocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  last_msg = 0;
  if (Mastersocket == -1){
      printf("erreur socket register \n");
      exit(0);
  }
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port_gest);
  inet_aton(gest_ip, &serveraddr.sin_addr);
  int r = connect(Mastersocket,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr_in));

  if(r != -1){
  char buffer[BUFSIZE];
  printf("Connecté au Gestionnaire\n");
  int rec;
  do{
  memset(buffer,0,strlen(buffer));
  send(Mastersocket, info, strlen(info), 0);
  printf("REGI send\n");
  rec = recv(Mastersocket,buffer,sizeof(buffer),0);
  buffer[rec]= '\0';
  sleep(5);
  }while(strcmp(buffer,"")==0 || strcmp(buffer,"RENO") == 0 );


if(strstr(buffer,"REOK") != NULL){
    while (1)
    {
        rec = recv(Mastersocket,buffer,sizeof(buffer),0);
        buffer[rec]= '\0';
        if(strstr(buffer,"RUOK") != NULL){
        send(Mastersocket, "IMOK\r\n", strlen("IMOK\r\n"), 0);
        printf("RUOK reçue\n");
        }

    }
}
}
return 0;
}



int checkerror(int exp, const char *msg){
if (exp == SOCKETERROR){
  perror(msg);
  exit(1);
}
return exp;
}

//S'occupe des connection TCP avec l'Utilisateur ex : LAST mess , MESS
void handle_connection(int Clientsocket){
  char buffer[BUFSIZE];
  int boolean = 1;

  read(Clientsocket,buffer,sizeof(buffer));
  boolean = handle_msg(buffer);
  if(boolean != 0){ // si handl0e message est un int donc un last message
    getlastmsg(boolean);//faut que je stock les message pour send
    char * full_msg = malloc(149 * sizeof(char));                               //On prend la somme id + message
    char * content = malloc(140 * sizeof(char));
    for(int i = 1000 - boolean; i<1000; i++){
      full_msg = msg_list[modulo(last_msg +i, 1000)];                         //On lit tous les messages en commençant par celui à la case last_msg
      content = memcpy(content, full_msg, 140);
      send(Clientsocket, content, strlen(content), 0);

      }

    }

  close(Clientsocket);
  printf("Closing connexion with Utilisateur\n");
}

void display_msg(char content[140]){                                    //Affiche la chaîne de caractère suivant la structure demandée des messages

  for(int i=0; i<140; i++){                                                   //On lit le message caractère par caractère
    if((content[i] == '\r') && (i<139))                                     //Si on tombe sur un \r puis un \n, on stoppe l'affichage puisqu'on terminé le message
      if(content[i+1] =='\n')
    break;
    printf("%c", content[i]);                                               //Sinon on affiche le caractère
  }
  write(STDOUT_FILENO, "\n",1);                                               //Et quand on a fini, on revient à la ligne

}

void display_list(){                                                    //Affiche les messages dans la liste
    printf("Messages stockés : \n");
    char * full_msg = malloc(149 * sizeof(char));                               //On prend la somme id + message
    char * content = malloc(140 * sizeof(char));

    for(int i = 0; i<1000; i++){
        full_msg = msg_list[modulo(last_msg +i, 1000)];                         //On lit tous les messages en commençant par celui à la case last_msg
        if(full_msg == NULL)
          continue;

        content = memcpy(content, full_msg+9, 140);
        printf("%d : ",i);                               //On isole le message en lui même
        for(int i = 0; i<8; i++){
            char c = full_msg[i];
            if(c != '#')
                write(STDOUT_FILENO,&c, 1);                                 //On affiche l'identifiant de l'emetteur
        }
        write(STDOUT_FILENO," : ", 3);
        display_msg(content);                                                       //Puis on appelle display_msg pour afficher le message
    }
    write(STDOUT_FILENO, "\n\n\n",3);                                                   //Et on n'oublie pas de revenir à la ligne
}

void getlastmsg(int n){                                                    //Affiche les messages dans la liste
  char * full_msg = malloc(149 * sizeof(char));                               //On prend la somme id + message
  char * content = malloc(140 * sizeof(char));

  for(int i = 1000 - n; i<1000; i++){
    full_msg = msg_list[modulo(last_msg +i, 1000)];                         //On lit tous les messages en commençant par celui à la case last_msg
    if(full_msg == NULL)
      continue;

    content = memcpy(content, full_msg, 140);
    //printf("%d : ",i);                               //On isole le message en lui même
   //display_msg(content);                                                   //Puis on appelle display_msg pour afficher le message
  }
  printf("*****Les messages demandés ont été envoyés*******\n");
  write(STDOUT_FILENO, "\n",1);                                               //Et on n'oublie pas de revenir à la ligne
}


int handle_msg(char message[BUFSIZE]){                                  //Fonction qui gère le message

  char * head = malloc(4*sizeof(char));
  memcpy(head,message,4);
//  printf("message %s\n",message);

  char c = '0';

  if(strcmp(head,"LAST")==0){                                                 //Reçoit une demande de renvoyer des messages
    int no = 0;
    for(int i =0; i<3; i++){
      no += (message[5+i]-c) * power(10,(2-i));  //Calcule le nombre de messages à renvoyer
    }
    printf("Nombre de messages demandés par l'utilisateur : %d\n",no);
    return no;

  }else if(strcmp(head,"MESS")==0 && message[4]==' ' && message[13]==' '){       //Reçoit un message de la part de l'utilisateur
    char rest[149];
    memcpy(rest, message + (5*sizeof(char)),129);
    msg_list[last_msg +10] = rest;
    last_msg ++;
  }else
    printf("Received invalid message\n");

  return 0;
}



void *multi_msg(void * useless){
  int mastersocket=socket(AF_INET,SOCK_DGRAM,0);
  struct addrinfo *first_info;
  struct addrinfo hints;
  char * full_msg = malloc(149 * sizeof(char));                               //On prend la somme id + message
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype=SOCK_DGRAM;
  int r=getaddrinfo("225.1.2.4","2727",NULL,&first_info);
  if(r==0){
    if(first_info!=NULL){
      struct sockaddr *saddr=first_info->ai_addr;
      while(1){
        sleep(1);
        full_msg = msg_list[last_msg];                        //On lit tous les messages en commençant par celui à la case last_msg
        if(full_msg == NULL){
         // printf("error message");
        }else
          sendto(mastersocket,full_msg,strlen(full_msg),0,saddr,(socklen_t)sizeof(struct sockaddr_in));
        last_msg = modulo(last_msg +1,1000);
      }
    }
  }
  return NULL;
}

void *chatting(void *arg){
    int Mastersocket , Clientsocket , addr_size;
    int port = 1111;

    SA serveraddr, clientaddr;
    int option = 1;
    Mastersocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(Mastersocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    last_msg = 0;
    if (Mastersocket == -1){
        printf("erreur socket \n");
        exit(0);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);
    if (bind(Mastersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
        perror("ERROR in bindinguh IN TCP\n");
        exit(1);
    }

    if (listen(Mastersocket,5) != 0) {
        printf("Error while listening");
    }
    addr_size = sizeof(SA);
    a:
    if  ((Clientsocket = accept(Mastersocket,(SE*)&clientaddr,(socklen_t*)&addr_size)) < 0)
       printf("error connexion\n");
    printf("Connection à l'utilisateur...\n");

    if(fork() == 0){
       handle_connection(Clientsocket);
       exit(EXIT_SUCCESS);
    }else{
      goto a;
    }
    return NULL;

}
