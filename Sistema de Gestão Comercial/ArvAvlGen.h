#ifndef ARVAVLGEN_H_INCLUDED
#define ARVAVLGEN_H_INCLUDED

typedef struct noAVL ArvAVL;

ArvAVL* avl_inserir(ArvAVL *aux, void* dado, int (*cmp) (void*, void*));
ArvAVL* avl_carrega(ArvAVL* aux, FILE* fp, void* (*cb) (void*), int (*cmp) (void*, void*));
int avl_consultar(ArvAVL* aux, void* dado, int achou, int (*cmp) (void*, void*));
void avl_percorreEmOrdem(ArvAVL *aux, void* dado, void (*cb) (void*, void*));
ArvAVL* avl_remover(ArvAVL *aux, void* dado, int (*cmp) (void*, void*), void (*cb) (void*));
ArvAVL* avl_atualiza(ArvAVL *aux);
void avl_desalocar(ArvAVL* aux, void (*cb) (void*));
ArvAVL* avl_edita(ArvAVL* aux, void* dado, void* dado1, void* dado2, void (*cb) (void*, void*, void*), int (*cmp) (void*, void*));
#endif // ARVAVLGEN_H_INCLUDED
