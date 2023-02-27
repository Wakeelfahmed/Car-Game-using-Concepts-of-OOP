#pragma once
#include<iostream>
#include<Windows.h>
#include"Shop.h"
using namespace std;
class Game_Play
{
protected:
	Car Game_Car;
	short GamePLay_Difficulty;
	bool Collsion;
	COORD Position_Cordinates;
public:
	Game_Play();
	void set_Position_COORDS(short x, short y);
	bool get_Collision_Status() const;
	COORD get_Player_Position() const;
	short getPosition_X() const;
	short getPosition_Y() const;
	void setPosition_Y(short Y);
	void Update_Position_X(short x);
	void Update_Position_Y(short y);
	virtual void Draw_Car() = 0;
	void Erase_Car();
	short get_Car_width() const;
	void set_Difficulty(short Difficulty);
	short get_Difficulty() const;
};


