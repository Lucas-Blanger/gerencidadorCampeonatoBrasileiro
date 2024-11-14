/*
Nome: Lucas Blanger
Disciplina: Laboratório de Programação
Trabalho 2 - Campeonato Brasileiro
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TIMES 10
#define MAX_JOGADORES 25
#define MAX_PARTIDAS 10
#define MAX_EVENTOS 50

typedef struct {
    char nome[50];
    char estado[3];
    int jogadoresAtuais;
    int golsFeitos;
    int golsSofridos;
    int cartoesAmarelos;
    int cartoesVermelhos;
    int faltas;
} Time;

typedef struct {
    char nome[50];
    char posicao[20];
    int idade;
    int numeroCamisa;
    int gols;
} Jogador;

typedef struct {
    int minuto;
    char evento[100];
} Evento;

typedef struct {
    Time *time1;
    Time *time2;
    Evento eventos[MAX_EVENTOS];
    int totalEventos;
} Partida;

typedef struct {
    Time times[MAX_TIMES];
    Jogador jogadores[MAX_TIMES][MAX_JOGADORES];
    Partida partidas[MAX_PARTIDAS];
    int totalTimes;
    int totalPartidas;
} Campeonato;

void inicializarCampeonato(Campeonato *c) {
    c->totalTimes = 0;
    c->totalPartidas = 0;
}

void cadastrarTime(Campeonato *c, char nome[], char estado[]) {
    if (c->totalTimes < MAX_TIMES) {
        strcpy(c->times[c->totalTimes].nome, nome);
        strcpy(c->times[c->totalTimes].estado, estado);
        c->times[c->totalTimes].jogadoresAtuais = 0;
        c->times[c->totalTimes].golsFeitos = 0;
        c->times[c->totalTimes].golsSofridos = 0;
        c->times[c->totalTimes].cartoesAmarelos = 0;
        c->times[c->totalTimes].cartoesVermelhos = 0;
        c->times[c->totalTimes].faltas = 0;
        c->totalTimes++;
    }
}

void cadastrarJogador(Campeonato *c, int timeIndex, char nome[], char posicao[], int idade, int numeroCamisa) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes) {
        Time *t = &c->times[timeIndex];
        if (t->jogadoresAtuais < MAX_JOGADORES) {
            Jogador *j = &c->jogadores[timeIndex][t->jogadoresAtuais];
            strcpy(j->nome, nome);
            strcpy(j->posicao, posicao);
            j->idade = idade;
            j->numeroCamisa = numeroCamisa;
            j->gols = 0;
            t->jogadoresAtuais++;
        }
    }
}

void cadastrarPartida(Campeonato *c, int time1Index, int time2Index) {
    if (c->totalPartidas < MAX_PARTIDAS && time1Index >= 0 && time1Index < c->totalTimes && time2Index >= 0 && time2Index < c->totalTimes) {
        Partida *p = &c->partidas[c->totalPartidas];
        p->time1 = &c->times[time1Index];
        p->time2 = &c->times[time2Index];
        p->totalEventos = 0;
        c->totalPartidas++;
    }
}

Jogador* encontrarJogadorPorNome(Campeonato *c, int timeIndex, const char *nomeJogador) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes) {
        Time *t = &c->times[timeIndex];
        for (int i = 0; i < t->jogadoresAtuais; i++) {
            if (strcmp(c->jogadores[timeIndex][i].nome, nomeJogador) == 0) {
                return &c->jogadores[timeIndex][i];
            }
        }
    }
    return NULL;
}

void narrarEvento(Campeonato *c, int partidaIndex, int minuto, char evento[]) {
    if (partidaIndex >= 0 && partidaIndex < c->totalPartidas) {
        Partida *p = &c->partidas[partidaIndex];
        if (p->totalEventos < MAX_EVENTOS) {
            Evento *e = &p->eventos[p->totalEventos];
            e->minuto = minuto;
            strcpy(e->evento, evento);
            p->totalEventos++;
            
            if (strstr(evento, "Gol de") != NULL) {
                char nomeJogador[50];
                sscanf(evento, "Gol de %49[^\n]", nomeJogador);
                Jogador *jogador = encontrarJogadorPorNome(c, (strstr(nomeJogador, "A") ? 0 : 1), nomeJogador);
                if (jogador != NULL) {
                    jogador->gols++;
                    if (p->time1 == &c->times[0]) {
                        p->time1->golsFeitos++;
                        p->time2->golsSofridos++;
                    } else {
                        p->time2->golsFeitos++;
                        p->time1->golsSofridos++;
                    }
                }
            } else if (strstr(evento, "Cartão Amarelo para") != NULL) {
                char nomeJogador[50];
                sscanf(evento, "Cartão Amarelo para %49[^\n]", nomeJogador);
                Jogador *jogador = encontrarJogadorPorNome(c, (strstr(nomeJogador, "A") ? 0 : 1), nomeJogador);
                if (jogador != NULL) {
                    (strstr(nomeJogador, "A") ? &c->times[0] : &c->times[1])->cartoesAmarelos++;
                }
            } else if (strstr(evento, "Cartão Vermelho para") != NULL) {
                char nomeJogador[50];
                sscanf(evento, "Cartão Vermelho para %49[^\n]", nomeJogador);
                Jogador *jogador = encontrarJogadorPorNome(c, (strstr(nomeJogador, "A") ? 0 : 1), nomeJogador);
                if (jogador != NULL) {
                    (strstr(nomeJogador, "A") ? &c->times[0] : &c->times[1])->cartoesVermelhos++;
                }
            } else if (strstr(evento, "Falta de") != NULL) {
                (strstr(evento, "Jogador_A") ? &c->times[0] : &c->times[1])->faltas++;
            }
        }
    }
}

void imprimirRelatorioClassificacao(Campeonato *c) {
    printf("Classificação Geral:\n");
    for (int i = 0; i < c->totalTimes; i++) {
        Time *t = &c->times[i];
        printf("Time: %s | Gols Feitos: %d | Gols Sofridos: %d\n", t->nome, t->golsFeitos, t->golsSofridos);
    }
}

void imprimirRelatorioArtilharia(Campeonato *c) {
    printf("Artilharia:\n");
    for (int i = 0; i < c->totalTimes; i++) {
        for (int j = 0; j < c->times[i].jogadoresAtuais; j++) {
            Jogador *jog = &c->jogadores[i][j];
            printf("Jogador: %s | Gols: %d\n", jog->nome, jog->gols);
        }
    }
}

void imprimirRelatorioEstatisticas(Campeonato *c) {
    printf("Estatísticas dos times:\n");
    for (int i = 0; i < c->totalTimes; i++) {
        Time *t = &c->times[i];
        printf("Time: %s | Gols Feitos: %d | Gols Sofridos: %d | Amarelos: %d | Vermelhos: %d | Faltas: %d\n", 
            t->nome, t->golsFeitos, t->golsSofridos, t->cartoesAmarelos, t->cartoesVermelhos, t->faltas);
    }
}

void mostrarRelatorio(Campeonato *c) {
    imprimirRelatorioClassificacao(c);
    printf("\n");
    imprimirRelatorioArtilharia(c);
    printf("\n");
    imprimirRelatorioEstatisticas(c);
}

void excluirTime(Campeonato *c, int timeIndex) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes) {
        for (int i = timeIndex; i < c->totalTimes - 1; i++) {
            c->times[i] = c->times[i + 1];
            memcpy(c->jogadores[i], c->jogadores[i + 1], sizeof(Jogador) * MAX_JOGADORES);
        }
        c->totalTimes--;
    }
}

void excluirJogador(Campeonato *c, int timeIndex, int jogadorIndex) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes &&
        jogadorIndex >= 0 && jogadorIndex < c->times[timeIndex].jogadoresAtuais) {
        for (int i = jogadorIndex; i < c->times[timeIndex].jogadoresAtuais - 1; i++) {
            c->jogadores[timeIndex][i] = c->jogadores[timeIndex][i + 1];
        }
        c->times[timeIndex].jogadoresAtuais--;
    }
}

void excluirPartida(Campeonato *c, int partidaIndex) {
    if (partidaIndex >= 0 && partidaIndex < c->totalPartidas) {
        for (int i = partidaIndex; i < c->totalPartidas - 1; i++) {
            c->partidas[i] = c->partidas[i + 1];
        }
        c->totalPartidas--;
    }
}

Time* buscarTime(Campeonato *c, char nome[]) {
    for (int i = 0; i < c->totalTimes; i++) {
        if (strcmp(c->times[i].nome, nome) == 0) {
            return &c->times[i];
        }
    }
    return NULL;
}

Jogador* buscarJogador(Campeonato *c, int timeIndex, char nome[]) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes) {
        for (int i = 0; i < c->times[timeIndex].jogadoresAtuais; i++) {
            if (strcmp(c->jogadores[timeIndex][i].nome, nome) == 0) {
                return &c->jogadores[timeIndex][i];
            }
        }
    }
    return NULL;
}

Partida* buscarPartida(Campeonato *c, int time1Index, int time2Index) {
    for (int i = 0; i < c->totalPartidas; i++) {
        if (c->partidas[i].time1 == &c->times[time1Index] &&
            c->partidas[i].time2 == &c->times[time2Index]) {
            return &c->partidas[i];
        }
    }
    return NULL;
}

void montarEscalacaoPadrao(Campeonato *c, int timeIndex, int numJogadores) {
    if (timeIndex >= 0 && timeIndex < c->totalTimes && numJogadores <= c->times[timeIndex].jogadoresAtuais) {
        printf("Escalação padrão para o time %s:\n", c->times[timeIndex].nome);
        for (int i = 0; i < numJogadores; i++) {
            Jogador *j = &c->jogadores[timeIndex][i];
            printf("Nome: %s | Posição: %s | Camisa: %d\n", j->nome, j->posicao, j->numeroCamisa);
        }
    }
}


int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Campeonato campeonato;
    inicializarCampeonato(&campeonato);
    
    cadastrarTime(&campeonato, "15 de Piracicaba", "SP");
    cadastrarTime(&campeonato, "Gaúcho", "RS");
    cadastrarTime(&campeonato, "Ypiranga de Erechim", "RS");
    
    for (int i = 0; i < 11; i++) {
        char nome[20];
        sprintf(nome, "Jogador_A%d", i + 1);
        cadastrarJogador(&campeonato, 0, nome, "Atacante", 20 + i, i + 1);
    }

    for (int i = 0; i < 11; i++) {
        char nome[20];
        sprintf(nome, "Jogador_B%d", i + 1);
        cadastrarJogador(&campeonato, 1, nome, "Defensor", 22 + i, i + 1);
    }

    cadastrarPartida(&campeonato, 0, 1);
    cadastrarPartida(&campeonato, 1, 0);

    narrarEvento(&campeonato, 0, 5, "Gol de Jogador_A1");
    narrarEvento(&campeonato, 0, 15, "Cartão Amarelo para Jogador_B3");
    narrarEvento(&campeonato, 0, 45, "Falta de Jogador_A4 em Jogador_B5");

    narrarEvento(&campeonato, 1, 10, "Gol de Jogador_B2");
    narrarEvento(&campeonato, 1, 30, "Cartão Vermelho para Jogador_A7");
    narrarEvento(&campeonato, 1, 60, "Substituição: Sai Jogador_A9, Entra Jogador_A10");

    
    mostrarRelatorio(&campeonato);

    Time* time = buscarTime(&campeonato, "Gaúcho");
    if (time != NULL) {
        int timeIndex = time - campeonato.times;
        excluirTime(&campeonato, timeIndex);
    }

    cadastrarTime(&campeonato, "Gaúcho", "RS");
    cadastrarJogador(&campeonato, 1, "Jogador_B1", "Goleiro", 27, 1);


    Jogador* jogador = buscarJogador(&campeonato, 0, "Jogador_A2");
    if (jogador != NULL) {
        int jogadorIndex = jogador - campeonato.jogadores[0];
        excluirJogador(&campeonato, 0, jogadorIndex);
    }

    Partida* partida = buscarPartida(&campeonato, 0, 1);
    if (partida != NULL) {
        int partidaIndex = partida - campeonato.partidas;
        excluirPartida(&campeonato, partidaIndex);
    }

    Jogador* jogadorB1 = buscarJogador(&campeonato, 1, "Jogador_B1");
    if (jogadorB1 != NULL) {
        printf("Jogador encontrado: %s - Posição: %s - Camisa: %d\n", jogadorB1->nome, jogadorB1->posicao, jogadorB1->numeroCamisa);
    } else {
        printf("Jogador_B1 não encontrado\n");
    }

    montarEscalacaoPadrao(&campeonato, 0, 2);
    
}
