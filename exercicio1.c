#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct restaurante {
    char nome[100];
    char endereco[100];
    char tipo[100];
    float preco_medio;
    struct restaurante *proximo;

} Restaurante;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

Restaurante *dadosRestaurante() {
    Restaurante *novo_restaurante = (Restaurante *)malloc(sizeof(Restaurante));
    if (novo_restaurante == NULL) {
        printf("Erro\n");
        return NULL;
    }

    printf("Digite o nome do restaurante: ");
    fgets(novo_restaurante->nome, sizeof(novo_restaurante->nome), stdin);
    novo_restaurante->nome[strcspn(novo_restaurante->nome, "\n")] = '\0';
    limparBuffer();
    printf("Digite o endereço do restaurante: ");
    fgets(novo_restaurante->endereco, sizeof(novo_restaurante->endereco), stdin);
    novo_restaurante->endereco[strcspn(novo_restaurante->endereco, "\n")] = '\0';
    limparBuffer();
    printf("Digite o preço médio do restaurante: ");
    scanf("%f", &novo_restaurante->preco_medio);
    limparBuffer();
    printf("Digite o tipo de comida do restaurante: ");
    fgets(novo_restaurante->tipo, sizeof(novo_restaurante->tipo), stdin);
    novo_restaurante->tipo[strcspn(novo_restaurante->tipo, "\n")] = '\0';
    novo_restaurante->proximo = NULL;

    return novo_restaurante;
}


void adicionarRestaurante(Restaurante **lista) {
    Restaurante *novo_restaurante = dadosRestaurante();
    if (novo_restaurante == NULL){
        printf("Não foi possível adicionar o restaurante.\n");
        return;
    }

    if (*lista == NULL){
        *lista = novo_restaurante;
    }
    else{
        Restaurante *atual = *lista;
        while (atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novo_restaurante;
    }

    printf("Restaurante adicionado \n");
}


void listarRestaurantes(Restaurante *lista) {
    if (lista == NULL) {
        printf("Não tem nenhum restaurante na lista.\n");
        return;
    }

    printf("Lista de restaurantes:\n");
    Restaurante *atual = lista;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Endereço: %s\n", atual->endereco);
        printf("Preço médio: %.2f\n", atual->preco_medio);
        printf("Tipo de comida: %s\n\n", atual->tipo);
        
        atual = atual->proximo;
    }
}

int main() {
    Restaurante *lista = NULL;
    int opcao;

    do {
        printf("1. Adicionar restaurante\n");
        printf("2. Listar restaurantes\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:
            adicionarRestaurante(&lista);
            break;
        case 2:
            listarRestaurantes(lista);
            break;
        case 3:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 3);

    Restaurante *atual = lista;
    while (atual != NULL) {
        Restaurante *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
