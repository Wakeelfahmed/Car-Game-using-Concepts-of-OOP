#pragma once
#include<iostream>
#include<Windows.h>
#include"Shop.h"
using namespace std;
class Game_Play
{
protected:
	Car Game_Car;
	int GamePLay_Difficulty;
	bool Collsion;
	COORD Position_Cordinates;
public:
	Game_Play();
	void set_Position_COORDS(int x, int y);
	bool get_Collision_Status() const;
	COORD get_Player_Position() const;
	int getPosition_X() const;
	int getPosition_Y() const;
	void setPosition_Y(int Y);
	void Update_Position_X(int x);
	void Update_Position_Y(int y);
	virtual void Draw_Car() = 0;
	void Erase_Car();
	int get_Car_width() const;
	void set_Difficulty(int Difficulty);
	int get_Difficulty() const;
};


