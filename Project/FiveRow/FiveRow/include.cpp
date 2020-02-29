
#include "include.h"

bool isInMap(int x, int y)
{
	return x>=0&&x<MAPWIDTH && y>=0 && y<MAPWIDTH;
}

bool isInMap(POSITION p)
{
	return isInMap(p.x,p.y);
}

bool isFileExist(LPCWSTR filename)
{
	WIN32_FIND_DATA wfd;
	bool rValue = false;

	HANDLE hFind = FindFirstFile(filename, &wfd);
	if (hFind != INVALID_HANDLE_VALUE)  {
		rValue = true;
	}
	FindClose(hFind);
	return rValue;
}

bool isFileExistN(LPCWSTR filename, int size, int N)
{
	for (int i = 0; i < N; i++) {
		if (!isFileExist(filename)) {
			return false;
		}
		filename += size;
	}
	return true;
}

int WstrRcat(LPWSTR dest, LPCWSTR source)
{
	LPWSTR buffer = new WCHAR[lstrlenW(dest)+lstrlenW(source)+1];
	int n = wsprintfW(buffer, L"%s%s", source, dest);
	lstrcpyW(dest, buffer);
	delete []buffer;
	return n;
}

int WstrRcatN(LPWSTR destN, int size, int N, LPCWSTR source)
{
	int n = 0;
	for (int i = 0; i < N; i++) {
		n += WstrRcat(destN, source);
		destN += size;
	}
	return n;
}
