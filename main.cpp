#include "mainwindow.h"
#include "gaugecar.h"
#include "global.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	global::ReadFromFile();	//读取配置文件一定要在最前面，否则窗口先初始化
    QApplication a(argc, argv);
	MainWindow w;
    w.setWindowIcon(QIcon(":/logo/logo88"));
	w.show();

	return a.exec();
}
