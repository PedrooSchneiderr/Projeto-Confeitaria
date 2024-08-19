#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NOME 100
#define MAX_ENDERECO 200

typedef struct {
    int produto;
    int qtd;
} Escolha;

typedef struct {
    int ID;
    char nome[MAX_NOME];
    float valor;
} Produto;

typedef struct {
    char nome[MAX_NOME];
    int cpf;
    int contato;
    char endereco[MAX_ENDERECO];
} Cadastrando;

typedef struct {
    int num_pedido;
    int qntd;
    float valor_pedido;
} Pedido;

int bem_vindo() {
    int option = 0;
    printf("**********************************************\n");
    printf("*           Bem-vindo A Confeitaria          *\n");
    printf("*        === Delicias Tecnologicas ===       *\n");
    printf("**********************************************\n");
    printf("\033[1;1H\033[2J"); // Limpa a tela
    return option;
}

void menu() {
    printf("\n********************************************\n");
    printf("*                Bem-vindo                 *\n");
    printf("*      Conheca um pouco do nosso menu      *\n");
    printf("********************************************\n");
    printf("Qual das opcoes deseja?\n");
    printf("1- Nega Maluca (R$ 80)\n");
    printf("2- Cento Salgados (R$ 120)\n");
}

Escolha* escolha_menu() {
    Escolha* escolha = malloc(sizeof(Escolha));
    if (escolha == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    menu();
    printf("Opcao: ");
    scanf("%d", &escolha->produto);
    printf("Digite a quantidade que deseja: ");
    scanf("%d", &escolha->qtd);
    return escolha;
}

Produto* criar_produto(int ID, const char* nome, float valor) {
    Produto* produto = malloc(sizeof(Produto));
    if (produto == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    produto->ID = ID;
    strncpy(produto->nome, nome, MAX_NOME);
    produto->valor = valor;
    return produto;
}

void imprimir_produto(Produto* produto) {
    printf("ID: %d\n", produto->ID);
    printf("Nome: %s\n", produto->nome);
    printf("Valor: R$ %.2f\n", produto->valor);
}

Produto* produto_escolher(int produto) {
    Produto* produtos[2];
    produtos[0] = criar_produto(1, "Nega Maluca", 80.0);
    produtos[1] = criar_produto(2, "Cento de salgados", 120.0);

    if (produto == 1 || produto == 2) {
        return produtos[produto - 1];
    } else {
        printf("Opcao invalida! Selecionando o primeiro produto.\n");
        return produtos[0];
    }
}

Cadastrando* cadastrar_cliente() {
    Cadastrando* cadastro = malloc(sizeof(Cadastrando));
    if (cadastro == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    getchar(); // Limpa o buffer de entrada antes de fgets
    printf("Digite seu nome: ");
    fgets(cadastro->nome, MAX_NOME, stdin);
    cadastro->nome[strcspn(cadastro->nome, "\n")] = 0;

    printf("Digite seu CPF (somente numeros): ");
    scanf("%d", &cadastro->cpf);

    printf("Digite o seu numero para contato: ");
    scanf("%d", &cadastro->contato);

    getchar(); // Limpa o buffer de entrada antes de fgets
    printf("Qual o endereco de entrega: ");
    fgets(cadastro->endereco, MAX_ENDERECO, stdin);
    cadastro->endereco[strcspn(cadastro->endereco, "\n")] = 0;

    return cadastro;
}

Pedido* fazer_pedido(Produto* produto_escolhido, int qntd) {
    Pedido* pedido = malloc(sizeof(Pedido));
    if (pedido == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    srand(time(NULL));
    pedido->num_pedido = rand() % 900000 + 100000;
    pedido->qntd = qntd;
    pedido->valor_pedido = produto_escolhido->valor * qntd;
    return pedido; // Corrigido para retornar o ponteiro do pedido em vez de 0
}

int main() {
    int opcao;
    Escolha* escolha;
    Produto* produto;
    Cadastrando* cliente;
    Pedido* pedido;

    opcao = bem_vindo();
    escolha = escolha_menu();
    produto = produto_escolher(escolha->produto);

    cliente = cadastrar_cliente();
    pedido = fazer_pedido(produto, escolha->qtd);

    printf("\nResumo do pedido:\n");

    // Imprime detalhes do pedido
    imprimir_produto(produto);
    printf("Quantidade: %d\n", pedido->qntd);
    printf("Valor total: R$ %.2f\n", pedido->valor_pedido);
    printf("Nome do cliente: %s\n", cliente->nome);
    printf("CPF: %d\n", cliente->cpf);
    printf("Contato: %d\n", cliente->contato);
    printf("Endereco: %s\n", cliente->endereco);
    printf("Numero do pedido: %d\n", pedido->num_pedido);

    // Libera a memória alocada
    free(escolha);
    free(produto);
    free(cliente);
    free(pedido);

    return 0;
}

