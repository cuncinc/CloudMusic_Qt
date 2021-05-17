#include "findwindow.h"
#include "ui_findwindow.h"

FindWindow::FindWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FindWindow)
{
	ui->setupUi(this);
}

FindWindow::~FindWindow()
{
	delete ui;
}
