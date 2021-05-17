#include "detailwindow.h"
#include "ui_detailwindow.h"

DetailWindow::DetailWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DetailWindow)
{
	ui->setupUi(this);
}

DetailWindow::~DetailWindow()
{
	delete ui;
}
