#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include "cell.h"
#include <QWidget>
#include <QVector>

class ReversiWidget : public QWidget
{
    Q_OBJECT

public:
    ReversiWidget(QWidget *parent = 0);
    ~ReversiWidget();

private slots:
    void cellClicked(int row, int column);

private:
    QVector<QVector<Cell*>> m_cells;
};

#endif // REVERSIWIDGET_H
