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
        printf("\n6  - Registrar saida de produtos");
        printf("\n7  - Relatorio de estoque");
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
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para consulta: ");
        scanf("%d", &codigoBusca);

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("\nProduto encontrado:\n");
                printf("Codigo: %d\n", produtos[i].codigo);
                printf("Nome: %s\n", produtos[i].nome);
                printf("Quantidade: %d\n", produtos[i].quantidade);
                printf("Preco: R$ %.2f\n", produtos[i].preco);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("\nProduto nao encontrado.\n");
        }
    }

    void atualizarEstoque() {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }
        
        int codigoBusca;
        int novaQuantidade;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para atualizar o estoque: ");
        scanf("%d", &codigoBusca);

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a nova quantidade: ");
                scanf("%d", &novaQuantidade);

                if (novaQuantidade < 0) {
                    printf("\nQuantidade invalida. A quantidade nao pode ser negativa.\n");
                } else {
                    produtos[i].quantidade = novaQuantidade;
                    printf("\nEstoque atualizado com sucesso!\n");
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("\nProduto nao encontrado.\n");
        }

        printf("\nModulo de atualizacao de estoque. \n");
    }

    void registrarEntrada() {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int quantidadeEntrada;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para registrar a entrada: ");
        scanf("%d", &codigoBusca);

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a quantidade de entrada: ");
                scanf("%d", &quantidadeEntrada);

                if (quantidadeEntrada < 0) {
                    printf("\nQuantidade invalida. A quantidade nao pode ser negativa.\n");
                } else {
                    produtos[i].quantidade += quantidadeEntrada;
                    printf("\nEntrada registrada com sucesso!. Novo Estoque: %d\n", produtos[i].quantidade);
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("\nProduto nao encontrado.\n");
        }
        printf("\nModulo de registro de entrada de produtos. \n");
    }

    void registrarSaida() {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int quantidadeSaida;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para registrar a saida: ");
        scanf("%d", &codigoBusca);

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a quantidade de saida: ");
                scanf("%d", &quantidadeSaida);

                if (quantidadeSaida <= 0) {
                    printf("\nQuantidade invalida. A quantidade nao pode ser negativa.\n");
                } else if (quantidadeSaida > produtos[i].quantidade) {
                    printf("\nQuantidade insuficiente em estoque. Estoque atual: %d\n", produtos[i].quantidade);
                } else {
                    produtos[i].quantidade -= quantidadeSaida;
                    printf("\nSaida registrada com sucesso!. Novo Estoque: %d\n", produtos[i].quantidade);
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("\nProduto nao encontrado.\n");
        }
        
    }

    void relatorioEstoque() {
        if (totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int totalUnidades = 0;
        float valorTotalEstoque = 0.0;

        printf("\n=== Relatorio de Estoque ===\n");

        for (int i = 0; i < totalProdutos; i++) {
            printf("\nCodigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preco: R$ %.2f\n", produtos[i].preco);

            totalUnidades += produtos[i].quantidade;
            valorTotalEstoque += produtos[i].quantidade * produtos[i].preco;
        }
        printf("\nTipos de produtos cadastrados: %d\n", totalProdutos);
        printf("Total de unidades em estoque: %d\n", totalUnidades);
        printf("Valor total do estoque: R$ %.2f\n", valorTotalEstoque);
        
    }


