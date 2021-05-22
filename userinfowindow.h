#ifndef USERINFOWINDOW_H
#define USERINFOWINDOW_H

#include "global.h"
#include <QWidget>

namespace Ui {
class UserInfoWindow;
}

class UserInfoWindow : public QWidget
{
	Q_OBJECT

public:
	explicit UserInfoWindow(QWidget *parent = nullptr);
	~UserInfoWindow();
	inline void setUserId(long long uid){userId = uid;}
	void initView();
	void setAvatarUrl(const QString &path);

private:
	Ui::UserInfoWindow *ui;
	long long userId;
};

#endif // USERINFOWINDOW_H
