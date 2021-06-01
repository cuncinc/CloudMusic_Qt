#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(const QString &replyName, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CommentDialog)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui->setupUi(this);

	if (nullptr == replyName)
	{
		type = CommentType::Comment;
	}
	else
	{
		type = CommentType::Reply;
		ui->comment->setPlaceholderText("回复 @" + replyName);
	}
}

CommentDialog::~CommentDialog()
{
	delete ui;
}

void CommentDialog::on_comment_textChanged()
{
	int len = ui->comment->toPlainText().length();
	if (len > 0)
	{
		ui->commenButton->setEnabled(true);
	}
	else
	{
		ui->commenButton->setEnabled(false);
	}
}

void CommentDialog::on_commenButton_clicked()
{
	QString text = ui->comment->toPlainText();
	emit textInputed(type, text);
	this->close();
}
