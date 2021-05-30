#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaContent>
#include <QQueue>
#include <QList>

// 播放顺序
enum PlayOrder
{
	Sequence = 1,	//列表
	ListCircle = 2,	//列表循环
	OneCircle = 3,	//单曲循环
	Random = 4,		//随机
};

// 歌曲类型`
enum SongFromType
{
	None,		//未设置
	Local,		//来自本地
	Network,	//来自网络
};

struct SongInfo
{
	QString id;
	QString name;
	QString author;
	QString coverUrl;
};

class Player : public QMediaPlayer
{
Q_OBJECT

public:
	Player();
	~Player();

signals:
	void songChanged(SongInfo info);			// 歌曲改变
	void songStop();							// 单曲播放完毕
public:
	void playSongId(const QString &id);
	void initViewById(const QString &id);
	void setSongNetworkUrl(const QString &url);	//待播放音乐的路径
	void setSongLocalPath(const QString &path);	//待播放音乐的路径
	void setPlayIdList(const QList<QString>& list);
	SongFromType type() const;
	PlayOrder playOrder() const;

public slots:
	void pauseSong();			// 暂停
	void playSong();			// 播放
	void nextSong();			// 播放下一首音乐
	void lastSong();			// 播放上一首音乐
	void setPlayTime(int time);	// 进度条，播放时间
	void nextPlayOrder();		// 切换播放顺序
	void playFM();				// 播放私人FM的音乐

private slots:
	void on_stateChanged(QMediaPlayer::State newState);

private:
	PlayOrder order;
	QString curSongNetworkUrl;
	QString curSongLocalPath;
	SongFromType fromType = SongFromType::None;
	SongInfo info;
	QQueue<QString> fmIdQueue;
	bool isFM = false;
	QList<QString> playIdList;
	int curPlayIndex = 0;
};

#endif // PLAYER_H
