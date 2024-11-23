# Campeonato Brasileiro - Team and Match Management System
## About the Project

This is a system written in C, developed as part of an assignment for the Programming Lab course. The goal is to simulate the management of a football championship, allowing the registration of teams, players, matches, and events occurring during the matches. Additionally, the system generates detailed reports on the general standings, top scorers, and team statistics.

## Features

### Team Management
- Register new teams with basic information (name and state).
- Remove registered teams.
- Search for teams by name.

### Player Management
- Register players associated with a team.
- Remove specific players.
- Search for players by name.

### Match Management
- Register matches between two teams.
- Record events during matches (goals, cards, fouls, etc.).
- Remove registered matches.
- Search for matches between two teams.

### Reports
- General Standings: Goals scored and conceded by each team.
- Top Scorers: List of players with the number of goals scored.
- General Statistics: Fouls, yellow/red cards, and other information for each team.

### Line-up
- Create a standard line-up for a team based on the specified number of players.
    
## Prerequisites for Running

- Compatible C compiler (such as gcc).
  - System supporting C99 or higher standard.
  - Locale configured to pt_BR.UTF-8 for correct character display.

## How to Run

Compile the code using the command:

     gcc campeonato.c -o campeonato

Run the program:

     ./campeonato
