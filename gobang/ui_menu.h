#pragma once

#include <easyx.h>
#include <Windows.h>

#include "resource.h"

enum SELECTION {
	STARTGAME=1,
	ABOUTGAME=2,
	EXITGAME=0,
};

class UIMENU{
public:
	void draw();
	SELECTION getSelection();
	UIMENU(int width, int height);
	~UIMENU();

private:
	int m_width;
	int m_height;
	IMAGE *m_menuImg;
};



