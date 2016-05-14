#pragma once

#include <QWidget>
#include <QVector>
#include <array>
#include "Cell.h"

class ReversiWidget : public QWidget
{
	Q_OBJECT

public:
	ReversiWidget(QWidget *parent = 0);
	~ReversiWidget();

private slots:
	void cellClicked(Cell* cell);

private:
	std::array<std::array<Cell*, 8>, 8> mCells;
	Piece::Side mCurrentSide = Piece::Side::Dark;
};
