#pragma once

#include <QWidget>

class Piece : public QWidget
{
	Q_OBJECT
public:
	enum class Side : char
	{
		Dark = -1,
		Light = 1,

		Empty = 0,
		Wall = 2,
	};

	explicit Piece(Side side, QWidget *parent = 0);

	Side side() { return mSide;}
	void setSide(Side side);

	static Side nextSide(Side side);

signals:

public slots:

protected:
	void paintEvent(QPaintEvent *);

private:
	Side mSide = Side::Dark;
};
