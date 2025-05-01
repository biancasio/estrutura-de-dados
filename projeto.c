#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     

// Define uma estrutura para representar uma data
typedef struct Data {
    int dia;    // Dia da data
    int mes;    // Mês da data
    int ano;    // Ano da data
} Data;

// Define a estrutura que representa um paciente (nó da lista)
typedef struct Registro {
    char nome[80];          // Nome do paciente 
    int idade;              // Idade do paciente
    char rg[9];             // RG do paciente 
    Data* entrada;          // Ponteiro para a data de entrada
    struct Registro* proximo; // Ponteiro para o próximo registro 
} Registro;

// Define a estrutura que representa a lista de pacientes
typedef struct Lista {
    Registro* inicio;  // Ponteiro para o primeiro paciente da lista
    int qtd;           // Quantidade de pacientes 
} Lista;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX CADASTRAR XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// Função que cadastra um novo paciente no início da lista
void cadastrar(Lista* lista) {
    Registro* novo = (Registro*) malloc(sizeof(Registro)); // Aloca memória para um novo paciente
    if (novo == NULL) {
        printf("Erro ao alocar memória para o registro.\n");
        return;
    }

    novo->entrada = (Data*) malloc(sizeof(Data)); // Aloca memória para a data de entrada
    if (novo->entrada == NULL) {
        printf("Erro ao alocar memória para a data.\n");
        free(novo);
        return;
    }

    getchar(); // Limpa o buffer

    printf("\nDigite o nome do paciente: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; // Remove o \n 
    printf("Digite a idade do paciente: ");
    scanf("%d", &novo->idade);
    getchar();

    printf("Digite o RG do paciente: ");
    fgets(novo->rg, sizeof(novo->rg), stdin);
    novo->rg[strcspn(novo->rg, "\n")] = '\0';

    printf("Digite a data de entrada (dd mm aaaa): ");
    scanf("%d %d %d", &novo->entrada->dia, &novo->entrada->mes, &novo->entrada->ano);

    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->qtd++;

    printf("Paciente cadastrado com sucesso! Total de pacientes: %d\n", lista->qtd);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX LISTAR XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// Função que lista todos os pacientes cadastrados
void elista(Lista* lista) {
    if (lista->inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    Registro* atual = lista->inicio;
    int pos = 1;

    printf("\n--- Lista de Pacientes Cadastrados ---\n");

    while (atual != NULL) {
        printf("Paciente %d:\n", pos);
        printf("  Nome: %s\n", atual->nome);
        printf("  Idade: %d\n", atual->idade);
        printf("  RG: %s\n", atual->rg);
        printf("  Data de entrada: %02d/%02d/%04d\n",
               atual->entrada->dia,
               atual->entrada->mes,
               atual->entrada->ano);
        printf("--------------------------------------\n");
        atual = atual->proximo;
        pos++;
    }

    printf("Total de pacientes: %d\n", lista->qtd);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX CONSULTAR XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Função que consulta um paciente pelo RG
void consultar(Lista* lista, const char* rgBusca) {
    Registro* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->rg, rgBusca) == 0) {
            printf("\nPaciente encontrado:\n");
            printf("  Nome: %s\n", atual->nome);
            printf("  Idade: %d\n", atual->idade);
            printf("  RG: %s\n", atual->rg);
            printf("  Data de entrada: %02d/%02d/%04d\n",
                   atual->entrada->dia, atual->entrada->mes, atual->entrada->ano);
            return;
        }
        atual = atual->proximo;
    }
    printf("Paciente com RG %s não encontrado.\n", rgBusca);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ATUALIZAR XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Função que atualiza dados de um paciente pelo RG
void atualizar(Lista* lista, const char* rgBusca) {
    Registro* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->rg, rgBusca) == 0) {
            printf("Atualizando paciente com RG %s:\n", rgBusca);

            getchar(); // Limpa o buffer

            printf("Novo nome: ");
            fgets(atual->nome, sizeof(atual->nome), stdin);
            atual->nome[strcspn(atual->nome, "\n")] = '\0';

            printf("Nova idade: ");
            scanf("%d", &atual->idade);
            getchar();

            printf("Nova data de entrada (dd mm aaaa): ");
            scanf("%d %d %d", &atual->entrada->dia, &atual->entrada->mes, &atual->entrada->ano);

            printf("Dados atualizados com sucesso.\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Paciente com RG %s não encontrado.\n", rgBusca);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX REMOVER XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Função que remove um paciente pelo RG
void remover(Lista* lista, const char* rgBusca) {
    Registro* atual = lista->inicio;
    Registro* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->rg, rgBusca) == 0) {
            if (anterior == NULL) {
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual->entrada);
            free(atual);
            lista->qtd--;

            printf("Paciente com RG %s removido com sucesso.\n", rgBusca);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Paciente com RG %s não encontrado.\n", rgBusca);
}




//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX MENU XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Função principal com menu
int main() {
    Lista listaPacientes;
    listaPacientes.inicio = NULL;
    listaPacientes.qtd = 0;

    int opcao;
    int op;
    char rgBusca[9];
   
    while (opcao != 0){
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar;\n");
        printf("2. Atendimento;\n");
        printf("3. Atendimento prioritário;\n");
        printf("4. Pesquisa;\n");
        printf("5. Desfazer;\n");
        printf("6. Carregar/ Salvar;\n");
        printf("7. Sobre;\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 1){
            
//Operações: Cadastrar novo paciente; Consultar paciente cadastrado; Mostrar lista completa; Atualizar dados de paciente; Remover paciente.
            while(op!=0){
                printf("\n--- Menu - Cadastrar ---\n");
                printf("1. Cadastrar Novo Paciente;\n");
                printf("2. Consultar Paciente Cadastrado;\n");
                printf("3. Mostrar Lista Completa;\n");
                printf("4. Atualizar Dados de Paciente;\n");
                printf("5. Remover Paciente;\n");
                printf("0. Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &op);
                
                if (op==1){
                    cadastrar(&listaPacientes);
                }
                else if (op==2){
                    printf("Digite o RG do paciente: ");
                    scanf("%s", rgBusca);
                    consultar(&listaPacientes, rgBusca);
                }
                else if (op==3){
                    elista(&listaPacientes);
                }
                else if (op==4){
                    printf("Digite o RG do paciente a atualizar: ");
                    scanf("%s", rgBusca);
                    atualizar(&listaPacientes, rgBusca);
                }
                else if (op==5){
                    printf("Digite o RG do paciente a remover: ");
                    scanf("%s", rgBusca);
                    remover(&listaPacientes, rgBusca);
                }
                else if(op==0){
                    printf("Encerrando o programa...\n");
                }
                else{
                    printf("Opção inválida.\n");
                }    
            }      
        }
    }
}