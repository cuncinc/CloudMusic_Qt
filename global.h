#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

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

	static void ReadFromFile();
	static void StoreToFile();
};

#endif // GLOBAL_H
