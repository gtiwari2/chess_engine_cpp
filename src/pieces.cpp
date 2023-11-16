#include "pieces.h"
#include "board.h"
#include "utils.h"
#include <iostream>

// note:
// board checks (empty space, taking a piece etc.) will be made within the board class (TO DO)
// other checks are included here for extra error catching
pos::pos()
	: xPos(0), yPos(0)
{
}

pos::pos(signed char x, signed char y)
	: xPos(x), yPos(y)
{
}

pos pos::operator-(const pos& delta)
{
	return pos(xPos - delta.xPos, yPos - delta.yPos);
}

pos pos::operator+(const pos& delta)
{
	return pos(xPos + delta.xPos, yPos + delta.yPos);
}

void pos::operator+=(const pos& delta) 
{
	xPos += delta.xPos;
	yPos += delta.yPos;
}

std::ostream& operator<<(std::ostream& stream, const pos& position)
{
	stream << position.xPos << ", " << position.yPos;
	return stream;
}

std::ostream& operator>>(std::ostream& stream, const pos&)
{
	// TODO: insert return statement here
	return stream;
}

	
pos Piece::getCoords() const
{
	return m_coords;
}

Piece::side Piece::getSide() const
{
	return m_color;
}

char pos::setCoords(std::string coords)
{
	if (coords.length() == COORD_LEN && 
		CHAR_ONE <= coords[0] && coords[0] <= CHAR_EIGHT && 
		CHAR_A <= coords[1] && coords[1] <= CHAR_H)
	{
		xPos = coords[0] - (CHAR_ONE - 1), yPos = coords[1] - (CHAR_A - 1);
		return 0;
	}

	return -1;
}

// calls board move function, does not check if move is valid for a piece
char Piece::Move(Board& curBoard, const pos dest)
{
	if (curBoard.MovePiece(getCoords(), dest) == 0)
	{
		m_coords = dest;

		// if Pawn, set unmoved = false;
		if (getName() == 'P')
			moved();

		return 0;
	}

	return -1;
}

Piece::Piece(Piece::side team, pos startingPos)
	: m_coords(startingPos), m_color(team)
{
}

void Piece::moved()
{
	return;
}

// TO DO: implement piece specific canMove functions

// Pawn functions
char Pawn::getName() const
{
	return 'P';
}

bool Pawn::canMoveTo(pos to)
{
	pos curPos{ getCoords() };
	side pieceCol{ getSide() };

	// moving in the wrong direction
	if (pieceCol == white && curPos.yPos >= to.yPos || pieceCol == black && curPos.yPos <= to.yPos)
		return false;

	// case: moving forward
	if (curPos.xPos == to.xPos)
	{
		unsigned char yDiff{ (unsigned char) abs(curPos.yPos - to.yPos) };

		// correct direction but too far or not at all
		return (yDiff > 0 && (unmoved && yDiff < 3 || !unmoved && yDiff == 1));
	}
	// case: moving diagonally to take a piece
	// board isValidMove function checks that if moving diagonally, the Pawn is moving to an enemy piece loc
	else
		return (abs(curPos.xPos - to.xPos) == 1 && abs(curPos.yPos - to.yPos) == 1);
}

void Pawn::moved()
{
	unmoved = false;
}

// Knight functions

char Knight::getName() const
{
	return 'N';
}

bool Knight::canMoveTo(pos to)
{
	pos curPos{ getCoords() };

	// must move in L shape (1 in x dir and 2 in y or vice versa)
	return (abs(curPos.xPos - to.xPos) == 1 && abs(curPos.yPos - to.yPos) == 2 || abs(curPos.yPos - to.yPos) == 1 && abs(curPos.xPos - to.xPos) == 2);
}

// Bishop functions
char Bishop::getName() const
{
	return 'B';
}

bool Bishop::canMoveTo(pos to)
{
	pos curPos{ getCoords() };

	// must move in a diagonal
	return (abs(curPos.xPos - to.xPos) == abs(curPos.yPos - to.yPos) && abs(curPos.xPos - to.yPos) > 0);
}

// Rook functions
char Rook::getName() const
{
	return 'R';
}

bool Rook::canMoveTo(pos to)
{
	pos curPos { getCoords() };

	// must move in either x or y direction but not both
	return (curPos.xPos == to.xPos && curPos.yPos != to.yPos || curPos.yPos == to.yPos && curPos.xPos != to.xPos);
}

// King functions
char King::getName() const
{
	return 'K';
}

bool King::canMoveTo(pos to)
{
	pos curPos{ getCoords() };
	unsigned char moveDiff{ (unsigned char) (abs(curPos.xPos - to.xPos) + abs(curPos.yPos - to.yPos)) };

	// can move one space in any direction, including diagonals (restricted to 1 in x and y direction)
	return (moveDiff > 0 && moveDiff < 3);
}

// Queen functions
char Queen::getName() const
{
	return 'Q';
}

bool Queen::canMoveTo(pos to)
{
	pos curPos{ getCoords() };

	// can move in either column, rank, or diagonal (girlboss)
	return	(curPos.xPos == to.xPos && curPos.yPos != to.yPos || curPos.yPos == to.yPos && curPos.xPos != to.xPos) ||
			(abs(curPos.xPos - to.xPos) == abs(curPos.yPos - to.yPos) && abs(curPos.xPos - to.yPos) > 0);
}