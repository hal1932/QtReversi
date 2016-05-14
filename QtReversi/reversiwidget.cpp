#include "reversiwidget.h"

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

    m_cells.resize(8);
    for (auto row = 0; row < 8; ++row)
    {
        m_cells[row].resize(8);
        for (auto column = 0; column < 8; ++column)
        {
            auto* cell = new Cell(row, column);
            connect(cell, SIGNAL(clicked(int,int)),
                    this, SLOT(cellClicked(int,int)));
            gridLayout->addWidget(cell, row, column);
            m_cells[row][column] = cell;
        }
    }

    setLayout(gridLayout);

    m_cells[3][3]->setPiece(new Piece(Piece::LightSide));
    m_cells[4][4]->setPiece(new Piece(Piece::LightSide));

    m_cells[4][3]->setPiece(new Piece(Piece::DarkSide));
    m_cells[3][4]->setPiece(new Piece(Piece::DarkSide));
}

ReversiWidget::~ReversiWidget()
{
    // ツリー破棄時にQtが勝手に破棄してるから子供のdeleteはしない
    // 破棄時にはdestroyedシグナルがくる
    // すぐに破棄してほしくないときはdeleteLater()を呼んでおくとイベントループを抜けるまで遅延してくれる
}

void ReversiWidget::cellClicked(int row, int column)
{
    auto piece = m_cells[row][column]->piece();
    if (piece != nullptr)
    {
        piece->reverse();
    }
}

