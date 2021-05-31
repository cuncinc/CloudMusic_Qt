#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingDialog(QWidget *parent = nullptr);
	~SettingDialog();

private slots:
	void on_onlineQuality_currentIndexChanged(int index);

	void on_downloadQuality_currentIndexChanged(int index);

	void on_downloadPath_clicked();

private:
	Ui::SettingDialog *ui;
	void initView();
};

#endif // SETTINGDIALOG_H
