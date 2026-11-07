#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_PRODUTOS 100
#define ENTRADAS 0
#define SAIDAS 1
#define TAMANHO_LINHA 256

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
 void cadastroProduto(void);
 void listaProdutos(void);
 void consultaProduto(void);
 void atualizarEstoque(void);
 void registrarEntrada(void);
 void registrarSaida(void);
 void relatorioEstoque(void);
 void carregarProdutos(void);
 int salvarProdutos(void);
 int lerLinha(FILE *entrada, char *linha, size_t tamanho);
 int lerInteiro(int *valor);
 int lerPreco(float *valor);
 int lerNome(char nome[], size_t tamanho);
 int converterInteiro(const char *texto, int *valor);
 int converterPreco(const char *texto, float *valor);
 int lerCampoInteiro(char **cursor, char separador, long *valor);
 int lerCampoPreco(char **cursor, char separador, float *valor);

 /* Algoritmo principal: exibe o menu repetidamente e chama a funcao escolhida. */
 int main(void) {


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
        if (!lerInteiro(&opcao)) {
            if (feof(stdin)) {
                printf("\nEntrada encerrada.\n");
                break;
            }
            printf("\nDigite uma opcao usando numeros inteiros.\n");
            opcao = -1;
            continue;
        }

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
    void cadastroProduto(void) {
        if (totalProdutos >= MAX_PRODUTOS) {
            printf("\nLimite de produtos atingido.\n");
            return;
        }

        Produto *produto = &produtos[totalProdutos];

        printf("\nCodigo: ");
        if (!lerInteiro(&produto->codigo)) {
            printf("\nO codigo deve ser um numero inteiro valido.\n");
            return;
        }
        if (produto->codigo <= 0) {
            printf("\nO codigo deve ser maior que zero.\n");
            return;
        }
        for (int i = 0; i < totalProdutos; i++) {
    if (produtos[i].codigo == produto->codigo) {
        printf("\nEsse codigo ja esta cadastrado.\n");
        return;
    }
}

        printf("Nome: ");
        if (!lerNome(produto->nome, sizeof(produto->nome))) {
            printf("\nNome invalido ou muito longo (maximo de 49 caracteres).\n");
            return;
        }

        printf("Quantidade: ");
        if (!lerInteiro(&produto->quantidade)) {
            printf("\nA quantidade deve ser um numero inteiro valido.\n");
            return;
        }
        if (produto->quantidade < 0) {
    printf("\nA quantidade nao pode ser negativa.\n");
    return;
}

        printf("Preco: ");
        if (!lerPreco(&produto->preco)) {
            printf("\nO preco deve ser um numero decimal valido.\n");
            return;
        }
        if (produto->preco < 0) {
    printf("\nO preco nao pode ser negativo.\n");
    return;
}

        totalProdutos++;
        if (!salvarProdutos()) {
            totalProdutos--;
            printf("\nCadastro cancelado porque os dados nao foram salvos.\n");
            return;
        }

        printf("\nProduto cadastrado com sucesso!\n");
    }

    /* Percorre o vetor e mostra os dados de todos os produtos cadastrados. */
    void listaProdutos(void) {
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
    void consultaProduto(void) {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para consulta: ");
        if (!lerInteiro(&codigoBusca)) {
            printf("\nO codigo deve ser um numero inteiro valido.\n");
            return;
        }

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
    void atualizarEstoque(void) {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }
        
        int codigoBusca;
        int novaQuantidade;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para atualizar o estoque: ");
        if (!lerInteiro(&codigoBusca)) {
            printf("\nO codigo deve ser um numero inteiro valido.\n");
            return;
        }

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a nova quantidade: ");
                if (!lerInteiro(&novaQuantidade)) {
                    printf("\nA quantidade deve ser um numero inteiro valido.\n");
                    return;
                }

                if (novaQuantidade < 0) {
                    printf("\nQuantidade invalida. A quantidade nao pode ser negativa.\n");
                } else {
                    int quantidadeAnterior = produtos[i].quantidade;
                    produtos[i].quantidade = novaQuantidade;
                    if (!salvarProdutos()) {
                        produtos[i].quantidade = quantidadeAnterior;
                        printf("\nAtualizacao cancelada; o estoque anterior foi restaurado.\n");
                    } else {
                        printf("\nEstoque atualizado com sucesso!\n");
                    }
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
    void registrarEntrada(void) {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int quantidadeEntrada;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para registrar a entrada: ");
        if (!lerInteiro(&codigoBusca)) {
            printf("\nO codigo deve ser um numero inteiro valido.\n");
            return;
        }

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a quantidade de entrada: ");
                if (!lerInteiro(&quantidadeEntrada)) {
                    printf("\nA quantidade deve ser um numero inteiro valido.\n");
                    return;
                }

                if (quantidadeEntrada <= 0) {
                    printf("\nQuantidade invalida. A entrada deve ser maior que zero.\n");
                } else if (quantidadeEntrada > INT_MAX - produtos[i].quantidade ||
                           quantidadeEntrada > INT_MAX - movimentacoes[i][ENTRADAS]) {
                    printf("\nA entrada ultrapassa o limite de quantidade permitido.\n");
                } else {
                    produtos[i].quantidade += quantidadeEntrada;
                    movimentacoes[i][ENTRADAS] += quantidadeEntrada;
                    if (!salvarProdutos()) {
                        produtos[i].quantidade -= quantidadeEntrada;
                        movimentacoes[i][ENTRADAS] -= quantidadeEntrada;
                        printf("\nEntrada cancelada; os valores anteriores foram restaurados.\n");
                    } else {
                        printf("\nEntrada registrada com sucesso. Novo estoque: %d\n", produtos[i].quantidade);
                    }
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
    void registrarSaida(void) {
        if(totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        int codigoBusca;
        int quantidadeSaida;
        int encontrado = 0;

        printf("\nDigite o codigo do produto para registrar a saida: ");
        if (!lerInteiro(&codigoBusca)) {
            printf("\nO codigo deve ser um numero inteiro valido.\n");
            return;
        }

        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigoBusca) {
                printf("Quantidade atual: %d\n", produtos[i].quantidade);
                printf("Digite a quantidade de saida: ");
                if (!lerInteiro(&quantidadeSaida)) {
                    printf("\nA quantidade deve ser um numero inteiro valido.\n");
                    return;
                }

                if (quantidadeSaida <= 0) {
                    printf("\nQuantidade invalida. A saida deve ser maior que zero.\n");
                } else if (quantidadeSaida > produtos[i].quantidade) {
                    printf("\nQuantidade insuficiente em estoque. Estoque atual: %d\n", produtos[i].quantidade);
                } else if (quantidadeSaida > INT_MAX - movimentacoes[i][SAIDAS]) {
                    printf("\nO total de saidas ultrapassaria o limite permitido.\n");
                } else {
                    produtos[i].quantidade -= quantidadeSaida;
                    movimentacoes[i][SAIDAS] += quantidadeSaida;
                    if (!salvarProdutos()) {
                        produtos[i].quantidade += quantidadeSaida;
                        movimentacoes[i][SAIDAS] -= quantidadeSaida;
                        printf("\nSaida cancelada; os valores anteriores foram restaurados.\n");
                    } else {
                        printf("\nSaida registrada com sucesso. Novo estoque: %d\n", produtos[i].quantidade);
                    }
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
    void relatorioEstoque(void) {
        if (totalProdutos == 0) {
            printf("\nNenhum produto cadastrado.\n");
            return;
        }

        long long totalUnidades = 0;
        double valorTotalEstoque = 0.0;

        printf("\n=== Relatorio de Estoque ===\n");

        for (int i = 0; i < totalProdutos; i++) {
            printf("\nCodigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            printf("Total de entradas registradas: %d\n", movimentacoes[i][ENTRADAS]);
            printf("Total de saidas registradas: %d\n", movimentacoes[i][SAIDAS]);

            totalUnidades += produtos[i].quantidade;
            valorTotalEstoque += (double)produtos[i].quantidade * (double)produtos[i].preco;
        }
        printf("\nTipos de produtos cadastrados: %d\n", totalProdutos);
        printf("Total de unidades em estoque: %lld\n", totalUnidades);
        printf("Valor total do estoque: R$ %.2f\n", valorTotalEstoque);
        
    }

    int salvarProdutos(void) {
        const char *arquivoTemporario = "produtos.tmp";
        FILE *arquivo = fopen(arquivoTemporario, "w");

        if (arquivo == NULL) {
            printf("\nErro: nao foi possivel criar o arquivo temporario.\n");
            return 0;
        }

        int sucesso = fprintf(arquivo, "%d\n", totalProdutos) >= 0;

        for (int i = 0; sucesso && i < totalProdutos; i++) {
            sucesso = fprintf(arquivo, "%d;%d;%.9g;%d,%d;%s\n",
                              produtos[i].codigo,
                              produtos[i].quantidade,
                              (double)produtos[i].preco,
                              movimentacoes[i][ENTRADAS],
                              movimentacoes[i][SAIDAS],
                              produtos[i].nome) >= 0;
        }

        if (ferror(arquivo)) {
            sucesso = 0;
        }
        if (fclose(arquivo) != 0) {
            sucesso = 0;
        }

        if (!sucesso) {
            remove(arquivoTemporario);
            printf("\nErro ao gravar os dados. O arquivo anterior foi mantido.\n");
            return 0;
        }

#ifdef _WIN32
        if (!MoveFileExA(arquivoTemporario, "produtos.txt",
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
#else
        if (rename(arquivoTemporario, "produtos.txt") != 0) {
#endif
            remove(arquivoTemporario);
            printf("\nErro ao substituir produtos.txt. O arquivo anterior foi mantido.\n");
            return 0;
        }

        printf("\nDados salvos com seguranca em produtos.txt.\n");
        return 1;
    }

    void carregarProdutos(void) {
        FILE *arquivo = fopen("produtos.txt", "r");

        /* Na primeira execucao, o arquivo ainda nao existe. */
        if (arquivo == NULL) {
            totalProdutos = 0;
            return;
        }

        char linha[TAMANHO_LINHA];
        int quantidadeLida;
        Produto produtosLidos[MAX_PRODUTOS];
        int movimentacoesLidas[MAX_PRODUTOS][2] = {{0}};
        int arquivoValido = 1;
        totalProdutos = 0;

        if (!lerLinha(arquivo, linha, sizeof(linha)) ||
            !converterInteiro(linha, &quantidadeLida) ||
            quantidadeLida < 0 || quantidadeLida > MAX_PRODUTOS) {
            arquivoValido = 0;
        }

        for (int i = 0; arquivoValido && i < quantidadeLida; i++) {
            long codigo, quantidade, entradas, saidas;
            float preco;
            char *cursor;

            if (!lerLinha(arquivo, linha, sizeof(linha))) {
                arquivoValido = 0;
                break;
            }

            cursor = linha;
            if (!lerCampoInteiro(&cursor, ';', &codigo) ||
                !lerCampoInteiro(&cursor, ';', &quantidade) ||
                !lerCampoPreco(&cursor, ';', &preco) ||
                !lerCampoInteiro(&cursor, ',', &entradas) ||
                !lerCampoInteiro(&cursor, ';', &saidas)) {
                arquivoValido = 0;
                break;
            }

            size_t tamanhoNome = strlen(cursor);
            if (codigo <= 0 || codigo > INT_MAX ||
                quantidade < 0 || quantidade > INT_MAX ||
                entradas < 0 || entradas > INT_MAX ||
                saidas < 0 || saidas > INT_MAX ||
                preco < 0 || !isfinite(preco) ||
                tamanhoNome == 0 || tamanhoNome >= sizeof(produtosLidos[i].nome)) {
                arquivoValido = 0;
                break;
            }

            for (int j = 0; j < i; j++) {
                if (produtosLidos[j].codigo == (int)codigo) {
                    arquivoValido = 0;
                    break;
                }
            }
            if (!arquivoValido) {
                break;
            }

            produtosLidos[i].codigo = (int)codigo;
            produtosLidos[i].quantidade = (int)quantidade;
            produtosLidos[i].preco = preco;
            movimentacoesLidas[i][ENTRADAS] = (int)entradas;
            movimentacoesLidas[i][SAIDAS] = (int)saidas;
            memcpy(produtosLidos[i].nome, cursor, tamanhoNome + 1);
        }

        /* Recusa qualquer conteudo extra nao vazio ao final do arquivo. */
        while (arquivoValido && fgets(linha, sizeof(linha), arquivo) != NULL) {
            for (char *p = linha; *p != '\0'; p++) {
                if (!isspace((unsigned char)*p)) {
                    arquivoValido = 0;
                    break;
                }
            }
        }
        if (ferror(arquivo)) {
            arquivoValido = 0;
        }
        if (fclose(arquivo) != 0) {
            arquivoValido = 0;
        }

        if (!arquivoValido) {
            printf("\nArquivo produtos.txt invalido ou corrompido. Nenhum produto foi carregado.\n");
            return;
        }

        for (int i = 0; i < quantidadeLida; i++) {
            produtos[i] = produtosLidos[i];
            movimentacoes[i][ENTRADAS] = movimentacoesLidas[i][ENTRADAS];
            movimentacoes[i][SAIDAS] = movimentacoesLidas[i][SAIDAS];
        }
        totalProdutos = quantidadeLida;
        printf("\nProdutos carregados: %d.\n", totalProdutos);
    }

    int lerLinha(FILE *entrada, char *linha, size_t tamanho) {
        if (fgets(linha, (int)tamanho, entrada) == NULL) {
            return 0;
        }

        size_t comprimento = strlen(linha);
        if (comprimento > 0 && linha[comprimento - 1] == '\n') {
            linha[--comprimento] = '\0';
        } else if (!feof(entrada)) {
            int caractere;
            while ((caractere = fgetc(entrada)) != '\n' && caractere != EOF) {
                /* Descarta o restante de uma linha grande demais. */
            }
            return 0;
        }

        if (comprimento > 0 && linha[comprimento - 1] == '\r') {
            linha[comprimento - 1] = '\0';
        }
        return 1;
    }

    int converterInteiro(const char *texto, int *valor) {
        char *fim;
        errno = 0;
        long valorLido = strtol(texto, &fim, 10);

        if (fim == texto) {
            return 0;
        }
        while (isspace((unsigned char)*fim)) {
            fim++;
        }
        if (*fim != '\0' || errno == ERANGE ||
            valorLido < INT_MIN || valorLido > INT_MAX) {
            return 0;
        }

        *valor = (int)valorLido;
        return 1;
    }

    int converterPreco(const char *texto, float *valor) {
        char *fim;
        errno = 0;
        float valorLido = strtof(texto, &fim);

        if (fim == texto) {
            return 0;
        }
        while (isspace((unsigned char)*fim)) {
            fim++;
        }
        if (*fim != '\0' || errno == ERANGE || !isfinite(valorLido)) {
            return 0;
        }

        *valor = valorLido;
        return 1;
    }

    int lerInteiro(int *valor) {
        char linha[128];
        return lerLinha(stdin, linha, sizeof(linha)) && converterInteiro(linha, valor);
    }

    int lerPreco(float *valor) {
        char linha[128];
        return lerLinha(stdin, linha, sizeof(linha)) && converterPreco(linha, valor);
    }

    int lerNome(char nome[], size_t tamanho) {
        char linha[128];
        if (!lerLinha(stdin, linha, sizeof(linha))) {
            return 0;
        }

        size_t comprimento = strlen(linha);
        if (comprimento == 0 || comprimento >= tamanho) {
            return 0;
        }

        memcpy(nome, linha, comprimento + 1);
        return 1;
    }

    int lerCampoInteiro(char **cursor, char separador, long *valor) {
        char *fim;
        errno = 0;
        long valorLido = strtol(*cursor, &fim, 10);
        if (*cursor == fim || errno == ERANGE || *fim != separador) {
            return 0;
        }

        *valor = valorLido;
        *cursor = fim + 1;
        return 1;
    }

    int lerCampoPreco(char **cursor, char separador, float *valor) {
        char *fim;
        errno = 0;
        float valorLido = strtof(*cursor, &fim);
        if (*cursor == fim || errno == ERANGE || !isfinite(valorLido) || *fim != separador) {
            return 0;
        }

        *valor = valorLido;
        *cursor = fim + 1;
        return 1;
    }



        
    

    



