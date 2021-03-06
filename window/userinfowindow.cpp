#include "window/userinfowindow.h"
#include "ui_userinfowindow.h"

#include "utils/httpclient.h"
#include <QJsonObject>
#include <QJsonDocument>

UserInfoWindow::UserInfoWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::UserInfoWindow)
{
	ui->setupUi(this);
}

UserInfoWindow::~UserInfoWindow()
{
	delete ui;
}

void UserInfoWindow::initView()
{
	HttpClient("/user/detail").success([=](const QString &response) {
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
		int level = object.value("level").toInt();
		QJsonObject profile = object.value("profile").toObject();
		QString nickname = profile.value("nickname").toString();
		QString avatarUrl = profile.value("avatarUrl").toString();
		int eventNum = profile.value("eventCount").toInt();
		int followNum = profile.value("follows").toInt();
		int fanNum = profile.value("allSubscribedCount").toInt();	//此字段不确定
		bool followMe = profile.value("followMe").toBool();

		ui->levelLayout->setText("Lv"+QString::number(level));
		ui->nickNameLabel->setText(nickname);
		ui->eventNum->setText(QString::number(eventNum));
		ui->followNum->setText(QString::number(followNum));
		ui->fanNum->setText(QString::number(fanNum));
		setAvatarUrl(avatarUrl);
	}).param("uid", userId).get();
}

void UserInfoWindow::setAvatarUrl(const QString &path)
{
	QUrl url(path);
	QNetworkAccessManager manager;
	QEventLoop loop;

	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray jpegData = reply->readAll();
	QPixmap pixmap;
	pixmap.loadFromData(jpegData);
	ui->avatarLabel->setPixmap(pixmap);
}

void UserInfoWindow::on_quitButton_clicked()
{
	global::meId = -1;
	global::token = "";
	global::cookie = "";
	global::isLogin = false;
}
