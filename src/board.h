#pragma once

#include "pieces.h"

#define ROWS_COLS 8
#define GRID_SIZE ROWS_COLS*ROWS_COLS

class Board
{
private:
	Piece* m_board[GRID_SIZE];
	bool m_boardInitialized;

	template <typename cavalryType>
	void m_InitCavalry();

	template <typename royaltyType>
	void m_InitRoyalty();

	void m_InitPawns();

	void m_DeleteBoard();

public:
	char offset;

	Board(bool initBoard);

	void ResetBoard();

	void PrintBoard();

	~Board();
};