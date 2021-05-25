#include "mainwindow.h"
#include "gaugecar.h"
#include "global.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	//读取配置文件一定要在最前面，否则窗口先初始化
	global::ReadFromFile();

    QApplication a(argc, argv);
	MainWindow w;

	//设置上次退出时的窗口大小
	global::xSize = global::xSize > 800 ? global::xSize : 800;
	global::ySize = global::ySize > 600 ? global::ySize : 600;
	w.resize(global::xSize, global::ySize);

	w.show();

	return a.exec();
}
