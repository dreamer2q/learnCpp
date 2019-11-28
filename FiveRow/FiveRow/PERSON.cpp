#include "PERSON.h"

void PERSON::play(POSITION p)
{
	m_map->putChess(p);
}

int PERSON::getPlayerInt()
{
	return ::PLAYER;
}
