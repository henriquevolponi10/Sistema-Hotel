#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_FUNCIONARIOS 100
#define MAX_QUARTOS 100
#define MAX_ESTADIAS 100

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
    char cargo[30];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidade_hospedes;
    float valor_diaria;
    char status[10];
} Quarto;

typedef struct {
    int codigo;
    struct tm data_entrada;
    struct tm data_saida;
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto;
} Estadia;

Cliente clientes[MAX_CLIENTES];
Funcionario funcionarios[MAX_FUNCIONARIOS];
Quarto quartos[MAX_QUARTOS];
Estadia estadias[MAX_ESTADIAS];

int total_clientes = 0;
int total_funcionarios = 0;
int total_quartos = 0;
int total_estadias = 0;

int gerarCodigoUnicoCliente() {
    return total_clientes + 1;
}

int gerarCodigoUnicoFuncionario() {
    return total_funcionarios + 1;
}

int gerarCodigoUnicoEstadia() {
    return total_estadias + 1;
}

void cadastrarCliente() {
    if (total_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente c;
    c.codigo = gerarCodigoUnicoCliente();
    printf("Nome: ");
    scanf(" %[^\n]s", c.nome);
    printf("Endereco: ");
    scanf(" %[^\n]s", c.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]s", c.telefone);

    clientes[total_clientes++] = c;
    printf("Cliente cadastrado com sucesso! Codigo: %d\n", c.codigo);
}

void cadastrarFuncionario() {
    if (total_funcionarios >= MAX_FUNCIONARIOS) {
        printf("Limite de funcionarios atingido.\n");
        return;
    }

    Funcionario f;
    f.codigo = gerarCodigoUnicoFuncionario();
    printf("Nome: ");
    scanf(" %[^\n]s", f.nome);
    printf("Telefone: ");
    scanf(" %[^\n]s", f.telefone);
    printf("Cargo: ");
    scanf(" %[^\n]s", f.cargo);
    printf("Salario: ");
    scanf("%f", &f.salario);

    funcionarios[total_funcionarios++] = f;
    printf("Funcionario cadastrado com sucesso! Codigo: %d\n", f.codigo);
}

void cadastrarQuarto() {
    if (total_quartos >= MAX_QUARTOS) {
        printf("Limite de quartos atingido.\n");
        return;
    }

    Quarto q;
    printf("Numero do quarto: ");
    scanf("%d", &q.numero);
    printf("Quantidade de hospedes: ");
    scanf("%d", &q.quantidade_hospedes);
    printf("Valor da diaria: ");
    scanf("%f", &q.valor_diaria);
    strcpy(q.status, "desocupado");

    quartos[total_quartos++] = q;
    printf("Quarto cadastrado com sucesso! Numero: %d\n", q.numero);
}

int calcularQuantidadeDiarias(struct tm entrada, struct tm saida) {
    time_t t_entrada = mktime(&entrada);
    time_t t_saida = mktime(&saida);
    double diff = difftime(t_saida, t_entrada);
    return diff / (60 * 60 * 24);
}

void cadastrarEstadia() {
    if (total_estadias >= MAX_ESTADIAS) {
        printf("Limite de estadias atingido.\n");
        return;
    }

    int codigo_cliente, numero_quarto;
    struct tm data_entrada, data_saida;
    int quantidade_hospedes;

    printf("Codigo do cliente: ");
    scanf("%d", &codigo_cliente);
    printf("Quantidade de hospedes: ");
    scanf("%d", &quantidade_hospedes);
    printf("Data de entrada (dd mm yyyy hh mm): ");
    scanf("%d %d %d %d %d", &data_entrada.tm_mday, &data_entrada.tm_mon, &data_entrada.tm_year, &data_entrada.tm_hour, &data_entrada.tm_min);
    data_entrada.tm_mon -= 1;
    data_entrada.tm_year -= 1900;
    printf("Data de saida (dd mm yyyy hh mm): ");
    scanf("%d %d %d %d %d", &data_saida.tm_mday, &data_saida.tm_mon, &data_saida.tm_year, &data_saida.tm_hour, &data_saida.tm_min);
    data_saida.tm_mon -= 1;
    data_saida.tm_year -= 1900;

    int quarto_encontrado = 0;
    for (int i = 0; i < total_quartos; i++) {
        if (quartos[i].quantidade_hospedes >= quantidade_hospedes && strcmp(quartos[i].status, "desocupado") == 0) {
            numero_quarto = quartos[i].numero;
            strcpy(quartos[i].status, "ocupado");
            quarto_encontrado = 1;
            break;
        }
    }

    if (!quarto_encontrado) {
        printf("Nao ha quartos disponiveis para a quantidade de hospedes informada.\n");
        return;
    }

    Estadia e;
    e.codigo = gerarCodigoUnicoEstadia();
    e.data_entrada = data_entrada;
    e.data_saida = data_saida;
    e.quantidade_diarias = calcularQuantidadeDiarias(data_entrada, data_saida);
    e.codigo_cliente = codigo_cliente;
    e.numero_quarto = numero_quarto;

    estadias[total_estadias++] = e;
    printf("Estadia cadastrada com sucesso! Codigo: %d\n", e.codigo);
}

void baixaEstadia() {
    int codigo_cliente;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    for (int i = 0; i < total_estadias; i++) {
        if (estadias[i].codigo_cliente == codigo_cliente) {
            for (int j = 0; j < total_quartos; j++) {
                if (quartos[j].numero == estadias[i].numero_quarto) {
                    strcpy(quartos[j].status, "desocupado");
                    float valor_total = estadias[i].quantidade_diarias * quartos[j].valor_diaria;
                    printf("Valor total a ser pago: R$%.2f\n", valor_total);
                    return;
                }
            }
        }
    }

    printf("Estadia nao encontrada para o cliente informado.\n");
}

void pesquisarCliente() {
    int opcao;
    printf("Pesquisar por: 1. Codigo 2. Nome\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int codigo;
        printf("Codigo: ");
        scanf("%d", &codigo);
        for (int i = 0; i < total_clientes; i++) {
            if (clientes[i].codigo == codigo) {
                printf("Codigo: %d, Nome: %s, Endereco: %s, Telefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
        }
    } else if (opcao == 2) {
        char nome[50];
        printf("Nome: ");
        scanf(" %[^\n]s", nome);
        for (int i = 0; i < total_clientes; i++) {
            if (strcmp(clientes[i].nome, nome) == 0) {
                printf("Codigo: %d, Nome: %s, Endereco: %s, Telefone: %s\n", clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
        }
    }

    printf("Cliente nao encontrado.\n");
}

void pesquisarFuncionario() {
    int opcao;
    printf("Pesquisar por: 1. Codigo 2. Nome\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int codigo;
        printf("Codigo: ");
        scanf("%d", &codigo);
        for (int i = 0; i < total_funcionarios; i++) {
            if (funcionarios[i].codigo == codigo) {
                printf("Codigo: %d, Nome: %s, Telefone: %s, Cargo: %s, Salario: %.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
        }
    } else if (opcao == 2) {
        char nome[50];
        printf("Nome: ");
        scanf(" %[^\n]s", nome);
        for (int i = 0; i < total_funcionarios; i++) {
            if (strcmp(funcionarios[i].nome, nome) == 0) {
                printf("Codigo: %d, Nome: %s, Telefone: %s, Cargo: %s, Salario: %.2f\n", funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
        }
    }

    printf("Funcionario nao encontrado.\n");
}

void mostrarEstadiasCliente() {
    int opcao;
    printf("Pesquisar por: 1. Codigo 2. Nome\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int codigo;
        printf("Codigo: ");
        scanf("%d", &codigo);
        for (int i = 0; i < total_estadias; i++) {
            if (estadias[i].codigo_cliente == codigo) {
                printf("Codigo Estadia: %d, Data Entrada: %d/%d/%d %d:%d, Data Saida: %d/%d/%d %d:%d, Quantidade Diarias: %d, Numero Quarto: %d\n", 
                    estadias[i].codigo, estadias[i].data_entrada.tm_mday, estadias[i].data_entrada.tm_mon + 1, estadias[i].data_entrada.tm_year + 1900, estadias[i].data_entrada.tm_hour, estadias[i].data_entrada.tm_min,
                    estadias[i].data_saida.tm_mday, estadias[i].data_saida.tm_mon + 1, estadias[i].data_saida.tm_year + 1900, estadias[i].data_saida.tm_hour, estadias[i].data_saida.tm_min,
                    estadias[i].quantidade_diarias, estadias[i].numero_quarto);
            }
        }
    } else if (opcao == 2) {
        char nome[50];
        printf("Nome: ");
        scanf(" %[^\n]s", nome);
        for (int i = 0; i < total_clientes; i++) {
            if (strcmp(clientes[i].nome, nome) == 0) {
                for (int j = 0; j < total_estadias; j++) {
                    if (estadias[j].codigo_cliente == clientes[i].codigo) {
                        printf("Codigo Estadia: %d, Data Entrada: %d/%d/%d %d:%d, Data Saida: %d/%d/%d %d:%d, Quantidade Diarias: %d, Numero Quarto: %d\n", 
                            estadias[j].codigo, estadias[j].data_entrada.tm_mday, estadias[j].data_entrada.tm_mon + 1, estadias[j].data_entrada.tm_year + 1900, estadias[j].data_entrada.tm_hour, estadias[j].data_entrada.tm_min,
                            estadias[j].data_saida.tm_mday, estadias[j].data_saida.tm_mon + 1, estadias[j].data_saida.tm_year + 1900, estadias[j].data_saida.tm_hour, estadias[j].data_saida.tm_min,
                            estadias[j].quantidade_diarias, estadias[j].numero_quarto);
                    }
                }
            }
        }
    }
}

void calcularPontosFidelidade() {
    int codigo;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo);
    int pontos = 0;
    for (int i = 0; i < total_estadias; i++) {
        if (estadias[i].codigo_cliente == codigo) {
            pontos += estadias[i].quantidade_diarias * 10;
        }
    }
    printf("Pontos de fidelidade: %d\n", pontos);
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Baixa em Estadia\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Mostrar Estadias de Cliente\n");
        printf("9. Calcular Pontos de Fidelidade\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarFuncionario(); break;
            case 3: cadastrarQuarto(); break;
            case 4: cadastrarEstadia(); break;
            case 5: baixaEstadia(); break;
            case 6: pesquisarCliente(); break;
            case 7: pesquisarFuncionario(); break;
            case 8: mostrarEstadiasCliente(); break;
            case 9: calcularPontosFidelidade(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}
