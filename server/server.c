#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*tamanho máximo da entrada*/
#define SERV_PORT 3000 /*porta*/
#define MAX_CONNECTIONS 8 /*número máximo de conexões*/

void clean_entrada(char *buf)
{
        int i;
        for(i = 0; i < MAXLINE; i++)
                buf[i] = '\0';
}

char *decifra_mensagem(char *chave, char *palavra_cifrada, int tamanho)
{  
  //alocando memória dinamicamente para a palavra a ser decifrada
  //char *palavra_decifrada = new char[tamanho];
  char *palavra_decifrada = (char *)malloc(sizeof(char) * MAXLINE);
  int i = 0;
  for(i = 0; i < tamanho; i++)
  {
    //algoritmo para decifrar a mensagem
    //C = C - K + 26 (mod 26)
    int c = int(chave[i]);
    //int c = (int)chave[i];
    int p = int(palavra_cifrada[i]);
    //int p = (int)palavra_cifrada[i];
    int caractre_decifrado = 0;
    if (c > p)
      caractre_decifrado = c - p  + 26 % 26; 
    else
      caractre_decifrado = p - c  + 26 % 26;
      palavra_decifrada[i] = char(caractre_decifrado);
  }     
  return palavra_decifrada;  
}

int main (int argc, char **argv)
{
   int listenfd, connfd, n;
   socklen_t clilen;
   
   char buf[MAXLINE];
   char chave[MAXLINE];

   struct sockaddr_in cliaddr, servaddr;

   //cria o socket
   listenfd = socket (AF_INET, SOCK_STREAM, 0);

   //configura o socket com IP e porta
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(SERV_PORT);

   bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
   
   //faz o server escutar o máximo de MAX_CONNECTIONS
   listen(listenfd, MAX_CONNECTIONS);

   printf("%s\n","Server online... Aceitando novas conexões...");

   clilen = sizeof(cliaddr);
   connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
   printf("%s\n","Conexão recebida... aguardando mensagem...");

   for ( ; ; ) 
   {   
      //recebe a mensagem
      n = recv(connfd, buf, MAXLINE,0);             
      if (n <= 0) 
      {
         perror("Falha na leitura. Encerrando servidor.");
         close(connfd);
         close (listenfd);
         exit(1);
      }

      printf("%s\n","Mensagem criptografada recebida:");
      puts(buf);

      //recebe a chave
      n = recv(connfd, chave, MAXLINE,0);             
       
      //decifra a mensagem
      char *mensagem = decifra_mensagem(chave,buf,strlen(buf));
      //printf("A mensagem decifrada é: \n%s", mensagem);       
      printf("\n\n%s","A mensagem decifrada é: ");       
      puts(mensagem);

      //limpa as variáveis de conteúdo
      clean_entrada(buf);
      clean_entrada(chave);
      clean_entrada(mensagem);

      puts("================================================================");
    }   
   //encerra a conexão
   close(connfd);
   close(listenfd);
}