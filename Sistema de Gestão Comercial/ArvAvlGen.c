#include <stdio.h>
#include <stdlib.h> /*malloc - free*/
#include "ArvAvlGen.h"

struct noAVL{
    int altd, alte;
    void* info;
    struct noAVL* dir;
    struct noAVL* esq;
};

/**CRIAR**/
static ArvAVL* avl_criaNO()
{
    ArvAVL* no = (ArvAVL*) malloc(sizeof(ArvAVL));
    return no;
}

/**ROTACIONAR À ESQUERDA**/
static ArvAVL* avl_rotacaoEsquerda(ArvAVL* aux)
{
    ArvAVL *aux1, *aux2;
    aux1 = aux->dir;
    aux2 = aux1->esq;
    aux->dir = aux2;
    aux1->esq = aux;
    if(aux->dir == NULL)
        aux->altd = 0;
    else if(aux->dir->alte > aux->dir->altd)
        aux->altd = aux->dir->alte+1;
    else
        aux->altd = aux->dir->altd+1;

    if(aux1->esq->alte > aux1->esq->altd)
        aux1->alte = aux1->esq->alte+1;
    else
        aux1->alte = aux1->esq->altd+1;
    return aux1;
}

/**ROTACIONAR À DIREITA**/
static ArvAVL* avl_rotacaoDireita(ArvAVL* aux)
{
    ArvAVL *aux1, *aux2;
    aux1 = aux->esq;
    aux2 = aux->dir;
    aux->esq = aux2;
    aux1->dir = aux;
    if(aux->esq == NULL)
        aux->alte = 0;
    else if(aux->esq->alte > aux->esq->altd)
        aux->alte = aux->esq->alte+1;
    else
        aux->alte = aux->esq->altd+1;

    if(aux1->dir->alte > aux1->dir->altd)
        aux1->altd = aux1->dir->alte+1;
    else
        aux1->altd = aux1->dir->altd+1;
    return aux1;
}

/**BALANCEAR**/
static ArvAVL* avl_balanceamento(ArvAVL* aux)
{
    int d, df;
    d = aux->altd - aux->alte;
    if(d == 2)
    {
        df = aux->dir->altd - aux->dir->alte;
        if(df >= 0)
        {
            aux = avl_rotacaoEsquerda(aux);
        }
        else
        {
            aux->dir = avl_rotacaoDireita(aux->dir);
            aux = avl_rotacaoEsquerda(aux);
        }
    }
    else if(d == -2)
    {
        df = aux->esq->altd - aux->esq->alte;
        if(df <= 0)
        {
            aux = avl_rotacaoDireita(aux);
        }
        else
        {
            aux->esq = avl_rotacaoEsquerda(aux->esq);
            aux = avl_rotacaoDireita(aux);
        }
    }
    return aux;
}

///INSERIR
ArvAVL* avl_inserir(ArvAVL *aux, void* dado, int (*cmp) (void*, void*))
{
    ArvAVL *novo;
    if(aux == NULL)
    {
        novo = avl_criaNO();
        novo->info = dado;
        novo->altd = 0;
        novo->alte = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        aux = novo;
    }
    else if(cmp(dado,aux->info) < 0)
    {
        aux->esq = avl_inserir(aux->esq, dado, cmp);
        if(aux->esq->altd > aux->esq->alte)
            aux->alte = aux->esq->altd + 1;
        else
            aux->alte = aux->esq->alte + 1;
        aux = avl_balanceamento(aux);
    }
    else
    {
        aux->dir = avl_inserir(aux->dir, dado, cmp);
        if(aux->dir->altd > aux->dir->alte)
            aux->altd = aux->dir->altd + 1;
        else
            aux->altd = aux->dir->alte + 1;
        aux = avl_balanceamento(aux);
    }
    return aux;
}

/**CONSULTAR**/
int avl_consultar(ArvAVL* aux, void* dado, int achou, int (*cmp) (void*, void*))
{
    if(aux != NULL && achou == 0)
    {
        if(cmp(dado, aux->info) == 0)
            achou = 1;
        else if(cmp(dado, aux->info) < 0)
            achou = avl_consultar(aux->esq, dado, achou, cmp);
        else
            achou = avl_consultar(aux->dir, dado, achou, cmp);
    }
    return achou;
}

///EDITAR DADOS
ArvAVL* avl_edita(ArvAVL* aux, void* dado, void* dado1, void* dado2, void (*cb) (void*, void*, void*), int (*cmp) (void*, void*))
{
    if(cmp(dado, aux->info) == 0)
    {
        cb(dado1, dado2, aux->info);
    }
    else if(cmp(dado,aux->info) < 0)
    {
        aux->esq = avl_edita(aux->esq, dado, dado1, dado2, cb, cmp);
    }
    else
    {
        aux->dir = avl_edita(aux->dir, dado, dado1, dado2, cb, cmp);
    }
    return aux;
}

///IMPRIMIR COM A NOTACAO
void avl_percorreNE(ArvAVL *aux, void (*cb) (void*))
{
    printf("<");
    if(aux != NULL)
    {
        cb(aux->info);
        avl_percorreNE(aux->esq, cb);
        avl_percorreNE(aux->dir, cb);
    }
    printf(">");
}

///IMPRIMIR EM ORDEM
void avl_percorreEmOrdem(ArvAVL *aux, void* dado, void (*cb) (void*,void*))
{
    if(aux != NULL)
    {
        avl_percorreEmOrdem(aux->esq, dado, cb);
        cb(aux->info, dado);
        avl_percorreEmOrdem(aux->dir, dado, cb);
    }
}

///REMOVER
ArvAVL* avl_remover(ArvAVL *aux, void* dado, int (*cmp) (void*, void*), void (*cb) (void*))
{
    ArvAVL *p, *p2;
    if(cmp(dado, aux->info) == 0)
    {
        if(aux->esq == aux->dir) //o elemento a ser removido não tem filhos
        {
            cb(aux->info);
            free(aux);
            return NULL;
        }
        else if(aux->esq == NULL) // o elemento a ser removido não tem filho para a esquerda
        {
            p = aux->dir;
            cb(aux->info);
            free(aux);
            return p;
        }
        else if(aux->dir == NULL) // o elemento a ser removido não tem filho para a direita
        {
            p = aux->esq;
            cb(aux->info);
            free(aux);
            return p;
        }
        else // o elemento a ser removido tem filhos para ambos os lados
        {
            p2 = aux->dir;
            p = aux->dir;
            while(p->esq != NULL)
            {
                p = p->esq;
            }
            p->esq = aux->esq;
            cb(aux->info);
            free(aux);
            return p2;
        }
    }
    else if(cmp(dado,aux->info) < 0)
        aux->esq = avl_remover(aux->esq, dado, cmp, cb);
    else
        aux->dir = avl_remover(aux->dir, dado, cmp, cb);
    return aux;
}

///ATUALIZAR
ArvAVL* avl_atualiza(ArvAVL *aux)
{
    if(aux != NULL)
    {
        aux->esq = avl_atualiza(aux->esq);
        if(aux->esq == NULL)
            aux->alte = 0;
        else if(aux->esq->alte > aux->esq->altd)
            aux->alte = aux->esq->alte + 1;
        else
            aux->alte = aux->esq->altd + 1;

        aux->dir = avl_atualiza(aux->dir);
        if(aux->dir == NULL)
            aux->altd = 0;
        else if(aux->dir->alte > aux->dir->altd)
            aux->altd = aux->dir->alte + 1;
        else
            aux->altd = aux->dir->altd + 1;
        aux = avl_balanceamento(aux);
    }
    return aux;
}

///DESALOCAR
void avl_desalocar(ArvAVL* aux, void (*cb) (void*))
{
    if(aux != NULL)
    {
        avl_desalocar(aux->esq, cb);
        avl_desalocar(aux->dir, cb);
        cb(aux->info);
        free(aux);
    }
}
