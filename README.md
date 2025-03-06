# Overview

![](https://upload.wikimedia.org/wikipedia/en/2/23/Picture_of_Azul_game_box.jpg)[-

This is a C program for the board game Azul. The goal of the game is to get as many points as you can to beat your opponents, which could be played by 2-4 people. They collected tiles from the Factory Display (discs) and placed them to their own walls with certain rules. The game ends when a player completed a horizontal row of the wall. Please refer to the details and gameplay examples of the official game instructions: https://tesera.ru/images/items/1108676/EN-Azul-Rules.pdf

# Pre-game setup

There are 100 coloured tiles, with 20 tiles for each color (cyan, orange, red, black, white), are being filled in a bag. For a 4-player game, place 9 discs; For a 3-player game, place 7 discs; For a 2-player game, place 5 discs; Each disc will be initialised with 4 tiles, randomly picked from the bag every turn. 

# Gameplay

![](https://imgur.com/a/HVjKQ8G)[-

Each player take turns to either pick all tiles of a chosen colour from a disc or the centre, which contains tiles unselected from the disc selected other than the chosen colour. The game designer states that the player visited Portugal most recently goes first, indicated by the first player marker, with a "1" on it. It is placed in the centre at the start of every turn, the first player who choose the centre should also collect the first player marker, putting it on the floor line, corresponds to the penalty points (Please refer to scoring below).

The player will pick a number of selected colour tiles and place them on the left of their own board, in one of the row from row 1 to row 5, starting from the left. For every row, the tiles number should not exist the row number, all tiles must be the same colour according to the tiles first placed on the left, and the colour must not be placed which already exists in the wall from the wall-tiling phase (see next paragraph). If that happens, they should be placed in the floor line, starting from the left. If the floor line is full with 7 tiles, the tiles could be discarded. 

The turn ends when all tiles are collected from the discs and the centre, the players will transfer their fully filled row color to the right, from the first row to the last row, the wall tile corresponding to that color. All other tiles from the row will be discarded and the turn starts again until one of the player filled a row of the wall tiles. If there are not enough tiles in the bag, transfer all discarded tiles to it.

# Scoring

In the wall-tiling phase, player will score for the tile of the wall transfered from every fully filled row. If none of the wall tile already exists vertically or horizontally to the newly placed wall tile, the player will score 1 point. If there is either tiles vertically or horizontally, the player will score the number of linked tiles. If there are horizontally and vertically wall tiles, the number will score the points adding up the linked vertical and linked horizontal tiles. The score will then be detucted according to the penalty on the floor tile, in the order of -1, -1, -2, -2, -3, -3, -3, and the tiles will all be discarded before next turn.

At the end of the game, the player will get extra 2 points for a whole horizontal row, 7 points for a whole vertical row and 10 points for every colour completed with 5 tiles on the wall.

# Strategy

The basic strategy is to fill horizontal lines or vertical lines as fast as you can. You may also pursue for colour completition but it will divert from completing the rows or columns since each of the colour is diagonally placed. You could be aware for the order of tiles in the wall-tiling phases, since it will affect every wall tiles scoring. You should aware of the number of tiles you picked in order not to get too many penalty points. Sometimes selecting the centre with the first player marker correspond to penalty will be benficial.

# Implementation and UI

I use dashes and strokes to replicate the Azul game, highlighted **X** corresponds to a tile while, the colour of the wall demonstrates the position of the coloured-tile could be placed in the wall-tiling phase. The penalty point will be highlighted with the colour of the tile.

Every turn, the player will be asked to input either the disc number or the centre, if tiles exist. Input will be checked to confirm validity. The player will then chose a colour, hinted inside the brackets. Again, the player cannot proceed if the input is invalid. The player then select the row number. All points will be calculated automatically and winner will be determined at the end of the game.

# AI

My so-called AI is a naive random number generator trying their best to get as many points as it can with some while loops and if-then-else, calculating the value of each move and select the valid move with maximum value. I like the game tree idea in !(https://domwil.co.uk/posts/azul-ai/), but my AI is nowhere near of that guy, only my AI run faster and I can test my program with a computer to see if the gameplay is valid.

# How to Play

Download the azul.c and run `
gcc azul.c -o azul
./azul
`
to enjoy the two-player game.



# Motivation

This Azul game is made to prepare for an on-site C program technical tests of a job interview. In fact, it is a simple written test, and I failed the interview.



