//fonte do server
//1 - ficará escutando initerruptamente a conexão do client
//2 - se receber um pedido de geração de chave pública, entregará ao client uma nova chave pública
//3 - se receber uma mensagem criptografada, irá exibir em tela a mensagem descriptografada

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define MAX_CONNECTIONS 8 /*maximum number of client connections */

void clean_buf(char *buf)
{
	int i;
	for(i = 0; i < MAXLINE; i++)
		buf[i] = '\0';
}
int main (int argc, char **argv)
{
   int listenfd, connfd, n;
   socklen_t clilen;
   char buf[MAXLINE];
   struct sockaddr_in cliaddr, servaddr;

   //creation of the socket
   listenfd = socket (AF_INET, SOCK_STREAM, 0);

   //preparation of the socket address
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(SERV_PORT);

   bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

   listen(listenfd, MAX_CONNECTIONS);

   printf("%s\n","Server online... Aceitando novas conexões...");

   for ( ; ; ) 
   {    
       clilen = sizeof(cliaddr);
       connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
       printf("%s\n","Received request...");

       while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  
       {
           printf("%s","Texto recebido: ");
           puts(buf);           
           clean_buf(buf);
           //send(connfd, buf, n, 0);
       }

       if (n < 0) 
       {
           perror("Falha na leitura");
           exit(1);
       }

       close(connfd);
    }
   //close listening socket
   close (listenfd);
}
