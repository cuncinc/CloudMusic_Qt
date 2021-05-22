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

private slots:
	void login_result(const QString & resp);
	void on_toEmail_clicked();
	void on_toPhone_clicked();
	void on_toLogon_clicked();
	void on_toQRCode_clicked();
	void on_logonButton_clicked();
	void on_emailLogin_clicked();
	void on_phoneLogin_clicked();

private:
	Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
