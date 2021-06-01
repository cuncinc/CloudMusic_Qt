#include "dialog/trackdialog.h"
#include "ui_trackdialog.h"

TrackDialog::TrackDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TrackDialog)
{
	ui->setupUi(this);
}

TrackDialog::~TrackDialog()
{
	delete ui;
}
