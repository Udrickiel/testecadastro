//cadastro simples de clientes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_clientes 100
//Inclusao de bibliotecas basicas e definido o maximo de clientes

struct cliente{
    char nome[100];
    int idade;
    char email[100];
};

typedef struct cliente cliente;
//estrutura basica de cadastro de cliente

//Validar email
int validar_email(const char *email){
    const char *arroba = strchr(email, '@');
        if (arroba && strchr(arroba, '.')){
            return 1;
        }
    return 0;
}


void salvar_dados(cliente clientes[], int cont){
    FILE *file = fopen("clientes.txt", "w");
    if (file == NULL){
        printf("Erro ao abir arquivo!\n");
        return;
    }
    fwrite(&cont, sizeof(int), 1, file);
    fwrite(&clientes, sizeof(cliente), cont, file);
    fclose;
    printf("Dados salvos com sucesso!\n");
}

int carregar_dados(cliente clientes[]){
    FILE *file = fopen("cliente.txt", "r");
    if(file == NULL){
        printf("Nenhum arquivo de dados encontrado.\n");
        return 0;
    }
    int cont;
    fread(&cont, sizeof(int), 1, file);
    fread(&clientes, sizeof(cliente), cont, file);
    fclose(file);
    printf("Dados carregados com sucesso!\n");
    return cont;
}

void cadastrar_cliente(cliente clientes[], int*cont){
    if(*cont >= Max_clientes){
        printf("limite de cadastro atingido");
        return;
    }
    printf("Digite o nome do cliente: ");
    scanf(" %99[^\n]", clientes[*cont].nome);
    getchar();

            do{
            printf("Digite a idade do cliente: ");
            scanf("%d", &clientes[*cont].idade);
            getchar();

        //Verificar idade
            if (clientes[*cont].idade < 0 || clientes[*cont].idade >150){
                printf("Idade invalida. Por favor digite uma idade valida.\n ");
            }
        } while (clientes[*cont].idade < 0 || clientes[*cont].idade > 150);

        do{
            printf("Digite o email do cliente: ");
            scanf(" %99[^\n]", clientes[*cont].email);
            getchar();

            if(!validar_email(clientes[*cont].email)){
                printf("Email invalido. Tente novamente.\n");
            }
        }while(!validar_email(clientes[*cont].email));

        (*cont)++;
        printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes(cliente clientes[], int cont){
    printf("\nClientes Cadastrados: \n");
    for (int i = 0; i < cont; i++){
        printf("Cliente %d: \n", i + 1);
        printf("Nome: %s\n",clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("Email: %s\n",clientes[i].email);
    }
}

void buscar_clientes(cliente clientes[], int cont){
    char busca[100];
    printf("Digite o nome ou email do cliente a buscar: ");
    scanf(" %99[^\n]",busca);
    getchar();

    for (int i = 0; i < cont; i++){
        if (strstr(clientes[i].nome, busca)|| strstr(clientes[i].email , busca)) {
            printf("Cliente encontrado: \n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Idade: %d\n", clientes[i].idade);
            printf("Email: %s\n", clientes[i].email);
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

int main(){

    cliente clientes[Max_clientes];
    int cont = 0;
    char op;

    cont = carregar_dados(clientes);


    do {
        printf("\n---Menu---\n");
        printf("1 - Cadastrar cliente.\n");
        printf("2 - Listar Clientes.\n");
        printf("3 - Buscar Clientes.\n");
        printf("4 - Salvar Dados.\n");
        printf("5 - Carregar Dados.\n");
        printf("0 - Sair.\n");
        printf("Escolha uma opçao.");
        scanf(" %c",&op);
        getchar();

        switch (op){
            case '1' :
            cadastrar_cliente(clientes, &cont);
            break;

            case '2' :
            listar_clientes(clientes, cont);
            break;

            case '3' :
            buscar_clientes(clientes, cont);
            break;

            case '4' :
            salvar_dados(clientes, cont);
            break;

            case '5' :
            cont = carregar_dados(clientes);
            break;

            case '0' :
            printf("Saindo...\n");
            break;

            default :
            printf("Opcao invalida.\n");
        }
    }while(op != 0);

    return 0;

}
