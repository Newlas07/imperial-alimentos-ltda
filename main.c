 #include <stdio.h>

#define MAX_PRODUTOS 100

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

 //Prototipos das funcoes
 void cadastroProduto();
 void listaProdutos();
 void consultaProduto();
 void atualizarEstoque();
 void registrarEntrada();
 void registrarSaida();
 void relatorioEstoque();

 int main() {


     int opcao;

     do {
        printf("\n=========================================================\n");
        printf("             Imperial Alimentos Ltda\n");
        printf("             SISTEMA DE GERENCIAMENTO\n");
        printf("=========================================================\n");

        printf("\n 1  - Cadastro de Produtos");
        printf("\n2  - lista de Produtos");
        printf("\n3  - consulta de Produtos");
        printf("\n4  - atualizar estoque");
        printf("\n5  - Registrar entrada de produtos");
        printf("\n6  - Registrar saída de produtos");
        printf("\n7  - Relatório de estoque");
        printf("\n0  -    Sair");

        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastroProduto();
                break;
            case 2:
                listaProdutos();
                break;
            case 3:
                consultaProduto();
                break;
            case 4:
                atualizarEstoque();
                break;
            case 5:
                registrarEntrada();
                break;
            case 6:
                registrarSaida();
                break;
            case 7:
                relatorioEstoque();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        } while (opcao != 0);

        return 0;
    }

    //Funcoes iniciais

    void cadastroProduto() {
        if (totalProdutos >= MAX_PRODUTOS) {
            printf("\nLimite de produtos atingido.\n");
            return;
        }

        Produto *produto = &produtos[totalProdutos];

        printf("\nCodigo: ");
        scanf("%d", &produto->codigo);

        printf("Nome: ");
        scanf(" %49[^\n]", produto->nome);

        printf("Quantidade: ");
        scanf("%d", &produto->quantidade);

        printf("Preco: ");
        scanf("%f", &produto->preco);

        totalProdutos++;

        printf("\nProduto cadastrado com sucesso!\n");
    }

    void listaProdutos() {
        if (totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        printf("\n=== Produtos cadastrados ===\n");

        for (int i = 0; i < totalProdutos; i++) {
            printf("\nCodigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
        }
    }

    void consultaProduto() {
        printf("\nModulo de consulta de produtos. \n");
    }

    void atualizarEstoque() {
        printf("\nModulo de atualizacao de estoque. \n");
    }

    void registrarEntrada() {
        printf("\nModulo de registro de entrada de produtos. \n");
    }

    void registrarSaida() {
        printf("\nModulo de registro de saida de produtos. \n");
    }

    void relatorioEstoque() {
        printf("\nModulo de relatorio de estoque. \n");
    }


