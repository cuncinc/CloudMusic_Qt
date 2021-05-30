#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "httpclient.h"
#include "toast.h"
#include "global.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	searchAction = new QAction(this);
	searchAction->setIcon(QIcon(":/img/asserts/biyingjunUI/search.png"));
	ui->searchLine->addAction(searchAction, QLineEdit::TrailingPosition);

	connect(searchAction, &QAction::triggered, this, &SearchWindow::onSearch);
	connect(ui->searchLine, &QLineEdit::returnPressed, this, &SearchWindow::onSearch);
	connect(ui->tableView, &QTableView::doubleClicked, this, &SearchWindow::showClick);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_tabBar_currentItemChanged(int index, const QString &item)
{
    qDebug() << index <<" " << item;
}

void SearchWindow::onSearch()
{
    //点击搜索后单曲bar显示的内容(歌名，歌手)
    QString keyword = ui->searchLine->text();
	if (nullptr == keyword || keyword.size() == 0)
	{
		Toast::showTip("请输入要搜索的关键词");
	}

	HttpClient("/cloudsearch").success([=](const QString &response) {
		QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
		int code = object.value("code").toInt();
		if (200 != code)
		{
			Toast::showTip("未搜索到任何东西");
			return;
		}

		QJsonArray songs = object.value("result").toObject().value("songs").toArray();
		setTableView(songs);

	}).param("keywords", keyword).param("type","1").get();
}

void SearchWindow::setTableView(const QJsonArray &songs)
{
	idList.clear();
	itemModel.clear();

	for (int i=0; i<songs.size(); ++i)
	{
		QString id = QString::number(songs[i].toObject().value("id").toVariant().toLongLong());
		QString name = songs[i].toObject().value("name").toString();
		int time =  songs[i].toObject().value("dt").toInt();
		int seconds = int(time/1000);
		QString timeStr = QDateTime::fromTime_t(uint(seconds)).toUTC().toString("mm:ss");
		QString album = songs[i].toObject().value("al").toObject().value("name").toString();
		QString author = songs[i].toObject().value("ar").toArray()[0].toObject().value("name").toString();

		idList.push_back(id);

		itemModel.setItem(i, 0, new QStandardItem(name));
		itemModel.setItem(i, 1, new QStandardItem(author));
		itemModel.setItem(i, 2, new QStandardItem(album));
		itemModel.setItem(i, 3, new QStandardItem(timeStr));
	}
	ui->tableView->setModel(&itemModel);
}

void SearchWindow::showClick(QModelIndex index)
{
	int d = index.row();
	global::player->playSongId(idList.at(d));
}
