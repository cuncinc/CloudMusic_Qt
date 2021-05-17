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

private:
	Ui::FindWindow *ui;
};

#endif // FINDWINDOW_H
