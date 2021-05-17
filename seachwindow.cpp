#include "seachwindow.h"
#include "ui_seachwindow.h"

SeachWindow::SeachWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SeachWindow)
{
	ui->setupUi(this);
}

SeachWindow::~SeachWindow()
{
	delete ui;
}
