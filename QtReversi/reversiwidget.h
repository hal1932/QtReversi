#pragma once

#include <QWidget>
#include <QLabel>
#include <array>
#include "Cell.h"
#include "Board.h"

class ReversiWidget : public QWidget
{
	Q_OBJECT

public:
	ReversiWidget(QWidget *parent = 0);
	~ReversiWidget();

	void initialize();
	void finalize();

private slots:
	void cellClicked(Cell* cell);

private:
	std::array<std::array<Cell*, 8>, 8> mCells;
	Board mBoard;
	Piece::Side mCurrentSide = Piece::Side::Dark;
	QLabel* mResultLabel = nullptr;

private:
	void updateCells_(const Board& board);
	void showResult_(Piece::Side winner);

};
