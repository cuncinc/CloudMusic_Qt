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
	static bool isSinging;		//是否在播放歌曲
    static QString  currentId;            //当前播放歌曲的id
	static Player* player;
	static int  xSize;			//窗口尺寸x
	static int  ySize;			//窗口尺寸y

	static void ReadFromFile();
	static void StoreToFile();
};

#endif // GLOBAL_H
