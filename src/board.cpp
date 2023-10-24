#include "board.h"
#include <iostream>

// initialize Rook -> Knight -> Bishop -> Queen -> King to maintain correct offset
template <typename cavalryType>
void Board::m_InitCavalry()
{
	m_board[offset] = new cavalryType(white, pos(offset, 0));
	m_board[ROWS_COLS - 1 - offset] = new cavalryType(white, pos(ROWS_COLS - 1 - offset, 0));
	m_board[GRID_SIZE - 1 - offset] = new cavalryType(black, pos(ROWS_COLS - 1 - offset, ROWS_COLS - 1));
	m_board[GRID_SIZE - ROWS_COLS + offset] = new cavalryType(black, pos(offset, ROWS_COLS - 1));

	offset++;
}

template <typename royaltyType>
void Board::m_InitRoyalty()
{
	m_board[offset] = new royaltyType(white, pos(offset, 0));
	m_board[GRID_SIZE - (ROWS_COLS - offset)] = new royaltyType(black, pos(offset, ROWS_COLS - 1));

	offset++;
}

void Board::m_InitPawns()
{
	side color = white;
	char row = 0;

	for (char flip = 0; flip < 2; flip++, color = black, row = ROWS_COLS - 1)
		for (char i = 0; i < ROWS_COLS; i++)
			m_board[i] = new Pawn(color, pos(i, row));
}

void Board::m_DeleteBoard()
{
	// free memory of pieces
	for (char i = 0; i < GRID_SIZE; i++)
		delete m_board[i], m_board[i] = nullptr;
}

Board::Board(bool initBoard = true)
	: m_board{nullptr}, m_boardInitialized(false), offset(0)
{
	if (initBoard)
		ResetBoard();
}

void Board::ResetBoard()
{
	// initialize pieces based on offset order
	m_InitCavalry<Rook>();
	m_InitCavalry<Knight>();
	m_InitCavalry<Bishop>();

	m_InitRoyalty<Queen>();
	m_InitRoyalty<King>();

	m_InitPawns();

	// board is now initialized
	m_boardInitialized = true;
}

void Board::PrintBoard()
{
	// TO DO: loop through each piece and print a character accordingly
	for (char i = 0; i < ROWS_COLS; i++)
	{
		for (char j = 0; j < ROWS_COLS; j++)
		{
			Piece* curPiece = m_board[i * ROWS_COLS + j];
			// check if there is really a piece here (nullptr or not)
			if (curPiece != nullptr)
				// print character depending on what type of piece it is
				std::cout << '|P|'; // placeholder
			else
				std::cout << '| |';
		}

		std::cout << std::endl << "________________________" << std::endl;
	}
}

// free/reset memory and vars
Board::~Board()
{
	m_DeleteBoard();
	m_boardInitialized = false;
	offset = 0;
}