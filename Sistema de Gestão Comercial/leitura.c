#include <stdio.h>
#include <string.h> /* strlen */
#include <ctype.h> /* isdigit - isalpha*/
#include "leitura.h"
#include "interacao.h" /* le_string - limpa_buffer - le_double */

static int valida_nome(char* str){
	int i = 0;
	while(str[i] != '\0'){
        if(isalpha(str[i])== 0 && str[i] != ' ') //retorna 0 se caracter é numero
            return 0;
        i++;
	}
	return 1;
}

char* le_nome(char* string){
    char* nome;
    printf("%s: ",string);
    nome = le_string();
    while(valida_nome(nome) == 0){
        limpa_buffer();
        printf("ENTRADA INCORRETA.DIGITE O %s: ",string);
        nome = le_string();
    }
    return nome;
}

static int valida_cpf(char* cpf){
	int i = 0;
	while(isdigit(cpf[i]))
	    i++;
	return i;
}

char* le_cpf(void){
    char* cpf;
    int t_dig;
    printf("CPF ( %d DIGITOS ): ", CARACTERES_CPF);
    cpf = le_string();
    t_dig = valida_cpf(cpf);
    while(t_dig != CARACTERES_CPF){
        limpa_buffer();
        printf("ENTRADA INCORRETA.DIGITE UM CPF COM %d DIGITOS: ",CARACTERES_CPF);
        cpf = le_string();
        t_dig = valida_cpf(cpf);
    }
    return cpf;
}

float le_valor(char* string){
    float v;
    printf("%s: ",string);
    v = le_double();
    while((v<0) || (v == -1)){
        limpa_buffer();
        printf("ENTRADA INCORRETA.DIGITE O %s: ",string);
        v = le_double();
    }
    limpa_buffer();
    return v;
}

int le_senha(int s){
    int senha;
    senha = le_inteiro();
    while((senha != s) || (senha == -1)){
        limpa_buffer();
        printf("ENTRADA INCORRETA.DIGITE A SENHA NOVAMENTE: ");
        senha = le_inteiro();
    }
    limpa_buffer();
    return senha;
}
