#include "main2window.h"
#include "detailwindow.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
	void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
	Main2Window *main2Window;
	DetailWindow *detailWindow;
};
#endif // MAINWINDOW_H
