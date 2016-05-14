#pragma once

class Point
{
public:
	Point(int row, int column)
		: mRow(row), mColumn(column)
	{ }

	int row() const { return mRow; }
	int column() const { return mColumn; }

private:
	int mRow;
	int mColumn;
};
