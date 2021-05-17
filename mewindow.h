#ifndef MEWINDOW_H
#define MEWINDOW_H

#include <QWidget>

namespace Ui {
class MeWindow;
}

class MeWindow : public QWidget
{
	Q_OBJECT

public:
	explicit MeWindow(QWidget *parent = nullptr);
	~MeWindow();

private:
	Ui::MeWindow *ui;
};

#endif // MEWINDOW_H
