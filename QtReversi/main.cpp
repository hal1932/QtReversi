#include <QApplication>
#include "ReversiWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ReversiWidget w;
	w.show();

	return a.exec();
}
