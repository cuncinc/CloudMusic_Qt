#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "quc/include/navbar.h"
#include <QWidget>

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

private:
	Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
