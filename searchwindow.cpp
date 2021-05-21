#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QDebug>

SearchWindow::SearchWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchWindow)
{
	ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
	delete ui;
}


void SearchWindow::on_tabBar_currentItemChanged(int index, const QString &item)
{
	qDebug() << index <<" " << item;
}
