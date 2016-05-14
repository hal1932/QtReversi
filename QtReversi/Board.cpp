#include "Board.h"

Board::Board() { }
Board::~Board(){ }

void Board::initialize()
{
	for (auto& row : mCells)
	{
		for (auto& cell : row)
		{
			cell = Piece::Side::Empty;
		}
	}

	for (auto& cell : mCells[0])
	{
		cell = Piece::Side::Wall;
	}
	for (auto& cell : mCells[mCells.size() - 1])
	{
		cell = Piece::Side::Wall;
	}
	for (auto& row : mCells)
	{
		row[0] = Piece::Side::Wall;
		row[mCells.size() - 1] = Piece::Side::Wall;
	}

	mCells[4][4] = Piece::Side::Light;
	mCells[5][5] = Piece::Side::Light;
	mCells[5][4] = Piece::Side::Dark;
	mCells[4][5] = Piece::Side::Dark;
}

bool Board::placePiece(Piece::Side piece, int row, int column)
{
	const auto dir = findFlipDirection(piece, row, column);
	if (dir != Board::Direction::None)
	{
		mCells[row][column] = piece;
		flip(piece, row, column, dir);
		return true;
	}
	return false;
}

bool Board::canPlacePiece(Piece::Side piece, int row, int column)
{
	return (findFlipDirection(piece, row, column) != Direction::None);
}

Piece::Side Board::switchSide(Piece::Side side)
{
	if (side != Piece::Side::Empty && haveOptions_(side))
	{
		return Piece::nextSide(side);
	}
	return Piece::Side::Empty;
}

Board::Direction Board::findFlipDirection(Piece::Side piece, int row, int column)
{
	if (mCells[row][column] != Piece::Side::Empty)
	{
		return Direction::None;
	}

	auto dir = (unsigned int)Direction::None;

	const auto other = Piece::nextSide(piece);

	if (mCells[row - 1][column] == other)
	{
		auto r = row - 2;
		while (mCells[r][column] == other) --r;
		if (mCells[r][column] == piece) dir |= (unsigned int)Direction::Upper;
	}
	if (mCells[row + 1][column] == other)
	{
		auto r = row + 2;
		while (mCells[r][column] == other) ++r;
		if (mCells[r][column] == piece) dir |= (unsigned int)Direction::Lower;
	}
	if (mCells[row][column - 1] == other)
	{
		auto c = column - 2;
		while (mCells[row][c] == other) --c;
		if (mCells[row][c] == piece) dir |= (unsigned int)Direction::Left;
	}
	if (mCells[row][column + 1] == other)
	{
		auto c = column + 2;
		while (mCells[row][c] == other) ++c;
		if (mCells[row][c] == piece) dir |= (unsigned int)Direction::Right;
	}
	if (mCells[row - 1][column - 1] == other)
	{
		auto r = row - 2;
		auto c = column - 2;
		while (mCells[r][c] == other) --r, --c;
		if (mCells[r][c] == piece) dir |= (uint)Direction::UpperLeft;
	}
	if (mCells[row - 1][column + 1] == other)
	{
		auto r = row - 2;
		auto c = column + 2;
		while (mCells[r][c] == other) --r, ++c;
		if (mCells[r][c] == piece) dir |= (uint)Direction::UpperRight;
	}
	if (mCells[row + 1][column - 1] == other)
	{
		auto r = row + 2;
		auto c = column - 2;
		while (mCells[r][c] == other) ++r, --c;
		if (mCells[r][c] == piece) dir |= (uint)Direction::LowerLeft;
	}
	if (mCells[row + 1][column + 1] == other)
	{
		auto r = row + 2;
		auto c = column + 2;
		while (mCells[r][c] == other) ++r, ++c;
		if (mCells[r][c] == piece) dir |= (uint)Direction::LowerRight;
	}

	return (Direction)dir;
}

void Board::flip(Piece::Side piece, int row, int column, Direction dir)
{
	const auto d = (uint)dir;
	const auto none = (uint)Direction::None;
	const auto other = Piece::nextSide(piece);

	if ((d & (uint)Direction::Upper) != none)
	{
		auto r = row - 1;
		while (mCells[r][column] == other) mCells[r][column] = piece, --r;
	}
	if ((d & (uint)Direction::Lower) != none)
	{
		auto r = row + 1;
		while (mCells[r][column] == other) mCells[r][column] = piece, ++r;
	}
	if ((d & (uint)Direction::Left) != none)
	{
		auto c = column - 1;
		while (mCells[row][c] == other) mCells[row][c] = piece, --c;
	}
	if ((d & (uint)Direction::Right) != none)
	{
		auto c = column + 1;
		while (mCells[row][c] == other) mCells[row][c] = piece, ++c;
	}
	if ((d & (uint)Direction::UpperLeft) != none)
	{
		auto r = row - 1;
		auto c = column - 1;
		while (mCells[r][c] == other) mCells[r][c] = piece, --r, --c;
	}
	if ((d & (uint)Direction::UpperRight) != none)
	{
		auto r = row - 1;
		auto c = column + 1;
		while (mCells[r][c] == other) mCells[r][c] = piece, --r, ++c;
	}
	if ((d & (uint)Direction::LowerLeft) != none)
	{
		auto r = row + 1;
		auto c = column - 1;
		while (mCells[r][c] == other) mCells[r][c] = piece, ++r, --c;
	}
	if ((d & (uint)Direction::LowerRight) != none)
	{
		auto r = row + 1;
		auto c = column + 1;
		while (mCells[r][c] == other) mCells[r][c] = piece, ++r, ++c;
	}
}

int Board::countPieces(Piece::Side piece)
{
	auto count = 0;
	for (auto r = 1; r < mCells.size() - 1; ++r)
	{
		for (auto c = 1; c < mCells[r].size() - 1; ++c)
		{
			if (mCells[r][c] == piece) ++count;
		}
	}
	return count;
}

const std::vector<Point> Board::findOptions(Piece::Side piece)
{
	std::vector<Point> options;
	for (auto r = 1; r < mCells.size() - 1; ++r)
	{
		for (auto c = 1; c < mCells[r].size() - 1; ++c)
		{
			if (canPlacePiece(piece, r, c))
			{
				options.push_back(std::move(Point(r, c)));
			}
		}
	}
	return std::move(options);
}

bool Board::haveOptions_(Piece::Side piece)
{
	std::vector<Point> options;
	for (auto r = 1; r < mCells.size() - 1; ++r)
	{
		for (auto c = 1; c < mCells[r].size() - 1; ++c)
		{
			if (canPlacePiece(piece, r, c))
			{
				return true;
			}
		}
	}
	return false;
}
