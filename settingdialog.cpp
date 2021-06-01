#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "global.h"

#include <QFileDialog>
#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingDialog)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui->setupUi(this);
	initView();
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

void SettingDialog::initView()
{
	// 先暂存下来，在addItems时global会改变
	int onlineQuality = global::onlineQuality;
	int downloadQuality = global::downloadQuality;

	QStringList list;
	list.push_back("标准 (128kbit/s)");
	list.push_back("较高 (192kbit/s)");
	list.push_back("极高 (320kbit/s)");
	ui->onlineQuality->addItems(list);
	ui->downloadQuality->addItems(list);
	ui->downloadPath->setText(global::downloadPath);

	// 使用暂存下来的局部变量，不能使用global，否则无效
	switch (onlineQuality)
	{
	case 128000:
		ui->onlineQuality->setCurrentIndex(0);
		break;
	case 192000:
		ui->onlineQuality->setCurrentIndex(1);
		break;
	case 320000:
		ui->onlineQuality->setCurrentIndex(2);
		break;
	}

	switch (downloadQuality)
	{
	case 128000:
		ui->downloadQuality->setCurrentIndex(0);
		break;
	case 192000:
		ui->downloadQuality->setCurrentIndex(1);
		break;
	case 320000:
		ui->downloadQuality->setCurrentIndex(2);
		break;
	}
}

void SettingDialog::on_onlineQuality_currentIndexChanged(int index)
{
	int quality = 128000;
	switch (index)
	{
	case 0:
		quality = 128000;
		break;
	case 1:
		quality = 192000;
		break;
	case 2:
		quality = 320000;
		break;
	}
	global::onlineQuality = quality;
}

void SettingDialog::on_downloadQuality_currentIndexChanged(int index)
{
	int quality = 128000;
	switch (index)
	{
	case 0:
		quality = 128000;
		break;
	case 1:
		quality = 192000;
		break;
	case 2:
		quality = 320000;
		break;
	}
	global::downloadQuality = quality;
}

void SettingDialog::on_downloadPath_clicked()
{
	QString path = QFileDialog::getExistingDirectory(this, "选择文件夹", global::downloadPath);
	ui->downloadPath->setText(path);
	global::downloadPath = path;
}
