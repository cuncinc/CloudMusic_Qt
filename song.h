#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QDateTime>

class Song
{
public:
	QString id;
	QString name;
	QString author;
	QString coverUrl;
	QString album;
	int     durationSecond;
	QString getTime()
	{
		return  QDateTime::fromTime_t(uint(durationSecond)).toUTC().toString("mm:ss");
	}
};

#endif // SONG_H
