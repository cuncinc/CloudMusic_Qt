#include "window/main2window.h"
#include "window/detailwindow.h"
#include "utils/player.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
	void setCoverUrl(const QString &url);
	void changePlayIcon(Player::State state);	//修改播放按钮的图标
	void setNowTimeView(qint64 time);			//修改时间滑杆和时间Label
	void setSongView(SongInfo info);			// 歌曲、作者、封面
	void setTimeView(qint64 time);				// 歌曲播放时间

private slots:
	void on_lastButton_clicked();
	void on_playButton_clicked();
	void on_nextButton_clicked();
	void on_coverButton_clicked();
	void on_orderButton_clicked();

	void on_playListButton_clicked();

	void on_volumeButtom_clicked();

private:
    Ui::MainWindow *ui;
	Main2Window *main2Window;
	DetailWindow *detailWindow;
	Player *player;
	void initView();
};
#endif // MAINWINDOW_H
