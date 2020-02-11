#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "ArvAvlGen.h"
#include "leitura.h"

struct cliente{
    char nome[81], cpf[CARACTERES_CPF+1];
    float credito;
};

int consultar(void* dado, void* info){
    char* nome = (char*) dado;
    Cliente* c = (Cliente*) info;
    return strcmp(nome, c->nome);
}

///CONSULTAR CLIENTE NA ÁRVORE
int cliente_consultar(ArvAVL* c, void* dado, int achou){
    return avl_consultar(c,dado,achou,consultar);
}

static int consultar_CPF(void* dado, void* info){
    char* cpf = (char*) dado;
    Cliente* f = (Cliente*) info;
    return strcmp(cpf, f->cpf);
}

///CONSULTAR FUNCIONARIO NA ÁRVORE
int cliente_consultarCPF(ArvAVL* c, void* dado, int achou){
    return avl_consultar(c,dado,achou,consultar_CPF);
}

static void venda(void* dado, void* dado1, void* info){
    float* cred = (float*) dado;
    Cliente* c = (Cliente*) info;
    c->credito += *cred;
}

///ATUALIZAR CREDITO DE UM CLIENTE
ArvAVL* cliente_venda(ArvAVL* c, void* nome, void* cred){
    return avl_edita(c,nome,cred,NULL, venda,consultar);
}

static void atualiza(void* dado, void* dado1, void* info){
    float* deb = (float*) dado;
    Cliente* c = (Cliente*) info;
    c->credito -= (*deb);
}

///ATUALIZAR CREDITO DE UM CLIENTE
ArvAVL* cliente_atualizaCredito(ArvAVL* c, void* nome, void* deb){
    return avl_edita(c,nome,deb,NULL,atualiza,consultar);
}

static void imprime(void* info, void* extra){
    Cliente* c = (Cliente*) info;
    printf("\nNOME: %s\n", c->nome);
    printf("CPF: %s\n", c->cpf);
    printf("CRÉDITO: %.2f\n", c->credito);
}

///IMPRIMIR OS DADOS DOS CLIENTES
void cliente_imprime(ArvAVL* c){
    avl_percorreEmOrdem(c,NULL,imprime);
}

static Cliente* cria(char* nome, char* cpf, float cred){
    Cliente* c = (Cliente*) malloc(sizeof(Cliente));
    strcpy(c->nome, nome);
    strcpy(c->cpf, cpf);
    c->credito = cred;
    return c;
}

static int inserir(void* dado, void* cliente){
    Cliente* c1 = (Cliente*) dado;
    Cliente* c2 = (Cliente*) cliente;
    return strcmp(c1->nome, c2->nome);
}

///INSERIR UM CLIENTE NA ÁRVORE
ArvAVL* cliente_inserir(ArvAVL* c, char* nome, char* cpf, float cred){
    c =  avl_inserir(c, cria(nome,cpf,cred), inserir);
    return c;
}

///CARREGAR TODOS OS CLIENTES DO ARQUIVO NA ÁRVORE
ArvAVL* cliente_carrega(ArvAVL* c, FILE* fp){
    char linha[150];
    while(fgets(linha,150,fp) != NULL){
        char nome[81], cpf[CARACTERES_CPF+1];
        float cred;
        sscanf(linha,"%80[^\t]\t%11[^\t]\t%f",nome, cpf, &cred);
        c =  cliente_inserir(c,nome,cpf,cred);
    }
    return c;
}

static void salva(void* info, void* fp){
    Cliente* f = (Cliente*) info;
    FILE* arq = (FILE*) fp;
    fprintf(arq,"%s\t%s\t%.2f\n",f->nome,f->cpf,f->credito);
}

///SALVAR DADOS DE TODOS OS FUNCIONARIOS NO ARQUIVO
void cliente_salva(FILE* fp, ArvAVL* c){
    avl_percorreEmOrdem(c,fp,salva);
}

///REMOVER CLIENTE DA ÁRVORE
ArvAVL* cliente_remover(ArvAVL* c, char* nome){
    c =  avl_remover(c,nome,consultar,free);
    return avl_atualiza(c);
}

///VERIFICAR SE ÁRVORE CLIENTE VAZIA
int cliente_vazia(ArvAVL* c){
    return (c == NULL);
}

///LIBERAR ÁRVORE FUNCIONÁRIO
void cliente_libera(ArvAVL* c){
    avl_desalocar(c,free);
}
