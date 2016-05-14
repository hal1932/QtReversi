#include "Piece.h"

#include <QPainter>

Piece::Piece(Side side, QWidget *parent)
	: QWidget(parent),
	  mSide(side)
{ }

void Piece::setSide(Side side)
{
	mSide = side;
	update(); // repaintのリクエストを投げる
}

void Piece::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	switch (mSide)
	{
	case Side::Dark: painter.setBrush(Qt::black); break;
	case Side::Light: painter.setBrush(Qt::white); break;
	}
	painter.setPen(Qt::black);

	painter.drawEllipse(rect().adjusted(1, 1, -1, -1));
}

Piece::Side Piece::nextSide(Side side)
{
	return (Side)((int)side * -1);
}