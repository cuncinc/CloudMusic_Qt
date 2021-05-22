#ifndef MAIN2WINDOW_H
#define MAIN2WINDOW_H

#include "quc/include/navlistview.h"
#include "searchwindow.h"
#include "findwindow.h"
#include "eventwindow.h"
#include "songlistwindow.h"
#include "userinfowindow.h"

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
	void setAvatarUrl(const QString &path);

public slots:
	void updateMe();

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
	void on_avatarButton_clicked();

private:
	Ui::Main2Window *ui;
	SearchWindow *searchWindow;
	FindWindow *findWindow;
	EventWindow *eventWindow;
	SongListWindow *songListWindow;
	UserInfoWindow *meWindow;
};

#endif // MAIN2WINDOW_H
