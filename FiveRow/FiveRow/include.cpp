
#include "include.h"

bool isInMap(int x, int y)
{
	return x>=0&&x<MAPWIDTH && y>=0 && y<MAPWIDTH;
}

bool isInMap(POSITION p)
{
	return isInMap(p.x,p.y);
}
