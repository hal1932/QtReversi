#ifndef PIECE_H
#define PIECE_H

#include <QWidget>

class Piece : public QWidget
{
    Q_OBJECT
public:
    enum Side
    {
        DarkSide = -1,
        LightSide = 1,
    };

    explicit Piece(Side side, QWidget *parent = 0);

    Side side() { return m_side;}
    void reverse();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

private:
    Side m_side = DarkSide;
};

#endif // PIECE_H
