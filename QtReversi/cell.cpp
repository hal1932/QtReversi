#include "cell.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

Cell::Cell(int row, int column, QWidget *parent)
    : QWidget(parent),
      m_row(row),
      m_column(column)
{
    setAutoFillBackground(true);
    setPalette(Qt::green);

    m_layout = new QHBoxLayout();
    m_layout->setMargin(2);
    setLayout(m_layout);
}

void Cell::setPiece(Piece *piece)
{
    if (m_piece != nullptr)
    {
        m_layout->removeWidget(m_piece);
    }
    m_layout->addWidget(piece);

    m_piece = piece;
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawRect(rect());
}

void Cell::mousePressEvent(QMouseEvent *)
{
}

void Cell::mouseReleaseEvent(QMouseEvent* event)
{
    if (!rect().contains(event->pos()))
        return;

    emit clicked(m_row, m_column);
}
