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

// Structs
typedef struct{
    char nomeEstrutura[40];
    char telefoneEstrutura[15];
    char celularEstrutura[15];
    char emailEstrutura[40];
    struct EstruturaDeContato *proximoContato;
}EstruturaDeContato;

typedef struct{
    int diaEstrutura;
    int mesEstrutura;
    int anoEstrutura;
    char lembreteEstrutura[2048];
    struct EstruturaDeLembrete *proximoLembrete;
}EstruturaDeLembrete;

// Funções
void vetorRecebeVetorChar(char vetor1[2048], char vetor2[2048], int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        vetor1[i] = vetor2[i];
    }
}

EstruturaDeContato * inserirContatoPelaFrente(EstruturaDeContato *primeiroContato, char nome[40], char telefone[15], char email[40], char celular[15]){

    EstruturaDeContato *novoContato = (EstruturaDeContato*) malloc(sizeof(EstruturaDeContato));
    vetorRecebeVetorChar(novoContato->nomeEstrutura, nome, 40);
    vetorRecebeVetorChar(novoContato->telefoneEstrutura, telefone, 15);
    vetorRecebeVetorChar(novoContato->celularEstrutura, celular, 15);
    vetorRecebeVetorChar(novoContato->emailEstrutura, email, 40);
    novoContato->proximoContato = NULL;

    if(primeiroContato == NULL){
        return novoContato;
    } else {
        EstruturaDeContato *ultimoContatoDaEstruturaDeContato = primeiroContato;

        while(ultimoContatoDaEstruturaDeContato->proximoContato != NULL){
            ultimoContatoDaEstruturaDeContato = ultimoContatoDaEstruturaDeContato->proximoContato;
        }

        ultimoContatoDaEstruturaDeContato->proximoContato = novoContato;

        return primeiroContato;
    }
}

EstruturaDeLembrete * inserirLembretePelaFrente(EstruturaDeContato *primeiroLembrete, int dia, int mes, int ano, char lembrete[2048]){

    EstruturaDeLembrete *novoLembrete = (EstruturaDeLembrete*) malloc(sizeof(EstruturaDeLembrete));
    novoLembrete->diaEstrutura = dia;
    novoLembrete->mesEstrutura = mes;
    novoLembrete->anoEstrutura = ano;
    vetorRecebeVetorChar(novoLembrete->lembreteEstrutura, lembrete, 2048);
    novoLembrete->proximoLembrete = NULL;

    if(primeiroLembrete == NULL){
        return novoLembrete;
    } else {
        EstruturaDeLembrete *ultimoLembreteDaLista = primeiroLembrete;

        while(ultimoLembreteDaLista->proximoLembrete != NULL){
            ultimoLembreteDaLista = ultimoLembreteDaLista->proximoLembrete;
        }

        ultimoLembreteDaLista->proximoLembrete = novoLembrete;

        return primeiroLembrete;
    }
}

void imprimirTodosOsContatos(EstruturaDeContato *contato){
    int i = 1;

    while (contato != NULL){
        blue();
        printf("\n Contato %d", i);
        printf("\n - Nome:     |%s", contato->nomeEstrutura);
        printf("\n - Telefone: |%s", contato->telefoneEstrutura);
        printf("\n - Celular:  |%s", contato->celularEstrutura);
        printf("\n - Email:    |%s\n", contato->emailEstrutura);
        reset();
        contato = contato->proximoContato;
        i++;
    }
}

void imprimirTodosOsLembretes(EstruturaDeLembrete *primeiroLembrete){

    while (primeiroLembrete != NULL){
        printf("\nDia %d/%d/%d:\n", primeiroLembrete->diaEstrutura, primeiroLembrete->mesEstrutura, primeiroLembrete->anoEstrutura);
        printf("\n%s\n", primeiroLembrete->lembreteEstrutura);
        
        primeiroLembrete = primeiroLembrete->proximoLembrete;
    }
}

void imprimeContatoDaAgenda(EstruturaDeContato *contato, int posicao){
    int i;

    if(posicao > 0){
        for(i=1;i<posicao;i++){
            contato = contato->proximoContato;
        }

        blue();
        printf("\n - %s -", contato->nomeEstrutura);
        printf("\n - Telefone: |%s", contato->telefoneEstrutura);
        printf("\n - Celular:  |%s", contato->celularEstrutura);
        printf("\n - Email:    |%s\n", contato->emailEstrutura);
    }
}

void imprimeLembreteDaAgenda(EstruturaDeLembrete *lembrete, int posicao){
    int i;

    if(posicao > 0){
        for(i=1;i<posicao;i++){
            lembrete = lembrete->proximoLembrete;
        }
        printf("\n Dia %d/%d/%d:\n", lembrete->diaEstrutura, lembrete->mesEstrutura, lembrete->anoEstrutura);
        printf("\n%s\n", lembrete->lembreteEstrutura);
    }
}


int buscarContatoDaAgenda(EstruturaDeContato *contato, char nome[40]){
    int i = 1;
    EstruturaDeContato *ponteiroDeBusca = contato;

    if(contato == NULL){ // Essa condicional serve para resolver um erro que ocorre quando busca algo em uma lista encadeada nula.
        printf("\n Nao foi possivel encontrar '%s'\n", nome);
        return 0;
    }

    while( strcmp(ponteiroDeBusca->nomeEstrutura, nome) != 0 && ponteiroDeBusca != NULL){

        ponteiroDeBusca = ponteiroDeBusca->proximoContato;
        i++;

        if(ponteiroDeBusca == NULL){
        printf("\n Nao foi possivel encontrar '%s'\n", nome);
        return 0;
        }
    }
    
    return i;
}

int buscarLembreteDaAgenda(EstruturaDeLembrete *lembrete, int dia, int mes, int ano, int *vetorDosLembretes){ // esse vetor existe por temos varios lembretes de uma data só.
    int posicao = 1;
    int j = 0;
    int numeroDeLembretesAchados = 0;
    EstruturaDeLembrete *ponteiroDeBusca = lembrete;

    if(lembrete == NULL){ // Essa condicional serve para resolver um erro que ocorre quando busca algo em uma lista encadeada nula.
        printf("\nNao existem lembretes para o dia %d/%d/%d\n", dia, mes, ano);
        return 0;
    }

    while(ponteiroDeBusca->proximoLembrete != NULL || ponteiroDeBusca == NULL){
        while( !(ponteiroDeBusca->diaEstrutura == dia && ponteiroDeBusca->mesEstrutura == mes && ponteiroDeBusca->anoEstrutura == ano) && ponteiroDeBusca != NULL){

            ponteiroDeBusca = ponteiroDeBusca->proximoLembrete;
            posicao++;

            if(ponteiroDeBusca == NULL){
                printf("\nNao existem lembretes para o dia %d/%d/%d\n", dia, mes, ano);
                return 0;
            }

        }
        
        if(ponteiroDeBusca != NULL){
            vetorDosLembretes[j] = posicao;
            j++;
            posicao++;
            ponteiroDeBusca = ponteiroDeBusca->proximoLembrete;
            numeroDeLembretesAchados++;
        }
    }

    return numeroDeLembretesAchados;
    
}

EstruturaDeContato * transferirContatosDoArquivoParaOPrograma(EstruturaDeContato *contatos){
    FILE *arquivoComContatos = fopen("contatos.txt", "rb");
    EstruturaDeContato *ponteiroDoArquivo;

    while(fread(ponteiroDoArquivo, sizeof(EstruturaDeContato), 1, arquivoComContatos)==1){
        contatos = inserirContatoPelaFrente(contatos, ponteiroDoArquivo->nomeEstrutura, ponteiroDoArquivo->telefoneEstrutura, ponteiroDoArquivo->emailEstrutura, ponteiroDoArquivo->celularEstrutura);
    }

    fclose(arquivoComContatos);

    return contatos;
}

EstruturaDeLembrete * transferirLembretesDoArquivoParaOPrograma(EstruturaDeLembrete *lembretes){
    FILE *arquivoComLembretes = fopen("lembretes.txt", "rb");
    EstruturaDeLembrete *ponteiroDoArquivo;

    while(fread(ponteiroDoArquivo, sizeof(EstruturaDeLembrete), 1, arquivoComLembretes)==1){
        lembretes = inserirLembretePelaFrente(lembretes, ponteiroDoArquivo->diaEstrutura, ponteiroDoArquivo->mesEstrutura, ponteiroDoArquivo->anoEstrutura, ponteiroDoArquivo->lembreteEstrutura);
    }

    fclose(arquivoComLembretes);

    return lembretes;
}

void transferirContatosParaArquivo(EstruturaDeContato *contatos){
    FILE *arquivo = fopen("contatos.txt", "wb");

    while(contatos != NULL){
        fwrite(contatos, sizeof(EstruturaDeContato), 1, arquivo);
        contatos = contatos->proximoContato;
    }

    fclose(arquivo);
}

void transferirLembretesParaArquivo(EstruturaDeLembrete *lembretes){
    FILE *arquivo2 = fopen("lembretes.txt", "wb");

    while(lembretes != NULL){
        fwrite(lembretes, sizeof(EstruturaDeLembrete), 1, arquivo2);
        lembretes = lembretes->proximoLembrete;
    }

    fclose(arquivo2);
}

EstruturaDeContato * excluirContato(EstruturaDeContato *contatos, int posicao){
    EstruturaDeContato *contatoParaExcluir = contatos;
    EstruturaDeContato *auxiliarDeReligagemDosContatos = NULL;
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

EstruturaDeLembrete * excluirLembrete(EstruturaDeLembrete *lembretes, int posicao){
    EstruturaDeLembrete *lembreteParaExcluir = lembretes;
    EstruturaDeLembrete *auxiliarDeReligagemDosLembretes = NULL;
    int i;

    if(posicao != 0){

        for(i=1;i<posicao;i++){
            auxiliarDeReligagemDosLembretes = lembreteParaExcluir;
            lembreteParaExcluir = lembreteParaExcluir->proximoLembrete;
        }

        printf("\nLembrete excluido com susseso\n");

        if(auxiliarDeReligagemDosLembretes == NULL){
            auxiliarDeReligagemDosLembretes = lembreteParaExcluir->proximoLembrete;
            free(lembreteParaExcluir);
            return auxiliarDeReligagemDosLembretes;
        } else {
            auxiliarDeReligagemDosLembretes->proximoLembrete = lembreteParaExcluir->proximoLembrete;
            free(lembreteParaExcluir);
            return(lembretes);
        }
    }
}

void excluirTodosOsContatos(EstruturaDeContato *contatos){
    EstruturaDeContato *contatoParaExcluir = contatos;
    EstruturaDeContato *auxiliarExclusao;

    while(contatoParaExcluir != NULL){
        auxiliarExclusao = (EstruturaDeContato *) contatoParaExcluir->proximoContato;
        free(contatoParaExcluir);
        contatoParaExcluir = auxiliarExclusao;
    }
}

void excluirTodosOsLembretes(EstruturaDeLembrete *lembretes){
    EstruturaDeLembrete *lembreteParaExcluir = lembretes;
    EstruturaDeLembrete *auxiliarExclusao;

    while(lembreteParaExcluir != NULL){
        auxiliarExclusao = (EstruturaDeLembrete *) lembreteParaExcluir->proximoLembrete;
        free(lembreteParaExcluir);
        lembreteParaExcluir = auxiliarExclusao;
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
char * imprimeNomeMes(int numeroDoMes)
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
               imprimeNomeMes(i),ano);
  
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
        blue();
        printf(" Hora: ");
        cyan();
        printf("%d:0%d \n",hora,minuto);
        reset();
    } else {
        blue();
        printf(" Hora: ");
        cyan();
        printf("%d:%d \n",hora,minuto);
        reset();
    }
    if(mes < 10) {
        blue();
        printf(" Data: ");
        cyan();
        printf("%d/0%d/%d",dia,mes,ano);
        reset();
    } else {
        blue();
        printf(" Data: ");
        cyan();
        printf("%d/%d/%d",dia,mes,ano);
        reset();
    }
    return 0;
}

// parte do menu dos lembretes.
EstruturaDeLembrete * abrirAgendaDeLembretes(EstruturaDeLembrete *primeiroLembrete) {
    
    int dia, mes, ano;
    char lembrete[2048];
    int entradaDeSelecao = 0;
    FILE *salvarLembretesEmArquivo;
    char entradaChar;
    int diaChave, mesChave, anoChave;
    int vetorDasPosicoesDosLembretes[300]; // esse vetor tem varias posiçoes, que são as posições dos lembretes que queremos imprimir.


    primeiroLembrete = transferirLembretesDoArquivoParaOPrograma(primeiroLembrete);

    salvarLembretesEmArquivo = fopen("lembretes.txt", "ab");

    while(entradaDeSelecao != 4){
    
        transferirLembretesParaArquivo(primeiroLembrete);

        blue();
        printf("\n -----------------------------------");
        reset();
        printf("\n");

        cyanBold();
        printf(" Tens ");
        redBold();
        printf("X");
        cyanBold();
        printf(" notificacoes,\n");
        redBold(); 
        printf(" X");
        cyanBold();
        printf(" para 18 de marco e ");
        redBold();
        printf("X");
        cyanBold();
        printf(" para amanha.\n");
        blue();
        printf(" -----------------------------------\n");
        reset();

        yellow();
        printf(" 1 - |");
        cyan();
        printf(" Criar novo lembrete |\n");
        yellow();
        printf(" 2 - |");
        cyan();
        printf(" Ver lembrete        |\n");
        yellow();
        printf(" 3 - |");
        cyan();
        printf(" Remover lembrete    |\n");
        yellow();
        printf(" 4 - |");
        red();
        printf(" Sair                | \n");
        reset();

        blue();
        printf(" -----------------------------------\n");
        red();
        printf(" ");
        scanf("%d",&entradaDeSelecao);
        reset();
        blue();
        printf(" -----------------------------------\n");
        reset();
        
        // criar lembretes
        if(entradaDeSelecao == 1) {

            blue();
            printf(" Informe o dia do lembrete (dd/mm/aaaa): ");
            red();
            scanf("%d/%d/%d", &dia, &mes, &ano);
            reset();
            setbuf(stdin, NULL); // isso sempre tem que ser usado antes de um gets para n dar problema.

            blue();
            printf("\n Lembrete: \n");

            yellow();
            fgets(&lembrete, 2048, stdin);

            primeiroLembrete = inserirLembretePelaFrente(primeiroLembrete, dia, mes, ano, lembrete);
        }

        // exibir lembretes
        else if(entradaDeSelecao == 2) {
            
            setbuf(stdin, NULL);
            entradaChar = 'n';
            blue();
            printf("Deseja ver todos os lembretes? (s/n) ");
            red();
            scanf("%c", &entradaChar);
            reset();

            if(entradaChar == 's'){

                yellow();
                imprimirTodosOsLembretes(primeiroLembrete);
            }
            else{
                int i;
                
                for(i=0;i<300;i++){
                    vetorDasPosicoesDosLembretes[i] = 0;
                }

                setbuf(stdin, NULL);
                blue();
                printf("Informe o dia do lembrete para a busca (dd/mm/aaaa): ");
                red();
                scanf("%d/%d/%d", &diaChave, &mesChave, &anoChave);
                reset();

                for(i=0;i<buscarLembreteDaAgenda(primeiroLembrete, diaChave, mesChave, anoChave, vetorDasPosicoesDosLembretes);i++){
                    yellow();
                    imprimeLembreteDaAgenda(primeiroLembrete, vetorDasPosicoesDosLembretes[i]);
                }
            }
        }
        
        // excluir
        else if(entradaDeSelecao == 3) {
            int i;
            
            setbuf(stdin, NULL);
            entradaChar = 'n';

            blue();
            printf("\n Deseja excluir todos os lembretes? (s/n)\n");
            red();
            scanf("%c", &entradaChar);
            reset();

            if(entradaChar == 's'){
                excluirTodosOsLembretes(primeiroLembrete);
                primeiroLembrete = NULL;
                
                cyan();
                printf("\n Todos os lembretes foram excluidos\n");

                transferirLembretesParaArquivo(primeiroLembrete);
            }else{
                int n;

                setbuf(stdin, NULL);
                blue();
                printf("\n Informe a data do lembrete que deseja excluir (dd/mm/aaaa): ");
                red();
                scanf("%d/%d/%d", &diaChave, &mesChave, &anoChave);
                reset();

                for(i=0;i<buscarLembreteDaAgenda(primeiroLembrete, diaChave, mesChave, anoChave, vetorDasPosicoesDosLembretes);i++){
                    yellow();
                    imprimeLembreteDaAgenda(primeiroLembrete, vetorDasPosicoesDosLembretes[i]);
                }

                setbuf(stdin, NULL);
                blue();
                printf("\n Qual dos lembretes deseja excluir?");
                cyanBold();
                printf("(Digite o numero da ordem que apareceu)\n");
                red();
                scanf("%d", &n);
                reset();
                
                primeiroLembrete = excluirLembrete(primeiroLembrete, vetorDasPosicoesDosLembretes[n-1]);
            }
        }
    }

    transferirLembretesParaArquivo(primeiroLembrete);

    return primeiroLembrete;
}

void abrirMenu() {
    blue();
    printf(" -------- MENU --------\n");
    cyan();
    yellow();
    printf(" 1 - |");
    cyan();
    printf(" Inserir Contato \n");
    yellow();
    printf(" 2 - |");
    cyan();
    printf(" Listar Contatos \n");
    yellow();
    printf(" 3 - |");
    cyan();
    printf(" Buscar Contato\n");
    yellow();
    printf(" 4 - |");
    cyan();
    printf(" Excluir Contato\n");
    yellow();
    printf(" 5 - |");
    cyan();
    printf(" Limpar os Contatos\n");
    yellow();
    printf(" 6 - |");
    cyan();
    printf(" Abrir Agenda \n");
    yellow();
    printf(" 7 - |");
    redBold();
    printf(" Sair\n");
    blue();
    printf(" ----------------------\n");
    reset();
}

// MAIN
int main(){
    FILE *salvaContatosEmArquivo;
    EstruturaDeContato *contato = NULL;
    EstruturaDeLembrete *lembretes = NULL;

    int entrada;
    char nomeContato[40];
    char telefoneContato[15];
    char emailContato[40];
    char celularContato[15];
    char chaveDeBusca[40];

    contato = transferirContatosDoArquivoParaOPrograma(contato);

    salvaContatosEmArquivo = fopen("contatos.txt", "ab");

    while(entrada != 7){
        transferirContatosParaArquivo(contato);
        blue();
        printf("\n ----------- Agenda em C -----------\n");
        reset();

        imprimirData();
        blue();
        printf("\n -----------------------------------\n");
        reset();
        
        printf("\n");
        abrirMenu();
        red();
        printf(" ");
        scanf("%d", &entrada);
        reset();
        blue();
        printf("\n ----------------------\n");
        reset();
        setbuf(stdin, NULL);

        if(entrada == 1){
            blue();
            printf(" - Inserindo Contatos -\n");
            printf(" ----------------------\n");

            printf("\n Nome do novo contato: ");

            cyan();
            gets(&nomeContato);

            blue();
            printf(" Telefone do novo contato: ");

            cyan();
            gets(&telefoneContato);

            blue();
            printf(" Celular do novo contato: ");

            cyan();
            gets(&celularContato);

            blue();
            printf(" Email do novo contato: ");
            cyan();
            gets(&emailContato);
            reset();
            contato = inserirContatoPelaFrente(contato, nomeContato, telefoneContato, emailContato, celularContato);
        }

        if(entrada == 2){
            
            if(contato == NULL) {
                printf("Nao ha contatos na Agenda!");
            } else {
                imprimirTodosOsContatos(contato);
            }
        }

        if(entrada == 3){

            printf("\nInsira o nome do contato para a busca:\n");
            gets(&chaveDeBusca);

            imprimeContatoDaAgenda(contato, buscarContatoDaAgenda(contato, chaveDeBusca));
        }

        if(entrada == 4){
            printf("\nInsira o nome do contato para excluir:\n");
            gets(&chaveDeBusca);

            contato = excluirContato(contato, buscarContatoDaAgenda(contato, chaveDeBusca));
        }

        if(entrada == 5){
            excluirTodosOsContatos(contato);
            printf("\nTodos os contatos foram excluidos!\n");
            contato = NULL;

            salvaContatosEmArquivo = fopen("contatos.txt", "wb");
        }
        if(entrada == 6) {
            calendario();
            lembretes = abrirAgendaDeLembretes(lembretes);
            transferirLembretesParaArquivo(lembretes);
        }
        
    }
    printf("\nFim do programa");

    transferirContatosParaArquivo(contato);
    transferirLembretesParaArquivo(lembretes);

    fclose(salvaContatosEmArquivo);
}// fim
