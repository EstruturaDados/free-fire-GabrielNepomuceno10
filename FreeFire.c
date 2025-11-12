#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura do item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Função para adicionar um item
void adicionarItem(struct Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
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
    getchar();

    (*total)++;
    printf("✅ Item adicionado com sucesso!\n");
}

// Função para remover um item
void removerItem(struct Item mochila[], int *total) {
    if (*total == 0) {
        printf("⚠️ Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover item ---\n");
    printf("Nome do item: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            encontrado = 1;
            printf("🗑️ Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado)
        printf("❌ Item não encontrado!\n");
}

// Função para listar todos os itens
void listarItens(struct Item mochila[], int total) {
    printf("\n--- Itens na mochila ---\n");
    if (total == 0) {
        printf("⚠️ Nenhum item cadastrado.\n");
        return;
    }

    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-20s %-15s %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// 🧙‍♂️ Função para buscar item por nome (nova!)
void buscarItem(struct Item mochila[], int total) {
    if (total == 0) {
        printf("⚠️ Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar item ---\n");
    printf("Digite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n🔎 Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
}

int main() {
    struct Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA DO AVENTUREIRO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n"); // 🆕 Nova opção
        printf("0. Sair\n");
        printf("==================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("👋 Saindo da mochila...\n");
                break;
            default:
                printf("❌ Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
