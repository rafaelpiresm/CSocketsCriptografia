//fonte do algoritmo de criptografia
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int MAX = 20;

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
 
char *cifra_mensagem(char *palavra, char *chave, int tamanho)
{
	char * palavra_cifrada = new char[tamanho];
	int i = 0;
	for(i = 0; i < tamanho; i++)
   	{
   		//C = P + K (mod 26)
    	int caractere_cifrado = int(palavra[i]) + int(chave[i]) % 26;
   		palavra_cifrada[i] = (char)caractere_cifrado;
   	}    		   		
   	return palavra_cifrada;
}

char *decifra_mensagem(char *chave, char *palavra_cifrada, int tamanho)
{
	char *palavra_decifrada = new char[tamanho];
    int i = 0;
    for(i = 0; i < tamanho; i++)
    {
    	//C = C - K + 26 (mod 26)
    	int c = int(chave[i]);
    	int p = int(palavra_cifrada[i]);
    	int caractre_decifrado = 0;
    	if (c > p)
   			caractre_decifrado = c - p  + 26 % 26; 
   		else
   			caractre_decifrado = p - c  + 26 % 26;
      palavra_decifrada[i] = (char)caractre_decifrado;    		
    }     
    return palavra_decifrada;  
}

int main()
{
    char palavra[MAX];        
    char *palavra_cifrada;
    char *chave;     
    char *palavra_decifrada;
    printf("Digite a palavra: ");
    //fflush(stdin);
    gets(palavra);
    printf("\nA palavra digitada e %s", palavra);
	  int i;
	  configura_start_random();        
    chave = gera_chave(chave,strlen(palavra));
    printf("\nO tamanho da chave eh: %d", strlen(chave));
   	printf("\nA chave e: %s", chave);     	

   	//cifra
   	palavra_cifrada = cifra_mensagem(palavra,chave,strlen(chave));   
    printf("\nA palavra cifrada eh: %s", palavra_cifrada);
    
    //decifra
    palavra_decifrada = decifra_mensagem(chave,palavra_cifrada,strlen(chave));
    printf("\nA palavra decifrada eh: %s", palavra_decifrada);    

    delete(chave);    	
    delete(palavra_cifrada);
    delete(palavra_decifrada);
    printf("\nPressione uma tecla para finalizar...");
    getchar();
    return 0;
}
