
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "cliente.c"
// #include "apartamento.c"

// definindo o total do vetor
#define tam_vet 50 

#define tam_cpf 11
#define tam_nome 21
#define tam_cidade 20
#define tam_email 20

#define tam_codigo 11
#define tam_data 11

typedef struct { 
    
    char CPF[tam_cpf];
    char nome[tam_nome];
    char cidade[tam_cidade];
    char email[tam_email];
    
} cliente;

typedef struct {
    
    char CODIGO[tam_codigo];
    // 1 = standard, 2 = luxo, 3 = superluxo
    int tipo;
    // 1 = frente, 2 = fundo
    int local;
    float valor;
    
} apartamento;

typedef struct  {
    char CPF[tam_cpf];
    char CODIGO[tam_codigo];
    struct tm dataEntrada;
    struct tm dataSaida;
    float valor;
} reserva;

int existeApt( apartamento *vetorApt, int totalApt, char codigo[])
{
    int i;
    for(i=0; i<totalApt; i++)
    {        
        if ( strcmp(vetorApt[i].CODIGO, codigo) == 0 )
            return i;
    }
            
    // Se nao achou. Retorna -1.
    return -1;
}

int existeCli( cliente *vetorCli, int totalCli, char cpf[]) 
{
    int i;    
    // Percorre os elementos existentes no vetor (de 0 ate totalCli).
    for(i=0; i<totalCli; i++)
    {
        // Compara o cpf neste elemento do vetor, com o cpf informado. Se achou, retorna o indice.
        if ( strcmp(vetorCli[i].CPF, cpf) == 0 )  //PASSEI O ENDEREcO ATRAVeS DE *vetorCli E AQUI POSSO USAR vetorCli[i].
            return i;
    }
            
    // Se  nao achou retorna -1.
    return -1;
}



int existeRes(reserva *vetorRes, int totalRes, char codigo[], struct tm dataEntrada, struct tm dataSaida) {
    int i;
    time_t entrada = mktime(&dataEntrada);
    time_t saida = mktime(&dataSaida);

    for(i=0; i<totalRes; i++) {
        // Mesma reserva é sobre o mesmo apto
        if ( strcmp(vetorRes[i].CODIGO, codigo) == 0) {
            time_t entradaReserva = mktime(&vetorRes[i].dataEntrada);
            time_t saidaReserva = mktime(&vetorRes[i].dataSaida);

            // A data de entrada desejada é durante uma reserva que já existe.
            if(entrada >= entradaReserva && entrada <= saidaReserva) {
                return i;
            }
            // A data de saida desejada é durante uma reserva que já existe.
            if(saida >= entradaReserva && saida <= saidaReserva) {
                return i;
            }
        }        
    }
    return -1;
}

int numeroDias(struct tm entrada, struct tm saida) {

    time_t ent = mktime(&entrada);
    time_t sai = mktime(&saida);

    // Calcula a diferenca entre as datas em segundos.
    double diferenca = difftime(sai, ent);

    return (int) (diferenca / (60*60*24));
}

void consultarResPeriodo(reserva *vetorRes, int *totalRes) {
    int dia, mes, ano;
    int i, count;
    char dataEntrada[tam_data];
    char LIXO[2];
    struct tm data = {0};  


    printf("\nDigite a DATA a ser consultada: ");  
    gets(dataEntrada);
    sscanf(dataEntrada, "%d/%d/%d", &dia, &mes, &ano);
    data.tm_year = ano-1900;
    data.tm_mon = mes-1;
    data.tm_mday = dia;

    time_t dataDesejada = mktime(&data);

    count = 0;
    printf("\nReservas encontradas!\n");
    for( i=0; i<(*totalRes); i++ )
    {     
        time_t dataEntrada = mktime(&vetorRes[i].dataEntrada);
        time_t dataSaida = mktime(&vetorRes[i].dataSaida);

        if(dataEntrada <= dataDesejada && dataDesejada <= dataSaida) {
            printf("Codigo: %s, CPF: %s ", vetorRes[i].CODIGO, vetorRes[i].CPF);
            struct tm tmpEntrada = vetorRes[i].dataEntrada;
            struct tm tmpSaida = vetorRes[i].dataSaida;

            printf("Data de entrada: %02d/%02d/%d ", tmpEntrada.tm_mday, tmpEntrada.tm_mon+1, tmpEntrada.tm_year+1900);
            printf("Data de saida: %02d/%02d/%d ", tmpSaida.tm_mday, tmpSaida.tm_mon+1, tmpSaida.tm_year+1900);

            printf("Valor: %.02f", vetorRes[i].valor);
            count++;
        }
    }

    if(count == 0) {
        printf("Nenhuma reserva encontrada!\n");
    }
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);
}

void consultarResCodigo(reserva *vetorRes, int *totalRes) {
    char LIXO[2];
    char codigo[tam_codigo];
    int i;
    int count = 0;
    
    if( (*totalRes) == 0 )
    {
        printf("\n Nenhuma reserva cadastrada!\n");
    }
    else
    {
        printf("Digite o CODIGO do apartamento:\n");
        gets(codigo);


        for( i=0; i<(*totalRes); i++ )
        {        
            if(strcmp(vetorRes[i].CODIGO, codigo) == 0) {
                printf("Codigo: %s, CPF: %s ", vetorRes[i].CODIGO, vetorRes[i].CPF);
                struct tm tmpEntrada = vetorRes[i].dataEntrada;
                struct tm tmpSaida = vetorRes[i].dataSaida;

                printf("Data de entrada: %02d/%02d/%d ", tmpEntrada.tm_mday, tmpEntrada.tm_mon+1, tmpEntrada.tm_year+1900);
                printf("Data de saida: %02d/%02d/%d ", tmpSaida.tm_mday, tmpSaida.tm_mon+1, tmpSaida.tm_year+1900);

                printf("Valor: %.02f", vetorRes[i].valor);
                count++;
            }
        }
        if(count == 0) {
            printf("Nenhuma reserva encontrada!\n");
        }
    }
    
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);
}


void consultarTodosRes( reserva *vetorRes, int *totalRes ) {
    char LIXO[2];
    int i;
    
    if( (*totalRes) == 0 )
    {
        printf("\n Nenhuma reserva cadastrada!\n");
    }
    else
    {
        printf("\n Todas as reservas:\n");
    
        for( i=0; i<(*totalRes); i++ )
        {        
            printf("Codigo: %s, CPF: %s ", vetorRes[i].CODIGO, vetorRes[i].CPF);
            struct tm dataEntrada = vetorRes[i].dataEntrada;
            struct tm dataSaida = vetorRes[i].dataSaida;

            printf("Data de entrada: %02d/%02d/%d ", dataEntrada.tm_mday, dataEntrada.tm_mon+1, dataEntrada.tm_year+1900);
            printf("Data de saida: %02d/%02d/%d ", dataSaida.tm_mday, dataSaida.tm_mon+1, dataSaida.tm_year+1900);

            printf("Valor: %.02f", vetorRes[i].valor);
        }
    }
    
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);    
}  

void incluirRes(reserva *vetorRes, int *totalRes, apartamento *vetorApt, int *totalApt, cliente *vetorCli, int *totalCli) {
    char codigo[tam_codigo];
    char cpf[tam_cpf];
    char dataEntrada[tam_data];
    char dataSaida[tam_data];
    float valor;
    char LIXO[2];    
        
    if ( *totalRes == tam_vet )
    {
        printf("\nERRO! Sem espaco para incluir mais uma reserva!\n"); 
    }
    else 
    {
        printf("\nIncluir reserva:\n");  
        
        printf("Digite o CODIGO do apartamento: ");
        gets(codigo);

        int indiceApt;
        indiceApt = existeApt(vetorApt, *totalApt, codigo);

        if (indiceApt == -1 ) 
        {
            printf("\n* APARTAMENTO nao existe*\n");
            printf("\nDigite <ENTER> para continuar....");
            gets(LIXO);
            return;
        }

        printf("Digite o CPF do cliente: ");
        gets(cpf);

        if (existeCli(vetorCli, *totalCli, cpf) == -1 ) 
        {
            printf("\n* CLIENTE nao existe!*\n");
            printf("\nDigite <ENTER> para continuar....");
            gets(LIXO);
            return;
        }

        int dia, mes, ano;
        struct tm dataEnt = {0};

        printf("Digite a DATA ENTRADA: ");
        gets(dataEntrada);
        sscanf(dataEntrada, "%d/%d/%d", &dia, &mes, &ano);

        dataEnt.tm_year = ano-1900;
        dataEnt.tm_mon = mes-1;
        dataEnt.tm_mday = dia;

        printf("Digite a DATA SAIDA: ");
        gets(dataSaida);

        struct tm dataSai = {0};
        sscanf(dataSaida, "%d/%d/%d", &dia, &mes, &ano);

        dataSai.tm_year = ano-1900;
        dataSai.tm_mon = mes-1;
        dataSai.tm_mday = dia;
        

        if(existeRes(vetorRes, *totalRes, codigo, dataEnt, dataSai) != -1) {
            printf("\n* RESERVA ja existe!*\n");
            printf("\nDigite <ENTER> para continuar....");
            gets(LIXO);
            return;
        }

        strcpy( vetorRes[*totalRes].CPF, cpf );
        strcpy( vetorRes[*totalRes].CODIGO, codigo );
        vetorRes[*totalRes].dataEntrada = dataEnt;
        vetorRes[*totalRes].dataSaida = dataSai;
        int num = numeroDias(dataEnt, dataSai);

        vetorRes[*totalRes].valor = (float) (num * vetorApt[indiceApt].valor) ;

        (*totalRes)++;
            
        printf("\n* reserva inserida com sucesso!\n");
    }
    
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
}


void incluirApt(apartamento *vetorApt, int *totalApt ) // O tam_vet DE cliente VAI POR REFERENCIA PORQUE QUANDO INCLUIR MAIS 1 TENHO A MAIS. 
{
    char codigo[tam_codigo];
    int tipo;
    int local;
    float valor;
    char LIXO[2];    
        
    if ( *totalApt == tam_vet )
    {
        printf("\nERRO! Sem espaco para incluir mais um apartamento!\n"); 
    }
    else 
    {
        printf("\nIncluir apartamento:\n");  
        
        printf("Digite o CODIGO do apartamento: ");
        gets(codigo);

        if (existeApt(vetorApt, *totalApt, codigo) != -1 ) 
        {
            printf("\n* CODIGO ja existe!*\n");
        }
        else
        {            

            strcpy( vetorApt[*totalApt].CODIGO, codigo );

            printf("Especifique o tipo do apartamento - 1: standard, 2: luxo, 3: superluxo   ");
            scanf("%d", &vetorApt[*totalApt].tipo);
            
            printf("Especifique o local do apartamento - 1: frente, 2: fundos   ");
            scanf("%d", &vetorApt[*totalApt].local);
            
            printf("Especifique o valor   ");
            scanf("%f", &vetorApt[*totalApt].valor);
             
            (*totalApt)++;
            
            printf("\n* apartamento inserido com sucesso!\n");
        }
    }
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
}

void alterarApt( apartamento *vetorApt, int *totalApt )
{
    char codigo[tam_codigo];
    int tipo;
    int local;
    float valor;

    char LIXO[2];
    int indice;
    
    
    printf("\n Alterar apartamento:\n");
    
    printf("Digite o codigo do apartamento: ");
    gets(codigo);
    
    // Verificar se o codigo existe no vetor:
    indice = existeApt(vetorApt, *totalApt, codigo);
    
    if ( indice == -1 )
    {
        printf("\n* Codigo inexistente!*\n");
    }
    else
    {     
        printf("Especifique o tipo do apartamento - 1: standard, 2: luxo, 3: superluxo   ");
        scanf("%d", &vetorApt[indice].tipo);
        
        printf("Especifique o local do apartamento - 1: frente, 2: fundos   ");
        scanf("%d", &vetorApt[indice].local);
        
        printf("Especifique o valor   ");
        scanf("%f", &vetorApt[indice].valor);
                    
        printf("\n* Apartamento alterado com sucesso!\n");
    }
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);
    
}

void apagarApt( apartamento *vetorApt, int *totalApt )
{
    char codigo[tam_codigo];
    int tipo;
    int local;
    float valor;
    char LIXO[2];

    int indice, i;

    printf("\n Apagar apartamento:\n");
    
    printf("Digite o codigo do apartamento: ");
    gets(codigo);
    
    // Verifica se o codigo existe no vetor:
    indice = existeApt(vetorApt, *totalApt, codigo);
    
    if ( indice == -1 )
    {
        printf("\n* Codigo inexistente!*\n");
    }
    else
    {         
        for( i=indice; i<(*totalApt)-1; i++)
        {
             { 
                strcpy( vetorApt[indice].CODIGO, vetorApt[indice+1].CODIGO ); 
                vetorApt[indice].tipo = vetorApt[indice+1].tipo;
                vetorApt[indice].local = vetorApt[indice+1].local;
                vetorApt[indice].valor =vetorApt[indice+1].valor;
            }
        }
        
        // Decrementa *totalApt:
        (*totalApt)--;
            
        printf("\n* Apartamento apagado com sucesso!\n");
    }
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);
    
} 

void consultarApt( apartamento *vetorApt, int *totalApt )
{
    char codigo[tam_codigo];
    char LIXO[2];
    int indice;    
    
    printf("\n Consultar apartamento:\n");
    
    printf("Digite o codigo do apartamento: ");
    gets(codigo);
    
    // Verificar se o codigo existe no vetor:
    indice = existeApt(vetorApt, *totalApt, codigo);
    
    if ( indice == -1 )
    {
        printf("\n* Codigo inexistente!*\n");
    }
    else
    {
        printf("Codigo %s, Tipo %d, Local %d, Valor %.02f\n", vetorApt[indice].CODIGO, vetorApt[indice].tipo, vetorApt[indice].local, vetorApt[indice].valor); 
    }
    
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO); 
}    






void consultarTodosApt( apartamento *vetorApt, int *totalApt )
{
    char LIXO[2];
    int i;
    
    if( (*totalApt) == 0 )
    {
        printf("\n Nenhum apartamento cadastrados!\n");
    }
    else
    {
        printf("\n Todos os apartamentos:\n");
    
        for( i=0; i<(*totalApt); i++ )
        {            
			printf("Codigo %s, Tipo %d, Local %d, Valor %.02f\n", vetorApt[i].CODIGO, vetorApt[i].tipo, vetorApt[i].local, vetorApt[i].valor);
        }
    }
    
    printf("\n  Clique <ENTER> e continue...");
    gets(LIXO);
    
}    




void consultarCli( cliente *vetorCli, int *totalCli )
{
    char cpf[tam_cpf];
    char LIXO[2];
    int indice;
    
    
    printf("\nConsultar cliente:\n");
    
    printf("Digite o CPF do cliente: ");
    gets(cpf);
    
    // Verificar se este CPF existe no vetor:
    indice = existeCli(vetorCli, *totalCli, cpf);
    
    if ( indice == -1 )
    {
        printf("\n* Este CPF nao existe!*\n");
    }
    else
    {
        // Tudo ok, exibir os dados:
            
        printf("CPF: %s\n",  vetorCli[indice].CPF);
        printf("Nome: %s\n", vetorCli[indice].nome);
        printf("Cidade: %s\n", vetorCli[indice].cidade);
        printf("email: %s\n", vetorCli[indice].email);
    }
    
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
    
}    

void incluirCli( cliente *vetorCli, int *totalCli ) // O tam_vet DE cliente VAI POR REFERENCIA PORQUE QUANDO INCLUIR MAIS 1 TENHO A MAIS. 
{
    char cpf[tam_cpf];
    char nome[tam_nome];
    char cidade[tam_cidade];
    char email[tam_email];
    char LIXO[2];    
        
    if ( *totalCli == tam_vet )
    {
        printf("\nERRO! Sem espaco para incluir mais um cliente!\n"); 
    }
    else 
    {
        printf("\nIncluir cliente:\n");  
        
        printf("Digite o CPF do cliente: ");
        gets(cpf);
        //verifica se foi digitado apenas numeros
        int i;
        for(i=0; i<strlen(cpf); i++)
        {
            if(cpf[i] < '0' || cpf[i] > '9')
            {
                printf("\n* CPF invalido! Digite apenas numeros*\n");
                printf("\nDigite <ENTER> para continuar....");
                gets(LIXO);
                return;
            }
        }

        if (existeCli(vetorCli, *totalCli, cpf) != -1 ) 
        {
            printf("\n* CPF ja existe!*\n");
        }
        else
        {            
            printf("Digite o nome do cliente: ");
            gets(nome);

            printf("Digite a cidade do cliente: ");
            gets(cidade);

            printf("Digite o email do cliente: ");
            gets(email);
        
            strcpy( vetorCli[*totalCli].CPF, cpf );
            strcpy( vetorCli[*totalCli].nome, nome );
            strcpy( vetorCli[*totalCli].cidade, cidade );
            strcpy( vetorCli[*totalCli].email, email );
            
            (*totalCli)++;
            
            printf("\n* cliente inserido com sucesso!\n");
        }
    }
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
}

void alterarCli( cliente *vetorCli, int *totalCli )
{
    char cpf[tam_cpf];
    char nome[tam_nome];
    char cidade[tam_cidade];
    char email[tam_email];
    char LIXO[2];
    int indice;    
    
    printf("\nAlterar cliente:\n");
    
    printf("Digite o CPF do cliente: ");
    gets(cpf);
    
    // Verificar se este CPF existe no vetor:
    indice = existeCli(vetorCli, *totalCli, cpf);
    
    if ( indice == -1 )
    {
        printf("\n* CPF inexistente!*\n");
    }
    else
    {
        // Tudo ok, receber o nome e alterar os dados no vetor:            
        printf("Digite o nome do cliente: ");
        gets(nome);

        printf("Digite a cidade do cliente: ");
        gets(cidade);

        printf("Digite o email do cliente: ");
        gets(email);
    
        strcpy( vetorCli[indice].CPF, cpf );
        strcpy( vetorCli[indice].nome, nome );
        strcpy( vetorCli[indice].cidade, cidade );
        strcpy( vetorCli[indice].email, email );
        
        printf("\n* Nome do cliente alterado com sucesso!\n");
    }
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);    
}

void apagarCli( cliente *vetorCli, int *totalCli )
{
    char cpf[tam_cpf];
    char LIXO[2];
    int indice, i;
    
    //APAGAR VETOR  
    printf("\nApagar cliente:\n");
    
    printf("Digite o CPF do cliente: ");
    gets(cpf);
    
    // Verificar se este CPF existe no vetor:
    indice = existeCli(vetorCli, *totalCli, cpf);
    
    if ( indice == -1 )
    {
        printf("\n* Este CPF nao existe!*\n");
    }
    else
    {
           
        for( i=indice; i<(*totalCli)-1; i++) // VAI DO INDICE ATE O NUMERO DE FUNCIONARIOS MENOS 1
        
        {  // >>>>>>>>>>>>>>>> SO INFORMO CPF E NOME?? TENHO QUE COLOCAR CIDADE E EMAIL??
            strcpy( vetorCli[indice].CPF, vetorCli[indice+1].CPF ); 
            strcpy( vetorCli[indice].nome, vetorCli[indice+1].nome );
            strcpy( vetorCli[indice].cidade, vetorCli[indice+1].cidade );
            strcpy( vetorCli[indice].email, vetorCli[indice+1].email );
        }
        
        // Decrementa *totalCli:
        (*totalCli)--;
            
        printf("\n* cliente apagado com sucesso!\n");
    }
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
    
}    

void consultarTodosCli( cliente *vetorCli, int *totalCli ) //NAO PRECISAVA SER POR REFERENCIA, PODIA SER POR VALOR.
{
    char LIXO[2];
    int i;
    
    if( (*totalCli) == 0 )
    {
        printf("\n Nenhum cliente cadastrado!\n");
    }
    else
    {
        printf("\n Exibindo todos os clientes cadastrados:\n");
    
        for( i=0; i<(*totalCli); i++ )
        {            
            printf("\nCPF: %s\n",  vetorCli[i].CPF);  
            printf("Nome: %s\n",   vetorCli[i].nome);
            printf("Cidade: %s\n", vetorCli[i].cidade);
        	printf("email: %s\n", vetorCli[i].email);
        }
    }
    
    printf("\nDigite <ENTER> para continuar....");
    gets(LIXO);
    
}    




int main()
{
    // Cria-se um tipo de dado cliente e apartamento e o vetor tipo cliente tem o tamanho 50 => tam_vet 50.
    // O BDclientes e BDapartamentos é criado vazio - o primeiro a ser cadastrado entra na primeira posicao.
	// Para alterar passa-se por referencia/endereço (ponteiro).
    cliente BDclientes[tam_vet]; 
    apartamento BDapartamentos[tam_vet]; 
    reserva BDreservas[tam_vet];
    int totalRes = 0;
    int totalCli = 0; 
    int totalApt = 0;

    //lendo dados do arquivo
    FILE *arquivo;
    //ler os dados de clientes
    arquivo = fopen("clientes.dat", "rb");
    if(arquivo != NULL)
    {
        //enviar a quantidade de dados
        fread(&totalCli, sizeof(int), 1, arquivo);
        //agora ler os dados do arquivo de clientes
        fread(BDclientes, sizeof(cliente), totalCli, arquivo);
        fclose(arquivo);
    }

    //ler os dados de apartamentos
    arquivo = fopen("apartamentos.dat", "rb");
    if(arquivo != NULL)
    {
        //enviar a quantidade de dados
        fread(&totalApt, sizeof(int), 1, arquivo);
        //agora ler os dados do arquivo de apartamentos
        fread(BDapartamentos, sizeof(apartamento), totalApt, arquivo);
        fclose(arquivo);
    }

    //ler dados de reservas
    arquivo = fopen("reservas.dat", "rb");
    if(arquivo != NULL)
    {
        //enviar a quantidade de dados
        fread(&totalRes, sizeof(int), 1, arquivo);
        //agora ler os dados do arquivo de apartamentos
        fread(BDreservas, sizeof(reserva), totalRes, arquivo);
        fclose(arquivo);
    }

    int principal, submenu;

    do {
        printf("****** MENU ******\n");
        printf("1. Cliente\n");
        printf("2. Apartamento\n");
        printf("3. Reservas\n");
        printf("4. Relatorios\n");
        printf("5. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d%*c", &principal);

        switch (principal) {
            case 1:
                do {
                    printf("\n ------ SUBMENU CLIENTES ------ S\n");
                    printf("1. Incluir\n");
                    printf("2. Alterar\n");
                    printf("3. Excluir\n");
                    printf("4. Consultar\n");
                    printf("5. Consultar todos\n");
                    printf("6. Voltar ao menu anterior\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &submenu);

                    switch (submenu) {
                        case 1:                            
                            incluirCli(BDclientes, &totalCli); 
                            break;
                        case 2:
                            alterarCli(BDclientes, &totalCli);
                            break;
                        case 3:
                            apagarCli(BDclientes, &totalCli);
                            break;
                        case 4:
                            consultarCli(BDclientes, &totalCli);
                            break;
                        case 5:
                            consultarTodosCli(BDclientes, &totalCli);
                            break;
                        case 6:
                            printf("Retornar ao menu anterior.\n");
                            break;
                        default:
                            printf("Digite uma opcao válida!\n");
                    }
                } while (submenu != 6);
                break;
            case 2:
                do {
                    printf("\n  ------ SUBMENU APARTAMENTOS ------ \n");
                    printf("1. Incluir\n");
                    printf("2. Alterar\n");
                    printf("3. Excluir\n");
                    printf("4. Consultar\n");
                    printf("5. Consultar todos\n");
                    printf("6. Voltar ao menu anterior\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &submenu);

                    switch (submenu) {
                        case 1:
                            incluirApt(BDapartamentos, &totalApt);
                            break;
                        case 2:
                            alterarApt(BDapartamentos, &totalApt);
                            break;
                        case 3:
                            apagarApt(BDapartamentos, &totalApt);
                            break;
                        case 4:
                            consultarApt(BDapartamentos, &totalApt);
                            break;
                        case 5:
                            consultarTodosApt(BDapartamentos, &totalApt);
                            break;
                        case 6:
                            printf("Retornar ao menu anterior.\n");
                            break;
                        default:
                            printf("Digite uma opcao valida!\n");
                    }
                } while (submenu != 6);
                break;
            case 3:
               do {
                    printf("\n  ------ SUBMENU RESERVA ------ \n");
                    printf("1. Incluir\n");
                    printf("2. Alterar\n");
                    printf("3. Excluir\n");
                    printf("4. Consultar\n");
                    printf("5. Consultar todos\n");
                    printf("6. Voltar ao menu anterior\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &submenu);

                    switch (submenu) {
                        case 1:
                            printf("Incluir reserva\n");
                            incluirRes(BDreservas, &totalRes, BDapartamentos, &totalApt, BDclientes, &totalCli);
                            break;
                        case 2:
                            printf("Alterar reserva\n");
                            break;
                        case 3:
                            printf("Excluir reserva\n");
                            break;
                        case 4:
                            printf("Consultar reserva\n");
                            break;
                        case 5:
                            printf("Consultar todas as reservas\n");
                            consultarTodosRes(BDreservas, &totalRes);
                            break;
                        case 6:
                            printf("Retornar ao menu anterior.\n");
                            break;
                        default:
                            printf("Digite uma opcao válida!\n");
                    }
                } while (submenu != 6);
                break;
            case 4:
                do {
                    printf("\n  ------ SUBMENU RELATORIOS ------ \n");
                    printf("1. Consultar apartamento\n");
                    printf("2. Mostrar reservas por periodo\n");
                    printf("3. Voltar ao menu anterior\n");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d%*c", &submenu);

                    switch (submenu) {
                        case 1:
                            printf("Consultar apartamento");
                            consultarResCodigo(BDreservas, &totalRes);
                            break;
                        case 2:
                            printf("Mostrar reservas por periodo\n");
                            consultarResPeriodo(BDreservas, &totalRes);
                            break;
                        case 3:
                            printf("Retornar ao menu anterior.\n");
                            break;
                        default:
                            printf("Digite uma opcao válida!\n");
                    }
                } while (submenu != 3);
                break;
            case 5:
                printf("Sair\n");
                if (totalCli != 0)
                {
                    arquivo = fopen("clientes.dat", "wb");
                    if(arquivo != NULL)
                    {
                        //enviar a quantidade de dados
                        fwrite(&totalCli, sizeof(int), 1, arquivo);
                        //agora gravar os dados do arquivo de clientes
                        fwrite(BDclientes, sizeof(cliente), totalCli, arquivo);
                        fclose(arquivo);
                    }
                }
                if (totalApt != 0)
                {
                    arquivo = fopen("apartamentos.dat", "wb");
                    if(arquivo != NULL)
                    {
                        //enviar a quantidade de dados
                        fwrite(&totalApt, sizeof(int), 1, arquivo);
                        //agora gravar os dados do arquivo de apartamentos
                        fwrite(BDapartamentos, sizeof(apartamento), totalApt, arquivo);
                        fclose(arquivo);
                    }
                }
                if (totalRes != 0)
                {
                    arquivo = fopen("reservas.dat", "wb");
                    if(arquivo != NULL)
                    {
                        //enviar a quantidade de dados
                        fwrite(&totalRes, sizeof(int), 1, arquivo);
                        //agora gravar os dados do arquivo de apartamentos
                        fwrite(BDreservas, sizeof(reserva), totalRes, arquivo);
                        fclose(arquivo);
                    }
                }

                break;
            default:
                printf("Digite uma opcao válida!\n");
        }
    } while (principal != 5);
	
	return 0;
}