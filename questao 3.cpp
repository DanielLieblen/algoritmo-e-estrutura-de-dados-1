//
// Created by Daniel Moura on 16/08/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "time.h"
#include "string.h"
#include "windows.h"

#define MAX 1000
typedef struct
{
    int sequencial;
    int matricula;
    char nome[200];
} Aluno;

int TotalAlunos = 0;
Aluno novoAluno[MAX];

void menuPrincipal();
void menuOrdem();
void cadastro();
void editar();
void deletar();
void trocar();
void bubbleSort_Matricula();
void bubbleSort_Nome();
void bubbleSort_Sequencial();
void salvarArquivo();
void carregarArquivo();



int main()
{
    int quantAlunos = 0;

//    printf("digite a quantidade de alunos total do sistema:\n");
//    scanf("%d", &TotalAlunos);
//    fflush(stdin);
//Aluno aluno[TotalAlunos];

    menuPrincipal();


}

void cadastro(int quantAlunos)
{
    Aluno aluno[quantAlunos]; // cria um array de aluno

    Aluno *n_aluno = &novoAluno[quantAlunos]; // ponteiro pra fazer comparacao e ver se os alunos sao iguais

    int flag = 0;

    srand(time(NULL)); // inicializa a seed de gerador de numeros aleatorios

    for (int i = 0; i < quantAlunos; i++)
    {


        novoAluno[i].sequencial = rand(); // gera numero aleatorio
        printf("digite o nome do aluno:\n");
        fgets(novoAluno[i].nome, sizeof(novoAluno[i].nome), stdin);
        fflush(stdin); // limpa o buffer de entrada

        printf("digite a matricula do aluno:\n");
        scanf("%d", &novoAluno[i].matricula);
        fflush(stdin); // limpa o buffer de entrada


        if (strcmp(aluno[i].nome, novoAluno[i].nome) == 0)
            {
                flag++;
            }
            if (flag != 0)
            {
                printf("O nome %s ja esta cadastrado\n", aluno[i].nome);
                printf("aperte qualquer tecla para voltar\n");
                fflush(stdin); // limpa o buffer de entrada
            }

        n_aluno = aluno;
        n_aluno++;
    }
}

void editar(char procurado[])
{
    printf("\n\nObs: sequencial nao pode ser alterado.\n\n");
//    printf("digite o nome do aluno que deseja editar:\n");
//    fgets(procurado, strlen(procurado), stdin);
//    procurado[strcspn(procurado, "\n")] = '\0';
//    getchar();

    for (int i = 0; i < TotalAlunos; i++)
    {
        if (strcmp(procurado, novoAluno[i].nome) == 0)
        {
            printf("Digite as alteracoes:\n");
            printf("Novo Nome do Aluno:\n");
            fflush(stdin);
            fgets(novoAluno[i].nome, sizeof(novoAluno[i].nome), stdin);
            novoAluno[i].nome[strcspn(novoAluno[i].nome, "\n")] = '\0';
            fflush(stdin);

            printf("Nova Matricula do Aluno:\n");
            fflush(stdin);
            scanf("%d", &novoAluno[i].matricula);
            fflush(stdin);

        }
    }
}
void deletar(char procurado[])
{

    printf("digite o nome do aluno que deseja deletar:\n");
    fgets(procurado, strlen(procurado), stdin);
    procurado[strcspn(procurado, "\n")] = '\0';
    getchar();

    for (int i = 0; i < TotalAlunos; i++)
    {
        if (strcmp(novoAluno[i].nome, procurado) == 0)
        {

                for (int j = i + 1; j < TotalAlunos - 1; j++)
                {

                    strcpy(novoAluno[i].nome, novoAluno[j].nome); //copia o nome do aluno posterior pro anterior
                    novoAluno[i].matricula = novoAluno[j].matricula; //mesma coisa com os demais dados
                    novoAluno[i].sequencial = novoAluno[j].sequencial;
                }
        }
    }
}

void pesquisarNome(Aluno aluno[], char procurado[])
{
    for (int i = 0; i < TotalAlunos; i++)
    {
        if (strcmp(novoAluno[i].nome, procurado) == 0)
        {
            printf("O nome do aluno %s esta na posicao %d\n", novoAluno[i].nome, i);
            printf("%d\n", novoAluno[i].sequencial);
            printf("%d\n", novoAluno[i].matricula);
            printf("%s\n", novoAluno[i].nome);
        }
    }
}

void pesquisarMatricula(Aluno aluno[], int matricula)
{
    for (int i = 0; i < TotalAlunos; i++)
    {
        if (novoAluno[i].matricula == matricula)
        {
            printf("O nome do aluno %s esta na posicao %d\n", novoAluno[i].nome, i);
            printf("%d\n", novoAluno[i].sequencial);
            printf("%d\n", novoAluno[i].matricula);
            printf("%s\n", novoAluno[i].nome);
        }
    }
}

void trocar(Aluno *a, Aluno *b)
{
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort_Matricula(Aluno aluno[])
{
    for (int i = 0; i < TotalAlunos - 1; i++)
    {
        for (int j = 0; j < TotalAlunos - i - 1; j++)
        {
            if (aluno[j].matricula > aluno[j + 1].matricula)
            {
                trocar(&aluno[j], &aluno[j + 1]);
            }
        }
    }
}

void bubbleSort_Sequencial(Aluno aluno[])
{
    for (int i = 0; i < TotalAlunos - 1; i++)
    {
        for (int j = 0; j < TotalAlunos - i - 1; j++)
        {
            if (aluno[j].sequencial > aluno[j + 1].sequencial)
            {
                trocar(&aluno[j], &aluno[j + 1]);
            }
        }
    }
}

void bubbleSort_Nome(Aluno aluno[])
{
    for (int i = 0; i < TotalAlunos - 1; i++)
    {
        for (int j = 0; j < TotalAlunos - i - 1; j++)
        {
            if (strcmp(aluno[j].nome, aluno[j + 1].nome) > 0)
            {
                trocar(&aluno[j], &aluno[j + 1]);
            }
        }
    }
}

void carregarArquivo(Aluno aluno[])
{
    FILE *arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    {
        printf("não foi possivel criar o arquivo");
        return;
    }
    //    fseek(arquivo, 0, SEEK_SET);
    //    long tamanho = ftell(arquivo);
    //    rewind(arquivo);

    for (int i = 0; i < TotalAlunos; i++)
    {
        fscanf(arquivo, "%d %d %199s", aluno[i].sequencial, aluno[i].matricula, aluno[i].nome);
    } // joga os dados das structs pra dentro do arquivo

    fclose(arquivo);
}

void salvarArquivo(Aluno aluno[])
{
    FILE *arquivo = fopen("arquivo.txt", "a");

    if (arquivo == NULL)
    {
        printf("não foi possivel criar o arquivo");
        return;
    }

    for (int i = 0; i < TotalAlunos; i++)
    {
        fprintf(arquivo, "%d %d %199s", aluno[i].sequencial, aluno[i].matricula, aluno[i].nome);
    }

    fclose(arquivo);
}


void menuOrdem()
{
    int op;

    do
    {
        system("cls");
        printf("====== Menu Ordenacao =====\n");
        printf("\n\n As opcoes sao:\n");
        printf("0 - Sair\n");
        printf("1 - Ordenar por nome\n");
        printf("2 - Ordenar por matricula\n");
        printf("3 - Ordenar por sequencial\n");
        printf("4 - voltar\n");
        printf("\n\n Informe a opcao(digite o numero a seguir):\n");
        scanf("%d", &op);

        getchar();
        switch (op)
        {
            case 0:
                system("exit");
                break;
            case 1:
                bubbleSort_Nome(novoAluno);
                break;
            case 2:
                bubbleSort_Matricula(novoAluno);
                break;
            case 3:
                bubbleSort_Sequencial(novoAluno);
                break;
            case 4:
                menuPrincipal();
                break;
        }
    } while (op != 0);
}

void menuPesquisar()
{
    int op, matricula = 0;
    char procurado[200];

    do
    {
        system("cls");
        printf("====== Menu de Pesquisa =====\n");
        printf("\n\n As opcoes sao:\n");
        printf("0 - Sair\n");
        printf("1 - Pesquisar por nome\n");
        printf("2 - Pesquisar por matricula\n");
        printf("4 - voltar\n");
        printf("\n\n Informe a opcao(digite o numero a seguir):\n");
        scanf("%d", &op);

        getchar();
        switch (op)
        {
            case 0:
                system("exit");
                break;
            case 1:
                printf("digite o nome do aluno a ser procurado:\n");
                fgets(procurado, strlen(procurado), stdin);
                procurado[strcspn(procurado, "\n")] = '\0';
                pesquisarNome(novoAluno, procurado);
                break;
            case 2:
                printf("digite a matricula do aluno a ser procurado:\n");
                scanf("%d", &matricula);
                pesquisarMatricula(novoAluno, matricula);
                break;
            case 4:
                menuPrincipal();
                break;
        }
    } while (op != 0);
}

void menuPrincipal()
{
    int op, quantAlunos;
    char procurado[200];

    do
    {
        system("cls");
        printf("====== Menu Principal =====\n");
        printf("\n\n As opcoes sao:\n");
        printf("0 - Carregar dados do Arquivo\n");
        printf("1 - Cadastro de Alunos\n");
        printf("2 - Alterar Cadastro\n");
        printf("3 - Deletar Cadastro\n");
        printf("4 - Ordenar alunos \n");
        printf("5 - Pesquisar Alunos \n");
        printf("9 - Gravar e Sair\n");
        printf("\n\n Informe a opcao(digite o numero a seguir):\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
            case 0:
                carregarArquivo(novoAluno);
                break;
            case 1:
                printf("digite a quantidade de alunos que deseja cadastrar:\n");
                scanf("%d", &quantAlunos);
                getchar();

//                if(quantAlunos ==0){
//                    op=0;
//                    break;
//                }
//                if(quantAlunos > MAX){
//                    printf("quantidade excedeu o limite maximo de alunos permitido pelo sistema.");
//                }

                cadastro(quantAlunos);
                TotalAlunos += quantAlunos;
                break;
            case 2:
                printf("digite a o aluno a ser alterado:\n");
                fflush(stdin);
                fgets(procurado, sizeof(procurado), stdin);
                fflush(stdin);
                procurado[strcspn(procurado, "\n")] = '\0';
                editar(procurado);
                break;
            case 3:
                printf("digite a o aluno a ser deletado:\n");
                fgets(procurado, strlen(procurado), stdin);
                procurado[strcspn(procurado, "\n")] = '\0';
                deletar(procurado);
                break;
            case 4:
                menuOrdem();
                break;
            case 5:
                menuPesquisar();
                break;
            case 9:
                salvarArquivo(novoAluno);
                break;
        }

    } while (op != 0);
}