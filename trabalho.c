/*+-------------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                    |
 | BACHARELADO EM CIENCIA DA COMPUTACAO.                        |
 | Trabalho..: Validacao de arquivos XML                        |
 | Disciplina: Algoritmos e Estrutura de Dados II – Pratica     |
 | Professor.: Fellipe Rey                                      |
 | Aluno(s)..: Gustavo Benfica Paulino                          |
 | Gustavo Borin Nascimento                                     |
 | Pedro Medina Stracieri                                       |
 | Vinícius Gomes                                               |
 | Data......: 11/11/2023                                       |
 +-------------------------------------------------------------+*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char info;
    struct no *prox;
}node;

void inserePilha(node **topo, node *novo_no){
    novo_no->prox = *topo;
    *topo = novo_no;
}

node *removePilha(node **topo){
    node *remove = NULL;
    if(*topo != NULL){
        remove = *topo;
        *topo = (*topo)->prox;
    }
    return remove;
}

void mostraPilha(node *topo){
    if(topo == NULL){
        printf("Pilha vazia\n");
    }else{
        while(topo != NULL){
            printf("%c   ", topo->info);
            topo = topo->prox;
        }
    }
}

int comparaTags(char tag1[100], char tag2[100]){ // deve receber as tags sem "<", ">" e "/"
    for (int i = 0; i < 100; i++){
        if(tag1[i] != tag2[i]){
            return 0; //False (0) se achar um diferente
        }
    }
    return 1; //True (1) se não achar nenhum caractere diferente
}

void percorreArquivo(FILE *arquivo){
    char linha[100], tag1[100], tag2[100];
    int j = 0;

    while(fgets(linha, 100, arquivo) != NULL){
        linha[strcspn(linha, "\n")] = '\0'; //função que acha o primeiro "\n" e substitui por '\0', indicando o final da string
        for(int i = 0; linha[i] != '0'; i++){ //percorre os caracteres da linha até o final de cada
            //se achar uma abertura de tag, coloca o conteudo em tag1
            if(linha[i] == '<' && linha[i+1] != '/'){
                while(linha[i] != '>'){
                    tag1[j] = linha[i+1];
                }
                //inserePilha(tag1);
                j = 0;
            //se achar um fechamento de tag, coloca o conteudo em tag2
            }else if(linha[i] == '<' && linha[i+1] == '/'){ 
                while(linha[i] != '>'){
                    tag2[j] = linha[i+2];
                }
                j = 0;
                //x = comparaTags(tag1, tag2);
                //se x == 1
                //removePilha(tag1, tag2);              //pensamento
                //se não = ERRO.
            }
            printf("tag 1: %s tag2: %s", tag1, tag2);
        }
    }

}

int main(){
    FILE *arquivo;
    arquivo = fopen("xml.txt", "r");

    if(arquivo == NULL){
        printf("arquivo não encontrado.\n");
        return 1;
    }
    percorreArquivo(arquivo);

    node *topo = NULL;
    

    fclose(arquivo);


    /*int resposta = -1;
    
    while(resposta != 0){
        printf("\n 0-sair\n 1-inserir\n 2-remover\n 3-mostrar pilha\n --------------\n");
        scanf(" %d", &resposta);
        if(resposta == 1){
            printf("digite o valor do novo no.\n");
            char conteudo;
            node *novo_no = (node*) malloc(sizeof(node));
            scanf(" %c", &novo_no->info);
            inserePilha(&topo, novo_no);
        }else if(resposta == 2){
            node *removido = removePilha(&topo);
            if(removido != NULL){
                printf("valor do no removido: %c", removido->info);
            }else{
                printf("Pilha Vazia, Impossivel remover.\n");
            }
            free(removido);
        }else if(resposta == 3){
            mostraPilha(topo);
        }else if(resposta == 0){
            printf("CLOSED!");
        }else{
            printf("resposta inválida.");
        }
    }*/

    return 0;
}