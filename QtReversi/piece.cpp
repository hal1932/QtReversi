#include "piece.h"

#include <QPainter>

Piece::Piece(Side side, QWidget *parent)
    : QWidget(parent),
      m_side(side)
{

}

void Piece::reverse()
{
    m_side = (Side)((int)m_side * -1);
    update(); // repaintのリクエストを投げる
}

void Piece::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    switch (m_side)
    {
    case DarkSide: painter.setBrush(Qt::black); break;
    case LightSide: painter.setBrush(Qt::white); break;
    }
    painter.setPen(Qt::black);

    painter.drawEllipse(rect().adjusted(1, 1, -1, -1));
}
