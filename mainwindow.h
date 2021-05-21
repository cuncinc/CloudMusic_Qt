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
	bool eventFilter(QObject *obj, QEvent *event);	// �¼���������ʵ��QLabel��click

public slots:
	void setImg(const QString &url);

private:
    Ui::MainWindow *ui;
	Main2Window *main2Window;
	DetailWindow *detailWindow;
};
#endif // MAINWINDOW_H
