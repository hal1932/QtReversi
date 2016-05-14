#pragma once

#include <QWidget>
#include <QVector>
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
	Cell* mCells[8][8];
	Piece::Side mCurrentSide = Piece::Side::Dark;
};
