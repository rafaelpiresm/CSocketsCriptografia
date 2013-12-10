void pim_configura_start_random();

int pim_gera_um_digito_chave ();

char* pim_gera_chave(int tamanho);

char* pim_cifra_mensagem(char *palavra, char *chave, int tamanho);

char* pim_decifra_mensagem(char *chave, char *palavra_cifrada, int tamanho);
