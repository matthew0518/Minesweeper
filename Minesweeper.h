/*
Author: Matthew Marbina (mmarbin, 251301786)
Description: Header file for the MineSweeper class. This class represents a single the logic for the minesweeper game. 
It declares the properties of the game and all functions used in the implementation class. 
Also has a guard to prevent multiple inclusions of the header file.
Date: 2025-02-08 
*/
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QIcon>
#include <random>
#include "Tile.h"

class Minesweeper : public QWidget {
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr); //Constructor for the Minesweeper class
    ~Minesweeper(); //Destructor for the Minesweeper class
    void setupBoard(); //Sets up the game board
    void resetGame(); //Resets the game
    void reveal(int row, int col); //Reveals the tile at the given row and column
    int countAdjacentMines(int row, int col); //Counts the number of adjacent mines
    void gameOver(bool won); //Checks if the game has either been won or lost

private:
    QGridLayout *grid; //The grid layout for the game
    std::vector<std::vector<Tile*>> buttons; //The tiles for the game represented as a 2D vector of Tile
    std::vector<int> mines; //The positions of the mines represented as a vector of integers
    std::vector<int> allPositions; //All possible positions on the board
    int revealedCount; //The number of tiles that have been revealed
    std::random_device rd; //Random device for shuffling the mines
    int row; //The row of the tile
    int col; //The column of the tile
    int numOfAdjacentMines; //The number of adjacent mines

private slots:
    void onLeftClick(); //Handles left click events
    void onRightClick(); //Handles right click events
};

#endif 
