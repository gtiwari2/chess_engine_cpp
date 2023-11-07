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

	bool m_IsValidMove(const Piece& mover, const pos dest) const;

public:
	char offset;

	Board(bool initBoard);

	void ResetBoard(const bool clearBoard = false);

	void PrintBoard();

	char MovePiece(const pos from, const pos to);

	~Board();
};