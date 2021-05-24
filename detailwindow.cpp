#include "detailwindow.h"
#include "ui_detailwindow.h"
#include "httpclient.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QDebug>

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

void DetailWindow::setSongId(const QString &id)
{
	curSongId = id;
}

void DetailWindow::setView(SongInfo info)
{
	curSongId = info.id;
	ui->nameLabel->setText(info.name);
	ui->authorLabel->setText(info.author);
	// lyric
	HttpClient("/lyric").success([=](const QString &response) {
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object().value("lrc").toObject();
		QString lyric = object.value("lyric").toString();
		QRegularExpression re("\\[.*\\]");
		lyric.replace(re, "");
//		qDebug() << lyric;
		ui->lyricLabel->setPlainText(lyric);
	}).param("id", curSongId).get();
	setCoverUrl(info.coverUrl);
}

void DetailWindow::setCoverUrl(const QString &path)
{
	if (nullptr == path)
	{
		QPixmap pixmap(":/img/default-cover");
		ui->coverLabel->setPixmap(pixmap);
		return;
	}

	QUrl url(path);
	QNetworkAccessManager manager;
	QEventLoop loop;

	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray jpegData = reply->readAll();
	QPixmap pixmap;
	pixmap.loadFromData(jpegData);
	ui->coverLabel->setPixmap(pixmap);
}
