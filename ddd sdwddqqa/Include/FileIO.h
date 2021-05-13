#pragma once

#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <string>
#include <list>
#include "Nalmak_Include.h"

BEGIN(Nalmak)
class NALMAK_DLL FileIO
{
public:
	FileIO();
	~FileIO();
public:
	static int IsFileOrDir(_wfinddata_t fd);
	static void SearchingDir(std::list<std::wstring> * fdList, const TCHAR* _path, const TCHAR* _extention);
};
END
#endif // !__FILEIO_H__
