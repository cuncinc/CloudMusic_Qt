#ifndef SEACHWINDOW_H
#define SEACHWINDOW_H

#include <QWidget>

namespace Ui {
class SeachWindow;
}

class SeachWindow : public QWidget
{
	Q_OBJECT

public:
	explicit SeachWindow(QWidget *parent = nullptr);
	~SeachWindow();

private:
	Ui::SeachWindow *ui;
};

#endif // SEACHWINDOW_H
