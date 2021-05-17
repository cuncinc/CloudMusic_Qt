#ifndef MAIN2WINDOW_H
#define MAIN2WINDOW_H

#include <QMainWindow>

namespace Ui {
class Main2Window;
}

class Main2Window : public QMainWindow
{
	Q_OBJECT

public:
	explicit Main2Window(QWidget *parent = nullptr);
	~Main2Window();

private:
	Ui::Main2Window *ui;
};

#endif // MAIN2WINDOW_H
