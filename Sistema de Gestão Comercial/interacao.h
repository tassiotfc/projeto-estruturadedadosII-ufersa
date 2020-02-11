#ifndef INTERACAO_H_INCLUDED
#define INTERACAO_H_INCLUDED

void apresenta_programa(char* msg);
void mensagem_despedida(char* msg);
void limpa_tela(void);
void limpa_buffer(void);
int le_opcao(int menor_valor, int maior_valor);
char* le_string(void);
double le_double(void);
int le_inteiro(void);
void apresenta_menu(int n_itens, int menor_opcao, ...);

#endif // INTERACAO_H_INCLUDED
