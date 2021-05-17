#include "mainwindow.h"
#include "gaugecar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();

//	GaugeCar w;
//	w.resize(800, 600);
//	w.show();

	return a.exec();
}
