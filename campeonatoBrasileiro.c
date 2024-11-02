#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TIMES 10
#define MAX_JOGADORES 25
#define MAX_PARTIDAS 10
#define MAX_EVENTOS 50

// Estruturas
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

// Funções
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

void narrarEvento(Campeonato *c, int partidaIndex, int minuto, char evento[]) {
    if (partidaIndex >= 0 && partidaIndex < c->totalPartidas) {
        Partida *p = &c->partidas[partidaIndex];
        if (p->totalEventos < MAX_EVENTOS) {
            Evento *e = &p->eventos[p->totalEventos];
            e->minuto = minuto;
            strcpy(e->evento, evento);
            p->totalEventos++;
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

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Campeonato campeonato;
    inicializarCampeonato(&campeonato);

    // Cadastrar 2 times
    cadastrarTime(&campeonato, "Internacional", "RS");
    cadastrarTime(&campeonato, "Flamengo", "RJ");

    // Cadastrar jogadores para os times
    cadastrarJogador(&campeonato, 0, "Gabriel", "Atacante", 25, 10);
    cadastrarJogador(&campeonato, 0, "Igor", "Defensor", 28, 4);
    cadastrarJogador(&campeonato, 1, "Ener", "Atacante", 22, 9);
    cadastrarJogador(&campeonato, 1, "Carlos", "Defensor", 30, 5);

    // Cadastrar duas partidas
    cadastrarPartida(&campeonato, 0, 1);
    narrarEvento(&campeonato, 0, 10, "Gol do Gabriel");
    narrarEvento(&campeonato, 0, 45, "Cartão amarelo para Carlos");

    // Relatórios
    imprimirRelatorioClassificacao(&campeonato);
    imprimirRelatorioArtilharia(&campeonato);
    imprimirRelatorioEstatisticas(&campeonato);

}
