#include "global.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <QDebug>

long long global::meId = -1;
QString global::token = nullptr;
QString global::cookie = nullptr;
QString global::dowloadPath = nullptr;
bool    global::isLogin = false;
int		global::currentId = -1;            //当前播放歌曲的id
bool	global::isSinging = false;
Player* global::player = nullptr;
int		global::xSize = 800;
int		global::ySize = 600;

void global::StoreToFile()
{
	QString filename = FILE_NAME;
	QFile file(filename);
	if (!file.exists() || !file.open(QIODevice::ReadWrite))
	{
		qDebug() << "config file can't be stored";
		return;
	}

	QMap<QString, QString> map;
	map.insert("meId", QString::number(meId));
	map.insert("cookie", cookie);
	map.insert("isLogin", QString::number(isLogin));
	map.insert("xSize", QString::number(xSize));
	map.insert("ySize", QString::number(ySize));

	QDataStream out(&file);
	out << quint32(FILE_MAGIC) << map;
	file.close();

	qDebug() << "save all configs";
}

void global::ReadFromFile()
{
	QString filename = FILE_NAME;
	QFile file(filename);
	if (!file.exists())
	{
		file.open(QIODevice::ReadWrite);
		QDataStream out(&file);
		out << quint32(FILE_MAGIC);
	}
	else if (!file.open(QIODevice::ReadWrite))
	{
		return;
	}
	QDataStream in(&file);
	quint32 n;	//magic number
	QMap<QString, QString> data;
	in >> n >> data;

	if (!data.isEmpty())
	{
		meId    = data["meId"].toLongLong();
		cookie  = data["cookie"];
		isLogin = data["isLogin"].toInt();
		xSize   = data["xSize"].toInt();
		ySize   = data["ySize"].toInt();

		qDebug() << "meId:  " << meId;
		qDebug() << "cookie:  " << cookie << "";
	}
	else
	{
		qDebug() << "data is empty";
	}

	qDebug() << "isLogin?" << data["isLogin"];

	file.close();
}
