#include "findwindow.h"
#include "ui_findwindow.h"

#include <QDate>

FindWindow::FindWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FindWindow)
{
	QDate today = QDate::currentDate();
	int day = today.day();
	today.day();
	ui->setupUi(this);
	ui->dateLabel->setText(QString::number(day).rightJustified(2, '0'));
}

FindWindow::~FindWindow()
{
	delete ui;
}

void FindWindow::on_fmButton_clicked()
{

}

void FindWindow::on_recButton_clicked()
{
	ui->startWidget->setVisible(false);
	ui->recWidget->setVisible(true);
}

void FindWindow::on_topButton_clicked()
{

}

void FindWindow::on_returnButton_clicked()
{
	ui->recWidget->setVisible(false);
	ui->startWidget->setVisible(true);
}
