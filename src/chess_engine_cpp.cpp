// chess_engine_cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "pieces.h"
#include "board.h"

int main()
{
    static Piece::side curSide = Piece::white;
    static std::string menuSelect;
    static pos pieceToMove, locationToMoveTo;

    std::cout << "Welcome! Type play to start a new game or type exit to quit. Press Escape at any point during the game to return to the Main Menu." << std::endl;
    std::cin >> menuSelect;

    std::cout << menuSelect << std::endl;

    if (menuSelect == "exit")
        return 0;

    // inits boards by default
    Board DefaultBoard;

    // access piece test : works
    // std::cout << DefaultBoard.m_board[0][0]->getName();

    // game loop
    while (!(GetKeyState(VK_ESCAPE) & 0x8000))
    {
        DefaultBoard.PrintBoard();
        // DefaultBoard->Draw();
        if (curSide == Piece::white)
            std::cout << "It is white's turn.\n";
        else
            std::cout << "It is black's turn.\n";
        std::cout << "Enter the location of the piece you would like to move:" << std::endl;
        std::cin >> pieceToMove;
        std::cout << pieceToMove << std::endl;
        //std::cout << DefaultBoard.m_board[pieceToMove.xPos][pieceToMove.yPos]->getName();
        //if (DefaultBoard->PieceExists())

        std::cout << "Enter the location you would like to move it to:" << std::endl;
        std::cin >> locationToMoveTo;
        std::cout << locationToMoveTo << std::endl;

        if (DefaultBoard.getPieceSide(pieceToMove) != curSide || DefaultBoard.MovePiece(pieceToMove, locationToMoveTo))
            // failure
            std::cout << "Invalid move.\n";
        else
            // next turn
            curSide = (curSide == Piece::white) ? Piece::black : Piece::white;
        // DefaultBoard->ValidateMove(<coords or chars?>);
    }

}
