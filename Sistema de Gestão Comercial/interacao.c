#include <stdio.h>
#include <stdlib.h> /* strtod */
#include <string.h> /* strlen - strcpy */
#include <ctype.h>  /* isalpha */
#include <stdarg.h> /* var_list - var_start - var_arg - var_end */
#include "interacao.h"

void apresenta_programa(char* msg){
    printf("%s\n",msg);
}

void mensagem_despedida(char* msg){
    printf("\n%s\n",msg);
}

void limpa_tela(void){
    system("cls");
}

void limpa_buffer(void){
	int valorLido;
    do{
        valorLido = getchar();
    }while ((valorLido != '\n') && (valorLido != EOF));
}

int le_opcao(int menor_valor, int maior_valor){
    int op;
        while(1){
            printf("\nDigite sua opcao: ");
            op=getchar();
            if(op>=menor_valor && op<=maior_valor){
                limpa_buffer();
                break;
            }else{
                printf("\nOpcao Invalida. Tente Novamente");
                printf("\nA opcao deve estar entre %c e %c. \n",menor_valor, maior_valor);
                limpa_buffer();
            }
        }
	return op;
}

char* le_string(void){
    char aux[101];
    scanf(" %100[^\n]", aux);
	int n = strlen(aux); //calcula a quantidade de caracteres inseridos na string
    char* string = (char*) malloc((n+1)*sizeof(char));
    strcpy(string, aux);
    return string;
}

double le_double(void){
    double v;
    char* str = le_string();
	int i = 0;
	while(str[i] != '\0'){
        if(isalpha(str[i]) != 0) //retorna 0 se caracter é numero
            return -1;
        i++;
	}
	v = strtod(str, NULL); //Converte pra double a string até encontrar um caracter
	return v;
}

int le_inteiro(void){
    int v;
    char* str = le_string();
	int i = 0;
	while(str[i] != '\0'){
        if(isalpha(str[i]) != 0) //retorna 0 se caracter é numero
            return -1;
        i++;
	}
	v = strtol(str, NULL, 10); //Converte pra long a string até encontrar um caracter
	return v;
}

void apresenta_menu(int n_itens, int menor_opcao, ...){
	int i;
	va_list argumentos;
	va_start(argumentos,menor_opcao);
	for(i = 0;i<n_itens;++i){
		printf("%c-%s\n",menor_opcao++,va_arg(argumentos, char *));
	}
	va_end(argumentos);
}
