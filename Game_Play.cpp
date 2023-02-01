#include "Game_Play.h"
HANDLE Console1 = GetStdHandle(STD_OUTPUT_HANDLE);
Game_Play::Game_Play() : Position_Cordinates({ 0,0 }), Collsion(0), GamePLay_Difficulty(90000) {}
void Game_Play::set_Position_COORDS(int x, int y) { Position_Cordinates.X = x;		Position_Cordinates.Y = y; }
bool Game_Play::get_Collision_Status() const { return Collsion; }
COORD Game_Play::get_Player_Position() const { return Position_Cordinates; }
int Game_Play::getPosition_X() const { return Position_Cordinates.X; }
int Game_Play::getPosition_Y() const { return Position_Cordinates.Y; }
void Game_Play::setPosition_Y(int Y) { Position_Cordinates.Y = Y; }
void Game_Play::Update_Position_X(int x) { Position_Cordinates.X = x; }
void Game_Play::Update_Position_Y(int y) { Position_Cordinates.Y = y; }
void Game_Play::Erase_Car()
{
	COORD X_and_Y;
	SetConsoleCursorPosition(Console1, Position_Cordinates);
	X_and_Y.X = Position_Cordinates.X;
	X_and_Y.Y = Position_Cordinates.Y + 1;
	SetConsoleCursorPosition(Console1, X_and_Y);
	for (int loop_iterator = 0; loop_iterator < 25; loop_iterator++)
	{
		if (loop_iterator % 5 == 0)
		{
			SetConsoleCursorPosition(Console1, X_and_Y);
			X_and_Y.Y++;
		}
		cout << " ";
	}
}
int Game_Play::get_Car_width() const { return Game_Car.get_Car_Width(); }
void Game_Play::set_Difficulty(int Difficulty) { GamePLay_Difficulty = Difficulty; }
int Game_Play::get_Difficulty() const { return GamePLay_Difficulty; }