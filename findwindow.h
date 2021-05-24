#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QWidget>

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
	void on_fmButton_clicked();

	void on_recButton_clicked();

	void on_topButton_clicked();

	void on_returnButton_clicked();

private:
	Ui::FindWindow *ui;
};

#endif // FINDWINDOW_H
