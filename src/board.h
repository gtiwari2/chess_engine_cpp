#pragma once

#define ROWS_COLS 8
#define GRID_SIZE ROWS_COLS*ROWS_COLS

class Piece;

struct pos;

class Board
{
private:
	Piece *m_board[GRID_SIZE];
	bool m_boardInitialized;

	template <typename cavalryType>
	void m_InitCavalry();

	template <typename royaltyType>
	void m_InitRoyalty();

	void m_InitPawns();

	void m_DeleteBoard();

	bool m_IsValidMove(Piece& mover, pos dest);

public:
	char offset;

	Board(bool initBoard);

	void ResetBoard(bool clearBoard = false);

	void PrintBoard();

	char MovePiece(pos from, pos to);

	~Board();
};