#ifndef CELL_H
#define CELL_H

#include "piece.h"
#include <QWidget>
#include <QBoxLayout>

class Cell : public QWidget
{
    Q_OBJECT // ・ｽ・ｽ・ｽ^・ｽ・ｽ・ｽﾌ趣ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽw・ｽ・ｽ・ｽ・ｽ・ｽ・ｽA・ｽﾈゑｿｽ・ｽﾆシ・ｽO・ｽi・ｽ・ｽ・ｽE・ｽX・ｽ・ｽ・ｽb・ｽg・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾈゑｿｽ
public:
    explicit Cell(int row, int column, QWidget *parent = 0);

    Piece* piece() { return m_piece; }
    void setPiece(Piece* piece);

signals:
    // signal・ｽﾌ趣ｿｽ・ｽ・ｽ・ｽ・ｽQt・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ驍ｩ・ｽ・ｽ骭ｾ・ｽ・ｽ・ｽ・ｽ・ｽﾉゑｿｽ・ｽﾄゑｿｽ・ｽ・ｽ
    void clicked(int row, int column);

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    int m_row = -1;
    int m_column = -1;
    Piece* m_piece = nullptr;
    QHBoxLayout* m_layout = nullptr;
};

#endif // CELL_H
