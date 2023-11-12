#pragma once
#include <string>

#define COORD_LEN	2
#define CHAR_ONE	65
#define CHAR_EIGHT	72
#define CHAR_A		49
#define CHAR_H		56
#define WHITE_END	8
#define BLACK_END	1

#define GRID_POS(position) (position.xPos * ROWS_COLS + position.yPos)

class Board;

struct pos {
	// how to enforce final position range?
	// (1 through 8)
	signed char xPos; // A (1) through H (8)
	signed char yPos; // 1 through 8

	pos();

	pos(signed char, signed char);

	char setCoords(std::string coords);

	pos operator-(const pos& delta);

	pos operator+(const pos& delta);

	void operator+=(const pos& delta);

	friend std::ostream& operator<<(std::ostream& stream, const pos&);
	friend std::ostream& operator>>(std::ostream& stream, const pos&);
};


class Piece
{
public:
	enum side : signed char
	{
		black = -1, white = 1
	};

	virtual char getName() = 0;

	virtual bool canMoveTo(pos to) = 0;

private:
	pos m_coords;
	side m_color;

protected:
	char Move(Board& curBoard, const pos dest);

public:
	Piece(side team, pos startingPos);

	pos getCoords() const;

	side getSide() const;
};

class Pawn : public Piece // private vs protected vs public inheritance??? TO DO
{
private:
	bool unmoved {true};

	enum pawnDir : signed char
	{
		left = -1, right = 1
	};

public:
	char MoveForward(Board& curBoard, unsigned char deltaX);

	// take piece
	char MoveDiagonal(Board& curBoard, pawnDir direction, bool enPassant);

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};

// TO DO: declare piece-specific move functions
class Knight : public Piece
{
	enum knightDir : signed char
	{
		downLeft, leftDown, leftUp, upLeft, upRight, rightUp, rightDown, downRight
	};

public:

	char Move(Board &curBoard, knightDir dir);

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};

class Bishop : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};

class Rook : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};

class Queen : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};

class King : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() override;

	virtual bool canMoveTo(pos to) override;
};