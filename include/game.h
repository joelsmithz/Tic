
#include <string>
#include <curses.h>
#include <stdio.h>
#include <map>

enum KEYS {
	R_LEFT  = 68,
	R_RIGHT = 67,
	R_DOWN  = 66,
	R_UP    = 65,
	R_Q     = 113,
	R_y     = 121,
	R_Y     = 89,
	R_ENTER = 10,
};

class Game {
public:
	Game(int mX, int mY);
	void init();
	bool loop(char key_press);

private:
	int _mX, _mY;
	bool _won;
	std::map<char, int> _scores;
	char _field[3][3];
	char _current_player;
	int _current_position[2];

	void change_player();
	
	void print_layout();
	void print_information();
	void print_status();
	void move_to_current_pos();

	void check_win();
};
