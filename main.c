 #include <stdio.h>

#define MAX_PRODUTOS 100
#define ENTRADAS 0
#define SAIDAS 1

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto produtos[MAX_PRODUTOS];
/* Matriz: cada linha pertence a um produto; colunas guardam entradas e saidas. */
int movimentacoes[MAX_PRODUTOS][2] = {0};
int totalProdutos = 0;

 //Prototipos das funcoes
 void cadastroProduto();
 void listaProdutos();
 void consultaProduto();
 void atualizarEstoque();
 void registrarEntrada();
 void registrarSaida();
 void relatorioEstoque();
 void carregarProdutos();
 void salvarProdutos();

 /* Algoritmo principal: exibe o menu repetidamente e chama a funcao escolhida. */
 int main() {


     int opcao;

     carregarProdutos();

     do {
        printf("\n=========================================================\n");
        printf("             Imperial Alimentos Ltda\n");
        printf("             SISTEMA DE GERENCIAMENTO\n");
        printf("=========================================================\n");

        printf("\n1  - Cadastro de Produtos");
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

    /* Cadastra os dados de um produto na proxima posicao livre do vetor. */
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
        salvarProdutos();

        printf("\nProduto cadastrado com sucesso!\n");
    }

    /* Percorre o vetor e mostra os dados de todos os produtos cadastrados. */
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

    /* Busca pelo codigo informado e mostra os dados quando encontra o produto. */
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

    /* Busca o produto e substitui a quantidade pelo novo valor informado. */
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
                    salvarProdutos();
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

    /* Busca o produto, valida a quantidade e soma a entrada ao estoque e a matriz. */
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
                    movimentacoes[i][ENTRADAS] += quantidadeEntrada;
                    salvarProdutos();
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

    /* Busca o produto, impede saida acima do estoque e registra a saida na matriz. */
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
                    movimentacoes[i][SAIDAS] += quantidadeSaida;
                    salvarProdutos();
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

    /* Percorre os produtos, mostra saldo e movimentacoes, e calcula os totais gerais. */
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
            printf("Total de entradas registradas: %d\n", movimentacoes[i][ENTRADAS]);
            printf("Total de saidas registradas: %d\n", movimentacoes[i][SAIDAS]);

            totalUnidades += produtos[i].quantidade;
            valorTotalEstoque += produtos[i].quantidade * produtos[i].preco;
        }
        printf("\nTipos de produtos cadastrados: %d\n", totalProdutos);
        printf("Total de unidades em estoque: %d\n", totalUnidades);
        printf("Valor total do estoque: R$ %.2f\n", valorTotalEstoque);
        
    }

    void salvarProdutos() {
        FILE *arquivo = fopen("produtos.txt", "w");
        
        if (arquivo == NULL) {
            printf("\nErro ao salvar os produtos.\n");
            return;
        }

        fprintf(arquivo, "%d\n", totalProdutos);

        for (int i =0; i < totalProdutos; i++) {
            fprintf(arquivo, "%d;%d;%.2f;%d,%d;%s\n",
                produtos[i].codigo,
                produtos[i].quantidade,
                produtos[i].preco,
                movimentacoes[i][ENTRADAS],
                movimentacoes[i][SAIDAS],
                produtos[i].nome);
        }        

        fclose(arquivo);
        printf("\nDados salvos no arquivo produtos.txt.\n");
    }
    void carregarProdutos() {
        FILE *arquivo = fopen("produtos.txt", "r");
        
        /* Na primeira execucao, o arquivo nao existe */
        if (arquivo == NULL) {
            return;
        }

        int quantidadeLida;

        if (fscanf(arquivo, "%d", &quantidadeLida)!= 1) {
            fclose(arquivo);
            return;
        }

        if (quantidadeLida < 0) {
           quantidadeLida = 0;
        }
        if (quantidadeLida > MAX_PRODUTOS) {
            quantidadeLida = MAX_PRODUTOS;
        }

        totalProdutos = 0;

        for (int i = 0; i < quantidadeLida; i++) {
            int resultado = fscanf(arquivo, "%d;%d;%f;%d,%d;%49[^\n]",
                &produtos[i].codigo,
                &produtos[i].quantidade,
                &produtos[i].preco,
                &movimentacoes[i][ENTRADAS],
                &movimentacoes[i][SAIDAS],
                produtos[i].nome);
             if (resultado != 6) {
                break;
             }

            totalProdutos++;
        }

        fclose(arquivo);
        printf("\nProdutos carregados: %d.\n", totalProdutos);
    }



        
    

    



