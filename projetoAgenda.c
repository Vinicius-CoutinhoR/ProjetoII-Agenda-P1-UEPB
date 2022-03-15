#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Agenda * Excluir_contato(Agenda *contatos, int posicao){
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

    printf("\n-Agendinha-\n");

    while(entrada != 6){
        transferirAgendaParaArquivo(contato);

        printf("\n- - - -MENU- - - -\n1 - Inserir Contato \n2 - Listar Contatos \n3 - Buscar Contato");
        printf("\n4 - Excluir Contato \n5 - Limpar a agenda \n6 - Sair\n-");
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

            contato = Excluir_contato(contato, buscaContatoDaAgenda(contato, chaveDeBusca));
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