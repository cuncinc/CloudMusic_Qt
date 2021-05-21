#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginDialog)
{
	ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
	delete ui;
}

void LoginDialog::on_toEmail_clicked()
{
	ui->start->setVisible(false);
	ui->email->setVisible(true);
}

void LoginDialog::on_toPhone_clicked()
{
	ui->start->setVisible(false);
	ui->phone->setVisible(true);
}

void LoginDialog::on_toLogon_clicked()
{
	ui->start->setVisible(false);
	ui->logon->setVisible(true);
}

void LoginDialog::on_toQRCode_clicked()
{

}
