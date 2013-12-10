#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../algoritmo/algoritmo.h"

#define MAXLINE 4096 /*tamanho máximo de entrada*/
#define SERV_PORT 3000 /*porta*/

int 
main(int argc, char **argv)
{
     int sockfd;
     struct sockaddr_in servaddr;
     char sendline[MAXLINE];    
     
     if (argc !=2) 
     {
	  perror("Use da seguinte forma: client <IP do servidor>");
	  exit(1);
     }
     /*
     //Criando socket para o cliente    
     */
     if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) 
     {
	  perror("Problema criando o socket");
	  exit(2);
     }
     
     /*
     //configurando o socket com IP e porta
     */
     memset(&servaddr, 0, sizeof(servaddr));
     servaddr.sin_family = AF_INET;
     servaddr.sin_addr.s_addr= inet_addr(argv[1]);
     servaddr.sin_port =  htons(SERV_PORT); 
     
     /*
     //fazendo a conexão com o servidor
     */
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
     
     printf("\n\nDigite a mensagem a ser criptografada e enviada ao servidor:\n");
     while (fgets(sendline, MAXLINE, stdin) != NULL) 
     {
	  char *chave;
	  char *palavra_cifrada;
	  int qtd_data_received;

	  /*
	  //configura função randômica para geração automática da chave
	  */
	  pim_configura_start_random();        
	  
	  /*
	  //gera a chave de acordo com o tamanho da entrada
	  */
	  chave = pim_gera_chave(strlen(sendline));
	  
	  /*
	  //cifra a mensagem informada de acordo com a chave gerada
	  */
	  palavra_cifrada = pim_cifra_mensagem(sendline, chave, strlen(sendline));   

	  printf("A palavra cifrada é: %s\n",palavra_cifrada);
	  printf("A chave é: %s\n",chave);
	  
	  /* envio da mensagem cifrada */
	  qtd_data_received = send(sockfd, palavra_cifrada, MAXLINE, 0);
	  
	  if (qtd_data_received > 0)
	       printf("A palavra cifrada foi entregue!\n");
	  else
	  {
	       printf("A mensagem não pode ser entregue!");
	       exit(3);
	  }        
	  
	  /* envio chave gerada */
	  qtd_data_received = send(sockfd, chave, MAXLINE, 0);
	  if (qtd_data_received > 0)
	       printf("A chave foi entregue!\n");
	  else
	  {
	       printf("A chave não pode ser entregue!\n");
	       exit(3);
	  }                           
	  
	  printf("\n\nDigite a mensagem a ser criptografada e enviada ao servidor:\n");
	  
	  /* desalocando memória alocada dinamicamente para a chave */
	  free(chave);
     }
     /* saída OK para o SO */
     exit(0);
}
