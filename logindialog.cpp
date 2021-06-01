#include "logindialog.h"
#include "ui_logindialog.h"
#include "httpclient.h"
#include "global.h"
#include "toast.h"
#include "qrcode/QrCode.hpp"

#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QDateTime>
#include <QTimer>

using namespace qrcodegen;

void paintQR(QPixmap *map, const QString &data)
{
	QPainter painter(map);
	QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::LOW);
	const int s = qr.getSize()>0 ? qr.getSize() : 1;
	const double w = map->width();
	const double h = map->height();
	const double aspect = w / h;
	const double size = ((aspect>1.0) ? h : w);
	const double scale = size / (s+2);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor("#FFFFFF"));
	for(int y=0; y<s; y++)
	{
		for(int x=0; x<s; x++)
		{
			const int color=qr.getModule(x, y);  // 0 for white, 1 for black
			if(0 != color)
			{
				const double rx1 = (x+1)*scale, ry1=(y+1)*scale;
				QRectF r(rx1, ry1, scale, scale);
				painter.drawRects(&r,1);
			}
		}
	}
}

LoginDialog::LoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginDialog)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui->setupUi(this);
	pollingTimer = new QTimer(this);
	connect(pollingTimer, &QTimer::timeout, this, QOverload<>::of(&LoginDialog::pollingQRCodeResult));
//	connect(this, &LoginDialog::qrcodeLoaded, this, &LoginDialog::pollingQRCodeResult);
	connect(this, &LoginDialog::qrcodeOk, this, &LoginDialog::onQrcodeOk);
	connect(this, &LoginDialog::qrcodeOverDues, this, &LoginDialog::onQrcodeOverdues);
}

LoginDialog::~LoginDialog()
{
	delete ui;
	delete pollingTimer;
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
	ui->start->setVisible(false);
	ui->qrcode->setVisible(true);
	loadQRCode();
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
		Toast::showTip("密码错误，请重新输入");
		return;
	}
	QString token = json.value("token").toString();
	QString cookie = json.value("cookie").toString();
	long long meId = json.value("account").toObject().value("id").toVariant().toLongLong();

	global::token = token;
	global::cookie = cookie;
	global::meId = meId;
	global::isLogin = true;

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

void LoginDialog::on_refreshButton_clicked()
{
	loadQRCode();
	ui->notValidFrame->setVisible(false);
}

void LoginDialog::loadQRCode()
{
	uint timestanp = QDateTime::currentDateTime().toTime_t();
	HttpClient("/login/qr/key").success([=](const QString &response) {
		QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
		key = json.value("data").toObject().value("unikey").toString();
		HttpClient("/login/qr/create").success([=](const QString &response) {
			QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
			QString qrurl = json.value("data").toObject().value("qrurl").toString();
			qDebug() << qrurl;
			QPixmap map(300, 300);
			paintQR(&map, qrurl);
			pollingTimer->start(1500);
			ui->qrcodeLabel->setPixmap(map);
//			emit qrcodeLoaded();
		}).param("key", key).param("timestamp", timestanp).get();
	}).param("timestamp", timestanp).get();
}

void LoginDialog::pollingQRCodeResult()
{
	uint timestanp = QDateTime::currentDateTime().toTime_t();

	HttpClient("/login/qr/check").success([=](const QString &response){
		QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = json.value("code").toInt();
		QString msg = json.value("message").toString();
		switch (code)
		{
		case 800:	//过期
			pollingTimer->stop();
			emit qrcodeOverDues();
			break;
		case 801:	//等待扫码
			break;
		case 802:	//待确认
			break;
		case 803:	//登录成功
			pollingTimer->stop();
			QString cookie = json.value("cookie").toString();
			emit qrcodeOk(cookie);
			break;
		}
		QDateTime now = QDateTime::currentDateTime();
		qDebug() << now.time() << msg;
	}).param("key", key).param("timestamp", timestanp).get();
}

void LoginDialog::onQrcodeOk(QString cookie)
{
	HttpClient("/user/account").success([=](const QString &response) {
		QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = json.value("code").toInt();
		if (200 != code)
		{
			QString msg = json.value("message").toString();
			qDebug() << "扫描登录失败：" + msg;
			Toast::showTip("扫描登录失败：" + msg);
		}

		long long meId = json.value("account").toObject().value("id").toVariant().toLongLong();
		global::meId = meId;
		global::cookie = cookie;
		global::token = "";
		global::isLogin = true;
		emit login(true);
		close();
	}).param("cookie", cookie).get();
}

void LoginDialog::onQrcodeOverdues()
{
	ui->notValidFrame->setVisible(true);
}
