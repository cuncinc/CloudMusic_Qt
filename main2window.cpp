#include "logindialog.h"
#include "main2window.h"
#include "ui_main2window.h"

#include <QDebug>

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

Main2Window::Main2Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Main2Window)
{
	ui->setupUi(this);

	searchWindow = new SearchWindow();
	findWindow = new FindWindow();
	eventWindow = new EventWindow();
	songListWindow = new SongListWindow();
	meWindow = new MeWindow();
	loginWindow = new LoginWindow();

	ui->stackedWidget->addWidget(searchWindow);
	ui->stackedWidget->addWidget(findWindow);
	ui->stackedWidget->addWidget(eventWindow);
	ui->stackedWidget->addWidget(songListWindow);
	ui->stackedWidget->addWidget(meWindow);
	ui->stackedWidget->addWidget(loginWindow);

	ui->navigation->setCurrentRow(FindMusic);	//初始化指向“发现音乐”
	ui->stackedWidget->setCurrentWidget(findWindow);
}

Main2Window::~Main2Window()
{
	delete searchWindow;
	delete findWindow;
	delete eventWindow;
	delete songListWindow;
	delete ui;
}

//	  void pressed(const QString &text, const QString &parentText);
//    void pressed(int index, int parentIndex);
//    void pressed(int childIndex);
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

void Main2Window::onLogin()
{
	qDebug() << "Login";
}

void Main2Window::on_avatarButton_clicked()
{
	LoginDialog *dialog = new LoginDialog();
	dialog->setWindowModality(Qt::ApplicationModal); //设置界面不可点击
	dialog->show();
}
