#include <Windows.h>
#include <easyx.h>
#include <conio.h>

#include "ui_menu.h"
#include "ui_map.h"
#include "game.h"

//using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {

	GAME game(WIDTH, HEIGHT);

	game.init();
	//game.startPersonVsPerson();
	
	game.startPersonVsAI();

	return 0;
}
