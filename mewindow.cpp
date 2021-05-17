#include "mewindow.h"
#include "ui_mewindow.h"

MeWindow::MeWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MeWindow)
{
	ui->setupUi(this);
}

MeWindow::~MeWindow()
{
	delete ui;
}
