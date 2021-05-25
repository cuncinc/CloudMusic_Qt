#include "logindialog.h"
#include "main2window.h"
#include "ui_main2window.h"
#include "httpclient.h"
#include "global.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPixmap>
#include <QPainterPath>
#include <QPainter>

enum Category
{
	Search = 1,		//搜索
	FindMusic = 2,	//发现音乐
	Event = 3,		//动态
	LocalMusic = 5,	//本地音乐
	DownLoad = 6,	//下载管理
	Recent = 7,		//最近播放
	Favorite = 8	//收藏歌单
};

// 图片圆形化，使用完要delete
QPixmap* roundedPixmap(QPixmap& orig)
{
	// getting size if the original picture is not square
	int size = qMax(orig.width(), orig.height());

	// creating a new transparent pixmap with equal sides
	QPixmap *rounded = new QPixmap(size, size);
	rounded->fill(Qt::transparent);

	// creating circle clip area
	QPainterPath painterPath;
	painterPath.addEllipse(rounded->rect());

	QPainter painter(rounded);
	painter.setClipPath(painterPath);

	// filling rounded area if needed
	painter.fillRect(rounded->rect(), Qt::black);

	// getting offsets if the original picture is not square
	int x = qAbs(orig.width() - size) / 2;
	int y = qAbs(orig.height() - size) / 2;
	painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
	return rounded;
}

Main2Window::Main2Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Main2Window)
{
	ui->setupUi(this);

	searchWindow = new SearchWindow();
	findWindow = new FindWindow();
	eventWindow = new EventWindow();
	songListWindow = new SongListWindow();
	meWindow = new UserInfoWindow();

	ui->stackedWidget->addWidget(searchWindow);
	ui->stackedWidget->addWidget(findWindow);
	ui->stackedWidget->addWidget(eventWindow);
	ui->stackedWidget->addWidget(songListWindow);
	ui->stackedWidget->addWidget(meWindow);

	ui->navigation->setCurrentRow(FindMusic);	//初始化指向“发现音乐”
	ui->stackedWidget->setCurrentWidget(findWindow);

	// 图片圆形化
	QPixmap pix(":/img/default-avatar");
	QPixmap *rounded = roundedPixmap(pix);
	QIcon buttonIcon(*rounded);
	delete rounded;
	ui->avatarButton->setIcon(buttonIcon);
	// 初始化登录信息View
	if (global::isLogin)
	{
		updateMe();
	}
}

Main2Window::~Main2Window()
{
	delete searchWindow;
	delete findWindow;
	delete eventWindow;
	delete songListWindow;
	delete ui;
}

void Main2Window::on_navigation_pressed(int index)
{
	switch (index)
	{
	case Search-1:
		onSearch();
		break;
	case FindMusic-1:
		onFindMusic();
		break;
	case Event-1:
		onEvent();
		break;
	case LocalMusic-2:
		onLocalMusic();
		break;
	case DownLoad-2:
		onDownLoad();
		break;
	case Recent-2:
		onRecent();
		break;
	case Favorite-2:
		onFavorite();
		break;
	default:
		break;
	}
}

void Main2Window::onSearch()
{
	qDebug() << "search";
	ui->stackedWidget->setCurrentWidget(searchWindow);
}

void Main2Window::onFindMusic()
{
	qDebug() << "FindMusic";
	ui->stackedWidget->setCurrentWidget(findWindow);
}

void Main2Window::onEvent()
{
	qDebug() << "Event";
	ui->stackedWidget->setCurrentWidget(eventWindow);
}

void Main2Window::onLocalMusic()
{
	qDebug() << "LocalMusic";
}

void Main2Window::onDownLoad()
{
	qDebug() << "DownLoad";
}

void Main2Window::onRecent()
{
	qDebug() << "Recent";
}

void Main2Window::onFavorite()
{
	qDebug() << "Favorite";
}

void Main2Window::onMe()
{
	qDebug() << "Me";
}

void Main2Window::on_avatarButton_clicked()
{
	if (global::isLogin)
	{
		meWindow->setUserId(global::meId);
		ui->stackedWidget->setCurrentWidget(meWindow);
		ui->navigation->setCurrentRow(0);
		meWindow->initView();
	}
	else
	{
		LoginDialog *dialog = new LoginDialog();
		connect(dialog, &LoginDialog::login, this, &Main2Window::updateMe);
		dialog->setWindowModality(Qt::ApplicationModal); //设置界面不可点击
		dialog->show();
	}
}

void Main2Window::updateMe()
{
	if (!global::isLogin)
	{
		ui->nickNameLabel->setText("未登录");
		QIcon icon(":/img/default-avatar");
		ui->avatarButton->setIcon(icon);
		return;
	}

	HttpClient("/user/account").success([=](const QString &response) {
		QJsonObject profile = QJsonDocument::fromJson(response.toUtf8()).object().value("profile").toObject();
		QString nickname = profile.value("nickname").toString();
		QString avatarUrl = profile.value("avatarUrl").toString();
		ui->nickNameLabel->setText(nickname);
		setAvatarUrl(avatarUrl);
	}).get();
}

void Main2Window::setAvatarUrl(const QString &path)
{
	QUrl url(path);
	QNetworkAccessManager manager;
	QEventLoop loop;

	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	//请求结束并下载完成后，退出子事件循环
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//开启子事件循环
	loop.exec();

	QByteArray jpegData = reply->readAll();
	QPixmap pixmap;
	pixmap.loadFromData(jpegData);
	QPixmap *rounded = roundedPixmap(pixmap);
	QIcon buttonIcon(*rounded);
	delete rounded;
	ui->avatarButton->setIcon(buttonIcon);
}
