#include "pieces.h"
#include "board.h"

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


pos Piece::getCoords() const
{
	return m_coords;
}

side Piece::getSide() const
{
	return m_color;
}

void Piece::Move(pos dest)
{
	m_coords = dest;
}

Piece::Piece(side team, pos startingPos)
	: m_coords(startingPos), m_color(team)
{
}


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


// returns 0 on success, -1 on failure
char Knight::Move(Board &curBoard, knightDir dir)
{
	pos to;

	switch (dir)
	{
	case downLeft:
		to = (getCoords() - pos(1, 2));
		break;
	case leftDown:
		to = (getCoords() - pos(2, 1));
		break;
	case leftUp:
		to = (getCoords() - pos(2, 0) + pos(0, 1));
		break;
	case upLeft:
		to = (getCoords() + pos(0, 2) - pos(1, 0));
		break;
	case upRight:
		to = (getCoords() + pos(2, 1));
		break;
	case rightUp:
		to = (getCoords() + pos(1, 2));
		break;
	case rightDown:
		to = (getCoords() + pos(2, 0) - pos(0, 1));
		break;
	case downRight:
		to = (getCoords() - pos(0, 2) + pos(1, 0));
		break;
	default:
		break;
	}

	if (curBoard.MovePiece(getCoords(), to) == 0)
		Piece::Move(to);
	else
		return -1;

	return 0;

}

/* TO DO: implement piece specific move functions

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