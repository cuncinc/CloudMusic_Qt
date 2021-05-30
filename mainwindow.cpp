#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httpclient.h"
#include "global.h"
#include "toast.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// 初始化UI
	main2Window = new Main2Window();
	ui->stackedWidget->addWidget(main2Window);
	ui->stackedWidget->setCurrentWidget(main2Window);
	detailWindow = new DetailWindow();
	ui->stackedWidget->addWidget(detailWindow);

	// 初始化音乐播放器
	global::player = new Player();
	player = global::player;

	// 播放状态 -> 播放按钮图标
	connect(player, &Player::stateChanged, this, &MainWindow::changePlayIcon);
	// 歌曲改变 -> 更新view(封面、作者)
	connect(player, &Player::songChanged, this, &MainWindow::setSongView);
	// 歌曲改变 -> 设置歌曲时间、滑杆最大值
	connect(player, &Player::durationChanged, this, &MainWindow::setTimeView);
	// 播放时间 -> 时间滑杆和时间Label
	connect(player, &Player::positionChanged, this, &MainWindow::setNowTimeView);
	// 时间滑杆 -> 播放时间
	connect(ui->slider, &XSlider::valueChanged, player, &Player::setPlayTime);
	// 歌曲改变 -> 初始化view
	connect(player, &Player::songChanged, detailWindow, &DetailWindow::setView);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete main2Window;
	delete detailWindow;
	delete player;
	// 保留窗口大小，下一次打开软件，恢复此窗口大小
	global::xSize = this->width();
	global::ySize = this->height();
	global::StoreToFile();	// 保存一些配置信息到文件中
}

// 修改播放按钮图标
void MainWindow::changePlayIcon(Player::State state)
{
	QIcon icon;
	if (Player::State::PausedState == state)
	{
		icon.addFile(":/icon/play");
	}
	else if (Player::State::PlayingState == state)
	{
		icon.addFile(":/icon/pasue");
	}
	else if (Player::State::StoppedState == state)
	{
		icon.addFile(":/icon/play");
	}
	ui->playButton->setIcon(icon);
}

void MainWindow::setNowTimeView(qint64 time)
{
	//	qDebug() << time;
	// 本来是毫秒的时间换成秒
	int now = int(time/1000);
	ui->slider->setValue(now);

	QString timeStr;
	if (now < 3600)	//1小时之内不显示小时
	{
		timeStr = QDateTime::fromTime_t(uint(now)).toUTC().toString("mm:ss");
	}
	else
	{
		timeStr = QDateTime::fromTime_t(uint(now)).toUTC().toString("hh:mm:ss");
	}
	ui->nowLabel->setText(timeStr);
}

void MainWindow::setTimeView(qint64 time)
{
	int seconds = int(time / 1000);
	ui->slider->setMaximum(seconds);
	QString timeStr;
	if (seconds < 3600)	//1小时之内不显示小时
	{
		timeStr = QDateTime::fromTime_t(uint(seconds)).toUTC().toString("mm:ss");
	}
	else
	{
		timeStr = QDateTime::fromTime_t(uint(seconds)).toUTC().toString("hh:mm:ss");
	}
	ui->timeLabel->setText(timeStr);
}

void MainWindow::setSongView(SongInfo info)
{
	ui->nameLabel->setText(info.name);
	ui->authorLabel->setText(info.author);
	setCoverUrl(info.coverUrl);
}

void MainWindow::setCoverUrl(const QString &path)
{
	if (nullptr == path)
	{
		QPixmap pixmap(":/img/default-cover");
		QIcon buttonIcon(pixmap);
		ui->coverButton->setIcon(buttonIcon);
		return;
	}

	//	qDebug() << "img:  " << path;
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
	QIcon buttonIcon(pixmap);
	ui->coverButton->setIcon(buttonIcon);
	//	ui->coverButton->setIconSize(ui->coverButton->size());
}

void MainWindow::on_lastButton_clicked()
{

}

void MainWindow::on_playButton_clicked()
{
	player->playSong();
}

void MainWindow::on_nextButton_clicked()
{
	player->nextSong();
}

void MainWindow::on_coverButton_clicked()
{
	if (ui->stackedWidget->currentWidget() == detailWindow)
	{
		ui->stackedWidget->setCurrentWidget(main2Window);
	}
	else
	{
		if (SongFromType::None != player->type())
			ui->stackedWidget->setCurrentWidget(detailWindow);
	}
}

void MainWindow::on_orderButton_clicked()
{
	player->nextPlayOrder();

	switch (player->playOrder())
	{
	case PlayOrder::Sequence:
		Toast::showTip("顺序播放");
		break;
	case PlayOrder::Random:
		Toast::showTip("随机播放");
		break;
	case PlayOrder::OneCircle:
		Toast::showTip("单曲循环");
		break;
	case PlayOrder::ListCircle:
		Toast::showTip("列表循环");
		break;
	}
}
