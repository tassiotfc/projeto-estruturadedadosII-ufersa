#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED
#include "ArvAvlGen.h"
#include "leitura.h"
typedef struct funcionario Funcionario;

int funcionario_consultar(ArvAVL* f, void* dado, int achou);
int funcionario_consultarCPF(ArvAVL* f, void* dado, int achou);
ArvAVL* funcionario_atualiza(ArvAVL* f, void* nome, void* cargo, void* sal);
void funcionario_imprime(ArvAVL* f);
ArvAVL* funcionario_inserir(ArvAVL* f, char* nome, char* cpf, char* cargo, float salario);
ArvAVL* funcionario_carrega(ArvAVL* f, FILE* fp);
void funcionario_salva(FILE* fp, ArvAVL* f);
ArvAVL* funcionario_remover(ArvAVL* f, char* nome);
int funcionario_vazia(ArvAVL* f);
void funcionario_libera(ArvAVL* f);
#endif // FUNCIONARIO_H_INCLUDED
