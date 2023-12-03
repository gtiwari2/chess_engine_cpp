#pragma once

#define ROWS_COLS 8

class Piece;

struct pos;

class Board
{
private:
	bool m_boardInitialized;

	template <typename pieceType>
	void m_InitPiece(char x, char y = 0);

	void m_DeleteBoard();

	bool m_IsEmptyPath(pos start, pos end) const;

	bool m_IsValidMove(Piece* &mover, const pos dest) const;

public:
	Piece* m_board[ROWS_COLS][ROWS_COLS];

	Board(bool initBoard = true);

	void ResetBoard(const bool clearBoard = false);

	void PrintBoard();

	signed char getPieceSide(const pos) const;

	char MovePiece(const pos from, const pos to);

	~Board();
};