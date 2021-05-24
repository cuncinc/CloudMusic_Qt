#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "quc/include/navbar.h"
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QStandardItemModel>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QWidget
{
	Q_OBJECT

public:
	explicit SearchWindow(QWidget *parent = nullptr);
	~SearchWindow();

private slots:
	void on_tabBar_currentItemChanged(int index, const QString &item);

    void on_pushButton_clicked();

    void showClick(QModelIndex index); // 点击listView后的响应

private:
	Ui::SearchWindow *ui;

public:
    QJsonObject result;
    QJsonArray ja;
    QStringListModel *Model;
    QStandardItemModel *ItemModel;
};

#endif // SEARCHWINDOW_H
