#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LoginDialog(QWidget *parent = nullptr);
	~LoginDialog();

public slots:

signals:
	void login(bool state);
	void qrcodeLoaded();			//二维码加载完成
	void qrcodeOverDues();			//二维码过期
	void qrcodeOk(QString cookie);	//扫码登录

private slots:
	void login_result(const QString & resp);
	void loadQRCode();
	void pollingQRCodeResult();		//轮询二维码结果
	void onQrcodeOk(QString cookie);
	void onQrcodeOverdues();
	void on_toEmail_clicked();
	void on_toPhone_clicked();
	void on_toLogon_clicked();
	void on_toQRCode_clicked();
	void on_logonButton_clicked();
	void on_emailLogin_clicked();
	void on_phoneLogin_clicked();
	void on_phoneAccount_textChanged(const QString &arg1);
	void on_phonePassword_textChanged(const QString &arg1);
	void on_emeailAccount_textChanged(const QString &arg1);
	void on_emailPassword_textChanged(const QString &arg1);
	void on_refreshButton_clicked();

private:
	Ui::LoginDialog *ui;
	QTimer *pollingTimer;
	QString key;
};

#endif // LOGINDIALOG_H
