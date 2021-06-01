#include "utils/global.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <QDebug>

long long global::meId = -1;
QString global::token = nullptr;
QString global::cookie = nullptr;
bool    global::isLogin = false;
Player* global::player = nullptr;
int		global::xSize = 800;
int		global::ySize = 600;
PlayOrder global::playOrder = PlayOrder::Sequence;
int     global::playVolume = 60;
int     global::onlineQuality;
int     global::downloadQuality;
QString global::downloadPath;

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
	map.insert("meId",			QString::number(meId));
	map.insert("cookie",		cookie);
	map.insert("isLogin",		QString::number(isLogin));
	map.insert("xSize",			QString::number(xSize));
	map.insert("ySize",			QString::number(ySize));
	map.insert("playOrder",		QString::number(playOrder));
	map.insert("playVolume",	QString::number(playVolume));
	map.insert("onlineQuality", QString::number(onlineQuality));
	map.insert("downloadQuality", QString::number(downloadQuality));
	map.insert("dowloadPath",	downloadPath);
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
		meId			= data["meId"].toLongLong();
		cookie			= data["cookie"];
		isLogin			= data["isLogin"].toInt();
		xSize			= data["xSize"].toInt();
		ySize			= data["ySize"].toInt();
		playOrder		= static_cast<PlayOrder>(data["playOrder"].toInt());
		playVolume		= data["palyVolume"].toInt();
		downloadQuality	= data["downloadQuality"].toInt();
		onlineQuality	= data["onlineQuality"].toInt();
		downloadPath	= data["dowloadPath"];

		qDebug() << "meId:  " << meId;
	}
	else
	{
		qDebug() << "data is empty";
	}

	qDebug() << "isLogin?" << data["isLogin"];

	file.close();
}
