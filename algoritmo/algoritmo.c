/* fonte do algoritmo de criptografia */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "algoritmo.h"

void 
pim_configura_start_random()
{
     srand(time(NULL));
}

int 
pim_gera_um_digito_chave ()
{
     int r = 1 + (rand() % 25);
     return r;
}
 
char* 
pim_gera_chave(int tamanho)
{
     int i;
     char* chave = (char *)malloc(sizeof(char) * tamanho);

     for (i = 0; i<tamanho; i++)        
     {
        	  int digito_randomico = pim_gera_um_digito_chave();                	
		  chave[i] = (char) digito_randomico;        
     }                        

     return chave;       
}

char* 
pim_cifra_mensagem(char *palavra, char *chave, int tamanho)
{
     char* palavra_cifrada = (char *)malloc(sizeof(char) * tamanho);
     int i = 0;
     for(i = 0; i < tamanho; i++)
     {
	  /* C = P + K (mod 26) */
	  int caractere_cifrado = (int) palavra[i] + (int) chave[i] % 26;
	  palavra_cifrada[i] = (char) caractere_cifrado;
     }    		   		

     return palavra_cifrada;
}

char* 
pim_decifra_mensagem(char *chave, char *palavra_cifrada, int tamanho)
{
     char *palavra_decifrada = (char *) malloc(sizeof(char) * tamanho);
     int i = 0;
     for(i = 0; i < tamanho; i++)
     {
	  int c = (int) chave[i];
	  int p = (int) palavra_cifrada[i];
	  int caractre_decifrado = 0;

	  if (c > p)
	       caractre_decifrado = c - p  + 26 % 26; 
	  else
	       caractre_decifrado = p - c  + 26 % 26;

	  palavra_decifrada[i] = (char)caractre_decifrado;    		
     }     
     return palavra_decifrada;  
}

