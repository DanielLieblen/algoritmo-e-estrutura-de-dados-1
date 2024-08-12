#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char cargo[30];
  int numero;
  char nome[50];
  char Partido[10];
  int quantidadeDeVotos;
  struct ptrCandidato *proximo;
} registro;

typedef registro elemento;

typedef registro *ptrCandidato;
const elemento VL_NULO = {"", 0, 0};

#include "tad_lst2.h"
#include "persistencia.h"


tipo_lista lista;

void menu();
// void inicializa_candidatos(tipo_lista *lista);
void listarCandidatosComVoto(tipo_lista *lista);
int cadastrarCandidatos(tipo_lista *lista);
int editarCandidato(tipo_lista *lista);
int excluirCandidato(tipo_lista *lista);
int votar(tipo_lista *lista);

int main() {

  inicializa_lista(&lista);
  menu();
}

// void inicializa_candidatos(tipo_lista *lista) {
// }

void listarCandidatosComVoto(tipo_lista *lista) {
  elemento elem;
  
  ptrCandidato atual = lista->lista;
  
  int i = 1;
  while (atual != NULL) {
    obter_elemento(*lista, i, &elem);
    if (elem.quantidadeDeVotos != 0) {
      printf("%s\n", elem.cargo);
      printf("%d\n", elem.numero);
      printf("%s\n", elem.nome);
      printf("%s\n", elem.Partido);
      printf("%d\n", elem.quantidadeDeVotos);
      i++;
    } 
    atual = atual->proximo;
  }
}

int cadastrarCandidatos(tipo_lista *lista) {
  elemento elem;
  printf("Digite o cargo do candidato:\n");
  fgets(elem.cargo, sizeof(elem.cargo), stdin);
  elem.cargo[strcspn(elem.cargo, "\n")] = '\0';
  
  printf("Digite o numero do candidato:\n");
  scanf("%d", &elem.numero);
  getchar();
  
  printf("Digite o nome do candidato:\n");
  fgets(elem.nome, sizeof(elem.nome), stdin);
  elem.nome[strcspn(elem.nome, "\n")] = '\0';
  
  printf("Digite o partido do candidato:\n");
  fgets(elem.Partido, sizeof(elem.Partido), stdin);
  elem.Partido[strcspn(elem.Partido, "\n")] = '\0';


  if (incluir_elemento(lista, 1, elem)) {
    return 1;
  } else {
    return 0;
  }
}

int editarCandidato(tipo_lista *lista) {
  elemento elem;
  char nome[50];

  printf("digite o nome do candidato a ser editado:");
  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = '\0';
  // primeiro le o nome do candidato a ser editado

  ptrCandidato atual = lista->lista;
  // cria a variavel auxiliar pra percorrer os nodos
  // essa variavel vai conter o nodo atual

  while (atual !=
         NULL) { // enquanto a variavel atual nao chegar a um endereço nulo
    // que basicamente significa o final da lista encadeada
    if (strcmp(nome, atual->nome) ==
        0) { // se o nome a ser editado for igual ao nome o qual a variavel
             // atual esta posicionada
      printf("Candidato encontrado:\n"); // da mensagem e mostra o candidato
      printf("Cargo: %s\n", atual->cargo);
      printf("Número: %d\n", atual->numero);
      printf("Nome: %s\n", atual->nome);
      printf("Partido: %s\n", atual->Partido);
      printf("Quantidade de Votos: %d\n", atual->quantidadeDeVotos);

      // Agora você pode realizar a edição dos campos do candidato aqui
      // Exemplo: Atualizar o cargo
      printf("Digite o novo cargo: ");
      fgets(atual->cargo, sizeof(atual->cargo), stdin);
      atual->cargo[strcspn(atual->cargo, "\n")] = '\0';

      // Exemplo: Atualizar o número
      printf("Digite o novo número: ");
      scanf("%d", &atual->numero);
      getchar(); // Consumir a nova linha pendente

      // Exemplo: Atualizar o partido
      printf("Digite o novo partido: ");
      fgets(atual->Partido, sizeof(atual->Partido), stdin);
      atual->Partido[strcspn(atual->Partido, "\n")] = '\0';

      // Outros campos podem ser atualizados de maneira semelhante

      printf("Candidato editado com sucesso!\n");
      return 1;
    }
    atual = atual->proximo;
  }

  printf("Candidato com nome %s não encontrado.\n", nome);
  return 0;
}

int excluirCandidato(tipo_lista *lista) {
  elemento elem;
  int numero = 0;

  printf("digite o numero do candidato a ser editado:");
  scanf("%d", numero);
  getchar();

  ptrCandidato atual = lista->lista;

  for (int i = 1; i <= lista->tamanho;) {
    if (numero == atual->numero) {
      excluir_elemento(&lista, i);
      return 1;
    } else {
      i++;
    }
  }
  printf("Candidato com nome %s não encontrado.\n", atual->numero);
  return 0;
}

int votar(tipo_lista *lista) {
  listarCandidatos(&lista); // primeiro mostra os candidatos
  int escolha;
  ptrCandidato atual = lista->lista;

  printf("digite o numero do candidato escolhido:");
  scanf("%d", &escolha);

  while (atual != NULL) {
    if (atual->numero == escolha) {
      printf("Voce escolheu o seguinte candidato:\n");
      printf("Nome: %s\n", atual->nome);
      printf("Cargo: %s\n", atual->cargo);

      printf("Deseja confirmar este voto? Digite 1 para confirmar e 0 para "
             "cancelar: \n");
      int confirmacao;
      scanf("%d", &confirmacao);
      if (confirmacao == 1) {
        // Voto confirmado, registre o voto e exiba uma mensagem de confirmação
        atual->quantidadeDeVotos++;
        printf("Voto registrado com sucesso.");
        return 1; // Voto registrado com sucesso
      } else {
        // Voto cancelado, retorne sem registrar o voto
        printf("Voto cancelado. Por favor, escolha novamente.\n");
        return 0; // Voto cancelado
      }
    }
    atual = atual->proximo;
  }
  // Se chegou aqui, o candidato não foi encontrado
  printf("Candidato não encontrado.\n");
  return 0; // Candidato não encontrado
}

void menu() {
  int opcao;

  while (1) {
    printf("\n----- Menu -----\n");
    printf("1 - Ler arquivo\n");
    printf("2 - Listar candidatos com quantidade de votos\n");
    printf("3 - Cadastrar candidato\n");
    printf("4 - Editar dados do candidato\n");
    printf("5 - Excluir candidato\n");
    printf("6 - Votar (simula a urna eletrônica)\n");
    printf("9 - Salvar e sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Opção 1 selecionada - Ler arquivo.\n");
      carregar_lista(&lista);
      break;
    case 2:
      printf(
          "Opção 2 selecionada - Listar candidatos com quantidade de votos.\n");
      listarCandidatosComVoto(&lista);
      break;
    case 3:
      printf("Opção 3 selecionada - Cadastrar candidato.\n");
      // declara um novo struct pra salvar o candidato atual
      cadastrarCandidatos(&lista);
      break;
    case 4:
      printf("Opção 4 selecionada - Editar dados do candidato.\n");
      editarCandidato(&lista);
      break;
    case 5:
      printf("Opção 5 selecionada - Excluir candidato.\n");
      excluirCandidato(&lista);
      break;
    case 6:
      printf("Opção 6 selecionada - Votar (simula a urna eletrônica).\n");
      votar(&lista);
      break;
    case 9:
      gravar_lista(lista);
      printf("Opção 9 selecionada - Salvar e sair. Encerrando o programa.\n");
      exit(0);
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  }
}