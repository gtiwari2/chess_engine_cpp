#pragma once

#define ROWS_COLS 8

class Piece;

struct pos;

class Board
{
private:
	// m_board[x][y]
	Piece *m_board[ROWS_COLS][ROWS_COLS];
	bool m_boardInitialized;

	template <typename pieceType>
	void m_InitPiece(char x, char y = 0);

	void m_DeleteBoard();

	bool m_IsValidMove(const Piece& mover, const pos dest) const;

public:
	Board(bool initBoard = true);

	void ResetBoard(const bool clearBoard = false);

	void PrintBoard();

	char MovePiece(const pos from, const pos to);

	~Board();
};