#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enumeração para critérios de ordenação
enum CriterioOrdenacao {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
};

// Estrutura do item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
};

// Função para adicionar um item
void adicionarItem(struct Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar novo item ---\n");
    printf("Nome: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &mochila[*total].prioridade);
    } while (mochila[*total].prioridade < 1 || mochila[*total].prioridade > 5);

    getchar();
    (*total)++;
    printf("Item adicionado com sucesso!\n");
}

// Função para listar itens
void listarItens(struct Item mochila[], int total) {
    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

// Função para ordenar usando Insertion Sort
void insertionSort(struct Item mochila[], int total, enum CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < total; i++) {
        struct Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;

            switch (criterio) {
                case ORDENAR_NOME:
                    cmp = strcmp(mochila[j].nome, chave.nome);
                    break;
                case ORDENAR_TIPO:
                    cmp = strcmp(mochila[j].tipo, chave.tipo);
                    break;
                case ORDENAR_PRIORIDADE:
                    cmp = mochila[j].prioridade - chave.prioridade;
                    break;
            }

            if (cmp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
    printf("Mochila ordenada com sucesso! (%d comparacoes)\n", *comparacoes);
}

// Função de busca binária por nome
void buscaBinaria(struct Item mochila[], int total, char nomeBusca[], bool estaOrdenadoPorNome) {
    if (!estaOrdenadoPorNome) {
        printf("A busca binaria so funciona se a lista estiver ordenada por nome!\n");
        return;
    }

    int inicio = 0, fim = total - 1;
    bool encontrado = false;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado)
        printf("Item '%s' nao encontrado.\n", nomeBusca);
}

// Menu principal
int main() {
    struct Item mochila[MAX_ITENS];
    int total = 0, opcao, comparacoes = 0;
    bool ordenadoPorNome = false;

    do {
        printf("\n===== MOCHILA DO MESTRE =====\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Ordenar mochila\n");
        printf("4. Buscar item por nome (busca binaria)\n");
        printf("0. Sair\n");
        printf("=============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &total);
                ordenadoPorNome = false;
                break;

            case 2:
                listarItens(mochila, total);
                break;

            case 3: {
                int criterio;
                printf("\nOrdenar por:\n");
                printf("1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
                scanf("%d", &criterio);
                getchar();

                insertionSort(mochila, total, criterio, &comparacoes);
                ordenadoPorNome = (criterio == ORDENAR_NOME);
                break;
            }

            case 4: {
                char nomeBusca[30];
                printf("\nDigite o nome do item a buscar: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscaBinaria(mochila, total, nomeBusca, ordenadoPorNome);
                break;
            }

            case 0:
                printf("Saindo da mochila...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
