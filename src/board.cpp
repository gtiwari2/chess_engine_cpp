#include "board.h"
#include "pieces.h"
#include <iostream>

// initialize Rook -> Knight -> Bishop -> Queen -> King to maintain correct offset

// initializes Rooks/Knights/Bishops based on template type
template <typename cavalryType>
void Board::m_InitCavalry()
{
	m_board[offset] = new cavalryType(white, pos(offset, 0));
	m_board[ROWS_COLS - 1 - offset] = new cavalryType(white, pos(ROWS_COLS - 1 - offset, 0));
	m_board[GRID_SIZE - 1 - offset] = new cavalryType(black, pos(ROWS_COLS - 1 - offset, ROWS_COLS - 1));
	m_board[GRID_SIZE - ROWS_COLS + offset] = new cavalryType(black, pos(offset, ROWS_COLS - 1));

	offset++;
}

// initializes Queens and Kings based on template type
template <typename royaltyType>
void Board::m_InitRoyalty()
{
	m_board[offset] = new royaltyType(white, pos(offset, 0));
	m_board[GRID_SIZE - (ROWS_COLS - offset)] = new royaltyType(black, pos(offset, ROWS_COLS - 1));

	offset++;
}


// initializes Pawns
void Board::m_InitPawns()
{
	side color = white;
	char row = 0;

	for (char flip = 0; flip < 2; flip++, color = black, row = ROWS_COLS - 1)
		for (char i = 0; i < ROWS_COLS; i++)
			m_board[i] = new Pawn(color, pos(i, row));
}


// does NOT check if the piece can move that way (this is done by piece)
// only checks if the dest pos is empty or has an enemy piece
bool Board::m_IsValidMove(Piece& mover, pos dest)
{
	return (m_board[GRID_POS(dest)] == nullptr || m_board[GRID_POS(dest)]->getSide() != mover.getSide());
}

// deletes all pieces on the board
void Board::m_DeleteBoard()
{
	// free memory of pieces
	for (char i = 0; i < GRID_SIZE; i++)
		delete m_board[i], m_board[i] = nullptr;
}

// initializes a new board, including the pieces by default
Board::Board(bool initBoard = true)
	: m_board{nullptr}, m_boardInitialized(false), offset(0)
{
	if (initBoard)
		ResetBoard();
}

void Board::ResetBoard(bool clearBoard)
{
	if (clearBoard)
		m_DeleteBoard();

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


// returns 0 on success, -1 on failure
char Board::MovePiece(pos from, pos to)
{
	if (m_board[GRID_POS(from)] != nullptr && m_IsValidMove(*m_board[GRID_POS(from)], to))
		m_board[GRID_POS(to)] = m_board[GRID_POS(from)], m_board[GRID_POS(from)] = nullptr;
	else
		return -1;
	
	return 0;
}


// free/reset memory and vars
Board::~Board()
{
	m_DeleteBoard();
	m_boardInitialized = false;
	offset = 0;
}