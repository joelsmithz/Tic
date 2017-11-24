
#include "game.h"

int main() {

	bool running = true;
	bool game_won = false;
	char key_press;

	int mX, mY;

	initscr();
	noecho(); // Don't echo out keypresses.
	getmaxyx(stdscr, mY, mX);
	raw();

	Game game(mX, mY);
	game.init();

	// Game loop.
	while (running) {

		key_press = getch();

		if(game_won) {
			switch(key_press) {
				case R_y:
				case R_Y:
					game.init();
					game_won = false;
					break;
				default:
					running = false;
			}
		} else {
			switch(key_press) {
				case R_Q:
					running = false;
					break;
				default:
					if(game.loop(key_press) == true) game_won = true;
					break;
			}
		}
	}

	endwin();

	return 0;
}
