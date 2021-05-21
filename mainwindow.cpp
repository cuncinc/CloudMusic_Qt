#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httpclient.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPixmap>

void test()
{
	HttpClient("/cloudsearch").success([=](const QString &response) {
		QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
		QJsonObject jsonObject = jsonDoc.object().value("result").toObject();
		QJsonArray jsonArray = jsonObject.value("songs").toArray();

		//		for (int i=0; i<jsonArray.size(); ++i)
		//		{
		//			QString name = jsonArray[i].toObject().value("name").toString();
		//			qDebug() << name;
		//		}

		foreach (const QJsonValue& value, jsonArray)
		{
			int id = value.toObject().value("id").toInt();
			QString name = value.toObject().value("name").toString();
			qDebug() << id << "\t" << name;
		}

		//		qDebug() << response;

	}).param("keywords", "GoodTime")			// 参数
			.param("limit", "5")
			.header("token", "test")		// Header
			.get();
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->imgLabel->installEventFilter(this);	//安装事件过滤器，实现clicked

	main2Window = new Main2Window();
	ui->stackedWidget->addWidget(main2Window);
	ui->stackedWidget->setCurrentWidget(main2Window);
	detailWindow = new DetailWindow();
	ui->stackedWidget->addWidget(detailWindow);

	test();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete main2Window;
	delete detailWindow;
}

void MainWindow::setCoverUrl(const QString &path)
{
	qDebug() << "img:  " << path;
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
	ui->imgLabel->setPixmap(pixmap); // 你在QLabel显示图片
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	//	qDebug() << "eventFilter";
	if (obj == ui->imgLabel && event->type() == QEvent::MouseButtonPress)
	{
		//		qDebug() << "image Label event";
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
		if(mouseEvent->button() == Qt::LeftButton)
		{
			if (ui->stackedWidget->currentWidget() == detailWindow)
			{
				ui->stackedWidget->setCurrentWidget(main2Window);
			}
			else
			{
				ui->stackedWidget->setCurrentWidget(detailWindow);
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// pass the event on to the parent class
		//		return QWidget::eventFilter(obj, event);
		return false;
	}
}

void MainWindow::on_lastButton_clicked()
{

}

void MainWindow::on_playButton_clicked()
{

}

void MainWindow::on_nextButton_clicked()
{

}
