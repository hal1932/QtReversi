#pragma once
#include <array>
#include <vector>
#include "Piece.h"
#include "Point.h"

class Board
{
public:
	enum class Direction : unsigned int
	{
		None = 0,
		Upper = 1,
		UpperLeft = 2,
		Left = 4,
		LowerLeft = 8,
		Lower = 16,
		LowerRight = 32,
		Right = 64,
		UpperRight = 128,
	};

	Board();
	~Board();

	void initialize();

	int rows() const { return mCells.size(); }
	int columns() const { return mCells[0].size(); }

	Piece::Side piece(int row, int column) const { return mCells[row][column]; }
	bool placePiece(Piece::Side piece, int row, int column);

	bool canPlacePiece(Piece::Side piece, int row, int column);
	Piece::Side switchSide(Piece::Side side);

	Direction findFlipDirection(Piece::Side piece, int row, int column);
	void flip(Piece::Side piece, int row, int column, Direction dir);
	int countPieces(Piece::Side piece);
	const std::vector<Point> findOptions(Piece::Side piece);

private:
	std::array<std::array<Piece::Side, 8 + 2>, 8 + 2> mCells;

private:
	bool haveOptions_(Piece::Side side);
};

