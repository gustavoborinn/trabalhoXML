/*+-------------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas.                    |
 | BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO.                        |
 | Trabalho..: Validação de arquivos XML                        |
 | Disciplina: Algoritmos e Estrutura de Dados II – Prática     |
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

typedef struct no {
    char info[100];
    struct no* prox;
} node;

void inserePilha(node** topo, node* novo_no) {
    novo_no->prox = *topo;
    *topo = novo_no;
}

node* removePilha(node** topo) {
    node* remove = NULL;
    if (*topo != NULL) {
        remove = *topo;
        *topo = (*topo)->prox;
    }
    return remove;
}

int comparaTags(char tag1[100], char tag2[100]) { // deve receber as tags sem "<", ">" e "/"
    int i;
    for (i = 0; tag1[i] != '\0' && tag2[i] != '\0'; i++) {
        if (tag1[i] != tag2[i]) {
            return 0; // caso encontre um caractere diferente
        }
    }
    if (tag1[i] != tag2[i]) {
        return 0;
    }
    return 1; // caso as tags sejam iguais
}

int percorreArquivo(FILE* arquivo, node** topo) {
    char linha[100], tagAbre[100], tagFecha[100];
    int j = 0, contaLinha = 0;

    while (fgets(linha, 100, arquivo) != NULL) {
        contaLinha++;
        linha[strcspn(linha, "\n")] = '\0'; //função que acha o primeiro "\n" e substitui por '\0', indicando o final da string

        for (int i = 0; linha[i] != '\0'; i++) {
            
            //se achar uma abertura de tag empilha
            if (linha[i] == '<' && linha[i + 1] != '/') {
                i++; // Avança para o próximo caractere após '<'
                while (linha[i] != '>' && j < 100) {
                    tagAbre[j] = linha[i];
                    i++;
                    j++;
                }
                tagAbre[j] = '\0'; //determinar o final da string
                j = 0;

                node* novo_no = malloc(sizeof(node));
                strcpy(novo_no->info, tagAbre); //copia o conteudo da string para o campo info do node
                inserePilha(topo, novo_no);

            //se achar um fechamento de tag, coloca o conteudo em tagFecha 
            } else if (linha[i] == '<' && linha[i + 1] == '/') {
                i = i + 2; // Avança para o próximo caractere após '</'
                while (linha[i] != '>' && j < 100) {
                    tagFecha[j] = linha[i];
                    i++;
                    j++;
                }
                tagFecha[j] = '\0'; //determinar o final da string
                j = 0;

                int x = comparaTags(tagFecha, (*topo)->info);
                if (x == 1) {
                    node *removido = removePilha(topo); //se TagFecha for igual ao topo, desempilha o topo
                    free(removido); //libera o espaco de memoria q o nó ocupava
                } else if (x == 0) {
                    printf("ERRO na linha %d do arquivo XML\n", contaLinha);
                    return 0; //caso ache um fechamento de tag errado
                }
            }
        }
    }
    return 1; //caso o arquivo esteja correto
}

int main() {
    char nomeArquivo[100];
    printf("\ndigite o nome do arquivo XML: \n");
    scanf("%s", nomeArquivo);
    strcat(nomeArquivo, ".xml");
    FILE* arquivo;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado.\n");
        return 1;
    }
    node* topo = NULL;
    int verificacao = percorreArquivo(arquivo, &topo);

    if (verificacao == 1) {
        printf("Arquivo XML correto!\n");
    }

    fclose(arquivo);

    return 0;
}