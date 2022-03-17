#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//Cores:
void black() {
    printf("\033[0;30m");
}
void red() {
    printf("\033[0;31m");
}
void yellow() {
    printf("\033[0;33m");
}
void blue() {
    printf("\033[0;34m");
}
void green() {
    printf("\033[0;32m");
}
void white() {
    printf("\033[0;37m");
}
void cyan() {
    printf("\033[0;36m");
}
void purple() {
    printf("Purple \033[0;35m");
}

//NEGRITO

void blackBold() {
    printf("\033[1;30m");
}
void redBold() {
    printf("\033[1;31m");
}
void yellowBold() {
    printf("\033[1;33m");
}
void blueBold() {
    printf("\033[1;34m");
}
void greenBold() {
    printf("\033[1;32m");
}
void whiteBold() {
    printf("\033[1;37m");
}
void cyanBold() {
    printf("\033[1;36m");
}
void purpleBold() {
    printf("Purple \033[1;35m");
}
void reset() {
    printf("\033[0m");
}

typedef struct{
    char nomeEstrutura[40];
    char telefoneEstrutura[15];
    char celularEstrutura[15];
    char emailEstrutura[40];
    struct Agenda *proximoContato;
}Agenda;

void vetorRecebeVetorChar(char vetor1[100], char vetor2[100], int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        vetor1[i] = vetor2[i];
    }
}

Agenda * inserirContatoPelaFrente(Agenda *primeiroContato, char nome[40], char telefone[15], char email[40], char celular[15]){

    Agenda *novoContato = (Agenda*) malloc(sizeof(Agenda));
    vetorRecebeVetorChar(novoContato->nomeEstrutura, nome, 40);
    vetorRecebeVetorChar(novoContato->telefoneEstrutura, telefone, 15);
    vetorRecebeVetorChar(novoContato->celularEstrutura, celular, 15);
    vetorRecebeVetorChar(novoContato->emailEstrutura, email, 40);
    novoContato->proximoContato = NULL;

    if(primeiroContato == NULL){
        return novoContato;
    } else {
        Agenda *ultimoContatoDaAgenda = primeiroContato;

        while(ultimoContatoDaAgenda->proximoContato != NULL){
            ultimoContatoDaAgenda = ultimoContatoDaAgenda->proximoContato;
        }

        ultimoContatoDaAgenda->proximoContato = novoContato;

        return primeiroContato;
    }
}

void imprimeAgendaCompleta(Agenda *contato){
    int i = 1;

    while (contato != NULL){
        printf("\nContato %d", i);
        printf("\n-Nome:     |%s", contato->nomeEstrutura);
        printf("\n-Telefone: |%s", contato->telefoneEstrutura);
        printf("\n-Celular:  |%s", contato->celularEstrutura);
        printf("\n-Email:    |%s\n", contato->emailEstrutura);
        
        contato = contato->proximoContato;
        i++;
    }
}

void imprimeContatoDaAgenda(Agenda *contato, int posicao){
    int i;

    if(posicao > 0){
        for(i=1;i<posicao;i++){
            contato = contato->proximoContato;
        }
        printf("\n- %s -", contato->nomeEstrutura);
        printf("\n-Telefone: |%s", contato->telefoneEstrutura);
        printf("\n-Celular:  |%s", contato->celularEstrutura);
        printf("\n-Email:    |%s\n", contato->emailEstrutura);
    }
}

int buscaContatoDaAgenda(Agenda *contato, char nome[40]){
    int i = 1;
    Agenda *ponteiroDeBusca = contato;

    if(contato == NULL){ // Essa condicional serve para resolver um erro que ocorre quando busca algo em uma lista encadeada nula.
        printf("\nNao foi possivel encontrar '%s'\n", nome);
        return 0;
    }

    while( strcmp(ponteiroDeBusca->nomeEstrutura, nome) != 0 && ponteiroDeBusca != NULL){

        ponteiroDeBusca = ponteiroDeBusca->proximoContato;
        i++;

        if(ponteiroDeBusca == NULL){
        printf("\nNao foi possivel encontrar '%s'\n", nome);
        return 0;
        }
    }
    
    return i;
}

Agenda * transferirDeArquivoParaAgenda(Agenda *contatos){
    FILE *arquivoComContatos = fopen("contatos.txt", "rb");
    Agenda *ponteiroDoArquivo;

    while(fread(ponteiroDoArquivo, sizeof(Agenda), 1, arquivoComContatos)==1){
        contatos = inserirContatoPelaFrente(contatos, ponteiroDoArquivo->nomeEstrutura, ponteiroDoArquivo->telefoneEstrutura, ponteiroDoArquivo->emailEstrutura, ponteiroDoArquivo->celularEstrutura);
    }

    fclose(arquivoComContatos);

    return contatos;
}

void transferirAgendaParaArquivo(Agenda *contatos){
    FILE *arquivo = fopen("contatos.txt", "wb");

    while(contatos != NULL){
        fwrite(contatos, sizeof(Agenda), 1, arquivo);
        contatos = contatos->proximoContato;
    }

    fclose(arquivo);
}

Agenda * excluirContato(Agenda *contatos, int posicao){
    Agenda *contatoParaExcluir = contatos;
    Agenda *auxiliarDeReligagemDosContatos = NULL;
    int i;

    if(posicao != 0){

        for(i=1;i<posicao;i++){
            auxiliarDeReligagemDosContatos = contatoParaExcluir;
            contatoParaExcluir = contatoParaExcluir->proximoContato;
        }

        printf("\nContato excluido com susseso\n");

        if(auxiliarDeReligagemDosContatos == NULL){
            auxiliarDeReligagemDosContatos = contatoParaExcluir->proximoContato;
            free(contatoParaExcluir);
            return auxiliarDeReligagemDosContatos;
        } else {
            auxiliarDeReligagemDosContatos->proximoContato = contatoParaExcluir->proximoContato;
            free(contatoParaExcluir);
            return(contatos);
        }
    }
}

void excluirTodosOsContatos(Agenda *contatos){
    Agenda *contatoParaExcluir = contatos;
    Agenda *auxiliarExclusao;

    while(contatoParaExcluir != NULL){
        auxiliarExclusao = (Agenda *) contatoParaExcluir->proximoContato;
        free(contatoParaExcluir);
        contatoParaExcluir = auxiliarExclusao;
    }
}

/*INICIO DAS FUNÇÕES DE CALENDARIO
Função que retorna o índice do
dia para a data DD/MM/YYYY
ss*/
int numeroDoDia(int dia, int mes, int ano)
{
  
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    ano -= mes < 3;
    return (ano + ano / 4
            - ano / 100
            + ano / 400
            + t[mes - 1] + dia)
           % 7;
}
  
/* Function that returns the name of the
mes for the given mes Number
January - 0, February - 1 and so on*/
char * receberNomeMes(int numeroDoMes)
{
    char* mes;
  
    switch (numeroDoMes) {
    case 0:
        mes = "Janeiro";
        break;
    case 1:
        mes = "Fevereiro";
        break;
    case 2:
        mes = "Marco";
        break;
    case 3:
        mes = "Abril";
        break;
    case 4:
        mes = "Maio";
        break;
    case 5:
        mes = "Junho";
        break;
    case 6:
        mes = "Julho";
        break;
    case 7:
        mes = "Agosto";
        break;
    case 8:
        mes = "Setembro";
        break;
    case 9:
        mes = "Outubro";
        break;
    case 10:
        mes = "Novembro";
        break;
    case 11:
        mes = "Dezembro";
        break;
    }
    return mes;
}
  
// Function to return the number of dias
// in a mes
int numeroDeDias(int numeroDoMes, int ano)
{
    // Janeiro
    if (numeroDoMes == 0)
        return (31);
  
    // Fevereiro
    if (numeroDoMes == 1) {
        // If the ano is leap then Feb
        // has 29 dias
        if (ano % 400 == 0
            || (ano % 4 == 0
                && ano % 100 != 0))
            return (29);
        else
            return (28);
    }
  
    // Março
    if (numeroDoMes == 2)
        return (31);
  
    // Abril
    if (numeroDoMes == 3)
        return (30);
  
    // Maio
    if (numeroDoMes == 4)
        return (31);
  
    // Junho
    if (numeroDoMes == 5)
        return (30);
  
    // Julho
    if (numeroDoMes == 6)
        return (31);
  
    // Agosto
    if (numeroDoMes == 7)
        return (31);
  
    // Setembro
    if (numeroDoMes == 8)
        return (30);
  
    // Outubro
    if (numeroDoMes == 9)
        return (31);
  
    // Novembro
    if (numeroDoMes == 10)
        return (30);
  
    // Dezembro
    if (numeroDoMes == 11)
        return (31);
}
  
// Function to print the calendar of
// the given ano
void exibirCalendario(int ano, int mes)
{
    int dias;
  
    // Index of the dia from 0 to 6
    int atual = numeroDoDia(1, mes, ano);
  
    // i for Iterate through months
    // j for Iterate through dias
    // of the mes - i
    for (int i = mes-1; i < mes; i++) {
        dias = numeroDeDias(i, ano);
  
        // Print the atual mes name
        blue();
        printf("\n ---------- %s - %d -----------\n",
               receberNomeMes(i),ano);
  
        // Print the columns
        red();
        printf(" Dom");
        cyan();
        printf("   Seg  Ter  Qua  Qui  Sex  ");
        red();
        printf("Sab\n");
        reset();
  
        // Print appropriate spaces
        int k;
        for (k = 0; k < atual; k++)
            printf("     ");
  
        for (int j = 1; j <= dias; j++) {
            printf("%5d", j);
  
            if (++k > 6) {
                k = 0;
                printf("\n");
            }
        }
  
        if (k)
            printf("\n");
  
        atual = k;
    }
  
    return;
}
//FINAL DO CALENDARIO

int calendario()
{
    SYSTEMTIME t;
    GetLocalTime(&t);

    int mes = t.wMonth;
    int ano = t.wYear;
    // Function Call
    exibirCalendario(ano, mes);
    return 0;
}

int imprimirData() {
    SYSTEMTIME data;
    GetLocalTime(&data);
    int dia = data.wDay;
    int mes = data.wMonth;
    int ano = data.wYear;

    int minuto = data.wMinute;
    int hora = data.wHour;

    if(minuto < 10) {
        printf(" Hora: %d:0%d \n",hora,minuto);
    } else {
        printf(" Hora: %d:%d \n",hora,minuto);
    }
    if(mes < 10) {
        printf(" Data: %d/0%d/%d",dia,mes,ano);
    } else {
        printf(" Data: %d/%d/%d",dia,mes,ano);
    }
    return 0;
}

int main(){
    FILE *salvaContatosEmArquivo;
    Agenda *contato = NULL;

    int entrada;
    char nomeContato[40];
    char telefoneContato[15];
    char emailContato[40];
    char celularContato[15];
    char chaveDeBusca[40];

    contato = transferirDeArquivoParaAgenda(contato);

    salvaContatosEmArquivo = fopen("contatos.txt", "ab");

    while(entrada != 6){
        transferirAgendaParaArquivo(contato);
        blue();
        printf(" ----------- Agenda em C -----------\n");
        reset();

        imprimirData();
        calendario();
        blue();
        printf(" ------------------------------------\n");
        reset();
        
        printf("\n");
        printf(" ------- MENU -------\n 1 - Inserir Contato \n 2 - Listar Contatos \n 3 - Buscar Contato");
        printf("\n 4 - Excluir Contato \n 5 - Limpar a agenda \n 6 - Sair\n");
        printf(" --------------------\n");
        scanf("%d", &entrada);
        setbuf(stdin, NULL);

        if(entrada == 1){
            printf("\nNome do novo contato: ");
            gets(&nomeContato);

            printf("Telefone do novo contato: ");
            gets(&telefoneContato);

            printf("Celular do novo contato: ");
            gets(&celularContato);

            printf("Email do novo contato: ");
            gets(&emailContato);

            contato = inserirContatoPelaFrente(contato, nomeContato, telefoneContato, emailContato, celularContato);
        }

        if(entrada == 2){
            
            if(contato == NULL) {
                printf("Nao ha contatos na agenda!");
            } else {
                imprimeAgendaCompleta(contato);
            }
        }

        if(entrada == 3){

            printf("\nInssira o nome do contato para a busca:\n");
            gets(&chaveDeBusca);

            imprimeContatoDaAgenda(contato, buscaContatoDaAgenda(contato, chaveDeBusca));
        }

        if(entrada == 4){
            printf("\nInsira o nome do contato para excluir:\n");
            gets(&chaveDeBusca);

            contato = excluirContato(contato, buscaContatoDaAgenda(contato, chaveDeBusca));
        }

        if(entrada == 5){
            excluirTodosOsContatos(contato);
            printf("\nTodos os contatos foram excluidos!\n");
            contato = NULL;

            salvaContatosEmArquivo = fopen("contatos.txt", "wb");
        }
        
    }
    printf("\nFim do programa");

    transferirAgendaParaArquivo(contato);

    fclose(salvaContatosEmArquivo);
}