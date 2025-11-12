#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// Estrutura que representa um item do inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

int main() {
    struct Item mochila[MAX_ITENS];  // Vetor de structs
    int total = 0;                   // Quantos itens já foram cadastrados
    int opcao;

    do {
        printf("\n===== INVENTÁRIO BÁSICO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("=============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o '\n' deixado no buffer

        switch (opcao) {

            // 🟢 1. Adicionar item
            case 1:
                if (total < MAX_ITENS) {
                    printf("\n--- Adicionar novo item ---\n");
                    printf("Nome: ");
                    fgets(mochila[total].nome, 30, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                    printf("Tipo: ");
                    fgets(mochila[total].tipo, 20, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    total++;
                    printf("✅ Item adicionado com sucesso!\n");
                } else {
                    printf("⚠️ Mochila cheia! Máximo de %d itens.\n", MAX_ITENS);
                }
                break;

            // 🔴 2. Remover item
            case 2:
                if (total == 0) {
                    printf("⚠️ Mochila vazia! Nenhum item para remover.\n");
                } else {
                    char nomeRemover[30];
                    printf("\n--- Remover item ---\n");
                    printf("Nome do item: ");
                    fgets(nomeRemover, 30, stdin);
                    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                    int encontrado = 0;
                    for (int i = 0; i < total; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            // Desloca os próximos itens uma posição para trás
                            for (int j = i; j < total - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            total--;
                            encontrado = 1;
                            printf("🗑️ Item removido com sucesso!\n");
                            break;
                        }
                    }
                    if (!encontrado)
                        printf("❌ Item não encontrado!\n");
                }
                break;

            // 📋 3. Listar itens
            case 3:
                printf("\n--- Itens na mochila ---\n");
                if (total == 0) {
                    printf("⚠️ Nenhum item cadastrado.\n");
                } else {
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("------------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade);
                    }
                }
                break;

            // 🚪 0. Sair
            case 0:
                printf("👋 Saindo do inventário...\n");
                break;

            // ❓ Opção inválida
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
