#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa
{
    int idade;
    char nome[100];
    char genero;
};
// primeira struct

int main(void)
{

    // leitura
    int N, maior = 0, contH = 0, contM = 0;

    FILE *arquivo = fopen("entrada.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo\n");
        return 1;
    }

    fscanf(arquivo, "%d", &N);
   // fgetc(arquivo);          // le o caractere de quebra de linha
    struct pessoa pessoa[N]; // aloca o numero de pessoas na struct

    //rewind(arquivo);


    printf("aqui: %d\n\n", N);

    for (int i = 0; i < N; i++)
    {
        fscanf(arquivo, " %c %99s %d\n", &pessoa[i].genero, &pessoa[i].nome, &pessoa[i].idade);

    }//colocar os dados do arquivo dentro da struct

    fclose(arquivo);

    // printar struct

    for (int i = 0; i < N; i++)
    {
        printf("idade: %d, nome: %s, genero: %c\n", pessoa[i].idade, pessoa[i].nome, pessoa[i].genero);
    }

    // processamento

     for (int i = 0; i < N; i++)
    {
        if (pessoa[i].genero == 'M')
       {
           contH=contH+1;
        }
        if (pessoa[i].genero == 'F')
        {
            contM=contM+1;
         }
        if (pessoa[i].idade > maior)
        {
             maior = pessoa[i].idade;
        }
    }
     //saida

    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL)
    {
        printf("Erro ao criar arquivo\n");
        return 1;
    }

        fprintf(saida, "o numero de homens: %d\n", contH);
        fprintf(saida, "O numero de mulheres: %d\n", contM);
        fprintf(saida, "A idade da pessoa mais velha eh: %d\n", maior);

    fclose(saida);

    return 0;
}