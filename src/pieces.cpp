#include "pieces.h"
#include "board.h"
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
		return 0;
	}

	return -1;
}

Piece::Piece(Piece::side team, pos startingPos)
	: m_coords(startingPos), m_color(team)
{
}

// TO DO: implement piece specific move functions

// Pawn functions
char Pawn::MoveForward(Board& curBoard, unsigned char deltaX)
{
	// make sure pawn has not reached the end already
	bool validMove = (getSide() == Piece::side::white) ? getCoords().yPos < WHITE_END : getCoords().yPos > BLACK_END;

	if (!validMove)
		return -1;

	// if white moves forward -> y pos increases
	// if black moves forward -> y pos decreases
	// move 1 or 2 spaces forward
	switch (deltaX)
	{
	case 2:
		if (unmoved)
		{
			unmoved = false;
			return Move(curBoard, getCoords() + pos(0, 2 * getSide()));
		}
		else
		{
			std::cout << "Invalid move; pawns can only take two spaces if unmoved" << std::endl;
			return -1;
		}
	case 1:
		unmoved = false;
		// TO DO : check for promotion
		// if ((getSide() == Piece::side::white) ? getCoords().yPos == WHITE_END - 1 : getCoords().yPos == BLACK_END + 1)
		//	promote pawn:
		//		remove pawn from location (delete at coordinate)
		//		prompt user to select a piece
		//		create new piece of that class at the coordinate
		// else:
		return Move(curBoard, getCoords() + pos(0, 1 * getSide()));
	default:
		return -1;
	}
}

char Pawn::MoveDiagonal(Board& curBoard, pawnDir direction, bool enPassant)
{
	// remove piece : TO DO

	if (enPassant)
	{
		//	remove (free) piece at loc - color
	}
	else
	{
		//	remove (free) piece at loc
		Move(curBoard, getCoords() + pos((direction * getSide()), getSide()));
	}

	return -1;
}

char Pawn::getName()
{
	return 'P';
}

bool Pawn::canMoveTo(pos to)
{
	return true;
}


// Knight functions

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

	return Piece::Move(curBoard, to);

}

char Knight::getName()
{
	return 'N';
}

bool Knight::canMoveTo(pos to)
{
	return true;
}

// Bishop functions
char Bishop::getName()
{
	return 'B';
}

bool Bishop::canMoveTo(pos to)
{
	return true;
}

// Rook functions
char Rook::getName()
{
	return 'R';
}

bool Rook::canMoveTo(pos to)
{
	return true;
}


// King functions
char King::getName()
{
	return 'K';
}

bool King::canMoveTo(pos to)
{
	return true;
}

// Queen functions
char Queen::getName()
{
	return 'Q';
}

bool Queen::canMoveTo(pos to)
{
	return true;
}