/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Ncurses
*/

#include "Ncurses.hpp"
#include <cstring>
#include <algorithm>
#include <iostream>

Arc::Ncurses::Ncurses()
{
}

Arc::Ncurses::~Ncurses()
{
}

void Arc::Ncurses::display(std::map<std::string, Item> &ItemList)
{
	erase();
	int maxY = 0;
	int maxX = 0;
	getmaxyx(stdscr, maxY, maxX);

	_maxX = maxX;
	_maxY = maxY;

	float ratioX = 1920.0f / (maxX - 4);
	float ratioY = 1080.0f / (maxY - 4);
	_ratio = std::max(ratioX, ratioY);

	if (has_colors())
		attron(COLOR_PAIR(1));
	box(stdscr, 0, 0);
	if (has_colors())
		attroff(COLOR_PAIR(1));

	if (has_colors())
		attron(COLOR_PAIR(3));
	for (const auto& pair : ItemList) {
		if (!pair.second.text.empty()) {
			int y = static_cast<int>(pair.second.position.second / _ratio) + 1;
			int x = static_cast<int>(pair.second.position.first / _ratio) + 2;
			
			if (y < 1) y = 1;
			if (y > maxY - 2) y = maxY - 2;
			if (x < 2) x = 2;
			if (x > maxX - 2) x = maxX - 2;
			
			mvprintw(y, x, "%s", pair.second.text.c_str());
		}
	}
	if (has_colors())
		attroff(COLOR_PAIR(3));
	refresh();
}

bool Arc::Ncurses::pollEvent(Event& event)
{
	int ch = getch();

	if (ch == ERR)
		return false;
	
	event.type = KeyPressed;
	event.code = Arc::None;
	
	if (ch == KEY_MOUSE) {
		MEVENT mevent;
		if (getmouse(&mevent) == OK) {
			event.mouse.x = mevent.x * _ratio;
			event.mouse.y = mevent.y * _ratio;
			
			
			if (mevent.bstate & BUTTON1_CLICKED) {
				event.code = Arc::MouseLeft;
				return true;
			}
			if (mevent.bstate & BUTTON3_CLICKED) {
				event.code = Arc::MouseRight;
				return true;
			}
		}
		return false;
	}
	
	if (ch == 27) {
		event.type = Quit;
		return true;
	}

	if (ch == KEY_LEFT) {
		event.code = Arc::Left;
		return true;
	}
	if (ch == KEY_RIGHT) {
		event.code = Arc::Right;
		return true;
	}
	if (ch == KEY_UP) {
		event.code = Arc::Up;
		return true;
	}
	if (ch == KEY_DOWN) {
		event.code = Arc::Down;
		return true;
	}
	if (ch == 'a' || ch == 'A') {
		event.code = Arc::A;
		return true;
	}
	if (ch == 'b' || ch == 'B') {
		event.code = Arc::B;
		return true;
	}
	if (ch == 'c' || ch == 'C') {
		event.code = Arc::C;
		return true;
	}
	if (ch == 'd' || ch == 'D') {
		event.code = Arc::D;
		return true;
	}
	if (ch == 'e' || ch == 'E') {
		event.code = Arc::E;
		return true;
	}
	if (ch == 'f' || ch == 'F') {
		event.code = Arc::F;
		return true;
	}
	if (ch == 'g' || ch == 'G') {
		event.code = Arc::G;
		return true;
	}
	if (ch == 'h' || ch == 'H') {
		event.code = Arc::H;
		return true;
	}
	if (ch == 'i' || ch == 'I') {
		event.code = Arc::I;
		return true;
	}
	if (ch == 'j' || ch == 'J') {
		event.code = Arc::J;
		return true;
	}
	if (ch == 'k' || ch == 'K') {
		event.code = Arc::K;
		return true;
	}
	if (ch == 'l' || ch == 'L') {
		event.code = Arc::L;
		return true;
	}
	if (ch == 'm' || ch == 'M') {
		event.code = Arc::M;
		return true;
	}
	if (ch == 'n' || ch == 'N') {
		event.code = Arc::N;
		return true;
	}
	if (ch == 'o' || ch == 'O') {
		event.code = Arc::O;
		return true;
	}
	if (ch == 'p' || ch == 'P') {
		event.code = Arc::P;
		return true;
	}
	if (ch == 'q' || ch == 'Q') {
		event.code = Arc::Q;
		return true;
	}
	if (ch == 'r' || ch == 'R') {
		event.code = Arc::R;
		return true;
	}
	if (ch == 's' || ch == 'S') {
		event.code = Arc::S;
		return true;
	}
	if (ch == 't' || ch == 'T') {
		event.code = Arc::T;
		return true;
	}
	if (ch == 'u' || ch == 'U') {
		event.code = Arc::U;
		return true;
	}
	if (ch == 'v' || ch == 'V') {
		event.code = Arc::V;
		return true;
	}
	if (ch == 'w' || ch == 'W') {
		event.code = Arc::W;
		return true;
	}
	if (ch == 'x' || ch == 'X') {
		event.code = Arc::X;
		return true;
	}
	if (ch == 'y' || ch == 'Y') {
		event.code = Arc::Y;
		return true;
	}
	if (ch == 'z' || ch == 'Z') {
		event.code = Arc::Z;
		return true;
	}
	if (ch == '0') {
		event.code = Arc::Num0;
		return true;
	}
	if (ch == '1') {
		event.code = Arc::Num1;
		return true;
	}
	if (ch == '2') {
		event.code = Arc::Num2;
		return true;
	}
	if (ch == '3') {
		event.code = Arc::Num3;
		return true;
	}
	if (ch == '4') {
		event.code = Arc::Num4;
		return true;
	}
	if (ch == '5') {
		event.code = Arc::Num5;
		return true;
	}
	if (ch == '6') {
		event.code = Arc::Num6;
		return true;
	}
	if (ch == '7') {
		event.code = Arc::Num7;
		return true;
	}
	if (ch == '8') {
		event.code = Arc::Num8;
		return true;
	}
	if (ch == '9') {
		event.code = Arc::Num9;
		return true;
	}
	if (ch == '\n') {
		event.code = Arc::Enter;
		return true;
	}
	if (ch == ' ') {
		event.code = Arc::Space;
		return true;
	}
	if (ch == 9) {
		event.code = Arc::Tab;
		return true;
	}
	if (ch == 127) {
		event.code = Arc::Backspace;
		return true;
	}

	return false;
}

void Arc::Ncurses::createWindow(int width, int height, const std::string& title)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	
	mousemask(BUTTON1_CLICKED | BUTTON3_CLICKED, NULL);
	
	if (has_colors()) {
		start_color();
		use_default_colors();
		init_pair(1, COLOR_CYAN, -1);
		init_pair(2, COLOR_YELLOW, -1);
		init_pair(3, COLOR_WHITE, -1);
	}
}

void Arc::Ncurses::clear()
{
	erase();
	refresh();
}

extern "C" {
	Arc::IRenderer* entryPoint([[maybe_unused]] std::map<std::string, Arc::Item>& itemList)
	{
		return new Arc::Ncurses();
	}
	
	int getLibraryType() {
		return static_cast<int>(Arc::LibraryType::Renderer); 
	}

	std::string getName() {
		return "Ncurses";
	}
}