#include "board.h"
#include "pieces.h"
#include <iostream>

// initializes a white and opposing black piece at the chosen offset (x coordinate)
template <typename pieceType>
void Board::m_InitPiece(char x, char y)
{
	m_board[x][y] = new pieceType(Piece::white, pos(x, y));
	m_board[x][ROWS_COLS - 1 - y] = new pieceType(Piece::black, pos(x, ROWS_COLS - 1 - y));
}


// does NOT check if the piece can move that way (this is done by piece)
// checks if the dest pos is empty or has an enemy piece
// and that the destination coordinates are within bounds
bool Board::m_IsValidMove(const Piece& mover, const pos dest) const
{
	return	dest.xPos < ROWS_COLS && dest.xPos >= 0 &&
			dest.yPos < ROWS_COLS && dest.yPos >= 0 &&
			(m_board[dest.xPos][dest.yPos] == nullptr || m_board[dest.xPos][dest.yPos]->getSide() != mover.getSide());
}

// deletes all pieces on the board
void Board::m_DeleteBoard()
{
	// free memory of pieces
	for (char x = 0; x < ROWS_COLS; x++)
		for (char y = 0; y < ROWS_COLS; y++)
		{
			delete m_board[x][y];
			m_board[x][y] = nullptr;
		}
}

// initializes a new board, including the pieces by default
Board::Board(bool initBoard)
	: m_board{nullptr}, m_boardInitialized(false)
{
	if (initBoard)
		ResetBoard(false);
}

void Board::ResetBoard(const bool clearBoard)
{
	if (clearBoard)
		m_DeleteBoard();

	// initialize pieces based on offset order
	char x_off = 0;

	m_InitPiece<Rook>(x_off);
	m_InitPiece<Rook>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Knight>(++x_off);
	m_InitPiece<Knight>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Bishop>(++x_off);
	m_InitPiece<Bishop>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Queen>(++x_off);
	m_InitPiece<King>(++x_off);

	for (x_off = 0; x_off < ROWS_COLS; x_off++)
		m_InitPiece<Pawn>(x_off, 1);

	// board is now initialized
	m_boardInitialized = true;
}

void Board::PrintBoard()
{
	// loops through each piece and print a character accordingly
	for (char y = 0; y < ROWS_COLS; y++)
	{
		std::cout << "\n________________________\n";

		for (char x = 0; x < ROWS_COLS; x++)
		{
			Piece* curPiece = m_board[x][y];

			// check if there is really a piece here (nullptr or not)
			if (curPiece != nullptr)
				std::cout << '|' << curPiece->getName() << '|';
			else
				std::cout << "| |";
		}
	}

	std::cout << "\n________________________" << std::endl;
}


// returns 0 on success, -1 on failure; checks if move is valid in terms of the board, not piece and then moves it
char Board::MovePiece(const pos from, const pos to)
{
	Piece*& fromPiece = m_board[from.xPos][from.yPos];
	Piece*& toPiece = m_board[to.xPos][to.yPos];
	if (fromPiece != nullptr && m_IsValidMove(*fromPiece, to) && fromPiece->canMoveTo(to))
	{
		if (toPiece != nullptr)
			delete toPiece;
		toPiece = fromPiece;
		fromPiece = nullptr;

		return 0;
	}
	
	return -1;
}


// free/reset memory and vars
Board::~Board()
{
	m_DeleteBoard();
	m_boardInitialized = false;
}