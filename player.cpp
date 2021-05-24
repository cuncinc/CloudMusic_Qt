#include "player.h"
#include "httpclient.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Player::Player()
{
//	mediaPlayer = new QMediaPlayer();

	this->setVolume(50);
}

Player::~Player()
{
//	delete mediaPlayer;
}

SongFromType Player::type() const
{
	return fromType;
}


void Player::pauseSong()
{
}

void Player::playSong()
{
	// 暂停
	if (State::PausedState == this->state())
	{
//		qDebug() << "paused";
		this->play();
	}
	else if (State::PlayingState == this->state())
	{
//		qDebug() << "playing";
		this->pause();
	}
	else if (State::StoppedState == this->state())
	{
//		qDebug() << "stopped";
		if (SongFromType::Network == fromType)
			this->setMedia(QUrl(curSongNetworkUrl));
		else if (SongFromType::Local == fromType)
			this->setMedia(QUrl::fromLocalFile(curSongLocalPath));
		this->play();
	}
}

void Player::nextSong()
{
}

void Player::lastSong()
{
}

void Player::setPlayTime(int time)
{
	//	判断传入的时间与当前时间的间隔，如果不超过1秒就不进行跳转，防止递归
	if (time != this->position()/1000)
	{
		// time是秒，设置的是毫秒
		this->setPosition(time * 1000);
	}
}

void Player::nextPlayOrder()
{
}

void Player::setSongId(const QString &id)
{
	fromType = SongFromType::Network;
	info.id = id;

	HttpClient("/song/url").success([=](const QString &response) {
		QJsonArray array = QJsonDocument::fromJson(response.toUtf8()).object().value("data").toArray();
		QString songUrl = array[0].toObject().value("url").toString();
		curSongNetworkUrl = songUrl;
	}).param("id", id).param("br", 160000).get();

	HttpClient("/song/detail").success([=](const QString &response) {
		QJsonArray array = QJsonDocument::fromJson(response.toUtf8()).object().value("songs").toArray();
		QJsonObject song = array[0].toObject();
		QString name = song.value("name").toString();
		QString author = song.value("ar").toArray().at(0).toObject().value("name").toString();
		QString coverUrl = song.value("al").toObject().value("picUrl").toString();
		coverUrl.replace("https", "http");
		info.name = name;
		info.author = author;
		info.coverUrl = coverUrl;
		emit songChanged(info);
	}).param("ids", id).get();
}

void Player::setSongNetworkUrl(const QString &url)
{
	fromType = SongFromType::Network;
	curSongNetworkUrl = url;

//	emit songChanged(info);
}

void Player::setSongLocalPath(const QString &path)
{
	fromType = SongFromType::Local;
	curSongLocalPath = path;

//	emit songChanged(info);
}
