//fonte do client
// 1 - na primeira conexão receberá uma chave pública e irá mantê-la
// 2 - recebe texto através da entrada padrão  (scanf)
// 3 - usa os algorimos para criptografar a mensagem
// 4 - conecta no server e entrega a mensagem


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];

    //basic check of the arguments
    //additional checks can be inserted
    if (argc !=2) 
    {
        perror("Use da seguinte forma: TCPClient <IP do servidor>");
        exit(1);
    }

    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) 
    {
        perror("Problema criando o socket");
        exit(2);
    }

    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

    //Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) 
    {
        perror("Problema na conexão com o servidor");
        exit(3);
    }
    else
    {
    	printf("\nConexão estabelecida com sucesso!\n");
    	printf("Host: %s",argv[1]);
    }
    printf("\n\nDigite a mensagem a ser criptografada e enviada ao servidor: ");
    while (fgets(sendline, MAXLINE, stdin) != NULL) 
    {
        int qtd_data_received = send(sockfd, sendline, strlen(sendline), 0);
        if (qtd_data_received > 0)
        	printf("A mensagem foi entregue!");
        else
        {
        	printf("A mensagem não pode ser entregue!");
        	exit(3);
        }
        printf("\n\nDigite a mensagem a ser criptografada e enviada ao servidor: ");

        /*if (recv(sockfd, recvline, MAXLINE,0) == 0)
        {
            //error: server terminated prematurely
            perror("O servidor encerrou prematuramente.");
            exit(4);
        }*/
        /*printf("%s\n", "String received from the server: ");
        fputs(recvline, stdout);*/
    }

    exit(0);
}
