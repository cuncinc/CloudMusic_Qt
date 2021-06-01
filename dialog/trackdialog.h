#ifndef TRACKDIALOG_H
#define TRACKDIALOG_H

#include <QDialog>

namespace Ui {
class TrackDialog;
}

class TrackDialog : public QDialog
{
	Q_OBJECT

public:
	explicit TrackDialog(QWidget *parent = nullptr);
	~TrackDialog();

private:
	Ui::TrackDialog *ui;
};

#endif // TRACKDIALOG_H
