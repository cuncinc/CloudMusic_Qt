#include "window/detailwindow.h"
#include "ui_detailwindow.h"
#include "utils/httpclient.h"
#include "utils/toast.h"
#include "utils/global.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>
#include <QDebug>
#include <QTextBlockFormat>

DetailWindow::DetailWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DetailWindow)
{
	ui->setupUi(this);

	// 设置行高，但无效
	//	QTextBlockFormat bf = ui->lyricLabel->textCursor().blockFormat();
	////	qDebug() << bf.lineHeight();
	//	bf.setLineHeight(2000, QTextBlockFormat::FixedHeight);
	//	ui->lyricLabel->textCursor().setBlockFormat(bf);
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
		if (nullptr == lyric || 0 == lyric.size())
		{
			lyric = "暂无歌词";
		}
		else
		{
			QRegularExpression re("\\[.*\\]");
			lyric.replace(re, "");
		}
		//		qDebug() << lyric;
		ui->lyricLabel->setPlainText(lyric);
	}).param("id", curSongId).get();

	// comment
	HttpClient("/comment/music").success([=](const QString &response) {
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
		int count = object.value("total").toInt();
		ui->comNumLabel->setNum(count);
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

void DetailWindow::comment(CommentType type, const QString text)
{
	QMap<QString, QVariant> map;
	map.insert("t", 1);
	map.insert("type", 0);
	map.insert("id", curSongId);
	map.insert("content", text);

	// To-Do reply
	if (CommentType::Reply == type)
	{
//		map.insert("commentId", 11111);
	}

	// To Do 似乎这个api评论不了，也许是我不会用
	HttpClient("/comment").success([=](const QString &response) {
		qDebug() << response;
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = object.value("code").toInt();
		if (code == 200)
		{
			Toast::showTip("评论成功");
		}
		else
		{
			QString msg = object.value("msg").toString();
			Toast::showTip(msg, 4000);
		}
	}).params(map).get();
}

void DetailWindow::on_likeButton_clicked()
{
	if (!global::isLogin)
	{
		Toast::showTip("需要登录");
		return;
	}

	HttpClient("/like").success([=](const QString &response) {
		int code = QJsonDocument::fromJson(response.toUtf8()).object().value("code").toInt();
		if (200 == code)
		{
			Toast::showTip("已添加到我喜欢的音乐");
			ui->likeButton->setText("取消喜欢");
		}
	}).param("id", curSongId).get();
}

void DetailWindow::on_downloadButton_clicked()
{
	if (global::downloadPath.isEmpty())
	{
		Toast::showTip("请设置下载路径");
		return;
	}
	else
	{
		Toast::showTip("开始下载");
	}
	SongInfo info = global::player->getInfo();
	QString fileBaseNmae = info.author + " - " + info.name;
	HttpClient("/song/url").success([=](const QString &response) {
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = object.value("code").toInt();
		QString msg = object.value("msg").toString();
		if (200 != code)
		{
			Toast::showTip("下载失败:" + msg);
			return;
		}

		QJsonObject song = object.value("data").toArray().at(0).toObject();
		QString url = song.value("url").toString();
		QString type = song.value("type").toString();
		QString fileName = fileBaseNmae + "." + type;
		QString path = global::downloadPath + "/" + fileName;
		HttpClient(url, false).success([=](const QString &response) {
			Toast::showTip(info.name+"下载完成");
		}).download(path);
	}).param("id", info.id).param("br", global::downloadQuality).get();
}

void DetailWindow::on_favoriteButton_clicked()
{
	if (!global::isLogin)
	{
		Toast::showTip("需要登录");
		return;
	}
}

void DetailWindow::on_toCommentButton_clicked()
{
	CommentDialog *dialog = new CommentDialog();
	connect(dialog, &CommentDialog::textInputed, this, &DetailWindow::comment);
	dialog->setWindowModality(Qt::ApplicationModal); //设置界面不可点击
	dialog->show();
}
