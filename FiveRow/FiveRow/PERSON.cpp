#include "PERSON.h"

POSITION PERSON::play()
{
	return m_OnLButtonDownPosition;
}

void PERSON::OnLButtonDown(POSITION p)
{
	m_OnLButtonDownPosition = p;
}

int PERSON::getPlayerInt()
{
	return ::PLAYER;
}
