#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int codigo_terminal;
    char data[9];
    int hora;
    char placa[10];
    int codigo_empresa;
    struct ptrOnibus *proximo;
}registro;

typedef registro elemento;

typedef registro *ptrOnibus;

const elemento VL_NULO = {0, "", 0, "", 0};

#include "tad_lst2.h"

tipo_lista lista;


    typedef struct{
        char placa[7];
        int tempo_trajeto_acumulado;
        int quantidade;
    }tipo_tempos;


int carregar_lista(tipo_lista *la);
int listar(tipo_lista *la);
int calcular_diferenca_horas(int hora1, int hora2);
int media_tempo(tipo_lista *la);
int valor_por_empresa(lista_encadeada *la);
void menu();

int main() {

    inicializa_lista(&lista);
    menu();
}


int carregar_lista(tipo_lista *la) {
    FILE *arquivo = fopen("D:/Sistemas - 3 periodo/Estrutura de Dados/TarifaOnibus/2019-09-06.txt", "r");

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }else{
        printf("Arquivo lido com exito.\n");
    }

    elemento elem = VL_NULO;

    while (fscanf(arquivo, "%d %s %d %s %d", &elem.codigo_terminal, elem.data, &elem.hora, elem.placa, &elem.codigo_empresa)!=EOF){
       if(! incluir_elemento(la, tamanho(*la)+ 1, elem)){
           printf("Erro ao adicionar elemento à lista.\n");
           break;
       }
    }

}


int listar(tipo_lista *la){
    elemento elem = VL_NULO;

    for(int i = 1; i <= tamanho(*la); i++){
        obter_elemento(*la, i, &elem);
            printf("%d\n", elem.codigo_terminal);
            printf("%s\n", elem.data);
            printf("%d\n", elem.hora);
            printf("%s\n", elem.placa);
            printf("%d\n\n", elem.codigo_empresa);
    }

}
int calcular_diferenca_horas(int hora1, int hora2) {
    int horas =0, minutos =0;
    int minutos1 = hora1 % 100;
    int minutos2 = hora2 % 100;
    int horas1 = hora1 / 100;
    int horas2 = hora2 / 60;

    if(minutos2 < minutos1) {
        hora2--;
        minutos2 = minutos2 +60;
    }
    int diferenca_horas = (horas2 - horas1) * 60 + (minutos2 - minutos1);

    return diferenca_horas;
}


int placa_esta_no_vetor(char placa[7], tipo_tempos vet[], int n){
    int ret=0;
    for(int i=0; i<=n; i++)){
        if(!strcmp(placa, vet[i].placa)){
            return (ret=1);
        }
    }
    return ret;
}

int media_tempo(tipo_lista *la) {
    elemento elem = VL_NULO;
    elemento proximoElem = VL_NULO;
    tipo_tempos vet_tempos[1000];
    int soma = 0, k=0;
    int viagens = 0;

    for (int i = 1; i < tamanho(*la); i++) {
        obter_elemento(*la, i, &elem);
        obter_elemento(*la, i + 1, &proximoElem);

        if (!(placa_esta_no_vetor(elem.placa, vet_tempos, k - 1))) { // ainda não usou para o cálculo da média

            if (strcmp(proximoElem.placa, elem.placa) == 0 && proximoElem.codigo_terminal != elem.codigo_terminal) {
                int diferenca = calcular_diferenca_horas(elem.hora, proximoElem.hora);
                soma += diferenca;
                viagens++;
            }
        }
        k++;
    }

    if (viagens > 0) {
        int media = soma / viagens;
        return media;
    } else {
        return 0; // Nenhuma viagem encontrada para calcular a média.
    }

    printf("\nPlaca\t || Media(em minutos)\n");
    for (int i=0; i<k; i++) {
        printf("%s\t || %0.0f\n", vet_tempos[i].placa, (float)vet_tempos[i].tempo_trajeto_acumulado/vet_tempos[i].quantidade);
    }

}


int valor_por_empresa(lista_encadeada *la){
    elemento elem = VL_NULO;
    elemento proximoElem = VL_NULO;

    int soma1 =0;
    int soma2 =0;

    for(int i=0; i< tamanho(*la); i++){
        obter_elemento(*la, i, &elem);
        obter_elemento(*la, i+1, &proximoElem);

        if(elem.codigo_empresa ==1){
            soma1+=100;
        }else{
            soma2+=100;
        }

    }
    printf("o valor recebido pela empresa 1: %d\n", soma1);
    printf("o valor recebido pela empresa 2: %d\n", soma2);
    return 0;
}


void menu(){
    int opcao=0;

    while(1){
        printf("\n----- Menu -----\n");
        printf("1 - Carregar Lista.\n");
        printf("2 - Listar dados.\n");
        printf("3 - media tempo das viagens dos veiculos.\n");
        printf("4 - Valor a receber por empresa.\n");
        printf("5 - Lista invertida.\n");
        printf("6 - Quantidade de itens na lista.\n");
        printf("9 - sair\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("");
                carregar_lista(&lista);
                break;
            case 2:
                listar(&lista);
                break;
            case 3:
                printf("a media das viagens dos veiculos eh: %d min.", media_tempo(&lista));
                break;
            case 4:
                valor_por_empresa(&lista);
                break;
            case 5:
                printf("lista invertida: %d\n", inverte_lista(&lista));
                break;
            case 6:
                printf("quantos elementos tem: %d\n", contar_elementos(&lista));
            case 9:
                exit(0);
                break;

        }


    }

}

