#include "ReversiWidget.h"

#include <QGridLayout>
#include <QDebug>

ReversiWidget::ReversiWidget(QWidget *parent)
	: QWidget(parent)
{
	setAutoFillBackground(true);
	setPalette(Qt::blue);
	resize(500, 500);

	auto* gridLayout = new QGridLayout();
	gridLayout->setSpacing(0);

	for (auto row = 0; row < mCells.size(); ++row)
	{
		for (auto column = 0; column < mCells[row].size(); ++column)
		{
			auto* cell = new Cell(row, column);
			connect(cell, SIGNAL(clicked(Cell*)),
					this, SLOT(cellClicked(Cell*)));
			gridLayout->addWidget(cell, row, column);
			mCells[row][column] = cell;
		}
	}

	setLayout(gridLayout);

	mCells[3][3]->setPiece(new Piece(Piece::Side::Light));
	mCells[4][4]->setPiece(new Piece(Piece::Side::Light));

	mCells[4][3]->setPiece(new Piece(Piece::Side::Dark));
	mCells[3][4]->setPiece(new Piece(Piece::Side::Dark));
}

ReversiWidget::~ReversiWidget()
{
	// ツリー破棄時にQtが勝手に破棄してるから子供のdeleteはしない
	// 破棄時にはdestroyedシグナルがくる
	// すぐに破棄してほしくないときはdeleteLater()を呼んでおくとイベントループを抜けるまで遅延してくれる
}

void ReversiWidget::cellClicked(Cell* cell)
{
	auto* piece = cell->piece();
	if (piece == nullptr)
	{
		cell->setPiece(new Piece(mCurrentSide));
		mCurrentSide = Piece::nextSide(mCurrentSide);
	}
}
