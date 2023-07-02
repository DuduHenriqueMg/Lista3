#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dieta {
    char comida[100];
    float peso;
    int calorias;
    struct Dieta* proximo;
} Dieta;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

Dieta* dadosDieta() {
    Dieta* dieta_nova = (Dieta*)malloc(sizeof(Dieta));
    if (dieta_nova == NULL) {
        printf("Erro \n");
        return NULL;
    }

    printf("Digite o nome da comida: ");
    fgets(dieta_nova->comida, sizeof(dieta_nova->comida), stdin);
    dieta_nova->comida[strcspn(dieta_nova->comida, "\n")] = '\0';
    printf("Digite o peso da comida (gramas): ");
    scanf("%f", &dieta_nova->peso);
    limparBuffer();
    printf("Digite o número de calorias: ");
    scanf("%d", &dieta_nova->calorias);
    limparBuffer();

    dieta_nova->proximo = NULL;

    return dieta_nova;
}

void adicionarDieta(Dieta** lista) {
    Dieta* dieta_nova = dadosDieta();
    if (dieta_nova == NULL) {
        printf("Não foi possível adicionar a dieta.\n");
        return;
    }

    if (*lista == NULL) {
        *lista = dieta_nova;
    } else {
        Dieta* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = dieta_nova;
    }

    printf("Dieta adicionada\n");
}

void listarDietas(Dieta* lista) {
    if (lista == NULL) {
        printf("A lista de dietas está vazia.\n");
        return;
    }

    printf("Lista de dietas:\n");
    int i = 1;
    Dieta* atual = lista;
    while (atual != NULL) {
        printf("Dieta %d:\n", i++);
        printf("Nome da comida: %s\n", atual->comida);
        printf("Peso da porção: %.2f gramas\n", atual->peso);
        printf("Número de calorias: %d\n\n", atual->calorias);
        atual = atual->proximo;
    }
}

void liberarLista(Dieta* lista) {
    while (lista != NULL) {
        Dieta* prox = lista->proximo;
        free(lista);
        lista = prox;
    }
}

int main() {
    Dieta* lista = NULL;
    int opcao;

    do {
        printf("1. Adicionar dieta\n");
        printf("2. Listar dietas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarDieta(&lista);
                break;
            case 2:
                listarDietas(lista);
                break;
            case 3:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 3);

    liberarLista(lista);

    return 0;
}