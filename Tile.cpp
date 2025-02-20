/*
Author: Matthew Marbina (mmarbin, 251301786)
Description: Implementation file for the Tile class. This class represents a single tile in the Minesweeper game and defines
all variables and functions related to the tile. It includes the constructor, where all the variables are defined, and the 
destructor for the class, as well as functions to get and set tile properties and a function to set the icon of the tile to 
the other icons (bomb, flag, question mark) based on the icon index. It also includes a function to handle mouse press events 
for the tile.
Date: 2025-02-08
*/
#include "Tile.h"

/*
Function Name: Tile
Description: Constructor for the Tile class. Initializes the tile with the given row and column, sets the size of the tile,
and sets the icon size. Initializes the tile properties (isMine, isRevealed, isFlagged, isQuestionMarked) to false and sets the
other icons (bomb, flag, question mark) to the corresponding icons.
Parameter Descriptions: 
    row: The row of the tile
    col: The column of the tile
    parent: The parent widget of the tile
Return Value: None
*/
Tile::Tile(int row, int col, QWidget *parent) : QPushButton(parent) {
    setFixedSize(30, 30);
    setIconSize(QSize(30, 30));
    this->row = row;
    this->col = col;
    isMine = false;
    isRevealed = false;
    isFlagged = false;
    isQuestionMarked = false;
    other_icons[0] = QIcon(":/icons/bomb.png");
    other_icons[1] = QIcon(":/icons/flag.png");
    other_icons[2] = QIcon(":/icons/qmark.png");
}

/*
Function Name: ~Tile
Description: Destructor for the Tile class
Parameter Descriptions: None
Return Value: None
*/
Tile::~Tile() {
    //Destructor for the Tile class, does nothing
}

/*
Function Name: getRow
Description: Getter for the row property
Parameter Descriptions: None
Return Value: The row of the tile
*/
int Tile::getRow() const {
    return row;
}

/*
Function Name: getCol
Description: Getter for the col property
Parameter Descriptions: None
Return Value: The column of the tile
*/
int Tile::getCol() const {
    return col;
}

/*
Function Name: getIsMine
Description: Getter for the isMine property
Parameter Descriptions: None
Return Value: Whether the tile is a mine
*/
bool Tile::getIsMine() const {
    return isMine;
}

/*
Function Name: getIsRevealed
Description: Getter for the isRevealed property
Parameter Descriptions: None
Return Value: Whether the tile has been revealed
*/
bool Tile::getIsRevealed() const {
    return isRevealed;
}

/*
Function Name: getIsFlagged
Description: Getter for the isFlagged property
Parameter Descriptions: None
Return Value: Whether the tile is flagged
*/
bool Tile::getIsFlagged() const {
    return isFlagged;
}

/*
Function Name: getIsQuestionMarked
Description: Getter for the isQuestionMarked property
Parameter Descriptions: None
Return Value: Whether the tile is question marked
*/
bool Tile::getIsQuestionMarked() const {
    return isQuestionMarked;
}

/*
Function Name: setIsMine
Description: Sets the isMine property of the tile given a boolean value
Parameter Descriptions: 
    isMine: Whether the tile is a mine
Return Value: None
*/
void Tile::setIsMine(bool isMine) {
    this->isMine = isMine;
}

/*
Function Name: setIsRevealed
Description: Sets the isRevealed property of the tile given a boolean value
Parameter Descriptions: 
    isRevealed: Whether the tile has been revealed
Return Value: None
*/
void Tile::setIsRevealed(bool isRevealed) {
    this->isRevealed = isRevealed;
}

/*
Function Name: setIsFlagged
Description: Sets the isFlagged property of the tile given a boolean value
Parameter Descriptions: 
    isFlagged: Whether the tile is flagged
Return Value: None
*/
void Tile::setIsFlagged(bool isFlagged) {
    this->isFlagged = isFlagged;
}

/*
Function Name: setIsQuestionMarked
Description: Sets the isQuestionMarked property of the tile given a boolean value
Parameter Descriptions: 
    isQuestionMarked: Whether the tile is question marked
Return Value: None
*/
void Tile::setIsQuestionMarked(bool isQuestionMarked) {
    this->isQuestionMarked = isQuestionMarked;
}

/*
Function Name: set_other_icon
Description: Sets the icon of the tile to the other icons (bomb, flag, question mark) based on the icon index.
Parameter Descriptions: 
    icon_index: The index of the other icons
Return Value: None
*/
void Tile::setOtherIcon(int iconIndex) {
    if (iconIndex >= 0 && iconIndex <= 2) {
        this->setIcon(other_icons[iconIndex]);
        this->setIconSize(QSize(30, 30));
        
    }
}

/*
Function Name: mousePressEvent
Description: Handles mouse press events for the tile. Emits signals for right and left clicks.
Parameter Descriptions: 
    e: The mouse event
Return Value: None
*/
void Tile::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        emit rightClicked();
    } else if (e->button() == Qt::LeftButton) {
        emit leftClicked();
    }
}
