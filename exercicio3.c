#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo {
    char dono[100];
    char modelo[100];
    char chassi[100];
    char combustivel[20];
    char cor[20];
    char placa[10];
    int ano;
    struct Veiculo* proximo;
} Veiculo;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

Veiculo* dadosVeiculo() {
    Veiculo* veiculo_novo = (Veiculo*)malloc(sizeof(Veiculo));

    if (veiculo_novo == NULL) {
        printf("Erro\n");
        return NULL;
    }

    printf("Digite o nome do dono ");
    fgets(veiculo_novo->dono, sizeof(veiculo_novo->dono), stdin);
    limparBuffer();
    veiculo_novo->dono[strcspn(veiculo_novo->dono, "\n")] = '\0';
    printf("Digite o tipo de combustível (alcool, diesel ou gasolina): ");
    limparBuffer();
    fgets(veiculo_novo->combustivel, sizeof(veiculo_novo->combustivel), stdin);
    veiculo_novo->combustivel[strcspn(veiculo_novo->combustivel, "\n")] = '\0';
    limparBuffer();
    printf("Digite o modelo do veículo: ");
    fgets(veiculo_novo->modelo, sizeof(veiculo_novo->modelo), stdin);
    veiculo_novo->modelo[strcspn(veiculo_novo->modelo, "\n")] = '\0';
    limparBuffer();
    printf("Digite a cor do veículo: ");
    fgets(veiculo_novo->cor, sizeof(veiculo_novo->cor), stdin);
    veiculo_novo->cor[strcspn(veiculo_novo->cor, "\n")] = '\0';
    limparBuffer();
    printf("Digite o número do chassi: ");
    fgets(veiculo_novo->chassi, sizeof(veiculo_novo->chassi), stdin);
    veiculo_novo->chassi[strcspn(veiculo_novo->chassi, "\n")] = '\0';
    limparBuffer();
    printf("Digite o ano do veículo: ");
    scanf("%d", &veiculo_novo->ano);
    limparBuffer();
    printf("Digite a placa do veículo (exemplo: ABC1234): ");
    fgets(veiculo_novo->placa, sizeof(veiculo_novo->placa), stdin);
    veiculo_novo->placa[strcspn(veiculo_novo->placa, "\n")] = '\0';
    veiculo_novo->proximo = NULL;

    return veiculo_novo;
}

void adicionarVeiculo(Veiculo** lista) {
    Veiculo* veiculo_novo = dadosVeiculo();
    if (veiculo_novo == NULL) {
        printf("Não foi possível adicionar o veículo.\n");
        return;
    }

    if (*lista == NULL) {
        *lista = veiculo_novo;
    } else {
        Veiculo* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = veiculo_novo;
    }

    printf("Veículo adicionado\n");
}

void listarVeiculos(Veiculo* lista, int opcao) {
    if (lista == NULL) {
        printf("A lista de veículos está vazia.\n");
        return;
    }

    switch (opcao) {
        case 1:
            printf("Donos de veículos do ano de 2010 ou posterior movidos a diesel:\n");
            while (lista != NULL) {
                if (lista->ano >= 2010 && strcmp(lista->combustivel, "diesel") == 0) {
                    printf("- %s\n", lista->dono);
                }
                lista = lista->proximo;
            }
            break;
        case 2:
            printf("Placas que começam com J e terminam com 0, 2, 4 ou 7 e seus respectivos dono:\n");
            while (lista != NULL) {
                if (lista->placa[0] == 'J' && (lista->placa[6] == '0' || lista->placa[6] == '2' ||
                                              lista->placa[6] == '4' || lista->placa[6] == '7')) {
                    printf("- %s: %s\n", lista->placa, lista->dono);
                }
                lista = lista->proximo;
            }
            break;
        case 3:
            printf("Modelo e cor dos veículos que as placas possuem como segunda letra uma vogal e que a soma dos valores numéricos fornece um número par:\n");
            while (lista != NULL) {
                if (strchr("AEIOUaeiou", lista->placa[1]) != NULL) {
                    int soma = 0;
                    for (int i = 3; i < 7; i++) {
                        soma += lista->placa[i] - '0';
                    }
                    if (soma % 2 == 0) {
                        printf("- Modelo: %s, Cor: %s\n", lista->modelo, lista->cor);
                    }
                }
                lista = lista->proximo;
            }
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void trocarDono(Veiculo* lista, const char* chassi) {
    if (lista == NULL) {
        printf("A lista de veículos está vazia.\n");
        return;
    }

    while (lista != NULL) {
        if (strcmp(lista->chassi, chassi) == 0) {
            if (strchr(lista->placa, '0') == NULL) {
                printf("Digite o novo nome do dono ");
                fgets(lista->dono, sizeof(lista->dono), stdin);
                lista->dono[strcspn(lista->dono, "\n")] = '\0';
                printf("Dono alterado\n");
                return;
            } else {
                printf("A troca de dono só é permitida para carros com placas sem dígitos iguais a zero.\n");
                return;
            }
        }
        lista = lista->proximo;
    }

    printf("Nenhum veículo encontrado com o número de chassi fornecido.\n");
}

void liberarLista(Veiculo* lista) {
    while (lista != NULL) {
        Veiculo* proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}

int main() {
    Veiculo* lista = NULL;
    int opcao;
    char chassi[100];

    do {
        printf("1. Adicionar veículo\n");
        printf("2. Listar donos de veículos do ano de 2010 ou posterior movidos a diesel\n");
        printf("3. Listar placas que começam com J e terminam com 0, 2, 4 ou 7 e seus respectivos donos\n");
        printf("4. Listar modelo e cor dos veículos que as placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par\n");
        printf("5. Trocar dono com fornecimento do número do chassi\n");
        printf("6. Sair\n\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarVeiculo(&lista);
                break;
            case 2:
            case 3:
            case 4:
                listarVeiculos(lista, opcao);
                break;
            case 5:
                printf("Digite o número do chassi do veículo: ");
                fgets(chassi, sizeof(chassi), stdin);
                chassi[strcspn(chassi, "\n")] = '\0';
                trocarDono(lista, chassi);
                break;
            case 6:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 6);

    liberarLista(lista);

    return 0;
}
