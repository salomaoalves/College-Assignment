#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Grafo.h"
#include "Funcoes.h"
#include "in_grafo.h"
#ifdef __unix__
    #include <stdio_ext.h>
    #define COLOR_RED         "\e[91m"
    #define COLOR_GREEN       "\e[32m"
    #define COLOR_LIGHT_YELLOW "\e[93m"
    #define COLOR_RESET       "\e[0m"
    #define COLOR_BLUE        "\e[96m"
    #define SEPARADOR         "/"
    #define OS                0
    #define limpar_buffer()   __fpurge(stdin)
    #define clear()           system("clear")
    #define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#elif defined(_WIN32) || defined(WIN32)
    #include <stdio.h>
    #include <windows.h>
    #define COLOR_RED         ""
    #define COLOR_GREEN       ""
    #define COLOR_LIGHT_YELLOW ""
    #define COLOR_RESET       ""
    #define COLOR_BLUE        ""
    #define SEPARADOR         "\\"
    #define OS                1
    #define limpar_buffer()    fflush(stdin)
    #define clear()           system("cls")
#endif

int lista_arquivos(char *arquivo);
const char *get_filename_ext(const char *filename);
char *encontra_arquivo(char *indice);
int isnumber(char *s);
void print_table(int nlines, int colswidth);
char *nome_arquivo(char* nome);

int main(){
    char arquivo[200], temp[200], r[10], o[10], reduzir[10];
    Grafo *g;
    int valido = 1, num_arquivos = 0;
    float porcentagem;
    clock_t start, end;
    do{
        do{
            clear();
            printf(COLOR_BLUE"+===========Trabalho pratico de TG===========+\n");
            printf("| "COLOR_LIGHT_YELLOW"1 - Inserir caminho do arquivo manualmente "COLOR_BLUE"|\n");
            printf("| "COLOR_LIGHT_YELLOW"2 - Listar grafos disponiveis              "COLOR_BLUE"|\n");
            printf("| "COLOR_LIGHT_YELLOW"0 - Sair                                   "COLOR_BLUE"|\n");
            printf("+============================================+\n"COLOR_LIGHT_YELLOW);
            printf("Opcao: ");
            limpar_buffer();
            scanf("%s", r);
            printf(COLOR_RESET);
            if(!strcmp(r,"1")){
                clear();
                printf(COLOR_LIGHT_YELLOW"Caminho do arquivo: ");
                limpar_buffer();
                scanf("%s", arquivo);
                printf(COLOR_RESET);
                if(strcmp(get_filename_ext(arquivo), "txt")){
                    printf(COLOR_RED"O arquivo \"%s\" nao e valido, pois deve ter extensao \".txt\"\n", arquivo);
                    valido = 0;
                }
                else
                    valido = 1;
            }else if(!strcmp(r,"2")){
                valido = 1;
                clear();
                printf(COLOR_BLUE"+============Grafos disponiveis============+\n");
                num_arquivos = lista_arquivos("grafos");
                if(num_arquivos == -1) valido = 0;
                if(valido == 1) {
                    printf(COLOR_BLUE"|"COLOR_LIGHT_YELLOW"  0 - voltar"COLOR_BLUE"                              |\n"COLOR_LIGHT_YELLOW);
                    printf(COLOR_BLUE"+==========================================+\n"COLOR_LIGHT_YELLOW);
                    printf("Opcao: ");
                    limpar_buffer();
                    scanf("%s", temp);
                    if(!strcmp(temp,"0")) valido = 2;
                    if(!isnumber(temp)){
                        printf(COLOR_RED "O arquivo deve ser indicado pelo seu indice\n"COLOR_RESET);
                        valido = 0;
                    }
                    if(atoi(temp) > num_arquivos && valido == 1) {
                        valido = 0;
                        printf(COLOR_RED"O indice do arquivo deve ser entre 1 e %d\n", num_arquivos);
                    }
                    if(valido == 1){
                        strcpy(arquivo, "grafos" SEPARADOR);
                        strcat(arquivo, encontra_arquivo(temp));
                    }
                } else {
                    printf(COLOR_BLUE"+==========================================+\n"COLOR_LIGHT_YELLOW);
                }
            }
            else if(!strcmp(r,"0")){
                clear();
                return 0;
            }
            else{
                    clear();
                    printf(COLOR_RED"Opcao invalida\n");
                    valido = 0;
            }
            if(valido)
                do {
                    clear();
                    printf(COLOR_LIGHT_YELLOW "Reduzir o tamanho do arquivo de entrada?(s/n) ");
                    scanf("%s", reduzir);
                } while(strcmp(reduzir, "s") && strcmp(reduzir,"n"));

            if(!strcmp(reduzir, "s")) {
                do{
                    clear();
                    printf(COLOR_LIGHT_YELLOW"Porcentagem do arquivo para ser carregado (0 ~ 100]: ");
                    scanf("%f", &porcentagem);
                    if(porcentagem < 0 || porcentagem > 100) {
                        printf(COLOR_RED"O valor deve estar entre 0 e 100\n");
                        getchar();
                    }
                }while(porcentagem < 0 || porcentagem > 100);
                porcentagem_grafo(arquivo, porcentagem);
            }

            if(valido == 1) {
                clear();
                printf(COLOR_GREEN"Abrindo grafo: \"%s\"", arquivo);
                if(!strcmp(reduzir,"s"))
                    printf("(%.2f%%)", porcentagem);
                printf("...\n");

                start = clock();
                g = le_grafo(arquivo);
                end = clock();
                if(g == NULL) {
                    do{
                        printf(COLOR_RED"Nao foi possivel iniciar o grafo do arquivo %s, tentar novamente? (s/n): "COLOR_LIGHT_YELLOW, arquivo);
                        limpar_buffer();
                        scanf("%s", r);
                        if(strcmp(r,"s") && strcmp(r,"S") && strcmp(r,"n") && strcmp(r,"N")) printf(COLOR_RED"Opcao invalida\n");
                    } while(strcmp(r,"s") && strcmp(r,"S") && strcmp(r,"n") && strcmp(r,"N"));
                    if(strcmp(r, "s")){
                        printf(COLOR_LIGHT_YELLOW"Pressione enter para sair...\n");
                        printf(COLOR_RESET);
                        limpar_buffer();
                        getchar();
                        clear();
                        return 0;
                    }
                }
            } else {
                g = NULL;
                if(valido != 2) {
                    printf(COLOR_RED"Tente novamente, pressione enter para continuar...\n"COLOR_RESET);
                    limpar_buffer();
                    getchar();
                }
            }
        }while(g == NULL);
        // clear();
        printf("Grafo carregado com sucesso em %.2lf segundos!\nPressione enter para continuar...\n", ((double) (end - start) / CLOCKS_PER_SEC));
        limpar_buffer();
        getchar();
        clear();
        printf(COLOR_BLUE);
        printf("+================Informacoes do grafo================+\n");
        print_table(12, 52);
        printf("+====================================================+\n");
        printf(COLOR_LIGHT_YELLOW);
        gotoxy(2 - OS,2 - OS);
        start = clock();
        printf(" %d vertices e %d arestas\n", get_numverts(g), get_numarestas(g));
        gotoxy(2 - OS,4 - OS);
        int con = componentesConexos(g);
        printf(" %d %s\n", con, con == 1 ? "componente conexo" : "componentes conexos");
        gotoxy(2 - OS,6 - OS);
        printf(" Numero cromatico %d\n", cromatico(g));
        gotoxy(2 - OS,8 - OS);
        printf(" Grau medio %f\n", grauMedio(g));
        gotoxy(2 - OS,10 - OS);
        printf(" Densidade %f\n", densidade(g));
        gotoxy(2 - OS,12 - OS);
        printf(" Agrupamento medio %f\n", agrupamentoMedio(g));
        gotoxy(2 - OS,14 - OS);
        printf(" Excentricidade media %f\n", excentricidadeMedia(g));
        gotoxy(2 - OS,16 - OS);
        printf(" Diametro efetivo %d\n", diametroEfetivo(g));
        gotoxy(2 - OS, 18 - OS);
        printf(" Raio efetivo %d\n", raioEfetivo(g));
        gotoxy(2 - OS, 20 - OS);
        printf(" Centralidade media %f\n", centralidadeMedia(g));
        gotoxy(2 - OS, 22 - OS);
        printf(" Vertices centrais %.2f%%...\n", porceVertCentral(g) * 100);
        gotoxy(2 - OS, 24 - OS);
        printf(" Porcentagem de extremos %f\n", porcetagemExtremos(g));
        end = clock();
        gotoxy(2 - OS, 26 - OS);
        printf("Tempo de analise ");
        if(!strcmp(reduzir, "s"))
            printf("de %.2f%% ", porcentagem);
        printf("do arquivo \"%s\": %.2lf segundos", nome_arquivo(arquivo), ((double) (end - start) / CLOCKS_PER_SEC));
        gotoxy(2 - OS, 28 - OS);
        do{
            printf("Analisar outro grafo? (s/n): ");
            limpar_buffer();
            scanf("%s", o);
            if(strcmp(o, "s") && strcmp(o, "n") && strcmp(o, "S") && strcmp(o, "N"))
                printf(COLOR_RED"Opcao invalida...\n"COLOR_LIGHT_YELLOW);
        } while(strcmp(o, "s") && strcmp(o, "n") && strcmp(o, "S") && strcmp(o, "N"));

    } while(strcmp(r, "0") && strcmp(o, "n"));
    printf(COLOR_RESET);
    clear();
    return 0;
}

int lista_arquivos(char *arquivo) {
    DIR *dir;
    struct dirent *ent;
    int index = 1, i;
    if ((dir = opendir(arquivo)) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            if(!strcmp(get_filename_ext(ent->d_name),"txt")){
                printf("|" COLOR_LIGHT_YELLOW "%3d - %s"COLOR_BLUE, index++, ent->d_name);
                for(i = 0; i < 36 - strlen(ent->d_name); i++)
                    printf(" ");
                printf("|\n");
            }
        }
    } else {
        printf("|"COLOR_RED"Nao foi possivel abrir o arquivo \"%s\""COLOR_BLUE" |\n", arquivo);
        return -1;
    }
    return index - 1;
}

char *encontra_arquivo(char *indice) {
    DIR *dir;
    struct dirent *ent;
    int index = atoi(indice), i = 0;
    if((dir = opendir("grafos")) != NULL) {
        while(i < index && (ent = readdir(dir)) != NULL)
            if( ent != NULL && !strcmp(get_filename_ext(ent->d_name),"txt"))
                i++;
        if(ent == NULL) return NULL;
        return ent->d_name;
    } else {
        printf("Diretorio de grafos nao encontrado\n");
        return NULL;
    }
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int isnumber(char *s) {
    int i;
    for(i = 0; i < strlen(s); i++) {
        if(!isdigit(s[i]))
            return 0;
    }
    return 1;
}

void print_table(int nlines, int colwidth) {
    int i, j;
    for(i = 0; i < nlines; i++) {
        printf("| Carregando...");
        for(j = 0; j < colwidth - strlen("Carregando...") - 1; j++)
            printf(" ");
        printf("|\n");
        if(i < nlines - 1){
            printf("+");
            for(j = 0; j < colwidth; j++)
                printf("%c", '-');
            printf("+\n");
        }
    }
}

char *nome_arquivo(char* nome) {
    //printf("\n%s,%c\n", nome, nome[strlen(nome)-1]);
    if(nome[strlen(nome)-1] == 'z') nome[strlen(nome)-4] = '\0';
    return nome;
}
