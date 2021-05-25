#include "logindialog.h"
#include "ui_logindialog.h"
#include "httpclient.h"
#include "global.h"
#include "toast.h"

#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>

LoginDialog::LoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginDialog)
{
	ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
	//	emit login(false);
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
	HttpClient("/msg/private").success([=](const QString &response) {
		qDebug() << response;
	}).get();
}

void LoginDialog::on_logonButton_clicked()
{

}

void LoginDialog::on_emailLogin_clicked()
{
	QString email = ui->emeailAccount->text();
	QString password = ui->emailPassword->text();

	HttpClient("/login").success([=](const QString &response) {
		login_result(response);
	}).param("email", email)
			.param("password", password)
			.get();
}

void LoginDialog::on_phoneLogin_clicked()
{
	QString phone = ui->phoneAccount->text();
	QString password = ui->phonePassword->text();

	HttpClient("/login/cellphone").success([=](const QString &response) {
		login_result(response);
	}).param("phone", phone)
			.param("password", password)
			.get();
}

void LoginDialog::login_result(const QString &resp)
{
	QJsonObject json = QJsonDocument::fromJson(resp.toUtf8()).object();
	int code = json.value("code").toInt();
	if (code != 200)
	{
		qDebug() << "code is " << code;
		Toast::showTip(tr("密码错误，请重新输入"));
		return;
	}
	QString token = json.value("token").toString();
	QString cookie = json.value("cookie").toString();
	long long meId = json.value("account").toObject().value("id").toVariant().toLongLong();

	global::token = token;
	global::cookie = cookie;
	global::meId = meId;
	global::isLogin = true;
//    global::isSinging=false;

	emit login(true);
	close();
}

void LoginDialog::on_phoneAccount_textChanged(const QString &arg1)
{
	if (ui->phoneAccount->text().length()  == 11 && ui->phonePassword->text().length() > 0)
	{
		ui->phoneLogin->setEnabled(true);
	}
	else
	{
		ui->phoneLogin->setEnabled(false);
	}
}

void LoginDialog::on_phonePassword_textChanged(const QString &arg1)
{
	on_phoneAccount_textChanged(arg1);
}

void LoginDialog::on_emeailAccount_textChanged(const QString &arg1)
{
	if (ui->emeailAccount->text().length()>0 && ui->emailPassword->text().length()>0)
	{
		ui->emailLogin->setEnabled(true);
	}
	else
	{
		ui->emailLogin->setEnabled(false);
	}
}

void LoginDialog::on_emailPassword_textChanged(const QString &arg1)
{
	on_emeailAccount_textChanged(arg1);
}
