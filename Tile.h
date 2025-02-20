/*
Author: Matthew Marbina (mmarbin, 251301786)
Description: Header file for the Tile class. This class represents a single tile in the Minesweeper game. 
It declares the properties of the tile and all functions used in the implementation class. 
Also has a guard to prevent multiple inclusions of the header file.
Date: 2025-02-08 
*/
#ifndef TILE_H
#define TILE_H

#include <QMouseEvent>
#include <QPushButton>
#include <QIcon>

class Tile : public QPushButton {
    Q_OBJECT

public:
    Tile(int row, int col, QWidget *parent = nullptr); //Constructor for the Tile class
    ~Tile(); //Destructor for the Tile class
    int getRow() const; //Getter for the row property
    int getCol() const; //Getter for the col property
    bool getIsMine() const; //Getter for the isMine property
    bool getIsRevealed() const; //Getter for the isRevealed property
    bool getIsFlagged() const; //Getter for the isFlagged property
    bool getIsQuestionMarked() const; //Getter for the isQuestionMarked property
    void setIsMine(bool isMine); //Setter for the isMine property
    void setIsRevealed(bool isRevealed); //Setter for the isRevealed property
    void setIsFlagged(bool isFlagged); //Setter for the isFlagged property
    void setIsQuestionMarked(bool isQuestionMarked); //Setter for the isQuestionMarked property
    void setOtherIcon(int iconIndex); //Sets the icon of the tile to the other icons (bomb, flag, question mark) based on the icon index

private:
    int row; //The row of the tile
    int col; //The column of the tile
    bool isMine; //Whether the tile is a mine
    bool isRevealed; //Whether the tile has been revealed
    bool isFlagged; //Whether the tile is flagged
    bool isQuestionMarked; //Whether the tile is question marked
    QIcon other_icons[3]; //Icons for the mine, flag, and question mark

protected:
    void mousePressEvent(QMouseEvent *e) override; //Handles mouse press events

signals:
    void rightClicked(); //Signal for right click
    void leftClicked(); //Signal for left click
};

#endif 
