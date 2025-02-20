/*
Author: Matthew Marbina (mmarbin, 251301786)
Description: Main file for the Minesweeper game. This file creates an instance of the Minesweeper class and displays the game window.
Date: 2025-02-08
*/
#include "Minesweeper.h"

/*
Function Name: main
Description: Main function that creates an instance of the Minesweeper class and displays the game window.
Parameter Descriptions: 
    argc: The number of command line arguments
    argv: The command line arguments
Return Value: The exit status of the application
*/
int main(int arg_count, char *arg_vector[]) {
    QApplication app(arg_count, arg_vector);

    Minesweeper minesweeper;
    minesweeper.setWindowTitle("Minesweeper");
    minesweeper.resize(900, 480);
    minesweeper.show();

    return app.exec();
}
