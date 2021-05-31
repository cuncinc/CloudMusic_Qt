#include "player.h"
#include "httpclient.h"
#include "global.h"
#include "toast.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Player::Player()
{
	global::playVolume = 61;
	this->setVolume(global::playVolume);
	order = global::playOrder;
	connect(this, &Player::stateChanged, this, &Player::on_stateChanged);
}

Player::~Player()
{
	global::playOrder = order;
	global::playVolume = volume();
}

SongFromType Player::type() const
{
	return fromType;
}

PlayOrder Player::playOrder() const
{
	return order;
}

void Player::on_stateChanged(QMediaPlayer::State newState)
{
//	qDebug() << "on_stateChanged: " << newState;
	// 只有判断出当为播放完的停止时，才自动切歌。
	// 若不判断duration() == position()，即已经播放完毕，也就是手动切歌，
	// 那么会递归调用，循环切歌
	if (State::StoppedState == newState && duration() == position())
	{
		nextSong();
	}
}

void Player::pauseSong()
{
}

void Player::playSong()
{	
	// 暂停
	if (State::PausedState == this->state())
	{
//		qDebug() << "playSong():  paused";
		this->play();
	}
	else if (State::PlayingState == this->state())
	{
//		qDebug() << "playSong():  playing";
		this->pause();
	}
	else if (State::StoppedState == this->state())
	{
//		qDebug() << "playSong():  stopped";
		if (SongFromType::Network == fromType)
			this->setMedia(QUrl(curSongNetworkUrl));
		else if (SongFromType::Local == fromType)
			this->setMedia(QUrl::fromLocalFile(curSongLocalPath));
		this->play();
	}
}

void Player::nextSong()
{
//	qDebug() << "nextSong()";
	if (isFM)
	{
		playFM();
		return;
	}
	else if (playIdList.isEmpty())
	{
		qDebug() << "player: playIdList is empty";
		return;
	}
	else if (SongFromType::Network == fromType)
	{
		switch (order)
		{
		case PlayOrder::Random:		//随机播放
			curPlayIndex = rand() % playIdList.size();
			playSongId(playIdList.at(curPlayIndex));
			break;
		case PlayOrder::Sequence:	//顺序播放
			curPlayIndex++;
			if (curPlayIndex < playIdList.size())
			{
				playSongId(playIdList.at(curPlayIndex));
			}
			else
			{
				Toast::showTip("播放列表到底了~", 4000);
			}
			break;
		case PlayOrder::OneCircle:	//单曲循环
			this->playSongId(info.id);
			break;
		case PlayOrder::ListCircle:	//列表循环
			curPlayIndex++;
			if (curPlayIndex >= playIdList.size())
			{
				curPlayIndex = 0;
			}
			playSongId(playIdList.at(curPlayIndex));
			break;
		}
	}
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
	int d = static_cast<int>(order);
	++d;
	if (d >= 5)
	{
		d = 1;
	}
	order = static_cast<PlayOrder>(d);
}

void Player::playSongId(const QString &id)
{
	fromType = SongFromType::Network;
	info.id = id;

	HttpClient("/song/url").success([=](const QString &response) {
		QJsonArray array = QJsonDocument::fromJson(response.toUtf8()).object().value("data").toArray();
		QString songUrl = array[0].toObject().value("url").toString();
		curSongNetworkUrl = songUrl;
		this->stop();
		playSong();
	}).param("id", id).param("br", 128000).get();

	initViewById(id);
}

void Player::initViewById(const QString &id)
{
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

void Player::playFM()
{
	isFM = true;
	if (!fmIdQueue.isEmpty())
	{
		playSongId(fmIdQueue.dequeue());
		return;
	}

	HttpClient("/personal_fm").success([=](const QString &response) {
		QJsonArray array = QJsonDocument::fromJson(response.toUtf8()).object().value("data").toArray();
//		qDebug() << "get FM num" << array.size();
		for (int i=0; i<array.size(); ++i)
		{
			long long id = array[i].toObject().value("id").toVariant().toLongLong();
			QString name = array[i].toObject().value("name").toString();
			qDebug() << "new FM " << id << "  " << name;
			fmIdQueue.enqueue(QString::number(id));
		}
		playSongId(fmIdQueue.dequeue());
	}).get();
}

void Player::setPlayIdList(const QList<QString>& list)
{
	playIdList.clear();
	foreach (QString id, list)
	{
		playIdList.push_back(id);
	}
}
