#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*strcmp - strcpy*/
#include "funcionario.h"
#include "ArvAvlGen.h"
#include "leitura.h"

struct funcionario{
    char nome[81], cpf[CARACTERES_CPF+1],cargo[21];
    float salario;
};

static int consultar(void* dado, void* info){
    char* nome = (char*) dado;
    Funcionario* f = (Funcionario*) info;
    return strcmp(nome, f->nome);
}

///CONSULTAR FUNCIONARIO NA ÁRVORE
int funcionario_consultar(ArvAVL* f, void* dado, int achou){
    return avl_consultar(f,dado,achou,consultar);
}

static int consultar_CPF(void* dado, void* info){
    char* cpf = (char*) dado;
    Funcionario* f = (Funcionario*) info;
    return strcmp(cpf, f->cpf);
}

///CONSULTAR FUNCIONARIO NA ÁRVORE
int funcionario_consultarCPF(ArvAVL* f, void* dado, int achou){
    return avl_consultar(f,dado,achou,consultar_CPF);
}

static void atualiza(void* dado, void* dado1, void* info){
    float* sal = (float*) dado;
    char* cargo = (char*) dado1;
    Funcionario* f = (Funcionario*) info;
    f->salario = *sal;
    strcpy(f->cargo,cargo);
}

///ATUALIZAR SALARIO E CARGO DE UM FUNCIONÁRIO
ArvAVL* funcionario_atualiza(ArvAVL* f, void* nome, void* cargo, void* sal){
    return avl_edita(f,nome,sal,cargo,atualiza,consultar);
}

static void imprime(void* info, void* extra){
    Funcionario* f = (Funcionario*) info;
    printf("\nNOME: %s\n", f->nome);
    printf("CPF: %s\n", f->cpf);
    printf("CARGO: %s\n", f->cargo);
    printf("SALARIO: %.2f\n", f->salario);
}

///IMPRIMIR OS DADOS DOS FUNCIONARIOS
void funcionario_imprime(ArvAVL* f){
    avl_percorreEmOrdem(f,NULL,imprime);
}

static Funcionario* cria(char* nome, char* cpf, char* cargo, float salario){
    Funcionario* f = (Funcionario*) malloc(sizeof(Funcionario));
    strcpy(f->nome, nome);
    strcpy(f->cpf, cpf);
    strcpy(f->cargo, cargo);
    f->salario = salario;
    return f;
}

static int inserir(void* dado, void* funcionario){
    Funcionario* f1 = (Funcionario*) dado;
    Funcionario* f2 = (Funcionario*) funcionario;
    return strcmp(f1->nome, f2->nome);
}

///INSERIR UM FUNCIONARIO NA ÁRVORE
ArvAVL* funcionario_inserir(ArvAVL* f, char* nome, char* cpf, char* cargo, float salario){
    f =  avl_inserir(f, cria(nome,cpf,cargo,salario), inserir);
    return f;
}

///CARREGAR TODOS OS FUNCIONÁRIOS DO ARQUIVO NA ÁRVORE
ArvAVL* funcionario_carrega(ArvAVL* f, FILE* fp){
    char linha[150];
    while(fgets(linha,150,fp) != NULL){
        char nome[81], cpf[CARACTERES_CPF+1], cargo[21];
        float salario;
        sscanf(linha,"%80[^\t]\t%11[^\t]\t%20[^\t]\t%f",nome, cpf, cargo, &salario);
        f =  funcionario_inserir(f,nome,cpf,cargo,salario);
    }
    return f;
}

static void salva(void* info, void* fp){
    Funcionario* f = (Funcionario*) info;
    FILE* arq = (FILE*) fp;
    fprintf(arq,"%s\t%s\t%s\t%.2f\n",f->nome,f->cpf,f->cargo,f->salario);
}

///SALVAR DADOS DE TODOS OS FUNCIONARIOS NO ARQUIVO
void funcionario_salva(FILE* fp, ArvAVL* f){
    avl_percorreEmOrdem(f,fp,salva);
}

///REMOVER FUNCIONÁRIO DA ÁRVORE
ArvAVL* funcionario_remover(ArvAVL* f, char* nome){
    f =  avl_remover(f,nome,consultar,free);
    return avl_atualiza(f);
}

///VERIFICAR SE ÁRVORE FUNCIONARIO VAZIA
int funcionario_vazia(ArvAVL* f){
    return (f == NULL);
}

///LIBERAR ÁRVORE CLIENTE
void funcionario_libera(ArvAVL* f){
    avl_desalocar(f,free);
}
