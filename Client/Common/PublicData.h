
#ifndef __PUBLIC_DATA_H__
#define __PUBLIC_DATA_H__

#include <xstring>

using namespace std;

enum OBJECT_TAG
{
	OBJECT_TAG_DEFAULT,
	OBJECT_TAG_PLAYER,
	OBJECT_TAG_ENVIRONMENT,
	OBJECT_TAG_MAX
};

const wstring g_objectTagName[OBJECT_TAG_MAX]
{
	L"Default",
	L"Player",
	L"Environment"
};



#endif // !__PUBLIC_DATA_H__

