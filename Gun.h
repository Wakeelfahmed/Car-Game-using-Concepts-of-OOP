#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
//#include""
//class Gun {
//protected:
//	int Bullet_color = 9;
//	string bullet = "\x18";
//	COORD Bullet_Position;
//	bool Active_Bullet_Status;
//	bool Bullet_Collision_wh_Enemy_car_status;
//public:
//	static int Gun_Maganize;
//	static int Number_of_Active_Bullets;
//	static int Maganize_Counter;
//	static bool Maganize_Reload[10];
//	Gun()
//	{
//		Maganize_Counter = 0;
//		Number_of_Active_Bullets = 0;
//		bullet = "\x18";
//		Active_Bullet_Status = 1;
//		Bullet_Collision_wh_Enemy_car_status = 0;
//		Gun_Maganize = 5;
//		//for (loop_iterator = 0; loop_iterator < 3; loop_iterator++)
//		//{
//		//	Maganize_Reload[loop_iterator];
//		//}
//	}		//Check this
//	static void update_Gun_Maganize(int newMaganize) { Gun_Maganize = newMaganize; }
//	static int get_Gun_Maganize() { return  Gun_Maganize; }
//	void Fire_Bullet(Player_GamePlay Player, int Signal)
//	{
//		Maganize_Counter++;
//		cout << "\a";
//		Active_Bullet_Status = 1;
//		Number_of_Active_Bullets++;
//		Bullet_Position = Player.get_Player_Position();
//		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 1)
//		{
//			if (Player.get_Car_width() == 3) {
//				Bullet_Position.X += 1;
//			}
//			if (Player.get_Car_width() == 4) {
//			}
//		}
//		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 2)
//			Bullet_Position.X += 3;
//
//		if (Player.get_items_Availabe_fr_Driv(0) && Player.get_items_Availabe_fr_Driv(2) == false)
//			Bullet_Position.X += 2;
//		SetConsoleTextAttribute(Console, Bullet_color);
//		SetConsoleCursorPosition(Console, Bullet_Position);
//		cout << "\x18";
//		//cout << bullet;
//	}
//	void Move_Bullet(Gun bullets[])
//	{
//		if (!(Bullet_Position.Y < 2))
//		{
//			bullet = "\x18";
//			Bullet_Position.Y--;
//			SetConsoleTextAttribute(Console, Bullet_color);
//			SetConsoleCursorPosition(Console, Bullet_Position);
//			cout << bullet;
//			SetConsoleCursorPosition(Console, { Bullet_Position.X, short(Bullet_Position.Y + 1) });
//			cout << " ";
//		}
//		if ((Bullet_Position.Y < 2))
//		{
//			SetConsoleCursorPosition(Console, { Bullet_Position.X, short((Bullet_Position.Y)) });
//			cout << " ";
//			Active_Bullet_Status = 0;
//		}
//	}
//	COORD get_Bullet_Position() const { return Bullet_Position; }
//	int get_Bullet_Position_Y() const { return Bullet_Position.Y; }
//	int get_Bullet_Position_X() const { return Bullet_Position.X; }
//	bool get_Active_Bullet_Status() const { return Active_Bullet_Status; }
//	void set_Bullet_Collision_wh_Enemy_car_status(bool truefalse) { Bullet_Collision_wh_Enemy_car_status = truefalse; }
//	bool get_Bullet_Collision_wh_Enemy_car_status() const { return Bullet_Collision_wh_Enemy_car_status; }
//	static void Jamm_Gun_till_reload() {
//		SetConsoleCursorPosition(Console, { 34,28 });
//		SetConsoleTextAttribute(Console, 9);
//		cout << Maganize_Counter << " / " << Gun::Gun_Maganize << " ";
//		if ((Maganize_Reload[0] == false))
//		{
//			Maganize_Reload[0] = true;
//			return;
//		}
//		if ((Maganize_Reload[1] == false && Maganize_Reload[0] == true))
//		{
//			Maganize_Reload[1] = true;
//			return;
//		}
//		if (Maganize_Reload[2] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true)
//		{
//			Maganize_Reload[2] = true;
//			return;
//		}
//		if (Maganize_Reload[3] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true)
//		{
//			Maganize_Reload[3] = true;
//			return;
//		}
//		if (Maganize_Reload[4] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true && Maganize_Reload[3] == true)
//		{
//			Maganize_Reload[4] = true;
//			Gun::Maganize_Counter = 0;
//			SetConsoleTextAttribute(Console, 9);
//			SetConsoleCursorPosition(Console, { 42,28 });
//			cout << "     Fire     ";
//			return;
//		}
//	}
//	static bool get_Maganize_Reload(int index) { return Maganize_Reload[index]; }
//	~Gun() {
//		bullet = "\x18";
//		Bullet_Position = { 0 ,0 };
//		Active_Bullet_Status = 0;
//		if (Number_of_Active_Bullets != 0)
//			Number_of_Active_Bullets--;
//	}
//};
//int Gun::Gun_Maganize = 5;
//int Gun::Number_of_Active_Bullets = 0; // static initialization
//int Gun::Maganize_Counter = 0; // static initialization
//bool Gun::Maganize_Reload[10] = { true };

