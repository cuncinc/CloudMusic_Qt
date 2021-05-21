#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>

class Player : public QMediaPlayer
{
Q_OBJECT

public:
	Player();

public slots:


private:
	QString curSongUrl;
};

#endif // PLAYER_H
