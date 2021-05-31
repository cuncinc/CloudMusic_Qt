#include "findwindow.h"
#include "ui_findwindow.h"
#include "global.h"
#include "toast.h"
#include "httpclient.h"
#include "quc/include/adswidget2.h"

#include <QDate>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#define BANNER_PATH "banner//"

FindWindow::FindWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::FindWindow)
{
	ui->setupUi(this);

	QDate today = QDate::currentDate();
	int day = today.day();
	today.day();
	ui->dateLabel->setText(QString::number(day).rightJustified(2, '0'));

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	connect(ui->tableView, &QTableView::doubleClicked, this, &FindWindow::onItemClick);

	initBannerView();
}

FindWindow::~FindWindow()
{
	delete ui;
}

void FindWindow::onItemClick(QModelIndex index)
{
	int d = index.row();
	global::player->playNetSongId(recIdList.at(d), &recIdList);
}

void FindWindow::initBannerView()
{
	HttpClient("/banner").success([=](const QString &response) {
		QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = json.value("code").toInt();
		if (200 != code)
		{
			QString msg = json.value("msg").toString();
			Toast::showTip("获取banner失败：" + msg);
			return;
		}

		QJsonArray banners = json.value("banners").toArray();
		QString titles;
		for (int i=0; i<banners.size(); ++i)
		{
			QString title = banners[i].toObject().value("typeTitle").toString();
			if (0 == titles.length())
			{
				titles += title;
			}
			else
			{
				titles += "|" + title;
			}
			QString url = banners[i].toObject().value("imageUrl").toString();
			HttpClient(url, false).download(QString::number(i) + ".jpg");
		}
		QString names = "0.jpg";
		for (int i=1; i<banners.size(); ++i)
		{
			names += "|" + QString::number(i) + ".jpg";
		}
		ui->banner->setImageTips(titles);
		ui->banner->setImageNames(names);
	}).param("type", 0).get();
}

void FindWindow::setTableView(const QJsonArray &songs)
{
	for (int i=0; i<songs.size(); ++i)
	{
		QString id = QString::number(songs[i].toObject().value("id").toVariant().toLongLong());
		QString name = songs[i].toObject().value("name").toString();
		int time =  songs[i].toObject().value("dt").toInt();
		int seconds = int(time/1000);
		QString timeStr = QDateTime::fromTime_t(uint(seconds)).toUTC().toString("mm:ss");
		QString album = songs[i].toObject().value("al").toObject().value("name").toString();
		QString author = songs[i].toObject().value("ar").toArray()[0].toObject().value("name").toString();

		recIdList.push_back(id);

		recItemModel.setItem(i, 0, new QStandardItem(name));
		recItemModel.setItem(i, 1, new QStandardItem(author));
		recItemModel.setItem(i, 2, new QStandardItem(album));
		recItemModel.setItem(i, 3, new QStandardItem(timeStr));
	}
	ui->tableView->setModel(&recItemModel);
}

void FindWindow::on_fmButton_clicked()
{
	global::player->playFM();
}

void FindWindow::on_recButton_clicked()
{
	if (!recIdList.isEmpty())
	{
		ui->startWidget->setVisible(false);
		ui->recWidget->setVisible(true);
	}

	HttpClient("/recommend/songs").success([=](const QString &response) {
		QJsonObject json = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = json.value("code").toInt();
		if (200 != code)
		{
			QString msg = json.value("msg").toString();
			Toast::showTip(msg);
			return;
		}

		QJsonArray songs = json.value("data").toObject().value("dailySongs").toArray();
		setTableView(songs);

		ui->startWidget->setVisible(false);
		ui->recWidget->setVisible(true);

	}).get();
}

void FindWindow::on_topButton_clicked()
{

}

void FindWindow::on_returnButton_clicked()
{
	ui->recWidget->setVisible(false);
	ui->startWidget->setVisible(true);
}
