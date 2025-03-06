# Overview

![](https://upload.wikimedia.org/wikipedia/en/2/23/Picture_of_Azul_game_box.jpg)[-

This is a C program for the board game Azul. The goal of the game is to score as many points as possible to beat your opponents, who can be 2-4 players. Players collect tiles from the Factory Display (discs) and place them on their own walls following certain rules. The game ends when a player completes a horizontal row of their wall. Please refer to the details and gameplay examples in the [official game instructions](https://tesera.ru/images/items/1108676/EN-Azul-Rules.pdf)

# Pre-game setup

There are 100 coloured tiles, with 20 tiles of each colour (cyan, orange, red, black, white), which are placed in a bag. For a 4-player game, place 9 discs; for a 3-player game, place 7 discs; for a 2-player game, place 5 discs. Each disc will be initialised with 4 tiles, randomly picked from the bag each turn.

# Gameplay

<img src="https://github.com/moabzomg/Azul/blob/main/azul.png" width="500">

Each player takes turns to either pick all tiles of a chosen colour from a disc or the centre, which contains the unselected tiles from the disc, other than the chosen colour. The game designer states that the player who visited Portugal most recently goes first, indicated by the first-player marker with a "1" on it. This marker is placed in the centre at the start of every turn. The first player to choose the centre should also collect the first-player marker, placing it on the floor line, which corresponds to penalty points (see scoring below).

The player will pick a number of selected colour tiles and place them on the left of their own board, in one of the rows from row 1 to row 5, starting from the left. For every row, the number of tiles should not exceed the row number. All tiles must be the same colour as the first tile placed on the left, and the colour must not already exist in the wall (from the wall-tiling phase, see next paragraph). If that happens, the tiles must be placed in the floor line, starting from the left. If the floor line is full with 7 tiles, the tiles may be discarded.

The turn ends when all tiles are collected from the discs and the centre. The players will then transfer their fully filled row's colour to the right, from the first row to the last row, filling the wall tile corresponding to that colour. All other tiles from the row will be discarded, and the turn starts again until one of the players fills a row of their wall tiles. If there are not enough tiles in the bag, all discarded tiles are transferred back into it.
# Scoring

In the wall-tiling phase, the player will score for the tile placed on the wall from every fully filled row. If the newly placed wall tile does not have any adjacent tiles vertically or horizontally, the player will score 1 point. If there are tiles either vertically or horizontally adjacent, the player will score the number of linked tiles. If there are both horizontally and vertically linked tiles, the score will be the sum of the vertical and horizontal linked tiles. The score will then be deducted according to the penalty for the floor tiles in the order of -1, -1, -2, -2, -3, -3, -3, and the tiles will be discarded before the next turn.

At the end of the game, the player will receive extra points: 2 points for a completed horizontal row, 7 points for a completed vertical column, and 10 points for every colour completed with 5 tiles on the wall.

# Strategy

The basic strategy is to fill horizontal or vertical lines as quickly as possible. You may also aim for colour completion, but this will divert attention from completing rows or columns since each colour is placed diagonally. You should be mindful of the order of tiles during the wall-tiling phase, as this will affect the scoring for wall tiles. Be cautious about the number of tiles you collect to avoid accumulating too many penalty points. Sometimes, selecting the centre and receiving the first-player marker (which comes with penalties) can be beneficial.

# Implementation and UI

I use dashes and strokes to replicate the Azul game, with highlighted X corresponding to a tile. The colour of the wall indicates where the coloured tiles can be placed during the wall-tiling phase. The penalty points are highlighted with the colour of the tile.

At the start of every turn, the player will be prompted to input either the disc number or the centre (if tiles are available). The input will be checked to ensure validity. The player will then choose a colour, which is indicated inside brackets. Again, the player cannot proceed if the input is invalid. The player must then select a row number. All points will be automatically calculated, and the winner will be determined at the end of the game.

# AI

My so-called AI is a simple random number generator that tries to score as many points as it can using while loops and if-then-else statements. It evaluates the value of each move and selects the valid move with the maximum value. I am inspired by the game tree concept from [Dom Wilson](https://domwil.co.uk/posts/azul-ai/), although my AI is far from that, running faster but not nearly as advanced. This AI helps me test my program to ensure the gameplay is valid.

# How to Play

Install `gcc` if you don't have one, e.g. 
`brew install gcc` in your terminal

Download the azul.c and run 
```
gcc azul.c -o azul
./azul
```
to enjoy the two-player game.

To change it with a game of 3 or 4 and with AI involvement, download and run `./azul.sh` in your terminal and follow the input prompts. 




# Motivation

This Azul game was created in preparation for an on-site C programming technical test during a job interview. It is, in fact, a simple written test, and I failed the interview.



