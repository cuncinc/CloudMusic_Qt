#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QWidget>

namespace Ui {
class DetailWindow;
}

class DetailWindow : public QWidget
{
	Q_OBJECT

public:
	explicit DetailWindow(QWidget *parent = nullptr);
	~DetailWindow();

private:
	Ui::DetailWindow *ui;
};

#endif // DETAILWINDOW_H
