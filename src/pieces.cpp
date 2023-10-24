#include "pieces.h"

// note:
// board checks (empty space, taking a piece etc.) will be made within the board class (TO DO)
// other checks are included here for extra error catching
pos::pos()
	: xPos(0), yPos(0)
{
}

pos::pos(unsigned char x, unsigned char y)
	: xPos(x), yPos(y)
{
}

void pos::setCoords(std::string coords)
{
	if (coords.length() == COORD_LEN && CHAR_ONE <= coords[0] && coords[0] <= CHAR_EIGHT && CHAR_A <= coords[1] && coords[1] <= CHAR_H)
		xPos = coords[0], yPos = coords[1];
}

void pos::operator+=(const pos& delta) 
{
	xPos += delta.xPos;
	yPos += delta.yPos;
}


pos Piece::getCoords() const
{
	return m_coords;
}

side Piece::getSide()
{
	return m_color;
}

void Piece::Move(pos coordsDelta)
{
	m_coords += coordsDelta;

	// move pointer on board (do it here or in board class?)
	// TO DO
}

Piece::Piece(side team, pos startingPos)
	: m_coords(startingPos), m_color(team)
{
}

Piece::Piece()
	: m_coords(pos(0,0)), m_color(white)
{};


void Pawn::MoveForward(unsigned char deltaX)
{
	switch (deltaX)
	{
	case 2:
		if (unmoved)
			Move(pos(0, 2));
		// TO DO else throw error
		break;
	case 1:
		Move(pos(0, 1));
		break;
	default:
		// TO DO throw warning
		break;
	}
}

void Pawn::MoveDiagonal(pawnDir direction, bool enPassant)
{
	// remove piece : TO DO

	if (enPassant)
	{
		//	remove (free) piece at loc - color
	}
	else
	{
		//	remove (free) piece at loc
		Move(pos((unsigned char)(direction * getSide()), getSide()));
	}
}

/* TO DO: implement piece specific move functions
class Knight : public Piece
{

};

class Bishop : public Piece
{

};

class Rook : public Piece
{

};

class Queen : public Piece
{

};

class King : public Piece
{

};
*/