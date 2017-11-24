
#include "game.h"

Game::Game(int mX, int mY) : _mX(mX), _mY(mY) {
	print_information();
}

void Game::init() {

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			_field[i][j] = ' ';
		}
	}

	for(int i = 0; i < 2; i++) _current_position[i] = 1;

	_scores['X'] = 0;
	_scores['O'] = 0;

	_current_player = 'X';

	_won = false;

	// Clear the screen of any previous game's output.
	mvprintw(_mY - 4, _mX / 2 - 6, "            ");
	mvprintw(_mY - 3, _mX / 2 - 20, "                                         ");

	print_layout();
	print_status();
}

void Game::change_player() {
	_current_player == 'X' ? _current_player = 'O' : _current_player = 'X';
}

bool Game::loop(char key_press) {

	switch(key_press) {
		case R_ENTER:
			// If the current space is not empty.
			if(_field[_current_position[0]][_current_position[1]] == ' ') {
				_field[_current_position[0]][_current_position[1]] = _current_player;
				_scores[_current_player]++;

				change_player();
				check_win();

				mvprintw(_mY / 2 - 10, _mX / 2 - 6, "        ");
			} else {
				mvprintw(_mY / 2 - 10, _mX / 2 - 6, "OCCUPIED");
			}
			break;
		case R_LEFT:
			if(_current_position[1] > 0) _current_position[1]--;
			break;
		case R_RIGHT:
			if(_current_position[1] < 2) _current_position[1]++;
			break;
		case R_UP:
			if(_current_position[0] > 0) _current_position[0]--;
			break;
		case R_DOWN:
			if(_current_position[0] < 2) _current_position[0]++;
			break;
	}

	print_layout();
	print_status();
	move_to_current_pos();

	return _won;
}

void Game::check_win() {
	for(int i = 0; i < 3; i++) {
		if(_field[i][0] == 'X' && _field[i][1] == 'X' && _field[i][2] == 'X') _won = true;
		if(_field[i][0] == 'O' && _field[i][1] == 'O' && _field[i][2] == 'O') _won = true;
	}

	for(int i = 0; i < 3; i++) {
		if(_field[0][i] == 'X' && _field[1][i] == 'X' && _field[2][i] == 'X') _won = true;
		if(_field[0][i] == 'O' && _field[1][i] == 'O' && _field[2][i] == 'O') _won = true;
	}

	if(_field[0][0] == 'X' && _field[1][1] == 'X' && _field[2][2] == 'X') _won = true;
	if(_field[0][0] == 'O' && _field[1][1] == 'O' && _field[2][2] == 'O') _won = true;

	if(_field[0][2] == 'X' && _field[1][1] == 'X' && _field[2][0] == 'X') _won = true;
	if(_field[0][2] == 'O' && _field[1][1] == 'O' && _field[2][0] == 'O') _won = true;

	bool tie = true;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(_field[i][j] == ' ') tie = false;
		}
	}

	if(tie) {
		_won = true;
		mvprintw(_mY - 4, _mX / 2 - 2, "TIE");
		mvprintw(_mY - 3, _mX / 2 - 20, "PRESS [ Y ] TO RESTART, ANY OTHER TO EXIT");
	} else if(_won) {
		mvprintw(_mY - 4, _mX / 2 - 6, "WINNER IS %c", _current_player == 'X' ? 'O' : 'X');
		mvprintw(_mY - 3, _mX / 2 - 20, "PRESS [ Y ] TO RESTART, ANY OTHER TO EXIT");
	}
}

void Game::move_to_current_pos() {
	move(_mY / 2 - 5 + _current_position[0] * 4, _mX / 2 - 8 + _current_position[1] * 6);
}

void Game::print_information() {
	mvprintw(_mY - 6, 1, "COMMANDS:");
	mvprintw(_mY - 4, 1, "QUIT [ Q ]");
	mvprintw(_mY - 2, 1, "MOVE [ LEFT | RIGHT | UP | DOWN ]");
}

void Game::print_status() {

	mvprintw(_mY / 2 - 10, _mX / 2 - 28, "CURRENT PLAYER: %c", _current_player);

	mvprintw(_mY / 2 - 6, _mX / 2 - 28, "PLAYER X: %i", _scores['X']);
	mvprintw(_mY / 2 - 4, _mX / 2 - 28, "PLAYER O: %i", _scores['O']);

	move_to_current_pos();
}

void Game::print_layout() {
	mvprintw(_mY / 2 - 7, _mX / 2 - 11, "+-----+-----+-----+");
	mvprintw(_mY / 2 - 6, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 - 5, _mX / 2 - 11, "|  %c  |  %c  |  %c  |", _field[0][0], _field[0][1], _field[0][2]);
	mvprintw(_mY / 2 - 4, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 - 3, _mX / 2 - 11, "+-----+-----+-----+");
	mvprintw(_mY / 2 - 2, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 - 1, _mX / 2 - 11, "|  %c  |  %c  |  %c  |", _field[1][0], _field[1][1], _field[1][2]);
	mvprintw(_mY / 2 - 0, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 + 1, _mX / 2 - 11, "+-----+-----+-----+");
	mvprintw(_mY / 2 + 2, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 + 3, _mX / 2 - 11, "|  %c  |  %c  |  %c  |", _field[2][0], _field[2][1], _field[2][2]);
	mvprintw(_mY / 2 + 4, _mX / 2 - 11, "|     |     |     |");
	mvprintw(_mY / 2 + 5, _mX / 2 - 11, "+-----+-----+-----+");

	move_to_current_pos();
}
