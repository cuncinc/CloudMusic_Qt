#ifndef MAIN2WINDOW_H
#define MAIN2WINDOW_H

#include "quc/include/navlistview.h"
#include "searchwindow.h"
#include "findwindow.h"
#include "eventwindow.h"
#include "songlistwindow.h"
#include "mewindow.h"
#include "loginwindow.h"

#include <QMainWindow>

namespace Ui {
class Main2Window;
}

class Main2Window : public QMainWindow
{
	Q_OBJECT

public:
	explicit Main2Window(QWidget *parent = nullptr);
	~Main2Window();

public slots:

private slots:
	void on_navigation_pressed(int childIndex);
	void onSearch();
	void onFindMusic();
	void onEvent();
	void onLocalMusic();
	void onDownLoad();
	void onRecent();
	void onFavorite();
	void onMe();
	void onLogin();

	void on_avatarButton_clicked();

private:
	Ui::Main2Window *ui;
	SearchWindow *searchWindow;
	FindWindow *findWindow;
	EventWindow *eventWindow;
	SongListWindow *songListWindow;
	MeWindow *meWindow;
	LoginWindow *loginWindow;
};

#endif // MAIN2WINDOW_H
