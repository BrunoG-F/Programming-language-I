//Bruno Gomes Farias Demétrio - 18103343

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 500
#define CTR 100
#define NUMAUT 5

//struct do principal do programa
typedef struct Acervo
{
  char titulo[CTR];
  char genero[CTR];
  char autor[NUMAUT][CTR];
  int isbn;
  int dia;
  int mes;
  int ano;
  int indice;
}Acervo;

Acervo acervo[MAX];

//declaracao de modularizações.
int lerstring(char a[CTR], int max);        // Função para corrigir problema com nomes compostos
int validadata(int dia, int mes, int ano);  // Funcao para comparar os meses que possuem 28, 30 e 31 dias e podendo ser inserido 29 quando entende-se que é mes 2 ou é ano bissexto.
void menu();                                // Função Menu, que comporta as primeiras e principais escolhas do programa
void cadastro_acervo();                     // Função que realiza o cadastro do livro no acervo
void alteracao_de_dados_do_acervo();        // Função que realiza a alteração dos dados do livro no acervo
void excluir_livro_acervo();                // Função para excluir algum livro determinado pelo usuário no acervo
void todos_os_livros_do_acervo();           // Função para exibir todos os livros do acervo
void consulta_livro_por_nome();             // Função para buscar um livro pelo nome, e que deve ser definido pelo usuário
void numero_de_livros_por_genero();         // Função que exibe a quantidade de livros de um determinado genero no acervo
void titulo_dos_livros_por_genero();        // Função que exibe o titulo dos livros de um determinado genero no acervo, o genero é determinado pelo usuário


//variáveis globais.
int aux, ind=0;

int main(){

    menu();

    return 0;
}

int lerstring(char s[CTR], int max){
  int i = 0;
  char letra;

  for (i = 0; i < (max - 1); i++)
  {
    letra = fgetc(stdin);

    if ((letra == '\n') && (i == 0))
    {
      i = i - 1;
      continue;
    }

    if (letra == '\n')
      break;
    s[i] = letra;
  }

  s[i] = 0;

  return (i);
}

int validadata(int dia, int mes, int ano){
  // verifica se os numeros sao validos
  if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100))
  {
    if ((dia == 29 && mes == 2) && (ano % 400 == 0 || ano % 4 == 0 && ano % 100 != 0)) // verifica ano bissexto
      return 1;
    if (dia <= 28 && mes == 2) // verifica o mes de feveireiro
      return 1;
    if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) // verifica os meses de 30 dias
      return 1;
    if ((dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) // verifica os meses de 31 dias
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

void menu(){

    int opcao;

    do{
        printf("\nEscolha uma das opcoes a seguir. \n");
        printf("\n1) Inserir novo livro no acervo. \n");
        printf("2) Atualizar dados de livros no acervo . \n");
        printf("3) Excluir livro do acervo. \n");
        printf("4) Relatorio de todos os livros cadastrados no acervo. \n");
        printf("5) Consulta por nome de um livro no acervo. \n");
        printf("6) Relatorio de numero de livros no acervo por genero. \n");
        printf("7) Relatorio com o titulo dos livros por genero. \n");
        printf("8) Finalizar programa. \n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastro_acervo();
            break;

        case 2:
            alteracao_de_dados_do_acervo();
            break;

        case 3:
            excluir_livro_acervo();
            break;

        case 4:
            todos_os_livros_do_acervo();
            break;

        case 5:
            consulta_livro_por_nome();
            break;
            
        case 6:
            numero_de_livros_por_genero();
            break;

        case 7:
            titulo_dos_livros_por_genero();
            break;
            
        case 8:
            printf("Programa finalizado! \n");
            break;
        }
    }while (opcao != 8);
}

void cadastro_acervo(){

    int quant, i, j, aut, num = 0;

    printf("\nQuantos livros serao inseridos? ");
    scanf("%d", &quant);

    for(i=ind;i<quant;i++){
        printf("\nDigite o codigo ISBN do livro a ser cadastrado: ");
        scanf("%d", &acervo[i].isbn);

        printf("\nDigite o titulo do livro: ");
        aux = lerstring(acervo[i].titulo, CTR);

        do{
            printf("\nEscolha um dos generos a seguir:\n");
            printf("1) Drama.\n");
            printf("2) Ficcao Cientifica.\n");
            printf("3) Suspense.\n");
            printf("4) Romance.\n");
            printf("5) Terror.\n");
            scanf("%d", &num);
        }while(num < 1 || num > 5);
        
        if (num == 1)
        {
            memcpy(acervo[i].genero, "Drama", CTR);
        }
        else if (num == 2)
        {
            memcpy(acervo[i].genero, "Ficcao Cientifica", CTR);
        }
        else if (num == 3)
        {
            memcpy(acervo[i].genero, "Suspense", CTR);
        }
        else if (num == 4)
        {
            memcpy(acervo[i].genero, "Romance", CTR);
        }
        else if (num == 5)
        {
            memcpy(acervo[i].genero, "Terror", CTR);
        }

        printf("\nO livro possui quantos autores? ");
        scanf("%d", &aut);

        while (aut <= 0)
        {
            printf("\nDigite um numero valido maior que 0 de autores.");
            scanf("%d", &aut);
        }

        if(aut == 1){
            printf("\nDigite o nome do autor do livro: ");
            aux = lerstring(acervo[i].autor[0], CTR);
        }
        else {
            printf("\nDigite o nome do(s) autor(es) do livro: ");
            for (j=0;j<aut;j++){
                aux = lerstring(acervo[i].autor[j], CTR);
            }
        }

        do // Do..While para validar a data de publicacao
        {
            printf("\nDigite a data de publicacaodo livro: ex: xx/xx/xxxx\n");
            scanf("%d/%d/%d", &acervo[i].dia, &acervo[i].mes, &acervo[i].ano);

            if (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1)
            {
                printf("Data invalida, digite a data novamente.\n");
            }
        } while (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1);

        acervo[ind].indice = ind;
        ind++;    
    }
    printf("\n");
}

void alteracao_de_dados_do_acervo(){

    int reg, choice = 0, num = 0, aut, i, j, opcao;

    printf("\nDigite o numero da ISBN do livro: ");
    scanf("%d", &reg);

    for (i=0;i<ind;i++){
        if(reg == acervo[i].isbn){

            do{
                printf("\nDigite 1 para alterar apenas um dado do livro ou 2 para alterar todos os dados do livro no acervo: ");
                scanf("%d", &choice);
            }while(choice < 1 || choice > 2);

            if (choice == 1){
                do{
                    printf("\n1) Alterar o codigo ISBN do livro. \n");
                    printf("2) Alterar o titulo do livro. \n");
                    printf("3) Alterar o genero do livro. \n");
                    printf("4) Alterar o nome do(s) autor(es) do livro. \n");
                    printf("5) Alterar a data de publicacao. ex: xx/xx/xxxx \n");
                    printf("6) Encerrar alteracoes! \n");
                    scanf("%d", &opcao);

                    switch (opcao)
                    {
                        case 1:
                            printf("\nDigite o novo codigo ISBN do livro: ");
                            scanf("%d", &acervo[i].isbn);

                            printf("\nO ISBN foi atualizado com sucesso para: %d\n", acervo[i].isbn);
                            break;

                        case 2:
                            printf("\nDigite o novo titulo do livro: ");
                            aux = lerstring(acervo[i].titulo, CTR);

                             printf("\nO titulo foi atualizado com sucesso para: %s\n", acervo[i].titulo);
                            break;

                        case 3:
                            do{
                                printf("\nEscolha um dos generos a seguir:\n");
                                printf("1) Drama.\n");
                                printf("2) Ficcao Cientifica.\n");
                                printf("3) Suspense.\n");
                                printf("4) Romance.\n");
                                printf("5) Terror.\n");
                                scanf("%d", &num);
                            }while(num < 1 || num > 5);
                            
                            if (num == 1)
                            {
                                memcpy(acervo[i].genero, "Drama", CTR);
                            }
                            else if (num == 2)
                            {
                                memcpy(acervo[i].genero, "Ficcao Cientifica", CTR);
                            }
                            else if (num == 3)
                            {
                                memcpy(acervo[i].genero, "Suspense", CTR);
                            }
                            else if (num == 4)
                            {
                                memcpy(acervo[i].genero, "Romance", CTR);
                            }
                            else if (num == 5)
                            {
                                memcpy(acervo[i].genero, "Terror", CTR);
                            }

                            printf("\nO genero foi atualizado com sucesso para: %s\n", acervo[i].genero);
                            break;

                        case 4:
                            printf("\nO livro possui quantos autores? ");
                            scanf("%d", &aut);

                            while (aut <= 0){
                                printf("\nDigite um numero valido maior que 0 de autores.");
                                scanf("%d", &aut);
                            }

                            if(aut == 1){
                                printf("\nDigite o novo nome do autor do livro: ");
                                aux = lerstring(acervo[i].autor[0], CTR);
            
                                printf("\nO nome do autor foi atualizado com sucesso para: %s\n", acervo[i].autor[0]);
                                }
                            else {
                                printf("\nDigite o novo nome dos autores do livro: ");                            
                                for (j=0;j<aut;j++){
                                    aux = lerstring(acervo[i].autor[j], CTR);
                                    printf("\nO nome do autor %d foi atualizado com sucesso para: %s\n", j+1, acervo[i].autor[j]);
                                }
                            }
                            break;
                            
                        case 5:
                            do // Do..While para validar a data de publicacao
                            {
                                printf("\nDigite a data de publicacaodo livro: ex: xx/xx/xxxx\n");
                                scanf("%d/%d/%d", &acervo[i].dia, &acervo[i].mes, &acervo[i].ano);

                                if (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1)
                                {
                                    printf("Data invalida, digite a data novamente.\n");
                                }
                            } while (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1);

                            printf("\nA data de publicacao foi atualizada com sucesso para: %d/%d/%d", acervo[i].dia, acervo[i].mes, acervo[i].ano);
                            break;

                        case 6:
                            printf("\nAlteracoes encerradas. \n");
                            break;
                    }
                }while (opcao != 6);
            }
            if (choice == 2){
                printf("\nDigite o novo codigo ISBN:.\n");
                scanf("%d", &acervo[i].isbn);

                printf("\nDigite o novo titulo do livro: ");
                aux = lerstring(acervo[i].titulo, CTR);

                do{
                    printf("\nEscolha um dos generos a seguir:\n");
                    printf("1) Drama.\n");
                    printf("2) Ficcao Cientifica.\n");
                    printf("3) Suspense.\n");
                    printf("4) Romance.\n");
                    printf("5) Terror.\n");
                    scanf("%d", &num);
                }while(num < 1 || num > 5);
                            
                if (num == 1)
                {
                    memcpy(acervo[i].genero, "Drama", CTR);
                }
                else if (num == 2)
                {
                    memcpy(acervo[i].genero, "Ficcao Cientifica", CTR);
                }
                else if (num == 3)
                {
                    memcpy(acervo[i].genero, "Suspense", CTR);
                }
                else if (num == 4)
                {
                    memcpy(acervo[i].genero, "Romance", CTR);
                }
                else if (num == 5)
                {
                    memcpy(acervo[i].genero, "Terror", CTR);
                }

                printf("\nO livro possui quantos autores? ");
                scanf("%d", &aut);

                while (aut <= 0)
                {
                    printf("\nDigite um numero valido maior que 0 de autores.");
                    scanf("%d", &aut);
                }

                if(aut == 1){
                    printf("\nDigite o novo nome do autor do livro: ");
                    aux = lerstring(acervo[i].autor[0], CTR);
                }
                else{
                    printf("\nDigite o nome dos autores do livro: ");
                    for (j=0;j<aut;j++){
                        aux = lerstring(acervo[i].autor[j], CTR);
                        printf("\n");
                    }
                }

                do // Do..While para validar a data de publicacao
                {
                    printf("\nDigite a data de publicacaodo livro: ex: xx/xx/xxxx\n");
                    scanf("%d/%d/%d", &acervo[i].dia, &acervo[i].mes, &acervo[i].ano);

                    if (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1){
                        printf("Data invalida, digite a data novamente.\n");
                    }
                } while (validadata(acervo[i].dia, acervo[i].mes, acervo[i].ano) != 1);

                printf("\nAlteracoes realizadas com sucesso.\n");
            }
        }
        if(reg != acervo[i].isbn){
            printf("\nNumero ISBN nao encontrado, voltando ao menu principal.\n\n");
        } 
    }
}

void excluir_livro_acervo(){

    int i, reg, tmp = 0;

    printf("\nDigite o numero do ISBN do livro no qual deseja excluir: ");
    scanf("%d", &reg);

    for (i=0;i<ind;i++){
        if(reg == acervo[i].isbn){
            acervo[i] = acervo[i + 1];
            acervo[i].indice = acervo[i].indice - 1;
            ind--;
            tmp++;
            printf("\nO livro foi exluido com sucesso.\n\n");
        }
    }
    if(tmp == 0){
        printf("\nO Numero ISBN nao foi encontrado, voltando ao menu principal.\n\n");
    }
}

void todos_os_livros_do_acervo(){

    int i, j;

    for (i=0;i<ind;i++){
        printf("\n|ID:                    %d\n", acervo[i].indice + 1);         
        printf("|ISBN:                  %d\n", acervo[i].isbn);                            
        printf("|Titulo:                %s\n", acervo[i].titulo);                           
        printf("|Genero:                %s\n", acervo[i].genero);
        for (j=0;j<NUMAUT;j++){
            if(acervo[i].autor[j][0] != '\0'){
                printf("|Autor(es):             %s\n", acervo[i].autor[j]);
            }
        }
        printf("|Data da publicacao:    %d/%d/%d", acervo[i].dia, acervo[i].mes, acervo[i].ano);
        printf("\n\n");
    }
    system("pause");
}

void consulta_livro_por_nome(){

    int i, j, tmp = 0;
    char titulo[CTR];

    printf("Para pesquisar por titulo, digite no minimo 5 caracteres: ");
    aux = lerstring(titulo, CTR);

    for (i=0;i<ind;i++){   // Foi utilizado a funcao strncmp que compara strings com uma quantidade x de caracter.
        if (strncmp(titulo, acervo[i].titulo, 5) == 0){
            printf("\n|ID:                    %d\n", acervo[i].indice + 1);         
            printf("|ISBN:                  %d\n", acervo[i].isbn);                            
            printf("|Titulo:                %s\n", acervo[i].titulo);                           
            printf("|Genero:                %s\n", acervo[i].genero);
            for (j=0;j<NUMAUT;j++){
                if(acervo[i].autor[j][0] != '\0'){
                    printf("|Autor(es):             %s\n", acervo[i].autor[j]);
                }
            }
            printf("|Data da publicacao:    %d/%d/%d\n", acervo[i].dia, acervo[i].mes, acervo[i].ano);
            tmp++;
            printf("\n\n");
            system("pause");
        }
    }
    if(tmp == 0){
        printf("\nNao foi encontrado o titulo no acervo.");
    }
}

void numero_de_livros_por_genero(){
    
    int i, j, auxgen, auxgen1, tmp = 0;

    for (i=0;i<ind;i++) //É feito um for primeiramente para correr o vetor.
    {
        auxgen=0;
        auxgen1=0;

        for (j=i;j>=0;j--) // Depois um segundo for para comparar a posicao do genero com o primeiro vetor e assim incrementar na variavel.
        {
            if (strcmp(acervo[i].genero, acervo[j].genero) == 0)
            {
                auxgen++;
            }
        }
        if (auxgen == 1) // Caso encontre um genero a variavel recebe 1 e inicia um novo for para correr entre os generos e incrementar numa segunda variavel o numero de generos disponiveis no vetor.
        {
            for (j = 0; j < ind; j++)
            {
                if (strcmp(acervo[i].genero, acervo[j].genero) == 0)
                {
                    auxgen1++;
                }
            }
            if (auxgen1 == 1){
                printf("\nExiste %d livro do genero %s no acervo.\n\n", auxgen1, acervo[i].genero);  // Printa a segunda variavel com o nome do genero e quantidade de vezes que foi encotrada e inicia novamente zerando as variaveis.
            }
            else if (auxgen1 > 1){
                printf("\nExistem %d livros do genero %s no acervo.\n\n", auxgen1, acervo[i].genero);
            }
            tmp++;
        }
    }
    if(tmp == 0){
        printf("\nNao existem titulos deste genero no acervo.\n");
    }
    system("pause");
    printf("\n");
}

void titulo_dos_livros_por_genero(){

    int choice = 0, i, num, tmp = 0;
    char ctr[CTR];

    do{
        printf("\nDigite 1 para escrever o genero ou 2 para escolher previamente: ");
        scanf("%d", &choice);
    }while(choice < 1 || choice > 2);

    if (choice == 1){
        printf("\nDigite pelo menos 5 caracteres do genero que deseja fazer a buscar: ");
        aux = lerstring(ctr, CTR);

        printf("\nTitulos no acervo do genero %s:\n", ctr);
        for(i=0;i<ind;i++){
            if(strncmp(ctr, acervo[i].genero, 5)==0){
                printf("\n|Titulo:                %s\n", acervo[i].titulo);
                tmp++;
            }
        }
        if(tmp == 0){
            printf("\nNao existem titulos deste genero no acervo.");
        }
    }
    if (choice == 2){
        do{
            printf("\nEscolha um dos generos para ver os titulos no acervo.");
            printf("\n1) Drama.\n");
            printf("2) Ficcao Cientifica.\n");
            printf("3) Suspense.\n");
            printf("4) Romance.\n");
            printf("5) Terror.\n");
            printf("6) Retornar ao menu anterior.\n");
            scanf("%d", &num);

            switch (num){
            case 1:
                memcpy(ctr, "Drama", CTR);
                printf("\nTitulos no acervo do genero %s:\n", ctr);
                for(i=0;i<ind;i++){
                    if(strcmp(ctr, acervo[i].genero)==0){
                        printf("\n|Titulo:                %s", acervo[i].titulo);
                        tmp++;
                    }
                }
                if(tmp == 0){
                    printf("\nNao existem titulos deste genero no acervo.");
                }
                break;
            
            case 2:
                memcpy(ctr, "Ficcao Cientifica", CTR);
                printf("\nTitulos no acervo do genero %s:\n", ctr);
                for(i=0;i<ind;i++){
                    if(strcmp(ctr, acervo[i].genero)==0){
                        printf("\n|Titulo:                %s", acervo[i].titulo);
                        tmp++;
                    }
                }
                if(tmp == 0){
                    printf("\nNao existem titulos deste genero no acervo.");
                }
                break;

            case 3:
                memcpy(ctr, "Suspense", CTR);
                printf("\nTitulos no acervo do genero %s:\n", ctr);
                for(i=0;i<ind;i++){
                    if(strcmp(ctr, acervo[i].genero)==0){
                        printf("\n|Titulo:                %s", acervo[i].titulo);
                        tmp++;
                    }
                }
                if(tmp == 0){
                    printf("\nNao existem titulos deste genero no acervo.");
                }
                break;

            case 4:
                memcpy(ctr, "Romance", CTR);
                printf("\nTitulos no acervo do genero %s:\n", ctr);
                for(i=0;i<ind;i++){
                    if(strcmp(ctr, acervo[i].genero)==0){
                        printf("\n|Titulo:                %s", acervo[i].titulo);
                        tmp++;
                    }
                }
                if(tmp == 0){
                    printf("\nNao existem titulos deste genero no acervo.");
                }
                break;

            case 5:
                memcpy(ctr, "Terror", CTR);
                printf("\nTitulos no acervo do genero %s:\n", ctr);
                for(i=0;i<ind;i++){
                    if(strcmp(ctr, acervo[i].genero)==0){
                        printf("\n|Titulo:                %s", acervo[i].titulo);
                        tmp++;
                    }
                }
                if(tmp == 0){
                    printf("\nNao existem titulos deste genero no acervo.");
                }
                break;

            case 6:
                printf("\n\nRetornando ao menu principal.\n\n");
                break;
            }

        } while (num != 6);
    }
}