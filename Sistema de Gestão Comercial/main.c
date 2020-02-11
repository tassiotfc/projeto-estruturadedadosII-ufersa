/********************************************************************************************************
UNIVERSIDADE FEDERAL RURAL DO SEMI-ÁRIDO
BACHARELADO EM TECNOLOGIA DA INFORMAÇÃO
LABORATÓRIO DE ALGORITMOS E ESTRUTURA DE DADOS II
PROF. ME. THIAGO PEREIRA RIQUE
TÁSSIO FERNANDES COSTA
AVALIAÇÃO 3º UNDIDADE: PROJETO - 2016.2 - PROGRAMA PARA GERENCIAR INFORMAÇÕES DE CLIENTES E FUNCIONÁRIOS
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h> /*exit*/
#include <locale.h> /*setlocale*/
#include <conio.h>
#include "ArvAvlGen.h"
#include "cliente.h"
#include "funcionario.h"
#include "interacao.h"
#include "leitura.h"

#define TITULO_ITEM1 "Logar como administrador"
#define TITULO_ITEM2 "Logar como funcionário"
#define TITULO_ITEM3 "Sair do programa"

#define N_ITENS 3
#define ITEM1 '1'
#define ITEM2 '2'
#define ITEM3 '3'

#define TITULO_OPCAO1 "Cadastrar funcionário"
#define TITULO_OPCAO2 "Atualizar dados do funcionário"
#define TITULO_OPCAO3 "Imprimir dados dos funcionarios"
#define TITULO_OPCAO4 "Excluir cadastro do funcionário"
#define TITULO_OPCAO5 "Voltar ao menu principal"
#define TITULO_OPCAO6 "Sair e salvar dados"

#define N_OPCOES 6
#define OPCAO1 '1'
#define OPCAO2 '2'
#define OPCAO3 '3'
#define OPCAO4 '4'
#define OPCAO5 '5'
#define OPCAO6 '6'

#define TITULO_OPTION1 "Cadastrar cliente"
#define TITULO_OPTION2 "Cadastrar compra"
#define TITULO_OPTION3 "Realizar pagamento"
#define TITULO_OPTION4 "Excluir cadastro do cliente"
#define TITULO_OPTION5 "Imprimir dados dos clientes"
#define TITULO_OPTION6 "Voltar ao menu principal"
#define TITULO_OPTION7 "Sair e salvar dados"

#define N_OPTIONS 7
#define OPTION1 '1'
#define OPTION2 '2'
#define OPTION3 '3'
#define OPTION4 '4'
#define OPTION5 '5'
#define OPTION6 '6'
#define OPTION7 '7'

#define SENHA_ADM  54321
#define SENHA_FUNC 12345

int main()
{
    setlocale(LC_ALL,"Portuguese");

    unsigned char op;
	unsigned int saida=0, saida1 = 0, saida2 = 0;
	char *nome,*cpf, *cargo;
	float deb, cred, sal;
    int achou;

	ArvAVL *FUNCIONARIO = NULL;
    int senhaA;
    FILE *funcionario;

	ArvAVL *CLIENTE = NULL;
	int senhaF;
	FILE *cliente;

	funcionario = fopen("funcionario.txt","rt");
    if(funcionario == NULL){
        funcionario = fopen("funcionario.txt","wt");
        if(funcionario == NULL){
            printf("Erro ao abrir arquivo!\n");
            exit(1);
        }
    }
    FUNCIONARIO = funcionario_carrega(FUNCIONARIO, funcionario);

    cliente = fopen("cliente.txt","rt");
    if(cliente == NULL){
        cliente = fopen("cliente.txt","wt");
        if(cliente == NULL){
            printf("Erro ao abrir arquivo!\n");
            exit(1);
        }
    }
    CLIENTE = cliente_carrega(CLIENTE, cliente);

	do{
		apresenta_programa("Cadastro de Clientes e Funcionários - [Versão 1.0]. Copyright (c) 2017");
        apresenta_programa("Desenvolvido por: Tássio F.C. Todos os direitos reservados.");
		printf("\n<<<<MENU PRINCIPAL>>>>\n\n");
		apresenta_menu(N_ITENS, ITEM1,TITULO_ITEM1,TITULO_ITEM2,TITULO_ITEM3);
		op=le_opcao(ITEM1, ITEM1+N_ITENS-1);
		switch(op){
            case ITEM1:
                printf("DIGITE A SENHA DE ADMINISTRADOR:");
                senhaA = le_senha(SENHA_ADM);
                limpa_tela();
                do{
                    printf("<<<<MENU ADMINISTRADOR>>>>\n\n");
                    apresenta_menu(N_OPCOES, OPCAO1,
                                   TITULO_OPCAO1,TITULO_OPCAO2,
                                   TITULO_OPCAO3,TITULO_OPCAO4,
                                   TITULO_OPCAO5,TITULO_OPCAO6);
                    op=le_opcao(OPCAO1, OPCAO1+N_OPCOES-1);
                    limpa_tela();
                    switch(op){
                        case OPCAO1:
                            printf("[INFORME OS DADOS DO FUNCIONÁRIO]\n\n");
                            nome = le_nome("NOME");
                            limpa_buffer();
                            cpf = le_cpf();
                            limpa_buffer();
                            achou = 0;
                            while(funcionario_consultarCPF(FUNCIONARIO,cpf,achou) || cliente_consultarCPF(CLIENTE, cpf, achou)){
                                printf("CPF JÁ EXISTE CADASTRADO. DIGITE UM CPF NÃO CADASTRADO AINDA.\n");
                                cpf = le_cpf();
                                limpa_buffer();
                            }
                            cargo = le_nome("CARGO");
                            sal = le_valor("SALARIO");
                            FUNCIONARIO = funcionario_inserir(FUNCIONARIO, nome, cpf, cargo, sal);
                            printf("\nINSERÇÃO REALIZADA COM SUCESSO!");
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPCAO2:
                            achou = 0;
                            printf("[INFORME O NOME DO FUNCIONÁRIO QUE DESEJA ATUALIZAR]\n\n");
                            nome = le_nome("NOME");
                            if(!funcionario_consultar(FUNCIONARIO, nome, achou)){
                                printf("\nNOME NÃO ENCONTRADO NO BANCO DE DADOS!");
                            }else{
                                printf("\nFORNEÇA OS NOVOS DADOS DO FUNCIONÁRIO:\n");
                                sal = le_valor("SALÁRIO");
                                cargo = le_nome("CARGO");
                                FUNCIONARIO = funcionario_atualiza(FUNCIONARIO, nome, cargo, &sal);
                                printf("\nDADOS ATUALIZADOS COM SUCESSO!");
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPCAO3:
                            if(funcionario_vazia(FUNCIONARIO)){
                                printf("NENHUM FUNCIONÁRIO ENCONTRADO!\n");
                            }else{
                                printf("[DADOS DOS FUNCIONÁRIOS]\n");
                                funcionario_imprime(FUNCIONARIO);
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_tela();
                            break;
                        case OPCAO4:
                            achou = 0;
                            printf("[INFORME O NOME DO FUNCIONÁRIO QUE DESEJA EXCLUIR]\n\n");
                            nome = le_nome("NOME");
                            if(!funcionario_consultar(FUNCIONARIO, nome, achou)){
                                printf("\nFUNCIONÁRIO NÃO CADASTRADO!");
                            }else{
                                FUNCIONARIO = funcionario_remover(FUNCIONARIO, nome);
                                printf("\nFUNCIONÁRIO EXCLUIDO!");
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPCAO5:
                            saida1 = 1;
                            break;
                        case OPCAO6:
                            saida = 1;
                            saida1 = 1;
                            mensagem_despedida("ENCERRANDO PROGRAMA. ATÉ BREVE...");
                            break;
                        default:
                            printf("ESTE PROGRAMA TEM UM BUG");
                            return 1;
                    }
                }while(!saida1);
                saida1 = 0;
                break;
            case ITEM2:
                printf("DIGITE A SENHA DE FUNCIONÁRIO:");
                senhaF = le_senha(SENHA_FUNC);
                limpa_tela();
                do{
                    printf("<<<<MENU FUNCIONÁRIO>>>>\n\n");
                    apresenta_menu(N_OPTIONS, OPTION1,
                                   TITULO_OPTION1,TITULO_OPTION2,
                                   TITULO_OPTION3,TITULO_OPTION4,
                                   TITULO_OPTION5,TITULO_OPTION6,
                                   TITULO_OPTION7);
                    op=le_opcao(OPTION1, OPTION1+N_OPTIONS-1);
                    limpa_tela();
                    switch(op){
                        case OPTION1:
                            printf("[INFORME OS DADOS DO CLIENTE]\n\n");
                            nome = le_nome("NOME");
                            limpa_buffer();
                            cpf = le_cpf();
                            limpa_buffer();
                            achou = 0;
                            while(cliente_consultarCPF(CLIENTE, cpf, achou) || funcionario_consultarCPF(FUNCIONARIO,cpf,achou)){
                                printf("CPF JÁ EXISTE CADASTRADO. DIGITE UM CPF NÃO CADASTRADO AINDA.\n");
                                cpf = le_cpf();
                                limpa_buffer();
                            }
                            cred = le_valor("CRÉDITO");
                            CLIENTE = cliente_inserir(CLIENTE, nome, cpf, cred);
                            printf("\nINSERÇÃO REALIZADA COM SUCESSO!");
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_tela();
                            break;
                        case OPTION2:
                            achou = 0;
                            printf("[INFORME O NOME DO CLIENTE CUJO CRÉDITO DEVE SER ATUALIZADO]\n\n");
                            nome = le_nome("NOME");
                            if(!cliente_consultar(CLIENTE, nome, achou)){
                                printf("\nNOME NÃO ENCONTRADO NO BANCO DE DADOS!");
                            }else{
                                printf("\nINFORME O VALOR DO CRÉDITO\n");
                                cred = le_valor("CRÉDITO");
                                CLIENTE = cliente_venda(CLIENTE, nome, &cred);
                                printf("\nVENDA CADASTRADA COM SUCESSO!");
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPTION3:
                            achou = 0;
                            printf("[INFORME O NOME DO CLIENTE PARA PROCEDERMOS COM O PAGAMENTO]\n\n");
                            nome = le_nome("NOME");
                            if(!cliente_consultar(CLIENTE, nome, achou)){
                                printf("\nNOME NÃO ENCONTRADO NO BANCO DE DADOS!");
                            }else{
                                printf("\nINFORME O VALOR DO DÉBITO\n");
                                deb = le_valor("DÉBITO");
                                CLIENTE = cliente_atualizaCredito(CLIENTE, nome, &deb);
                                printf("\nCRÉDITO ATUALIZADO COM SUCESSO!");
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPTION4:
                            achou = 0;
                            printf("[FORNEÇA O NOME DO CLIENTE CUJOS DADOS DESEJA EXCLUIR]\n\n");
                            nome = le_nome("NOME");
                            if(!cliente_consultar(CLIENTE, nome, achou)){
                                printf("\nFUNCIONÁRIO NÃO CADASTRADO!");
                            }else{
                                CLIENTE = cliente_remover(CLIENTE, nome);
                                printf("\nFUNCIONÁRIO EXCLUIDO!");
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_buffer();
                            limpa_tela();
                            break;
                        case OPTION5:
                            if(cliente_vazia(CLIENTE)){
                                printf("NENHUM CLIENTE ENCONTRADO!\n");
                            }else{
                                printf("[DADOS DOS CLIENTES]\n");
                                cliente_imprime(CLIENTE);
                            }
                            printf("\nVOLTAR AO MENU - DIGITE QUALQUER TECLA\n");
                            getch();
                            limpa_tela();
                            break;
                        case OPTION6:
                            saida2 = 1;
                            break;
                        case OPTION7:
                            saida2 = 1;
                            saida = 1;
                            mensagem_despedida("ENCERRANDO O PROGRAMA. ATÉ BREVE...");
                            break;
                        default:
                            printf("ESTE PROGRAMA POSSUI UM BUG");
                            return 1;
                    }
                }while(!saida2);
                saida2 = 0;
                break;
            case ITEM3:
                saida = 1;
				mensagem_despedida("ENCERRANDO O PROGRAMA. ATÉ BREVE...");
				break;
			default:
				printf("ESTE PROGRAMA POSSUI UM BUG");
				return 1;
		}
	}while(!saida);

    funcionario = fopen("funcionario.txt","wt");
    if(funcionario == NULL){
    printf("Erro ao salvar arquivo!\n");
        exit(1);
    }
    funcionario_salva(funcionario,FUNCIONARIO);
    fclose(funcionario);
	funcionario_libera(FUNCIONARIO);

	cliente = fopen("cliente.txt","wt");
    if(cliente == NULL){
    printf("ERRO AO ABRIR ARQUIVO!\n");
        exit(1);
    }
    cliente_salva(cliente,CLIENTE);
    fclose(cliente);
	cliente_libera(CLIENTE);
    system("pause");
    return 0;
}
