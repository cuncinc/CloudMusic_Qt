#ifndef SONGLISTWINDOW_H
#define SONGLISTWINDOW_H

#include <QWidget>

namespace Ui {
class SongListWindow;
}

class SongListWindow : public QWidget
{
	Q_OBJECT

public:
	explicit SongListWindow(QWidget *parent = nullptr);
	~SongListWindow();

private:
	Ui::SongListWindow *ui;
};

#endif // SONGLISTWINDOW_H
