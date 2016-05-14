#pragma once

#include <QWidget>
#include <QBoxLayout>
#include "Piece.h"

class Cell : public QWidget
{
	Q_OBJECT // メタ情報の自動生成を指示する、ないとシグナル・スロットが動かない
public:
	explicit Cell(int row, int column, QWidget *parent = 0);

	Piece* piece() { return mPiece; }
	void placePiece(Piece::Side pieceSide);

	int row() { return mRow; }
	int column() { return mColumn; }

signals:
	// signalの実装はQtが自動生成するから宣言だけにしておく
	void clicked(Cell* cell);

public slots:

protected:
	void paintEvent(QPaintEvent* evt);
	void mouseReleaseEvent(QMouseEvent* evt);

private:
	int mRow = -1;
	int mColumn = -1;
	Piece* mPiece = nullptr;
	QHBoxLayout* mLayout = nullptr;
};
