#ifndef TOAST_H
#define TOAST_H

#pragma once

#include <QWidget>
#include "ui_toast.h"

class Toast : public QWidget
{
	Q_OBJECT

public:
	Toast(QWidget *parent = Q_NULLPTR);
	~Toast();

	void setText(const QString& text);

	void showAnimation(int timeout = 2000);// 动画方式show出，默认2秒后消失

public:
	// 静态调用
	static void showTip(const QString& text, const int time = 2000, QWidget* parent = nullptr);

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	Ui::Toast ui;
};

#endif // TOAST_H
