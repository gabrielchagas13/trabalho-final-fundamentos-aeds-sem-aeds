#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estruturas
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
    int codigo;
    char dataEntrada[11];
    char dataSaida[11];
    int quantidadeDiarias;
    int codigoCliente;
    int numeroQuarto;
} Estadia;

// Funções
int gerarCodigoUnicoCliente() {
    FILE *file = fopen("clientes.dat", "rb");
    if (file == NULL) {
        return 1; // Primeiro código
    }

    Cliente cliente;
    int maxCodigo = 0;
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.codigo > maxCodigo) {
            maxCodigo = cliente.codigo;
        }
    }
    fclose(file);
    return maxCodigo + 1;
}

int gerarCodigoUnicoFuncionario() {
    FILE *file = fopen("funcionarios.dat", "rb");
    if (file == NULL) {
        return 1; // Primeiro código
    }

    Funcionario funcionario;
    int maxCodigo = 0;
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.codigo > maxCodigo) {
            maxCodigo = funcionario.codigo;
        }
    }
    fclose(file);
    return maxCodigo + 1;
}

int calcularDiarias(char *dataEntrada, char *dataSaida) {
    struct tm tmEntrada, tmSaida;
    strptime(dataEntrada, "%d/%m/%Y", &tmEntrada);
    strptime(dataSaida, "%d/%m/%Y", &tmSaida);
    time_t tEntrada = mktime(&tmEntrada);
    time_t tSaida = mktime(&tmSaida);
    double seconds = difftime(tSaida, tEntrada);
    return (seconds / (60 * 60 * 24));
}

void cadastrarCliente() {
    Cliente cliente;
    FILE *file = fopen("clientes.dat", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    cliente.codigo = gerarCodigoUnicoCliente();
    printf("Codigo do Cliente: %d\n", cliente.codigo);
    printf("Nome: ");
    scanf(" %[^\n]", cliente.nome);
    printf("Endereco: ");
    scanf(" %[^\n]", cliente.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", cliente.telefone);

    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);

    printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarFuncionario() {
    Funcionario funcionario;
    FILE *file = fopen("funcionarios.dat", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    funcionario.codigo = gerarCodigoUnicoFuncionario();
    printf("Codigo do Funcionario: %d\n", funcionario.codigo);
    printf("Nome: ");
    scanf(" %[^\n]", funcionario.nome);
    printf("Telefone: ");
    scanf(" %[^\n]", funcionario.telefone);
    printf("Cargo: ");
    scanf(" %[^\n]", funcionario.cargo);
    printf("Salario: ");
    scanf("%f", &funcionario.salario);

    fwrite(&funcionario, sizeof(Funcionario), 1, file);
    fclose(file);

    printf("Funcionario cadastrado com sucesso!\n");
}

void cadastrarEstadia() {
    Estadia estadia;
    FILE *file = fopen("estadias.dat", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Codigo da Estadia: ");
    scanf("%d", &estadia.codigo);
    printf("Codigo do Cliente: ");
    scanf("%d", &estadia.codigoCliente);
    printf("Quantidade de Hospedes: ");
    int quantidadeHospedes;
    scanf("%d", &quantidadeHospedes);

    // Aqui você deve verificar a disponibilidade de quartos para a quantidade de hóspedes
    // Vamos assumir que o quarto número 101 está disponível para simplificar
    estadia.numeroQuarto = 101;

    printf("Data de Entrada (dd/mm/yyyy): ");
    scanf(" %[^\n]", estadia.dataEntrada);
    printf("Data de Saida (dd/mm/yyyy): ");
    scanf(" %[^\n]", estadia.dataSaida);

    estadia.quantidadeDiarias = calcularDiarias(estadia.dataEntrada, estadia.dataSaida);

    fwrite(&estadia, sizeof(Estadia), 1, file);
    fclose(file);

    printf("Estadia cadastrada com sucesso!\n");
}

int main() {
    int opcao;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionario\n");
        printf("3. Cadastrar Estadia\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarFuncionario();
                break;
            case 3:
                cadastrarEstadia();
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
