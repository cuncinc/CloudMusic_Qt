#ifndef GLOBAL_H
#define GLOBAL_H

#include "player.h"

#include <QString>
#include <QMediaPlayer>

#define FILE_MAGIC 0xFFCC22CC
#define FILE_NAME ".cmusic"

class global
{
public:
	static QString token;
	static QString cookie;
	static QString dowloadPath;
	static long long meId;
	static bool    isLogin;
    static int  currentId ;            //当前播放歌曲的id
<<<<<<< HEAD
    static bool isSinging;
	static Player* player;
=======
    static bool isSinging;    //是否在播放歌曲
    static QMediaPlayer *player; //音频播放器
    static QString songUrl;     //歌曲url地址
>>>>>>> 30d6fbb4bac4b15fe0ae0d04fda82cf8b89a7c0a

	static void ReadFromFile();
	static void StoreToFile();
};

#endif // GLOBAL_H
