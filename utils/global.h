#ifndef GLOBAL_H
#define GLOBAL_H

#include "utils/player.h"

#include <QString>
#include <QMediaPlayer>

#define FILE_MAGIC 0xFFCC22CC
#define FILE_NAME ".cmusic"

class global
{
public:
	static QString	token;			//登录token
	static QString	cookie;			//登录cookie
	static QString	downloadPath;	//下载路径
	static int		onlineQuality;	//在线播放音质
	static int		downloadQuality;//下载音质
	static long long meId;			//登录用户id
	static bool		isLogin;		//是否登录
	static bool		isSinging;		//是否在播放歌曲
	static QString  currentId;		//当前播放歌曲的id
	static Player*	player;			//全局播放器
	static int		xSize;			//窗口尺寸x
	static int		ySize;			//窗口尺寸y
	static PlayOrder playOrder;		//音乐播放顺序
	static int		playVolume;		//音乐播放音量

	static void ReadFromFile();
	static void StoreToFile();
};

#endif // GLOBAL_H
