#pragma once
#include <string>

#define COORD_LEN	2
#define WHITE_END	8
#define BLACK_END	1
#define CHAR_0		48
#define CHAR_ONE	49
#define CHAR_EIGHT	56
#define CHAR_A		65
#define CHAR_H		104

class Board;

struct pos {
	// how to enforce final position range?
	// (1 through 8)
	int xPos; // A (1) through H (8)
	int yPos; // 1 through 8

	pos();

	pos(int, int);

	void normalizeXY();

	char setCoords(std::string coords);

	pos operator-(const pos& delta);

	pos operator+(const pos& delta);

	const bool operator==(const pos& other);

	const bool operator!=(const pos& other);

	void operator+=(const pos& delta);

	friend std::ostream& operator<<(std::ostream& stream, const pos&);
	friend std::istream& operator>>(std::istream& stream, pos&);
};


class Piece
{
public:
	enum side : signed char
	{
		black = -1, white = 1
	};

	// returns the character that represents the piece
	virtual char getName() const = 0;

	// returns if the target position would be a valid move for the piece without checking the board or bounds
	virtual bool canMoveTo(pos to) = 0;

	// used for Pawn only
	virtual void moved();

private:
	pos m_coords;
	side m_color;

public:
	Piece(side team, pos startingPos);

	char Move(Board& curBoard, pos dest);

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
	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;

	virtual void moved() override;
};

// TO DO: declare piece-specific move functions
class Knight : public Piece
{
public:
	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;
};

class Bishop : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;
};

class Rook : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;
};

class Queen : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;
};

class King : public Piece
{
public:

	using Piece::Piece;

	virtual char getName() const override;

	virtual bool canMoveTo(pos to) override;
};