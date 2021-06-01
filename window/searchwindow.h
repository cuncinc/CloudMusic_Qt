#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "quc/include/navbar.h"

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QDebug>
#include <QAction>

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
    void showClick(QModelIndex index); // 点击listView后的响应
	void onSearch();

private:
    Ui::SearchWindow *ui;
	QStandardItemModel itemModel;
	QList<QString> idList;
	QAction *searchAction;
	void setTableView(const QJsonArray &songs);
};

#endif // SEARCHWINDOW_H
