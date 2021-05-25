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
#include "mainwindow.h"
#include <QAction>

SearchWindow::SearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
    ui->tableView->setShowGrid(false);

    ui->tableView->horizontalHeader()->hide();//隐藏列头
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    ui->tableView->setFrameStyle(QFrame::NoFrame);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
//    ui->tableView->setRowHeight(0,20);
    ui->tableView->setStyleSheet("QHeaderView::section{border: 0px solid white;min-height: 32px;background-color:red} QTableView::item{selection-background-color:#E7E7EA}" );
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->searchLine->setStyleSheet("QLineEdit{border:1px groove #E4E4E7;border-radius:10px;padding:2px 4px}");

    pTrailingAction = new QAction(this);
    pTrailingAction->setIcon(QIcon(":/img/asserts/biyingjunUI/search.png"));
    ui->searchLine->addAction(pTrailingAction, QLineEdit::TrailingPosition);
    // 连接信号和槽
    connect(pTrailingAction, SIGNAL(triggered(bool)), this, SLOT(onSearch(bool)));
	connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
    }


SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::on_tabBar_currentItemChanged(int index, const QString &item)
{
    qDebug() << index <<" " << item;
}

void SearchWindow::onSearch(bool)
{
    QString id;
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
                    int time =  ja[i].toObject().value("dt").toInt();
                    qDebug()<<QString::number(time);
                    int seconds = int(time/1000);
                    QString zhuanji = ja[i].toObject().value("al").toObject().value("name").toString();
                    QString timeStr = QDateTime::fromTime_t(uint(seconds)).toUTC().toString("mm:ss");
                    QString singername = ja[i].toObject().value("ar").toArray()[0].toObject().value("name").toString();

                    ql[i] =ja[i].toObject().value("id").toInt();
//                    QString str = QString::number(id);
//                    strList.append(name+"                 "+singername+"                                                                                                                  ."+str);//用逗号分隔id
//                    list<<new QStandardItem(name)<<new QStandardItem(singername);
//                    ItemModel->appendRow(list);
//                                           qDebug() << name<<"   "+singername<<id;

                     ItemModel->setItem(i, 0, new QStandardItem(name));
//                     ItemModel->item(i, 0)->setFont( QFont( "", NULL,QFont::Bold ));
                     ItemModel->setItem(i, 1, new QStandardItem(singername));
//                     ItemModel->item(i, 1)->setFont( QFont( "", NULL,QFont::ExtraLight ));
                     ItemModel->setItem(i,2,new QStandardItem(zhuanji));
//                     ItemModel->item(i, 2)->setFont( QFont( "", NULL,QFont::Light ));
                     ItemModel->setItem(i,3,new QStandardItem(timeStr));
//                     ItemModel->item(i, 3)->setFont( QFont( "", NULL,QFont::Light ));
                }

//                       int nCount = strList.size();
//                       for(int i = 0; i < nCount; i++)
//                       {
//                           QString string = static_cast<QString>(strList.at(i));
//                           QStandardItem *item = new QStandardItem(string);
//                           ItemModel->appendRow(item);
//                       }
                      ui->tableView->setModel(ItemModel);
					  ui->tableView->setColumnWidth(0,350);
					  ui->tableView->setColumnWidth(1,200);
					  ui->tableView->setColumnWidth(2,200);
					  ui->tableView->setColumnWidth(3,200);

                      for(int i=0;i<ja.size();i++)
                      {
                          ui->tableView->setRowHeight(i,55);
                      }
					  ui->tableView->setFixedSize(1600,672);

			}).param("keywords", keyword).param("type","1")
                    .get();
}


void SearchWindow::showClick(QModelIndex index)
{
//    QString strTemp;
//    strTemp = index.data().toString();
//    QStringList list = strTemp.split(".");
//    int id=list[1].toInt();
    qDebug()<<index.data().toString();
    qDebug()<<index.row();
   //全局变量当前播放的歌曲id记录
//    global::currentId = id;
    int d = index.row();
    global::currentId = QString::number(ql[d]);
    qDebug()<<ql[d];
    global::player->playSongId(global::currentId);
    global::isSinging = true;
//    qDebug()<<list[1];
//    global::player->playSongId(list[1]);
//    HttpClient("/song/url").success([=](const QString &response) {
//    QJsonArray data = QJsonDocument::fromJson(response.toUtf8()).object().value("data").toArray();
//    QString url = data[0].toObject().value("url").toString(); // 获取搜索的歌曲的网络url地址
//    global::player->playSongId(global::currentId);
//    HttpClient("/song/url").success([=](const QString &response) {
//    QJsonArray data = QJsonDocument::fromJson(response.toUtf8()).object().value("data").toArray();
//    QString url = data[0].toObject().value("url").toString(); // 获取搜索的歌曲的网络url地址
//    qDebug()<<url;
//    }).param("id", list[1])
//            .param("br", "32000")
//            .get();
}
