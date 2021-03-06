#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include "utils/player.h"
#include "dialog/commentdialog.h"

#include <QWidget>

namespace Ui {
class DetailWindow;
}

class DetailWindow : public QWidget
{
	Q_OBJECT

public:
	explicit DetailWindow(QWidget *parent = nullptr);
	~DetailWindow();
	void setSongId(const QString &id);

public slots:
	void setView(SongInfo info);

private slots:
	void comment(CommentType type, const QString text);
	void on_likeButton_clicked();
	void on_downloadButton_clicked();
	void on_favoriteButton_clicked();
	void on_toCommentButton_clicked();

private:
	Ui::DetailWindow *ui;
	QString curSongId;
	void setCoverUrl(const QString &url);
};

#endif // DETAILWINDOW_H
