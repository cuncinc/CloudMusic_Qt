#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QDebug>
#include "httpclient.h"
#include "toast.h"
#include"global.h"
#include <QModelIndex>
#include <QStringListModel>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QMessageBox>

SearchWindow::SearchWindow(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchWindow)
{
	ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
	delete ui;
}


void SearchWindow::on_tabBar_currentItemChanged(int index, const QString &item)
{
	qDebug() << index <<" " << item;
}

void SearchWindow::on_pushButton_clicked()
{
    //点击搜索后单曲bar显示的内容(歌名，歌手)
    QString keyword = ui->searchLine->text();
            HttpClient("/cloudsearch").success([=](const QString &response) {
                result = QJsonDocument::fromJson(response.toUtf8()).object().value("result").toObject();
                ja =result.value("songs").toArray();
                ItemModel = new QStandardItemModel(this);
                QStringList strList;
                for (int i=0; i<ja.size(); ++i)
                {
                    QString name = ja[i].toObject().value("name").toString();
                    QString singername = ja[i].toObject().value("ar").toArray()[0].toObject().value("name").toString();
                    int id = ja[i].toObject().value("id").toInt();
                    QString str = QString::number(id);
                    strList.append(name+"                 "+singername+"                                                                                                            ,"+str);//用逗号分隔id
                    qDebug() << name<<"   "+singername<<id;
                }

                       int nCount = strList.size();
                       for(int i = 0; i < nCount; i++)
                       {
                           QString string = static_cast<QString>(strList.at(i));
                           QStandardItem *item = new QStandardItem(string);
                           ItemModel->appendRow(item);
                       }
                      ui->listView->setModel(ItemModel);

                      ui->listView->setFixedSize(754,422);

                      connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));

            }).param("keywords", keyword)
                    .get();
}

void SearchWindow::showClick(QModelIndex index)
{
    QString strTemp;
    strTemp = index.data().toString();
    QStringList list = strTemp.split(",");
    int id=list[1].toInt();
   //全局变量当前播放的歌曲id记录
    global::currentId = id;
    global::isSinging = true;
    qDebug()<<list[1];
//    QMessageBox msg;
//    msg.setText(list[1]);
//    msg.exec();
    qDebug()<<global::isSinging;
}
