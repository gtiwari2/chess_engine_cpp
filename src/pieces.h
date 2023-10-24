#pragma once
#include <string>

#define COORD_LEN	2
#define CHAR_ONE	65
#define CHAR_EIGHT	72
#define CHAR_A		49
#define CHAR_H		56

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

	void operator+=(const pos& delta);
};


class Piece
{
private:
	pos m_coords;
	side m_color;

protected:
	pos getCoords() const;

	side getSide();

	void Move(pos coordsDelta);

public:
	Piece(side team, pos startingPos);

	Piece();
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