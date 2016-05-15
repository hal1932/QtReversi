#include "ReversiWidget.h"

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

	for (auto row = 0; row < mCells.size(); ++row)
	{
		for (auto column = 0; column < mCells[row].size(); ++column)
		{
			auto* cell = new Cell(row, column);
			connect(cell, &Cell::clicked, [this](Cell* cell) { onCellClicked_(cell); });
			gridLayout->addWidget(cell, row, column);
			mCells[row][column] = cell;
		}
	}

	setLayout(gridLayout);
	initialize();
}

void ReversiWidget::initialize()
{
	if (mResultLabel != nullptr)
	{
		mResultLabel->close();
		delete mResultLabel;
		mResultLabel = nullptr;
	}

	mBoard.initialize();
	updateCells_(mBoard);

	mCurrentSide = Piece::Side::Dark;
}

void ReversiWidget::finalize()
{
	mCurrentSide = Piece::Side::Empty;
}

ReversiWidget::~ReversiWidget()
{
	// ツリー破棄時にQtが勝手に破棄してるから子供のdeleteはしない
	// 破棄時にはdestroyedシグナルがくる
	// すぐに破棄してほしくないときはdeleteLater()を呼んでおくとイベントループを抜けるまで遅延してくれる
}

void ReversiWidget::onCellClicked_(Cell* cell)
{
	const auto r = cell->row() + 1;
	const auto c = cell->column() + 1;
	if (mBoard.placePiece(mCurrentSide, r, c))
	{
		updateCells_(mBoard);

		const auto nextSide = mBoard.switchSide(mCurrentSide);
		if (nextSide == Piece::Side::Empty)
		{
			auto winner = mCurrentSide;
			if (mBoard.switchSide(nextSide) == Piece::Side::Empty)
			{
				const auto current = mBoard.countPieces(mCurrentSide);
				const auto next = mBoard.countPieces(nextSide);
				if (current > next)
				{
					winner = mCurrentSide;
				}
				else if (next > current)
				{
					winner = nextSide;
				}
				else
				{
					winner = Piece::Side::Empty;
				}
			}
			showResult_(winner);
			finalize();
			return;
		}
		mCurrentSide = nextSide;
	}
}

void ReversiWidget::updateCells_(const Board& board)
{
	for (auto row = 1; row < board.rows() - 1; ++row)
	{
		for (auto column = 1; column < board.columns() - 1; ++column)
		{
			auto piece = board.piece(row, column);
			if (piece != Piece::Side::Empty)
			{
				mCells[row - 1][column - 1]->placePiece(piece);
			}
		}
	}
}

void ReversiWidget::showResult_(Piece::Side winner)
{
	auto label = new QLabel(this);

	QColor fontColor;
	if (winner == Piece::Side::Dark)
	{
		label->setText("Dark wins");
		fontColor = Qt::black;
	}
	else if (winner == Piece::Side::Light)
	{
		label->setText("Light wins");
		fontColor = Qt::white;
	}
	else
	{
		label->setText("draw");
		fontColor = Qt::gray;
	}

	auto palette = label->palette();
	palette.setColor(label->foregroundRole(), fontColor);
	label->setPalette(palette);

	auto font = label->font();
	font.setPointSize(30);
	font.setBold(true);
	label->setFont(font);

	label->setGeometry(100, 100, label->sizeHint().width(), label->sizeHint().height());
	label->show();

	mResultLabel = label;
}
