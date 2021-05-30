#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QWidget>
#include <QList>
#include <QStandardItemModel>
#include <QModelIndex>

namespace Ui {
class FindWindow;
}

class FindWindow : public QWidget
{
	Q_OBJECT

public:
	explicit FindWindow(QWidget *parent = nullptr);
	~FindWindow();

private slots:
	void onItemClick(QModelIndex index);
	void on_fmButton_clicked();
	void on_recButton_clicked();
	void on_topButton_clicked();
	void on_returnButton_clicked();

private:
	Ui::FindWindow *ui;
	bool initRecView();
	void setTableView(const QJsonArray& songs);
	QList<QString> recIdList;
	QStandardItemModel recItemModel;
};

#endif // FINDWINDOW_H
