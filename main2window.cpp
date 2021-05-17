#include "main2window.h"
#include "ui_main2window.h"

Main2Window::Main2Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Main2Window)
{
	ui->setupUi(this);
}

Main2Window::~Main2Window()
{
	delete ui;
}
