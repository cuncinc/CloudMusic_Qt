#include "window/songlistwindow.h"
#include "ui_songlistwindow.h"

SongListWindow::SongListWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SongListWindow)
{
	ui->setupUi(this);
}

SongListWindow::~SongListWindow()
{
	delete ui;
}
