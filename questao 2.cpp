//
// Created by Daniel Moura on 14/08/2023.
//

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char nome[300];
    char palavra[148];
    char letraAtual;
    int dicionario[26] = {0};
    // entrada

    printf("digite o nome ou diretorio do arquivo:\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    FILE *arquivo = fopen(nome, "w");

    if (arquivo == NULL)
    {
        printf("nao foi possivel criar o arquivo.");
        return 1;
    }

    printf("digite a palavra ou frase que deseja escanear:\n");
    fgets(palavra, sizeof(palavra), stdin);

    palavra[strcspn(palavra, "\n")] = '\0';

    fclose(arquivo);

    // processamento

    FILE *novo = fopen(nome, "r");

    if (novo == NULL)
    {
        printf("arquivo invalido");
        return 1;
    }


    fscanf(novo, "%s", &palavra);

    for (int i = 0; i < strlen(palavra); i++)
    {
        letraAtual = toupper(palavra[i]); // deixa todas as letras maisculas
        if (isalpha(letraAtual))
        { // verifica se é realmente uma letra
            if (letraAtual >= 'A' && letraAtual <= 'Z')
            {                                   // verifica se o caractere está entre A e Z na tabela ascii
                dicionario[letraAtual - 'A']++; // incrementa o contador dicionario
            }
        }
    }
    fclose(arquivo);

    // saida

    FILE *newman = fopen(nome, "a");


    for (int i = 0; i < 26; i++)
    {
        if (dicionario[i] > 0)
        {
            fprintf(newman,"%c: %d vezes\n", 'A' + i, dicionario[i]);
        }
    }



    return 0;
}
