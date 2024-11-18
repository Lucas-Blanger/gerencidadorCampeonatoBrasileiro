## Campeonato Brasileiro - Sistema de Gerenciamento de Times e Partidas

## Sobre o Projeto

Este é um sistema em C desenvolvido como parte de um trabalho para a disciplina de Laboratório de Programação. O objetivo é simular a gestão de um campeonato de futebol, permitindo o cadastro de times, jogadores, partidas e eventos ocorridos durante as partidas. Além disso, o sistema gera relatórios detalhados sobre a classificação geral, artilharia e estatísticas dos times.

## Funcionalidades

1. Gerenciamento de Times

    -  Cadastro de novos times com informações básicas (nome e estado).
    - Exclusão de times cadastrados.
    - Consulta de times pelo nome.

2. Gerenciamento de Jogadores

    - Cadastro de jogadores associados a um time.
    - Exclusão de jogadores específicos.
    - Consulta de jogadores pelo nome.

3. Gerenciamento de Partidas

    - Cadastro de partidas entre dois times.
    - Registro de eventos durante as partidas (gols, cartões, faltas, etc.).
    - Exclusão de partidas cadastradas.
    - Consulta de partidas entre dois times.

4. Relatórios

    - Classificação Geral: Gols feitos e sofridos por cada time.
    - Artilharia: Lista de jogadores com a quantidade de gols marcados.
    - Estatísticas Gerais: Faltas, cartões amarelos/vermelhos e outras informações de cada time.

5. Escalação

    - Montagem de uma escalação padrão para um time, com base no número de jogadores especificado.

## Pré-requisitos para Execução

  - Compilador C compatível (como gcc).
  - Sistema com suporte ao padrão C99 ou superior.
  - Localização configurada para pt_BR.UTF-8 para correta exibição de caracteres.

## Como Executar

  Compile o código utilizando o comando:

    gcc campeonato.c -o campeonato

  Execute o programa:

    ./campeonato
