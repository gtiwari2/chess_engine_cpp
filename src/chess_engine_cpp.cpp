// chess_engine_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "pieces.h"
#include "board.h"

int main()
{
    static Piece::side curSide = Piece::white;
    static std::string menuSelect, pieceToMove, locationToMoveTo;

    std::cout << "Welcome! Type play to start a new game or type exit to quit. Press Escape at any point during the game to return to the Main Menu." << std::endl;
    std::cin >> menuSelect;

    std::cout << menuSelect << std::endl;

    if (menuSelect == "exit")
        return 0;

    // inits boards by default
    //Board* DefaultBoard;

    // game loop
    while (!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        // DefaultBoard->Draw();
        std::cout << (curSide == Piece::white) ? "It is white's turn.\n" : "It is black's turn.\n";
        std::cout << "Enter the location of the piece you would like to move:" << std::endl;
        std::cin >> pieceToMove;
        //if (DefaultBoard->PieceExists())

        std::cout << "Enter the location you would like to move it to:" << std::endl;
        std::cin >> locationToMoveTo;
        // DefaultBoard->ValidateMove(<coords or chars?>);
    }

}
