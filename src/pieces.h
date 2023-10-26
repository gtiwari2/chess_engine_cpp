#pragma once
#include <string>

#define COORD_LEN	2
#define CHAR_ONE	65
#define CHAR_EIGHT	72
#define CHAR_A		49
#define CHAR_H		56

#define GRID_POS(position) (position.xPos * ROWS_COLS + position.yPos)

class Board;

enum side : signed char
{
	white = -1, black = 1
};

struct pos {
	unsigned char xPos; // A (1) through H (8)
	unsigned char yPos; // 1 through 8

	pos();

	pos(unsigned char, unsigned char);

	void setCoords(std::string coords);

	pos operator-(const pos& delta);

	pos operator+(const pos& delta);

	void operator+=(const pos& delta);
};


class Piece
{
private:
	pos m_coords;
	side m_color;

protected:
	void Move(pos dest);

public:
	Piece(side team, pos startingPos);

	pos getCoords() const;

	side getSide() const;
};

class Pawn : public Piece // private vs protected vs public inheritance??? TO DO
{
private:
	bool unmoved = true;

	enum pawnDir : signed char
	{
		left = -1, right = 1
	};

public:
	void MoveForward(unsigned char deltaX);

	// take piece
	void MoveDiagonal(pawnDir direction, bool enPassant);

	using Piece::Piece;
};

// TO DO: declare piece-specific move functions
class Knight : public Piece
{
	enum knightDir : signed char
	{
		downLeft, leftDown, leftUp, upLeft, upRight, rightUp, rightDown, downRight
	};

	char Move(Board &curBoard, knightDir dir);

	using Piece::Piece;
};

class Bishop : public Piece
{
	using Piece::Piece;
};

class Rook : public Piece
{
	using Piece::Piece;
};

class Queen : public Piece
{
	using Piece::Piece;
};

class King : public Piece
{
	using Piece::Piece;
};