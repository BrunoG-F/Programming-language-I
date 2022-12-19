//Bruno Gomes Farias Demétrio - 18103343

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define CTR 50
#define MOD 15

//struct do principal do programa
typedef struct Transporte_veicular
{
  char nome_rota[CTR];
  char cidade[CTR][MOD];
  int paradas;
  float km[MOD];
  float valor;
}Onibus;

//declaração de funções.
int lerstring(char a[CTR], int max);
int menu();
Onibus cadastro_de_rota();
void relatorio_das_rotas(Onibus *bus, int indice);
void relatorio_financeiro(Onibus *bus, int indice);
void abrir_criar_arquivo_texto(Onibus *bus, int indice);
void ler_arquivo_texto(Onibus *bus, int *ind);

//Inicio da Main
int main(){

	int opcao, ind = 0;
  Onibus *dados;
  dados = (Onibus*)malloc(sizeof(Onibus) * MAX);

	do{
		opcao = menu();
        switch (opcao)
        {
        case 1:
          dados[ind] = cadastro_de_rota();
          ind++;
          break;

        case 2:
          relatorio_das_rotas(dados, ind);
          break;

        case 3:
          relatorio_financeiro(dados, ind);
          break;

        case 4:
          abrir_criar_arquivo_texto(dados, ind);
          break;

        case 5:
          ler_arquivo_texto(dados, &ind);
          break;
            
        case 6:
          printf("Programa finalizado! \n");
          break;
        }
  }while (opcao != 6);

  free(dados);
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

int menu(){

  int opcao;

  system("cls");

  printf("\nEscolha uma das opcoes a seguir. \n");
  printf("\n1) Cadastrar rota no sistema. \n");
  printf("2) Relatorio geral das rotas no sistema. \n");
  printf("3) Relatorio Financeiro. \n");
  printf("4) Exportar arquivos para um arquivo texto. \n");
  printf("5) Importar arquivos de um arquivo texto. \n");
  printf("6) Finalizar programa. \n");
  scanf("%d", &opcao);

	return opcao;
}

Onibus cadastro_de_rota(){

  Onibus p;
  int aux, i;

  printf("\nDigite o numero de paradas: ");
  scanf("%d", &p.paradas);
  printf("\nDigite o nome da rota: ");
  aux = lerstring(p.nome_rota, CTR);
  int temp = p.paradas;
  for(i=0;i<temp;i++){
    printf("\nDigite o nome da cidade: ");
    aux = lerstring(p.cidade[i], CTR);
    printf("\nDigite a quantidade de quilometros ate a cidade: ");
    scanf("%f", &p.km[i]);
  }
  printf("\nDigite ao valor da rota: ");
  scanf("%f", &p.valor);

  return p;
}

void relatorio_das_rotas(Onibus *bus, int indice){

  int i, j;
  float somaKM = 0;
  for (i=0;i<indice;i++)
  {
    printf("\nNome da rota: %s\n", bus[i].nome_rota);
    printf("Quantidade de paradas: %d\n", bus[i].paradas);
    int aux = bus[i].paradas;
    for(j=0;j<aux;j++){
      printf("Cidade %d: %s\n", j+1, bus[i].cidade[j]);
      printf("Quilometros ate a cidade %d: %.1fKm\n", j+1, bus[i].km[j]);
      somaKM = somaKM + bus[i].km[j];
    }
    printf("Distancia total da rota: %.1fKm\n", somaKM);
    printf("Valor cobrado pela rota: R$%.2f\n\n", bus[i].valor);
    somaKM = 0;
  }
  system("pause");
}

void relatorio_financeiro(Onibus *bus, int indice){

  float somaKM = 0, somaValor = 0;
  int i, j, somaCidade = 0;

  for(i=0;i<indice;i++){
    int aux = bus[i].paradas;
    for (j=0;j<aux;j++)
    {
      if(bus[i].cidade[j][0] != '\0')
      {
        somaCidade++;
      }
      somaKM = somaKM + bus[i].km[j];
    }
    somaValor = somaValor + bus[i].valor;
  }
  printf("\nDurante sua jornada a empresa Jotur passou por %d cidades, viajou %.1f quilometros e faturou R$%.2f reais desde sua primeira rota.\n\n", somaCidade, somaKM, somaValor);
  system("pause");
}

void abrir_criar_arquivo_texto(Onibus *bus, int indice){

  FILE *arq;
  int i, j, aux;

  arq = fopen("Jotur.txt", "w");
  if(arq == NULL){
    printf("Nao foi possivel criar/abrir o arquivo.");
    exit(0);
  }

  for (i=0;i<indice;i++)
  {
    fprintf(arq, "%s\n", bus[i].nome_rota);
    fprintf(arq, "%d\n", bus[i].paradas);
    aux = bus[i].paradas;
    for(j=0;j<aux;j++){
      fprintf(arq, "%s\n", bus[i].cidade[j]);
      fprintf(arq, "%.1f\n", bus[i].km[j]);
    }
    fprintf(arq, "%.2f\n", bus[i].valor);
  }

  fclose(arq);
  printf("\nArquivo exportado com sucesso.\n\n");
  system("pause");
}

void ler_arquivo_texto(Onibus *bus, int *ind){
    
  int i, aux;
  FILE *arq;
  *ind = 0;
  arq = fopen("Jotur.txt", "r");

  while(!feof(arq)){
    fscanf(arq, "%s\n", &bus[*ind].nome_rota);
    fscanf(arq, "%d\n", &bus[*ind].paradas);
    aux = bus[*ind].paradas;
    for(i=0;i<aux;i++){
      fscanf(arq, "%s\n", &bus[*ind].cidade[i]);
      fscanf(arq, "%f\n", &bus[*ind].km[i]);
    }
    fscanf(arq, "%f\n\n", &bus[*ind].valor);
    *ind += 1;
  }

  fclose(arq);
  printf("\nArquivo importado com sucesso.\n\n");
  system("pause");
}
