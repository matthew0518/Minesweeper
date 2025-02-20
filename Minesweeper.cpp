/*
Author: Matthew Marbina (mmarbin, 251301786)
Description: Implementation file for the MineSweeper class. This class represents the logic for the minesweeper game.
It defines all variables and functions related to the game. It includes the constructor, where the game board is set up,
and the resetGame function, which resets the game. It also includes functions to reveal a tile, count the number of adjacent
mines, and check if the game has been won or lost. It also includes functions to handle left and right click events.
Date: 2025-02-08
*/
#include "Minesweeper.h"
using namespace std;

/*
Function Name: Minesweeper
Description: Constructor for the Minesweeper class. Initializes the game board, sets the grid layout, and sets up the game board.
It also initializes the buttons, mines, the allPositions vector, and other properties of the game, as well as calling the setupBoard function and the 
resetGame function to make the game ready to play.
Parameter Descriptions: 
    parent: The parent widget of the game
Return Value: None
*/
Minesweeper::Minesweeper(QWidget *parent) : QWidget(parent) {
    grid = new QGridLayout(this);
    grid->setSpacing(0);
    buttons.resize(16, std::vector<Tile*>(30));
    mines.resize(99);
    allPositions.resize(480);
    revealedCount = 0;
    row = 0;
    col = 0;
    numOfAdjacentMines = 0;
    setupBoard();
    resetGame();
}

/*
Function Name: ~Minesweeper
Description: Destructor for the Minesweeper class
Parameter Descriptions: None
Return Value: None
*/
Minesweeper::~Minesweeper() {
    //Destructor for the Minesweeper class, does nothing
}

/*
Function Name: setupBoard
Description: Sets up the game board by creating a 16x30 grid of Tiles and adding them to the grid layout.
Parameter Descriptions: None
Return Value: None
*/
void Minesweeper::setupBoard() {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            buttons[row][col] = new Tile(row, col);
            grid->addWidget(buttons[row][col], row, col);
            connect(buttons[row][col], &Tile::leftClicked, this, &Minesweeper::onLeftClick);
            connect(buttons[row][col], &Tile::rightClicked, this, &Minesweeper::onRightClick);
        }
    }
    setLayout(grid);
}

/*
Function Name: resetGame
Description: Resets the game by clearing the mines, shuffling the positions, selecting the first 99 positions as mine locations,
and resetting the buttons. It also places the mines on the board.
Parameter Descriptions: None
Return Value: None
*/
void Minesweeper::resetGame() {
    revealedCount = 0;
    mines.clear();

    //Set all positions on the board
    for (int i = 0; i < 480; ++i) {
        allPositions[i] = i;
    }

    //Shuffle the positions to randomize them
    mt19937 gen(rd());
    shuffle(allPositions.begin(), allPositions.end(), gen);

    //Select the first 99 positions as mine locations
    for (int i = 0; i < 99; ++i) {
        mines[i] = allPositions[i];
    }

    //Reset the tiles
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            buttons[row][col]->setText("");
            buttons[row][col]->setStyleSheet("background-color: rgb(245, 245, 245)");
            buttons[row][col]->setIcon(QIcon());
            buttons[row][col]->setIsMine(false);
            buttons[row][col]->setIsRevealed(false);
            buttons[row][col]->setIsFlagged(false);
            buttons[row][col]->setIsQuestionMarked(false);
            buttons[row][col]->setEnabled(true);
        }
    }

    //Place mines
    for (int i = 0; i < 99; ++i) {
        row = mines[i] / 30;
        col = mines[i] % 30;
        buttons[row][col]->setIsMine(true);
    }
}

/*
Function Name: onLeftClick
Description: Handles left click events by revealing the tile at the given row and column. If the tile is a mine, the game is over.
If all non-mine tiles have been revealed, the game is won.
Parameter Descriptions: None
Return Value: None
*/
void Minesweeper::onLeftClick() {
    Tile *button = qobject_cast<Tile*>(sender()); //Get the button that was clicked
    if (button->getIsRevealed()) {
        return;
    }

    if (button->getIsMine()) {
        gameOver(false);
        return;
    }

    reveal(button->getRow(), button->getCol()); //Reveal the tile

    if (revealedCount == 16 * 30 - 99) {
        gameOver(true);
    }
}

/*
Function Name: onRightClick
Description: Handles right click events by flagging or question marking the tile at the given row and column.
Parameter Descriptions: None
Return Value: None
*/
void Minesweeper::onRightClick() {
    Tile *button = qobject_cast<Tile*>(sender()); //Get the button that was clicked
    
    //If the tile is already revealed, do nothing
    if (!button || button->getIsRevealed()) {
        return;
    }

    //If the tile is not flagged or question marked, flag it
    if (!button->getIsFlagged() && !button->getIsQuestionMarked()) {
        button->setOtherIcon(1);
        button->setIsFlagged(true);
    //If the tile is flagged, question mark it if the user right clicks again
    } else if (button->getIsFlagged() && !button->getIsQuestionMarked()) {
        button->setOtherIcon(2);
        button->setIsFlagged(false);
        button->setIsQuestionMarked(true);
    //If the tile is question marked, remove the question mark if the user right clicks again
    } else if (!button->getIsFlagged() && button->getIsQuestionMarked()) {
        button->setIcon(QIcon());
        button->setIsQuestionMarked(false);
    }
}

/*
Function Name: reveal
Description: Reveals the tile at the given row and column. If the tile is not a mine, it reveals all adjacent tiles that are not mines.
Parameter Descriptions: 
    row: The row of the tile
    col: The column of the tile
Return Value: None
*/
void Minesweeper::reveal(int row, int col) {
    //If the tile is out of bounds or has already been revealed, do nothing
    if (row < 0 || row >= 16 || col < 0 || col >= 30 || buttons[row][col]->getIsRevealed()) {
        return;
    }

    buttons[row][col]->setIsRevealed(true);
    buttons[row][col]->setEnabled(false);
    revealedCount++;

    int minesCount = countAdjacentMines(row, col); //Count the number of adjacent mines
    //If the tile is a mine, game over
    if (minesCount > 0) {
        buttons[row][col]->setIcon(QIcon(":/icons/" + QString::number(minesCount) + ".png"));
        buttons[row][col]->setIconSize(QSize(30, 30));
    //If the tile is not a mine, reveal all adjacent tiles that are not mines
    } else {
        buttons[row][col]->setIcon(QIcon());
        buttons[row][col]->setStyleSheet("background-color: rgb(192, 192, 192)");
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                reveal(row + i, col + j); //Recursive call to reveal adjacent tiles
            }
        }
    }
}

/*
Function Name: countAdjacentMines
Description: Counts the number of adjacent mines to the tile at the given row and column.
Parameter Descriptions: 
    row: The row of the tile
    col: The column of the tile
Return Value: The number of adjacent mines
*/
int Minesweeper::countAdjacentMines(int row, int col) {
    numOfAdjacentMines = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (row + i >= 0 && row + i < 16 && col + j >= 0 && col + j < 30 && buttons[row + i][col + j]->getIsMine()) {
                numOfAdjacentMines++;
            }
        }
    }
    return numOfAdjacentMines;
}

/*
Function Name: gameOver
Description: Checks if the game has either been won or lost. If the game has been won, a message box is displayed congratulating 
the player. If the game has been lost, a message box is displayed informing the player that they have hit a mine and exploded.
Parameter Descriptions: 
    won: Whether the game has been won
Return Value: None
*/
void Minesweeper::gameOver(bool won) {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            buttons[row][col]->setEnabled(false);
            if (buttons[row][col]->getIsMine()) {
                buttons[row][col]->setOtherIcon(0);
                buttons[row][col]->setStyleSheet("background-color: red");
            }
        }
    }

    QMessageBox msgBox; //Message box to display the game result
    msgBox.resize(700, 400);
    //Set the title and text of the message box based on whether the game has been won
    if (won) {
        msgBox.setWindowTitle("Congratulations!");
    } else {
        msgBox.setWindowTitle("Uh Oh!");
    }
    
    if (won) {
        msgBox.setText("Congratulations! You have won the game!");
    } else {
        msgBox.setText("Uh Oh! You have hit a mine and exploded!");
    }
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Retry);

    //If the player chooses to retry, reset the game
    if (msgBox.exec() == QMessageBox::Retry) {
        resetGame();
    } else {
        QApplication::quit();
    }
}
