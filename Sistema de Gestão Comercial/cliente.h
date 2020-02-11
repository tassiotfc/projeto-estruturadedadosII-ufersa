#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "ArvAvlGen.h"
#include "leitura.h"

typedef struct cliente Cliente;

int cliente_consultarCPF(ArvAVL* c, void* dado, int achou);
int cliente_consultar(ArvAVL* c, void* dado, int achou);
ArvAVL* cliente_venda(ArvAVL* c, void* nome, void* cred);
ArvAVL* cliente_atualizaCredito(ArvAVL* c, void* nome, void* deb);
void cliente_imprime(ArvAVL* c);
ArvAVL* cliente_inserir(ArvAVL* c, char* nome, char* cpf, float cred);
ArvAVL* cliente_carrega(ArvAVL* c, FILE* fp);
void cliente_salva(FILE* fp, ArvAVL* c);
ArvAVL* cliente_remover(ArvAVL* c, char* nome);
int cliente_vazia(ArvAVL* c);
void cliente_libera(ArvAVL* c);
#endif // CLIENTE_H_INCLUDED
