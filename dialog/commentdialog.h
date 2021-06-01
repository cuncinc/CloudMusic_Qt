#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include <QDialog>

namespace Ui {
class CommentDialog;
}

enum CommentType
{
	Comment = 1,
	Reply = 2
};

class CommentDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CommentDialog(const QString &replyName = nullptr, QWidget *parent = nullptr);
	~CommentDialog();

private slots:
	void on_comment_textChanged();

	void on_commenButton_clicked();

signals:
	void textInputed(CommentType type, const QString text);

private:
	Ui::CommentDialog *ui;
	CommentType type;
};

#endif // COMMENTDIALOG_H
