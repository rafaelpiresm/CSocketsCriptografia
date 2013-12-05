#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 4096 /*tamanho máximo de entrada*/
#define SERV_PORT 3000 /*porta*/

char *cifra_mensagem(char *palavra, char *chave, int tamanho)
{
    //alocando memória dinamicamente para a chave
    char *palavra_cifrada = new char[tamanho];
    int i = 0;
    for(i = 0; i < tamanho; i++)
    {
        //algoritmo para a cifra damensagem
        //C = P + K (mod 26)
        int caractere_cifrado = int(palavra[i]) + int(chave[i]) % 26;
        palavra_cifrada[i] = (char)caractere_cifrado;
    }                   
    return palavra_cifrada;
}

void configura_start_random()
{
    srand(time(NULL));
}

int gera_um_digito_chave ()
{
    int r = 1 + (rand() % 25);
    return r;
}
 
char *gera_chave(char *chave, int tamanho)
{
        int i;
        chave = new char[tamanho];
        for (i = 0; i<tamanho; i++)        
        {
              int digito_randomico = gera_um_digito_chave();                    
            chave[i] = (char)digito_randomico;        
        }                        
        return chave;
}


int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];    
    
    if (argc !=2) 
    {
        perror("Use da seguinte forma: client <IP do servidor>");
        exit(1);
    }

    //Criando socket para o cliente    
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) 
    {
        perror("Problema criando o socket");
        exit(2);
    }

    //configurando o socket com IP e porta
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons(SERV_PORT); 

    //fazendo a conexão com o servidor
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
        //configura função randômica para geração automática da chave
        configura_start_random();        

        //gera a chave de acordo com o tamanho da entrada
        char *chave = gera_chave(chave,strlen(sendline));

        //cifra a mensagem informada de acordo com a chave gerada
        char *palavra_cifrada = cifra_mensagem(sendline,chave,strlen(sendline));   
        printf("A palavra cifrada é: %s\n",palavra_cifrada);
        printf("A chave é: %s\n",chave);

        //envio da mensagem cifrada
        int qtd_data_received = send(sockfd, palavra_cifrada, MAXLINE, 0);

        if (qtd_data_received > 0)
        	printf("A palavra cifrada foi entregue!\n");
        else
        {
        	printf("A mensagem não pode ser entregue!");
        	exit(3);
        }        

        //envio chave gerada
        qtd_data_received = send(sockfd, chave, MAXLINE, 0);
        if (qtd_data_received > 0)
            printf("A chave foi entregue!\n");
        else
        {
            printf("A chave não pode ser entregue!\n");
            exit(3);
        }                           

        printf("\n\nDigite a mensagem a ser criptografada e enviada ao servidor:\n");

        //desalocando memória alocada dinamicamente para a chave
        delete(chave);
    }
    //saída OK para o SO
    exit(0);
}
