#include "main2window.h"
#include "detailwindow.h"

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
	bool eventFilter(QObject *obj, QEvent *event);	// 事件过滤器，实现QLabel的click

public slots:
	void setCoverUrl(const QString &url);

private slots:
	void on_lastButton_clicked();

	void on_playButton_clicked();

	void on_nextButton_clicked();

private:
    Ui::MainWindow *ui;
	Main2Window *main2Window;
	DetailWindow *detailWindow;
};
#endif // MAINWINDOW_H
