#include "Cell.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

Cell::Cell(int row, int column, QWidget* parent)
	: QWidget(parent),
	  mRow(row),
	  mColumn(column)
{
	setAutoFillBackground(true);
	setPalette(Qt::green);

	mLayout = new QHBoxLayout();
	mLayout->setMargin(2);
	setLayout(mLayout);
}

void Cell::setPiece(Piece* piece)
{
	if (mPiece != nullptr)
	{
		mLayout->removeWidget(mPiece);
	}
	mLayout->addWidget(piece);

	mPiece = piece;
}

void Cell::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawRect(rect());
}

void Cell::mouseReleaseEvent(QMouseEvent* evt)
{
	if (!rect().contains(evt->pos()))
		return;

	emit clicked(this);
}
