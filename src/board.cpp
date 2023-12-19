#include "board.h"
#include <iostream>

// initializes a single piece of the chosen side at the given space
template <typename pieceType>
void Board::m_InitSingularPiece(Piece::side pieceSide, pos pieceLoc)
{
	m_board[pieceLoc.xPos][pieceLoc.yPos] = new pieceType(pieceSide, pieceLoc);
}

// initializes a white and opposing black piece at the chosen offset (x coordinate)
template <typename pieceType>
void Board::m_InitPiece(char x, char y)
{
	m_board[x][y] = new pieceType(Piece::white, pos(x, y));
	m_board[x][ROWS_COLS - 1 - y] = new pieceType(Piece::black, pos(x, ROWS_COLS - 1 - y));
}

/* if the path is valid (in one direction or diagonal) and has no pieces, this function returns true. Returns false otherwise. */
bool Board::m_IsEmptyPath(pos start, pos end) const
{
	pos increment(end - start);

	/* invalid path: path of length 0 or incongruent movement in x and y direction */
	if (start == end || increment.xPos != 0 && increment.yPos != 0 && abs(increment.xPos) != abs(increment.yPos))
		return false;

	increment.normalizeXY();

	do
	{
		start += increment;
		if (start != end && m_board[start.xPos][start.yPos] != nullptr)
			return false;

	} while (start != end);

	return true;
}

// does NOT check if the piece can move that way (this is done by piece)
// checks that the destination coordinates are within bounds
// and if the dest pos is empty or has an enemy piece
// if the Piece is a Pawn, it checks that when it takes a piece there is a piece to take on the board
bool Board::m_IsValidMove(Piece* &mover, const pos dest) const
{
			/* bounds check */
	bool inBounds =
			dest.xPos < ROWS_COLS && dest.xPos >= 0 &&
			dest.yPos < ROWS_COLS && dest.yPos >= 0;

	char pieceName = mover->getName();

			/* check for pieces existing in path (exception for knights) */
	bool notBlocked =
			(mover->getName() == 'N' || m_IsEmptyPath(mover->getCoords(), dest));

			/* Pawn moving forward or non-Pawn pieces check */
	bool destClear =
			((mover->getName() != 'P' || mover->getName() == 'P' && dest.xPos == mover->getCoords().xPos) &&
			m_board[dest.xPos][dest.yPos] == nullptr ||
			mover->getName() != 'P' && m_board[dest.xPos][dest.yPos] != nullptr && m_board[dest.xPos][dest.yPos]->getSide() != mover->getSide());

			/* special Pawn taking piece case: if Pawn, and moving diagonally, then dest must have enemy piece */
	bool pawnTakingValidPiece =
			(mover->getName() == 'P' &&
			dest.xPos != mover->getCoords().xPos &&
			m_board[dest.xPos][dest.yPos] != nullptr && m_board[dest.xPos][dest.yPos]->getSide() != mover->getSide());

	return inBounds && notBlocked && (destClear || pawnTakingValidPiece);
}

// deletes all pieces on the board
void Board::m_DeleteBoard()
{
	// free memory of pieces
	for (char x = 0; x < ROWS_COLS; x++)
		for (char y = 0; y < ROWS_COLS; y++)
		{
			delete m_board[x][y];
			m_board[x][y] = nullptr;
		}
}

// initializes a new board, including the pieces by default
Board::Board(bool initBoard)
	: m_board{nullptr}, m_boardInitialized(false)
{
	if (initBoard)
		ResetBoard(false);
}

void Board::ResetBoard(const bool clearBoard)
{
	if (clearBoard)
		m_DeleteBoard();

	// initialize pieces based on offset order
	char x_off = 0;

	m_InitPiece<Rook>(x_off);
	m_InitPiece<Rook>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Knight>(++x_off);
	m_InitPiece<Knight>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Bishop>(++x_off);
	m_InitPiece<Bishop>(ROWS_COLS - 1 - x_off);

	m_InitPiece<Queen>(++x_off);
	m_InitPiece<King>(++x_off);

	for (x_off = 0; x_off < ROWS_COLS; x_off++)
		m_InitPiece<Pawn>(x_off, 1);

	// set king pieces
	m_BlackKing = m_board[KING_X][ROWS_COLS-1];
	m_WhiteKing = m_board[KING_X][0];

	// board is now initialized
	m_boardInitialized = true;

	std::cout << "Board is initialized";
}

void Board::PrintBoard()
{
	// loops through each piece and print a character accordingly
	for (char y = 0; y < ROWS_COLS; y++)
	{
		std::cout << "\n ________________________\n" << (int) y;

		for (char x = 0; x < ROWS_COLS; x++)
		{
			Piece* curPiece = m_board[x][y];

			// check if there is really a piece here (nullptr or not)
			if (curPiece != nullptr)
				std::cout << '|' << curPiece->getName() << '|';
			else
				std::cout << "| |";
		}
	}

	std::cout << "\n ________________________\n  A  B  C  D  E  F  G  H \n" << std::endl;
}

Piece* Board::getPiece(const pos piecePos) const
{
	return m_board[piecePos.xPos][piecePos.yPos];
}

signed char Board::getPieceSide(const pos piecePos) const
{
	Piece* curPiece = m_board[piecePos.xPos][piecePos.yPos];
	
	return (curPiece == nullptr) ? 0 : curPiece->getSide();
}

// returns 0 on success, -1 on failure; checks if move is valid in terms of the board, not piece and then moves it
char Board::MovePiece(const pos from, const pos to)
{
	/* bounds check */
	if (from.xPos >= ROWS_COLS || from.xPos < 0 ||
		from.yPos >= ROWS_COLS || from.yPos < 0 ||
		to.xPos >= ROWS_COLS || to.xPos < 0 ||
		to.yPos >= ROWS_COLS || to.yPos < 0)
		return  -1;

	Piece* &toPiece = m_board[to.xPos][to.yPos];
	Piece* &fromPiece = m_board[from.xPos][from.yPos];

	if (fromPiece != nullptr &&
		fromPiece->canMoveTo(to) &&
		m_IsValidMove(fromPiece, to))
	{
		if (toPiece != nullptr)
			delete toPiece;
		toPiece = fromPiece;
		fromPiece = nullptr;

		// update piece's coordinates
		toPiece->setCoords(to);

		// pawn reached the end, promote it
		if (toPiece != nullptr && toPiece->getName() == 'P' && (to.yPos == WHITE_END || to.yPos == BLACK_END))
		{
			char promoted;
			do
			{
				promoted = m_PromotePawn(to);
			} while (!promoted);
		}


		return 0;
	}
	
	return -1;
}

Piece::side Board::IsInCheck(Piece *lastMovingPiece) const
{
	Piece *enemyKing = (lastMovingPiece->getSide() == Piece::white) ? m_BlackKing : m_WhiteKing;
	pos enemyKingCoords = enemyKing->getCoords();

	if (lastMovingPiece->canMoveTo(enemyKingCoords) && m_IsValidMove(lastMovingPiece, enemyKingCoords))
		isInCheck = enemyKing->getSide();
	else
		isInCheck = Piece::side::neither;

	return isInCheck;
}


// returns true on success, false on failure (retry)
bool Board::m_PromotePawn(pos pawnLoc)
{
	Piece* &Pawn = m_board[pawnLoc.xPos][pawnLoc.yPos];
	Piece::side pawnSide = Pawn->getSide();
	char newPiece;

	std::cout << "Pawn promotion! Enter a character (K, B, R, or Q) to choose your new piece: ";

	std::cin >> newPiece;

	switch (newPiece)
	{
	case 'K':
		delete Pawn;
		m_InitSingularPiece<Knight>(pawnSide, pawnLoc);
		break;
	case 'B':
		delete Pawn;
		m_InitSingularPiece<Bishop>(pawnSide, pawnLoc);
		break;
	case 'R':
		delete Pawn;
		m_InitSingularPiece<Rook>(pawnSide, pawnLoc);
		break;
	case 'Q':
		delete Pawn;
		m_InitSingularPiece<Queen>(pawnSide, pawnLoc);
		break;
	default:
		return false;
	}

	return true;
}

// free/reset memory and vars
Board::~Board()
{
	m_DeleteBoard();
	m_boardInitialized = false;
}