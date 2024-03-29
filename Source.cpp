﻿#include<iostream>
#include<fstream>
#include<conio.h>
#include<ctime>
#include<string>
#include<thread>
#include"Game_Play.h"
#include"List/list.h"
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
using namespace std;
COORD UI_NEW, UI_OLD;
bool Reponsive_UI_PauseResume = 0, Reponsive_UI_Thread_Running = 0, RESPONSIVE_THREADING = 1;
CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
short loop_iterator = 0;
void hidecursor()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(Console, &info);
}
class SUPERADMIN {
private:
	short Password; //To Allow ADMIN TO ACCESS Special Features.
	COORD Coins;
	COORD Score;
	COORD High_Score;
	COORD Lives;
	//COORD Coins_Responisve;

public:
	SUPERADMIN() {
		Password = 1234;
		Coins = { 100,6 };
		Score = { 87,10 };
		High_Score = { 80, 7 };
		Lives = { 103 , 4 };
		//Coins_Responisve = {UI_NEW.X }
	}
	COORD Coins_Settings() const { return Coins; }
	COORD High_Score_Settings() const { return High_Score; }
	COORD Lives_Setting()const { return Lives; };
};
void get_console_sz_THREAD()
{
	//cout << "CALLED";
	//for (short i = 0; i < 1000000; i++) {}
	while (RESPONSIVE_THREADING)
		while (Reponsive_UI_Thread_Running)
		{
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			UI_OLD = UI_NEW;
			UI_NEW.Y = csbi.srWindow.Bottom - csbi.srWindow.Top; //y  vertical
			UI_NEW.X = csbi.srWindow.Right - csbi.srWindow.Left;   //x hori
			if (UI_NEW.X != UI_OLD.X || UI_NEW.Y != UI_OLD.Y)
				system("CLS");
		}
}
void Print_Center_Aligned(string Message, short Horizontal_Sc_height, short Text_color) {
	short Message_Newlegth = short(Message.size());
	short Correction = 0;
	short Message_legth_Correction = short(Message.size());
	if (Message.size() % 2 == 1) {
		Correction++;
		Message_legth_Correction = short((Message.size() / 2));
	}
	else {
		Correction++;//cout << "here";
		Message_legth_Correction = short((Message.size() / 2) - 1);  //org -1    // Center Align
		if (UI_NEW.X % 2 == 1)
		{
			Message_legth_Correction += 1;
		}
	}
	SetConsoleCursorPosition(Console, { short(UI_NEW.X / 2 - Message_legth_Correction + Correction) , Horizontal_Sc_height });
	SetConsoleTextAttribute(Console, Text_color);
	cout << Message;	//if (UI_NEW.X % 2 == 1)		cout << "jkfsd";
	//if (Message.size() % 2 == 0)		//cout << "here";	
}
class Driver
{
private:
	char Driver_Name[50] = "";			int High_score{ 0 };		int Coins{ 4000 };
	bool Items_Owned_Check[10]{ false };	Car Car_Owned[10];
	bool isActive{ false };
public:
	static short No_of_Player_Profiles;

	bool get_IsActive_Status() const { return isActive; }
	short static get_No_of_Player_Profiles() { return No_of_Player_Profiles; }
	void static Increment_No_of_Profiles() { No_of_Player_Profiles++; }
	static void reset_Number_ofProfiles() { No_of_Player_Profiles = -1; }
	void set_Player_Name() { isActive = true;  Print_Center_Aligned("Enter Name: ", 7, 15); cin.getline(Driver_Name, 50, '\n'); /*cout << "Enter Name: "; */ }
	char* get_Driver_Name() { return Driver_Name; }
	void Buy_Item(short Item_Index) { Items_Owned_Check[Item_Index] = true; }
	void update_high_Score(int new_high_score) { High_score = High_score + (new_high_score - High_score); }
	int get_high_score() const { return High_score; }
	void set_Player_Has_Car(short Car_Number, bool TrueFalse) {
		if (!TrueFalse)
			Car_Owned[Car_Number].Car_Shape[0] = '\0';
	}
	bool check_if_Player_has_item(short item_Index) const { return Items_Owned_Check[item_Index]; }
	bool check_if_Player_has_Car(short item_Index) const {
		if (Car_Owned[item_Index].Car_Shape[0] == '\0')
			return 0;
		return 1;
	}
	void Buy_Car(Car New_Car, short Car_Number) { Car_Owned[Car_Number] = New_Car; }
	void set_Car_Color(short Color, short Car_Number) { Car_Owned[Car_Number].set_Car_Color(Color); }
	short get_Car_width(short index) const { return Car_Owned[index].get_Car_Width(); }
	short get_Car_Color(short Car_Number) const { return Car_Owned[Car_Number].get_Car_Color(); }
	Car get_Player_Car(short Car_Number) const { return Car_Owned[Car_Number]; }
	short get_Number_of_Cars_Owned() const
	{
		short Counter = 0;
		for (loop_iterator = 0; loop_iterator < 10; loop_iterator++)
			if (Car_Owned[loop_iterator].Car_Shape[0] != '\0')
				Counter++;
		return Counter;
	}
	void Give_Coins() { Coins += 1; }
	int get_Coins() const { return Coins; }
	void operator-(int Coins_to_Deduce) { Coins -= Coins_to_Deduce; }
	void operator+ (int AddCoins) { Coins += AddCoins; }
	~Driver()
	{
		Coins = 4000;				isActive = 0;
		if (!(No_of_Player_Profiles <= -1))
			No_of_Player_Profiles--;
		strcpy_s(Driver_Name, "");
		High_score = 0;
		for (loop_iterator = 0; loop_iterator < 10; loop_iterator++) {
			Items_Owned_Check[loop_iterator] = false;
			//Cars_Owned_Check[loop_iterator] = false;
			Car_Owned[loop_iterator].~Car();
		}
	}
};
short Driver::No_of_Player_Profiles = -1;
class Player_GamePlay : public Game_Play	//Player car
{
private:
	Driver Driver_of_Car;
	int Score;
	short Lives;
public:
	Player_GamePlay() { Position_Cordinates = { 45,21 };	Score = 0;		Lives = 3; }
	void set_Driver_of_Car(Driver DriverofCar) { Driver_of_Car = DriverofCar; }
	void Set_Player_Car(Car New_Car) { Game_Car = New_Car; }
	void Draw_Car() //PLAYER Car Drawer
	{
		char Car[25];
		strcpy_s(Car, Game_Car.get_Car_Shape());
		COORD new_Position;
		new_Position.X = Position_Cordinates.X;
		new_Position.Y = Position_Cordinates.Y;
		SetConsoleTextAttribute(Console, Game_Car.get_Car_Color()); //Car Owned Color
		for (loop_iterator = 0; loop_iterator <= (4 * Game_Car.get_Car_Height()); loop_iterator++)			//		for (loop_iterator = 0; loop_iterator < car.size(); loop_iterator++)
		{
			if (loop_iterator % 4 == 0)
			{
				new_Position.Y++;
				SetConsoleCursorPosition(Console, new_Position);
			}
			cout << Car[loop_iterator];
		}
	}
	void Move_Player_Car(char UserInput) {
		if (UserInput == 'a' || UserInput == 'A' || UserInput == 75)//left
		{
			if (!(getPosition_X() < 3))
			{
				Erase_Car();
				Update_Position_X(getPosition_X() - 4);
				Draw_Car();
			}
		}
		else if (UserInput == 'd' || UserInput == 'D' || UserInput == 77)//right
		{
			if (!(getPosition_X() > (WIN_WIDTH))) {
				Erase_Car();
				Update_Position_X(getPosition_X() + 4);
				Draw_Car();
			}
		}
		else if (UserInput == 'w' || UserInput == 'W' || UserInput == 72)//Up
		{
			if (!(getPosition_Y() < 4))
			{
				Erase_Car();
				Update_Position_Y(getPosition_Y() - 4);
				Draw_Car();
			}
		}
		else if (UserInput == 's' || UserInput == 'S' || UserInput == 80)//down
		{
			if (!(getPosition_Y() > (SCREEN_HEIGHT - 8)))
			{
				Erase_Car();
				Update_Position_Y(getPosition_Y() + 4);
				Draw_Car();
			}
		}
	}
	bool get_items_Availabe_fr_Driv(short Index) const {
		return Driver_of_Car.check_if_Player_has_item(Index);
	}
	void display_Score() const {
		COORD Score_Position = { 83,4 };
		SetConsoleTextAttribute(Console, 14);
		SetConsoleCursorPosition(Console, Score_Position);
		cout << "Score:" << Score;
	}
	void reset_Score() { Score = 0; }
	int get_score() const { return Score; }
	short get_Lives() const { return Lives; }
	void Display_Lives(COORD Lives_Setting) const {
		SetConsoleCursorPosition(Console, { Lives_Setting.X,short(Lives_Setting.Y - 1) });
		SetConsoleTextAttribute(Console, 13);
		cout << "Lives";
		for (loop_iterator = 0; loop_iterator < Lives; loop_iterator++)
		{
			SetConsoleCursorPosition(Console, Lives_Setting);
			cout << char(3) << "  ";
			Lives_Setting.X += 2;
		}
	}
	void Reset_Lives() { Lives = 3; }
	void operator--() { if (!(Lives <= 0))Lives--; }
	void operator++() { Score++; }
};
class Gun {
private:
	short Bullet_color = 9;
	string bullet = "\x18";
	COORD Bullet_Position;
public:
	static short Gun_Maganize;
	static short Maganize_Counter;
	static bool Maganize_Reload[10];
	Gun()
	{
		bullet = "\x18";
		//Gun_Maganize = 5;
	}
	static void update_Gun_Maganize(short newMaganize) { Gun_Maganize = newMaganize; }
	static short get_Gun_Maganize() { return  Gun_Maganize; }
	void Fire_Bullet(Player_GamePlay Player, short Signal)
	{
		Maganize_Counter++;
		Bullet_Position = Player.get_Player_Position();
		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 1)
		{
			if (Player.get_Car_width() == 3) {
				Bullet_Position.X += 1;
			}
		}
		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 2)
			Bullet_Position.X += 3;

		if (Player.get_items_Availabe_fr_Driv(0) && Player.get_items_Availabe_fr_Driv(2) == false)
			Bullet_Position.X += 2;
		SetConsoleTextAttribute(Console, Bullet_color);
		SetConsoleCursorPosition(Console, Bullet_Position);
		cout << "\x18";
		//cout << bullet;
	}
	bool Move_Bullet() //signal 1 to destory bullet i.e it has passed the entire screen
	{
		if (!(Bullet_Position.Y < 2))
		{
			bullet = "\x18";
			Bullet_Position.Y--;
			SetConsoleTextAttribute(Console, Bullet_color);
			SetConsoleCursorPosition(Console, Bullet_Position);
			cout << bullet;
			SetConsoleCursorPosition(Console, { Bullet_Position.X, short(Bullet_Position.Y + 1) });
			cout << " ";
			return 0;
		}
		//if ((Bullet_Position.Y < 2))
		//{
		SetConsoleCursorPosition(Console, { Bullet_Position.X, short((Bullet_Position.Y)) });
		cout << " ";
		//}
		return 1;
	}
	COORD get_Bullet_Position() const { return Bullet_Position; }
	short get_Bullet_Position_Y() const { return Bullet_Position.Y; }
	void set_Bullet_Position_Y(short Y) { Bullet_Position.Y = Y; }
	short get_Bullet_Position_X() const { return Bullet_Position.X; }
	static void Jamm_Gun_till_reload() {
		SetConsoleCursorPosition(Console, { 34,28 });
		SetConsoleTextAttribute(Console, 9);
		cout << Maganize_Counter << " / " << Gun::Gun_Maganize << " ";
		if ((Maganize_Reload[0] == false))
		{
			Maganize_Reload[0] = true;
			return;
		}
		if ((Maganize_Reload[1] == false && Maganize_Reload[0] == true))
		{
			Maganize_Reload[1] = true;
			return;
		}
		if (Maganize_Reload[2] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true)
		{
			Maganize_Reload[2] = true;
			return;
		}
		if (Maganize_Reload[3] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true)
		{
			Maganize_Reload[3] = true;
			return;
		}
		if (Maganize_Reload[4] == false
			&& Maganize_Reload[0] == true
			&& Maganize_Reload[1] == true
			&& Maganize_Reload[2] == true
			&& Maganize_Reload[3] == true)
		{
			Maganize_Reload[4] = true;
			Gun::Maganize_Counter = 0;
			SetConsoleTextAttribute(Console, 9);
			SetConsoleCursorPosition(Console, { 42,28 });
			cout << "     Fire     ";
			return;
		}
	}
	static bool get_Maganize_Reload(short index) { return Maganize_Reload[index]; }
	bool operator==(const Gun Gun2) const { return (Bullet_Position.X == Gun2.Bullet_Position.X && Bullet_Position.Y == Gun2.Bullet_Position.Y); }
	~Gun() {
		bullet = "\x18";
		Bullet_Position = { 0 ,0 };
		Bullet_color = 9;
	}
};
short Gun::Gun_Maganize = 5;
short Gun::Maganize_Counter = 0; // static initialization
bool Gun::Maganize_Reload[10] = { true };
class Enemy_car : public Game_Play		//***** Enemy Car *****//
{
private:
	bool Enemy_car_Active;
public:
	Enemy_car() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.Y = 4;	//Starting point of Enemy
		Game_Car.set_Car_Color(12);
		char Car[25] = " -- *±±*±±±±*±±* vv ";
		Game_Car.set_Car_Shape(Car);
	}
	short generate_Enemy_X_coordinate() { return 0 + (rand() % WIN_WIDTH + 2); }
	void resetEnemy() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.Y = 4;
	}
	bool get_Enemy_Alive_Status() const { return Enemy_car_Active; }
	void Draw_Car(Player_GamePlay& Player_GamePlay) //Enemy Car 
	{
		if (get_Collision_Status())
			return;
		COORD new_Position = { 0,0 }; //bullet_Position;
		{
			if (!(Position_Cordinates.Y > SCREEN_HEIGHT + 2) && !get_Collision_Status())
			{
				char car[25];
				strcpy_s(car, Game_Car.get_Car_Shape());
				Position_Cordinates.Y++;
				SetConsoleCursorPosition(Console, Position_Cordinates);
				short count = 0;
				new_Position = Position_Cordinates;
				short counter = 0;
				for (loop_iterator = 19; loop_iterator >= 0; loop_iterator--)
				{
					counter++;
					if (counter == 5)
					{
						counter = 1;
						new_Position.Y--;
						SetConsoleCursorPosition(Console, new_Position);
					}
					SetConsoleTextAttribute(Console, Game_Car.get_Car_Color());
					if (!(new_Position.Y > SCREEN_HEIGHT - 2)) {
						cout << car[loop_iterator];
					}
				}
				if (new_Position.Y > SCREEN_HEIGHT - 2)
				{
					Enemy_car_Active = 0;
					++Player_GamePlay;
					Player_GamePlay.display_Score();
				}
				EraseEnemyTrail();
				if (new_Position.Y > SCREEN_HEIGHT - 2)
					resetEnemy();
			}
			else
				return;
		}
	}
	void Draw_Car() {}
	void EraseEnemyTrail() const {
		COORD Old_Position;
		Old_Position.X = Position_Cordinates.X;
		Old_Position.Y = (Position_Cordinates.Y - 5);
		SetConsoleCursorPosition(Console, Old_Position);
		cout << "    ";
	}
	void update_Collision_Status(bool new_Collision) { Collsion = new_Collision; }
	~Enemy_car() {
		Enemy_car_Active = 1;
		//car = " ";
		Position_Cordinates = { 0, 4 };
	}
};
void Validate_Input(short start, short& Input, short end) {
	while (Input < start || Input > end)
		Input = _getch() - '0';
}
bool Gun_jammed_Status() {
	short Counter = 0;
	for (loop_iterator = 0; loop_iterator < 3; loop_iterator++) {
		if (Gun::get_Maganize_Reload(loop_iterator) == true)
			Counter++;
	}
	if (Counter == 3)
		return true;		//cout << "  FIRE!!  ";

	//cout << "  !NO FIRE  ";
	return false;
}
void Print_Car_Char_Array(Car_Shop Cars[], COORD& position, short loop_iterator, bool signal, short Color) {
	SetConsoleCursorPosition(Console, { short(position.X - 3), short(position.Y + 2) });
	SetConsoleTextAttribute(Console, 15);//White - 15
	cout << loop_iterator << ". ";
	short yincrease = position.Y;
	char* car = Cars[loop_iterator].get_Car_Shape();	//	" ^^ [±±] ±± [±±] -- ";  " ^^ \n[±±]\n ±± \n[±±]\n -- "
	SetConsoleCursorPosition(Console, { position.X,position.Y });
	SetConsoleTextAttribute(Console, Color);
	for (short j = 0; j < strlen(car); j++)
	{
		if (j % (4) == 0)
			SetConsoleCursorPosition(Console, { position.X,short(yincrease++) });
		cout << car[j];
	}
	if (signal) {
		SetConsoleTextAttribute(Console, 15);
		SetConsoleCursorPosition(Console, { short(position.X - 2),short(position.Y + 5) });
		cout << "Price " << Cars[loop_iterator].get_price();
	}
	position.X += 13; //position.Y -= 4;
}
void get_console_size()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	UI_OLD = UI_NEW;
	UI_NEW.Y = csbi.srWindow.Bottom - csbi.srWindow.Top; //y  vertical
	UI_NEW.X = csbi.srWindow.Right - csbi.srWindow.Left;   //x hori
	if (UI_NEW.X != UI_OLD.X || UI_NEW.Y != UI_OLD.Y) {
		//cout << "Clearing";
		//for (loop_iterator = 0; loop_iterator < 90000000; loop_iterator++) {}
		system("CLS");
	}
}
string Reference_Message = "1. Career / Profile";
void Validate_Input_on_Kbhit(short start, short& Input, short end) {
	if (Input < start || Input > end)
		if (_kbhit())
			Input = _getch() - '0';
}
void Print_GamePlay_Instructions(Player_GamePlay Player, bool signal) {
	short positionX, positionY;
	if (signal) { // game Play instructions
		SetConsoleTextAttribute(Console, 14);
		positionX = 100;	positionY = 8;
	}
	else {	//3. View Instructions
		string message = "Instruction:";
		short Message_legth_Correction;
		if (message.size() % 2 == 1)
			Message_legth_Correction = short((message.size() / 2));
		else
			Message_legth_Correction = short((message.size() / 2) - 1);
		SetConsoleTextAttribute(Console, 15);
		positionX = UI_NEW.X / 2 - Message_legth_Correction;	positionY = 7;	//positionX = 58; //positionX = UI_NEW.X / 2 - 4; good to go
	}
	//Print_Center_Aligned("Instruction:", positionY++);
	SetConsoleCursorPosition(Console, { short(positionX - 1),positionY++ });
	cout << "Instruction:";
	//SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "Instruction:";
	//SetConsoleCursorPosition(Console, { short(positionX - 1),positionY++ });		cout << "Instruction:";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'A\' - Left";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'D\' - Right";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'W\' - Up";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'S\' - Down";
	SetConsoleCursorPosition(Console, { short(positionX - 3),positionY++ });		cout << "\'P\' - Pause\\Resume Game";
	if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2) || !(signal)) {
		SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'R\' - Reload";
		SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "Space - Fire";
	}
	SetConsoleCursorPosition(Console, { short(positionX - 2),positionY++ });		cout << "Q - Quit Gameplay";
}
void Print_Game_Instructions(Player_GamePlay Player) {
	short positionX, positionY;
	//3. View Instructions
	string message = "Instruction:";
	short Message_legth_Correction;
	if (message.size() % 2 == 1)
		Message_legth_Correction = short((message.size() / 2));
	else
		Message_legth_Correction = short((message.size() / 2) - 1);
	SetConsoleTextAttribute(Console, 15);
	positionX = UI_NEW.X / 2 - Message_legth_Correction;	positionY = 7;	//positionX = 58; //positionX = UI_NEW.X / 2 - 4; good to go

	//	while (Reponsive_UI_PauseResume) {}

	//Print_Center_Aligned("Instruction:",positionY++);
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "Instruction:";
	//SetConsoleCursorPosition(Console, { short(positionX - 1),positionY++ });		cout << "Instruction:";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'A\' - Left";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'D\' - Right";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'W\' - Up";
	SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'S\' - Down";
	SetConsoleCursorPosition(Console, { short(positionX - 3),positionY++ });		cout << "\'P\' - Pause\\Resume Game";
	if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2) || 1) {
		SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "\'R\' - Reload";
		SetConsoleCursorPosition(Console, { positionX,positionY++ });		cout << "Space - Fire";
	}
	SetConsoleCursorPosition(Console, { short(positionX - 2),positionY++ });		cout << "Q - Quit Gameplay";
	//for (size_t loop_iterator = 0; loop_iterator < 900000000000; loop_iterator++)
	{

	}
}
void Print_Left_wh_refer_Message(string Message, short Horizontal, string wh_respect_to) {
	short correction = 0;
	short Message_legth_Correction = short(wh_respect_to.size());
	if (wh_respect_to.size() % 2 == 1) {
		correction++;
		Message_legth_Correction = short((wh_respect_to.size() / 2));
	}
	else {
		Message_legth_Correction = short((wh_respect_to.size() / 2) - 1);
		correction++;
	}
	SetConsoleCursorPosition(Console, { short(UI_NEW.X / 2 - Message_legth_Correction + correction) , Horizontal });
	cout << Message;
}
void Main_Menu(short& Input, Driver Player_profile[], short size)
{
	system("CLS");
	Player_profile->reset_Number_ofProfiles();
	for (loop_iterator = 0; loop_iterator < size; loop_iterator++)
		if (Player_profile[loop_iterator].get_IsActive_Status())
			Player_profile->Increment_No_of_Profiles();
	Reponsive_UI_PauseResume = 1;
	while (Reponsive_UI_PauseResume) {
		get_console_size();
		if (Driver::get_No_of_Player_Profiles() >= 0)
			Print_Center_Aligned("1. Career/Profile", 6, 15);//SetConsoleCursorPosition(Console, { 53,6 });
		else
			Print_Center_Aligned("1. Career/Profile", 6, 8);

		Print_Center_Aligned("2. Create Profile", 7, 15);	//SetConsoleCursorPosition(Console, { 53,7 });
		Reference_Message = "1. Career/Profile";
		Print_Left_wh_refer_Message("3. View Instructions", 8, "1. Career/Profile");
		Print_Left_wh_refer_Message("4. Exit App (Player Progress will be Saved)", 9, "1. Career/Profile");
		if (_kbhit()) {
			Input = _getch() - '0';
			if (Driver::get_No_of_Player_Profiles() <= -1) {
				if (Input >= 2 && Input <= 4)
					Reponsive_UI_PauseResume = 0;
			}
			else
				if (Input >= 1 && Input <= 4)
					Reponsive_UI_PauseResume = 0;
		}
	}
}
void PrintInterface(string Message, COORD ADMIN, short color, short Value) {
	SetConsoleTextAttribute(Console, color);
	SetConsoleCursorPosition(Console, ADMIN);
	cout << Message << " " << Value << " ";
}
void PrintInterface_Wh_Percentage(string Message, short Percentage, short Horizontal, short color, short Value) {
	string Interface_Message = Message + " " + to_string(Value);
	SetConsoleTextAttribute(Console, color);
	SetConsoleCursorPosition(Console, { short(UI_NEW.X * (Percentage) / 100 - Interface_Message.size() / 2),Horizontal });
	cout << Message << " " << Value << " ";
}
void Player_Profile_Menu(short& Input, SUPERADMIN ADMIN, Driver Player_profile, string Message) {
	system("CLS");
	while (1)
	{
		short position = 11;
		get_console_size();
		PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile.get_high_score());
		PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile.get_Coins());
		Print_Center_Aligned(Message, 5, 15); //Welcome Back  !
		Print_Center_Aligned("1. Select Car and Play", position++, 15);	//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("2. Buy Car", position++, 15);	//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("3. Display Owned Cars", position++, 15);	//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("4. Shop items", position++, 15);	//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("5. View Items in Inventory", position++, 15);	//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("6. Delete Profile", position++, 15);			//SetConsoleCursorPosition(Console, { 51,position++ });
		Print_Center_Aligned("7. Exit Profile", position++, 15);			//SetConsoleCursorPosition(Console, { 51,position++ });
		if (_kbhit()) {
			Input = _getch() - '0';
			if (Input >= 1 || Input <= 7)
				break;
		}
	}
}
void Shop_Items_ReadWrite_Menu(short& input) {
	cout << "Intentory Read() Wirte()\n0.View Exisiting Data\t1.Enter Data\t2.Write to File\t\n(any other key to leave)";
	input = _getch() - '0';
}
int main()
{
	//PlaySound(TEXT("mixkit-retro-video-game-bubble-laser-277.wav"), NULL, SND_ASYNC);	//cout << "played"; //	cout << "not played";
	HWND hWnd = GetConsoleWindow();		ShowWindow(hWnd, SW_SHOWMAXIMIZED);	//Make Console open in Maximized window.
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	UI_NEW.Y = csbi.srWindow.Bottom - csbi.srWindow.Top;	//y  vertical
	UI_NEW.X = csbi.srWindow.Right - csbi.srWindow.Left;   //x hori
	//Player_GamePlay Car1;
	SetConsoleTextAttribute(Console, 15);
	Items_Shop items[4];	/* ITEMS SHOP */	Car_Shop Cars_Shop[9]; /* CARS SHOP */
	{ifstream ifstream_ob;
	ifstream_ob.open("Items_Inventory.txt", ios::in);
	if (!ifstream_ob) {
		cout << "Error - Items_Inventory.txt Not Found !!\n"; _getch();
	}
	ifstream_ob.read((char*)&items, sizeof(items));
	ifstream_ob.close(); }
	{//items[0].set_Item_Name("Gun");		items[0].set_Item_Price(800);	items[1].set_Item_Name("Extended Maganize"); items[1].set_Item_Price(800);
	//items[2].set_Item_Name("Double Gun");	items[2].set_Item_Price(1500);	items[3].set_Item_Name("Quick Reload");	items[3].set_Item_Price(600);
	}
	//Shop_Items_ReadWrite_Menu(input);
	hidecursor();
	SUPERADMIN ADMIN;
	Reponsive_UI_PauseResume = 1;
	//while (input >= 0 && input < 3) /*ITEMS SHOP READ WRITE*/ {
	//	if (input == 0)
	//		for (loop_iterator = 0; loop_iterator < 3; loop_iterator++)
	//			items[loop_iterator].Print_Details();
	//	else if (input == 1)
	//		for (loop_iterator = 0; loop_iterator < 3; loop_iterator++)
	//			items[loop_iterator].User_Input();
	//	else if (input == 2)
	//	{
	//		ofstream ofstream_ob;
	//		ofstream_ob.open("Items_Inventory.txt", ios::out);
	//		ofstream_ob.write((char*)&items, sizeof(items));
	//		ofstream_ob.close();
	//	}	
//	Shop_Items_ReadWrite_Menu(input);
//}
	short y = 1;	short Profile_Selected, Car_Selected, Input[5], No_of_Enemies = 4;
	//list <Driver> Player_Profile_List;
	Driver Player_profile[4];

	//cout << "\nDo you want to Read Players Records\?\nPress 1 to Read (any other key to leave)";
	//y = _getch() - '0';	cout << "\a";
	if (y == 1 || 1)
	{
		ifstream ifstream_ob1;
		ifstream_ob1.open("Player Profiles.txt", ios::in);
		ifstream_ob1.read((char*)&Player_profile, sizeof(Player_profile));
		ifstream_ob1.close();
		for (loop_iterator = 0; loop_iterator < sizeof(Player_profile) / sizeof(Driver); loop_iterator++)
			if (Player_profile[loop_iterator].get_IsActive_Status())
				Player_profile->Increment_No_of_Profiles();
	}
	{
		Cars_Shop[0].set_Car_Shape(" ^^ *±±* ±± *±±* -- ");
		Cars_Shop[1].set_Car_Shape(" ^^ [±±] ±± [±±] -- ");	Cars_Shop[1].set_Car_Width(4);
		Cars_Shop[2].set_Car_Shape("  \xEF  \xC9\xCB\xbb \xCC\xCE\xB9 \xC8\xCA\xBC \xCF\xCF\xCF");	Cars_Shop[2].set_Car_Width(3);	Cars_Shop[2].set_Car_Height(5);
		Cars_Shop[3].set_Car_Shape(" ±± ±**± ** ±**±");										Cars_Shop[3].set_Car_Height(4);
		Cars_Shop[4].set_Car_Shape(" ** ±**± ** ±**±");										Cars_Shop[4].set_Car_Height(4);
		Cars_Shop[5].set_Car_Shape(" ^^ ±±±± ±± ±\xEF\xEF±");								Cars_Shop[5].set_Car_Height(4);
		Cars_Shop[6].set_Car_Shape(" 00 0**0 ** 0**0");										Cars_Shop[6].set_Car_Height(4);
		Cars_Shop[7].set_Car_Shape(" ^±^ ±±± *±* *±* ---");	Cars_Shop[7].set_Car_Width(3);	Cars_Shop[7].set_Car_Height(5);
		Cars_Shop[8].set_Car_Shape("  \36  |±| ±±± ---");	Cars_Shop[8].set_Car_Width(3);	Cars_Shop[8].set_Car_Height(4);
		Cars_Shop[0].set_Car_Color(1);		Cars_Shop[1].set_Car_Color(2);		Cars_Shop[2].set_Car_Color(3);
		Cars_Shop[3].set_Car_Color(14);		Cars_Shop[4].set_Car_Color(5);		Cars_Shop[5].set_Car_Color(6);
		Cars_Shop[6].set_Car_Color(7);		Cars_Shop[7].set_Car_Color(8);		Cars_Shop[8].set_Car_Color(9);
	}// Car's Shop
	short position1 = 7, position = 12;
	thread ReponsiveUI(get_console_sz_THREAD);
	Player_GamePlay Player;		//Player.set_Position_COORDS(20, 20);		//Player.Draw_Car();
	Main_Menu(Input[0], Player_profile, sizeof(Player_profile) / sizeof(Driver));
	//Driver Selected_Driver_1;// Selected_Driver_0
	while (Input[0] == 1 || Input[0] == 2 || Input[0] == 3)
	{
		short position2 = 7, position = 0;
		static char chcheck = 't';
		switch (Input[0])
		{
		case 1:	//Select Profile
		{
			system("CLS");
			static string message;
			while (1) {
				position = 10;
				get_console_size();
				Print_Center_Aligned("Select your Profile", 5, 15); 				//Select Profile
				for (loop_iterator = 0; loop_iterator <= Driver::get_No_of_Player_Profiles(); loop_iterator++) {
					if (Player_profile[loop_iterator].get_IsActive_Status()) {

						message = to_string(loop_iterator) + ". " + Player_profile[loop_iterator].get_Driver_Name();
						Print_Center_Aligned(message, position++, 15);	//cout << Player_profile[loop_iterator].get_Driver_Name(); // << loop_iterator << ". "
					}
				}
				if (_kbhit())
				{
					Profile_Selected = _getch() - '0';
					if (Profile_Selected >= 0 && Profile_Selected <= Driver::get_No_of_Player_Profiles())
						break;
				}
			}
			//Validate_Input(0, Profile_Selected, Driver::get_No_of_Player_Profiles());
			//Selected_Driver_0 = Player_profile[Profile_Selected];
			Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
			message = "Welcome back  !";
			//static string Player_Welcome_Message = "Welcome back  !";
			//Player_Welcome_Message = "Welcome back  !"; 
			message.insert(13, Player_profile[Profile_Selected].get_Driver_Name());
			Player_Profile_Menu(Input[1], ADMIN, Player_profile[Profile_Selected], message);
			while (Input[1] >= 1 || Input[1] <= 7)
			{
				if (Input[1] == 1)  //Select Car and Play
				{
					if (Player_profile[Profile_Selected].get_Number_of_Cars_Owned() == 0)
					{
						short loop_iterator = 0;
						Reponsive_UI_PauseResume = 1;
						system("CLS");
						while (Reponsive_UI_PauseResume)
						{
							get_console_size();
							//PrintInterface_Wh_Percentage("Coins", 87, 7, 14, Player_profile[Profile_Selected].get_Coins());
							PrintInterface("Coins", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
							//	PrintInterface("Coins", { short(UI_NEW.X * (87) / 100 - Coins_Message.size() / 2), 7 }, 14, Player_profile[Profile_Selected].get_Coins());
							PrintInterface("High Score", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
							//SetConsoleTextAttribute(Console, 15);
							Print_Center_Aligned("You don't have any Car", 8, 15); //Length 22
							Print_Center_Aligned("Buy Car first !!", 9, 15); //16			//SetConsoleCursorPosition(Console, { 50,short(position - 7) });
							//	for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
							if (loop_iterator == 900)
								Reponsive_UI_PauseResume = 0;
							//cout << loop_iterator;
							loop_iterator++;
						}
					}
					else
					{
						system("CLS");
						position = 5;
						Print_Center_Aligned("Select your Car", 4, 15);//SetConsoleCursorPosition(Console, { 55,4 });
						COORD Printing_Cords = { 33 ,7 };
						short Counter = 0;
						for (short loop_iterator = 0; loop_iterator < 10; loop_iterator++)
							if (Player_profile[Profile_Selected].check_if_Player_has_Car(loop_iterator))
							{
								if (Counter == 5) {
									Printing_Cords = { 33 ,14 };
								}
								Print_Car_Char_Array(Cars_Shop, Printing_Cords, loop_iterator, 0, Player_profile[Profile_Selected].get_Car_Color(loop_iterator));
								Counter++;
							}
						Car_Selected = _getch() - '0';
						while (!Player_profile[Profile_Selected].check_if_Player_has_Car(Car_Selected) || (Car_Selected < 0 || Car_Selected > 9))
						{
							cout << "Select Car from your owned Car list only";
							Car_Selected = _getch() - '0';
						}
						Player.Set_Player_Car(Player_profile[Profile_Selected].get_Player_Car(Car_Selected));
						system("CLS");
						Print_Center_Aligned("Select Difficulty", 4, 15);	//SetConsoleCursorPosition(Console, { 55,4 });
						Print_Center_Aligned("1. Easy", 6, 15);				//SetConsoleCursorPosition(Console, { 58,6 });	
						Print_Center_Aligned("2. Medium", 8, 15);			//SetConsoleCursorPosition(Console, { 58,8 });
						Print_Center_Aligned("3. Hard", 10, 15);			//SetConsoleCursorPosition(Console, { 58,10 });	
						Input[2] = _getch() - '0';
						Validate_Input(1, Input[2], 3);
						if (Input[2] == 1)								Player.set_Difficulty(25);		//Easy
						else if (Input[2] == 2) { No_of_Enemies = 5;	Player.set_Difficulty(15); } //Medium
						else if (Input[2] == 3) { No_of_Enemies = 6;	Player.set_Difficulty(5); } //Hard
						static char ch1;
						SetConsoleTextAttribute(Console, 15);
						SetConsoleCursorPosition(Console, { 15,22 });
						cout << "q - Cancel";
						cout << "\033[5m";
						Print_Center_Aligned("Press Spacebar To Start Game!", 19, 15);
						cout << "\033[0m";
						ch1 = _getch(); cout << "\a";
						//Player.reset_Score();
						short Score_Coins_Counter = 0;
						if (ch1 == 32)
						{
							Player.Reset_Lives();
							system("CLS");
							Player.Display_Lives((ADMIN.Lives_Setting()));
							PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
							SetConsoleTextAttribute(Console, 15);
							srand(unsigned int(time(0)));
							COORD Position;	Position.X = WIN_WIDTH;	Position.Y = SCREEN_HEIGHT;
							list <Gun> Bullets_list;
							position2 = 8;
							Enemy_car Enemy2[10];
							Player.Draw_Car();
							Player.display_Score();
							if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
							{
								Player_profile[Profile_Selected].update_high_Score(Player.get_score());
								Score_Coins_Counter++;
								if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
								{
									Player_profile[Profile_Selected].Give_Coins();
									Score_Coins_Counter = 0;
								}
							}
							PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
							Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
							Print_GamePlay_Instructions(Player, 1);
							bool Game_Running = true;
							static short Counter = 0;
							Counter = 0;
							while (ch1 != 'q' && Game_Running)
							{
								static short Maganize_Counter_Main = 0;
								string Coins_Message = "Coins " + to_string(Player_profile[Profile_Selected].get_Coins());
								PrintInterface("Coins", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
								//PrintInterface_Wh_Percentage("Coins", 87, 7, 14, Player_profile[Profile_Selected].get_Coins());
								//PrintInterface("Coins", { short(UI_NEW.X * (87) / 100 - Coins_Message.size() / 2), 7 }, 14, Player_profile[Profile_Selected].get_Coins());
								if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
								{
									//cout << "GIVING";
									Player_profile[Profile_Selected].Give_Coins();
									Score_Coins_Counter = 0;
								}
								if (Player.get_items_Availabe_fr_Driv(1)) { Gun::Gun_Maganize = 10; }
								if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2)) {
									//Gun::Maganize_Counter = Maganize_Counter_Main;
									Gun::Jamm_Gun_till_reload();
								}
								if (_kbhit()) {
									ch1 = _getch();
									if (ch1 == 'a' || ch1 == 'A' || ch1 == 75 || ch1 == 'd' || ch1 == 'D' || ch1 == 77 || ch1 == 'w' || ch1 == 'W' || ch1 == 72 || ch1 == 's' || ch1 == 'S' || ch1 == 80)
									{
										Player.Move_Player_Car(ch1);
										//ifch1 == 75 || ch1 == 77 || ch1 == 72 || ch1 == 80)
										//Player[1].Move_Player_Car(ch1);
									}
									else if (ch1 == 'r' || ch1 == 'R')	//Reload
									{
										SetConsoleCursorPosition(Console, { 44,28 });
										cout << "RELOADING!!!";
										for (loop_iterator = 0; loop_iterator < 5; loop_iterator++)
											Gun::Maganize_Reload[loop_iterator] = false;
									}
									else if (ch1 == 32 && Player.get_items_Availabe_fr_Driv(0) && Gun_jammed_Status() || ch1 == 32 && Player.get_items_Availabe_fr_Driv(2) && Gun_jammed_Status())
									{
										//Maganize_Counter_Main++;
										Bullets_list.insert_end({});
										Bullets_list.get_Node_by_Pos(Bullets_list.Number_of_Nodes())->Data.Fire_Bullet(Player, 1);
										//Gun::Maganize_Counter = Maganize_Counter_Main;
										if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
										{
											SetConsoleCursorPosition(Console, { 44,28 });
											cout << "RELOADING!!!";
											for (loop_iterator = 0; loop_iterator < 5; loop_iterator++)
												Gun::Maganize_Reload[loop_iterator] = false;
										}
										if (Player.get_items_Availabe_fr_Driv(2)) {
											//Maganize_Counter_Main++;
											Bullets_list.insert_end({});
											Bullets_list.get_Node_by_Pos(Bullets_list.Number_of_Nodes())->Data.Fire_Bullet(Player, 2);
											//Gun::Maganize_Counter = Maganize_Counter_Main;
											if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
											{
												SetConsoleCursorPosition(Console, { 42,28 });
												cout << "RELOADING!!!";
												for (loop_iterator = 0; loop_iterator < 5; loop_iterator++)
													Gun::Maganize_Reload[loop_iterator] = false;
											}
										}
									}
									else if (ch1 == 'p' || ch1 == 'P') {
										while (chcheck != 'p')
											chcheck = _getch();
										chcheck = 't';
									}
									else if (ch1 == 'q')
										break;

								}
								for (short enemy_loop = 0; enemy_loop < No_of_Enemies; enemy_loop++)
								{
									if (!Enemy2[enemy_loop].get_Collision_Status())
									{
										Enemy2[enemy_loop].Draw_Car(Player);
										if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
										{
											Player_profile[Profile_Selected].update_high_Score(Player.get_score());
											Score_Coins_Counter++;
											if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
											{
												Player_profile[Profile_Selected].Give_Coins();
												Score_Coins_Counter = 0;
											}
										}
										PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
										COORD Position_Cordinates_enemy = Enemy2[enemy_loop].get_Player_Position(); // Enemy CAR Position
										COORD Player_Position = Player.get_Player_Position();
										if ((Position_Cordinates_enemy.Y - 1) >= Player_Position.Y && (Position_Cordinates_enemy.Y - 11) <= Player_Position.Y)//(//Position_Cordinates.Y - 1) == Player_Position.Y 
										{
											if (Position_Cordinates_enemy.X == Player_Position.X
												|| Position_Cordinates_enemy.X + 1 == Player_Position.X	 //player right by one, enemy left(pos).
												|| Position_Cordinates_enemy.X + 2 == Player_Position.X	 //player right by two, enemy left(pos).
												|| Player.get_Car_width() == 4 && Position_Cordinates_enemy.X + 3 == Player_Position.X //(pos)player right ,enemy left.   player most left collision with enemy most right(disable in thinner car)
												|| Position_Cordinates_enemy.X - 3 == Player_Position.X	 //(pos)player left ,enemy right.   player most right collision with enemy most left
												|| Position_Cordinates_enemy.X - 2 == Player_Position.X	 // player left by two, enemy right(pos).
												|| Position_Cordinates_enemy.X - 1 == Player_Position.X)	// player left by one, enemy right(pos).			
											{
												// COLLISION DETECTION !!!
												--Player;
												Player.Display_Lives((ADMIN.Lives_Setting()));
												if (Player.get_Lives() == 0) {
													system("CLS");
													Print_Center_Aligned("-----------", 9, 10);
													Print_Center_Aligned("GAME OVER", 10, 10);
													Print_Center_Aligned("-----------", 11, 10);
													message = "Score:" + to_string(Player.get_score());
													Print_Center_Aligned(message, 12, 10);
													//cout << "\b\b" << Player.get_score();
													Print_Center_Aligned("0. Restart\t\t\t               ", 14, 10);
													Print_Center_Aligned("\t\t\tPress any key to Continue", 14, 10);
													static short INPUTGAMEPLAY = 12;
													//USE SLEEP
													Sleep(1000);
													//for (loop_iterator = 0; loop_iterator < 100099999; loop_iterator++) {}
													INPUTGAMEPLAY = _getch() - '0';
													if (INPUTGAMEPLAY == 0) {
														system("CLS");
														Game_Running = true;
														Player.Reset_Lives();
														Player.reset_Score();
														Print_GamePlay_Instructions(Player, 1);
														Player.display_Score();
														Player.Display_Lives((ADMIN.Lives_Setting()));
														PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
														PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
													}
													else {
														system("CLS");
														Game_Running = false;
													}
												}
												Enemy2[enemy_loop].Update_Position_Y(Position_Cordinates_enemy.Y - 5);
												Enemy2[enemy_loop].Erase_Car();
												Player.Draw_Car();
												Enemy2[enemy_loop].resetEnemy(); //for checking
											}
										}
										else
											Enemy2[enemy_loop].update_Collision_Status(0);
										/*sinlge variable breaks the code*/
										//for (short loop_iterator = 0; loop_iterator < Gun::Number_of_Active_Bullets; loop_iterator++)
										for (short loop_iterator = 1; loop_iterator <= Bullets_list.Number_of_Nodes(); loop_iterator++)
										{
											if (Enemy2[enemy_loop].getPosition_Y() == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 1 == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 2 == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 3 == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 4 == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_Y())
											{
												if (Enemy2[enemy_loop].getPosition_X() == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_X()		//left most (1st col)
													|| (Enemy2[enemy_loop].getPosition_X() + 1) == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_X()	// 2nd column
													|| (Enemy2[enemy_loop].getPosition_X() + 2) == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_X()	//3rd col
													|| (Enemy2[enemy_loop].getPosition_X() + 3) == Bullets_list.get_Node_by_Pos(loop_iterator)->Data.get_Bullet_Position_X())	//4th col, right most
												{
													Enemy2[enemy_loop].Update_Position_Y(Position_Cordinates_enemy.Y - 5);
													Enemy2[enemy_loop].Erase_Car();
													Enemy2[enemy_loop].resetEnemy();
													Bullets_list.delete_Node(Bullets_list.get_Node_by_Pos(loop_iterator)->Data);
													++Player;
													Player.display_Score();
													if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
													{
														Player_profile[Profile_Selected].update_high_Score(Player.get_score());
														Score_Coins_Counter++;
														if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
														{
															Player_profile[Profile_Selected].Give_Coins();
															Score_Coins_Counter = 0;
														}
													}
													PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
												}
											}
										}
									}
								}
								if (Bullets_list.Number_of_Nodes() >= 1) {
									Node<Gun>* Temp = Bullets_list.get_head();
									static Gun Temp1;
									do
									{
										if (Temp->Data.Move_Bullet()) {
											Temp1 = Temp->Data;
											Temp = Temp->next;
											Bullets_list.delete_Node(Temp1);
										}
										if (Bullets_list.isEmpty())
											break;
										Temp = Temp->next;
									} while (Temp != Bullets_list.get_head());
								}
								Sleep(Player.get_Difficulty());
							}
						}
					}
				}
				else if (Input[1] == 2) {	//Buy Car
					system("CLS");
					PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
					//PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
					SetConsoleTextAttribute(Console, 15);
					short position1 = 7;
					//COORD Printing_Cords = { 33 ,7 };
					COORD Printing_Cords = { UI_NEW.X / 2 - 27 ,7 };
					Print_Center_Aligned("BUY CAR", 5, 15);
					for (loop_iterator = 0; loop_iterator < 9; loop_iterator++)
					{
						if (loop_iterator == 5)
							Printing_Cords = { short(UI_NEW.X / 2 - 20) ,14 };
						Print_Car_Char_Array(Cars_Shop, Printing_Cords, loop_iterator, 1, Cars_Shop[loop_iterator].get_Car_Color());
					}
					Print_Center_Aligned("9. Leave", 22, 15);
					Input[2] = _getch() - '0';
					Validate_Input(0, Input[2], 9);
					if (!(Input[2] == 9))
					{
						if (!(Player_profile[Profile_Selected].check_if_Player_has_Car(Input[2])))
						{
							if (Player_profile[Profile_Selected].get_Coins() >= Cars_Shop[Input[2]].get_price())
							{
								Player_profile[Profile_Selected].Buy_Car(Cars_Shop[Input[2]].get_Car(), Input[2]);
								Player_profile[Profile_Selected] - Cars_Shop[Input[2]].get_price();
								PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
								Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
							}
							else {
								Print_Center_Aligned("Need More Coins!", 24, 15);
								//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
								//USE SLEEP
								Sleep(10000);
							}
						}
						else
						{
							Print_Center_Aligned("Already owned", 24, 15);	//SetConsoleCursorPosition(Console, { 55,24 });
							//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
							Sleep(10000);
							//USE SLEEP
						}
					}
				}
				else if (Input[1] == 3)	//CAR GARAGE
				{
					system("CLS");
					PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
					//PrintInterface("High Score ", ADMIN.High_Score_Settings(), 12, Player_profile[Profile_Selected].get_high_score());
					//SetConsoleTextAttribute(Console, 15);
					short position1 = 7;
					COORD Printing_Cords = { 33 ,7 };
					short Counter = 0;
					Print_Center_Aligned("CAR GARAGE", 5, 15); // length 10
					for (loop_iterator = 0; loop_iterator < 9; loop_iterator++)
					{
						if (Counter == 5) {
							Printing_Cords = { 33 ,14 };
						}
						if (Player_profile[Profile_Selected].check_if_Player_has_Car(loop_iterator)) {
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, loop_iterator, 1, Player_profile[Profile_Selected].get_Car_Color(loop_iterator));
							Counter++;
						}
					}
					Print_Center_Aligned("9. Leave Garage", 22, 15); //SetConsoleCursorPosition(Console, { 50,23 });
					Input[2] = _getch() - '0';
					if (Input[2] >= 0 && Input[2] <= 8)
					{
						system("CLS");
						PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
						Printing_Cords = { 40, 11 };
						static short Color;
						Color = Player_profile[Profile_Selected].get_Car_Color(Input[2]);
						Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Color);
						SetConsoleCursorPosition(Console, { 55,12 });
						cout << "1. Change Car color";
						SetConsoleCursorPosition(Console, { 55,14 });
						Print_Center_Aligned("2. Sell Car", 14, 15);
						Input[3] = _getch() - '0';	cout << "\a";
						if (Input[3] == 1)
						{
							system("CLS");
							PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
							Printing_Cords = { 40, 11 };
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Player_profile[Profile_Selected].get_Car_Color(Input[2]));
							Print_Center_Aligned("Select New Color", 4, 15);//	SetConsoleCursorPosition(Console, { 55,4 });
							Printing_Cords = { 65,7 };
							short yincrease = Printing_Cords.Y;
							for (loop_iterator = 1; loop_iterator <= 15; loop_iterator++)
							{
								SetConsoleCursorPosition(Console, Printing_Cords);
								SetConsoleTextAttribute(Console, loop_iterator);
								if (loop_iterator < 10)
									cout << "0";
								cout << loop_iterator << ". \xDB\xDB";
								Printing_Cords.X += 15;
								if (loop_iterator % 2 == 0)
								{
									Printing_Cords.Y += 2;
									Printing_Cords.X = 65;
								}
							}
							SetConsoleCursorPosition(Console, { 30,25 });
							cout << "20. Cancel";
							SetConsoleCursorPosition(Console, { 45,25 });
							cout << "21. Apply Paint for 50 coins";
							Input[3] = _getch() - '0';		string s1 = to_string(Input[3]);
							Input[3] = _getch() - '0';	cout << "\a";	string s2 = to_string(Input[3]);
							//string * Final_Option = &s1 + &s2;
							string* Final_Option = new string;
							*Final_Option = s1 + s2;
							short* Final_Option_Num = new short;
							*Final_Option_Num = stoi(*Final_Option);
							short temp_Last_option = *Final_Option_Num;
							while (*Final_Option_Num >= 1 && *Final_Option_Num <= 15)
							{
								Printing_Cords = { 40, 11 };
								Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 0, *Final_Option_Num);
								temp_Last_option = *Final_Option_Num;
								Input[3] = _getch() - '0';	string s1 = to_string(Input[3]);
								Input[3] = _getch() - '0';	cout << "\a";	string s2 = to_string(Input[3]);
								string Final_Option = s1 + s2;
								*Final_Option_Num = stoi(Final_Option);
							}
							SetConsoleTextAttribute(Console, 15);
							if (*Final_Option_Num == 21 && !(temp_Last_option == *Final_Option_Num))
							{
								if (Player_profile[Profile_Selected].get_Coins() >= 50)
								{
									Player_profile[Profile_Selected] - 50;
									system("CLS");
									PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
									Printing_Cords = { 40, 11 };
									Player_profile[Profile_Selected].set_Car_Color(temp_Last_option, Input[2]);
									Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Player_profile[Profile_Selected].get_Car_Color(Input[2]));
									Print_Center_Aligned("Congrats! New Paint is Applied", 14, 15);//SetConsoleCursorPosition(Console, { 50,15 });
									//USE SLEEP
									//for (loop_iterator = 0; loop_iterator < 90000100; loop_iterator++) {}
								}
								else
									//Print_Center_Aligned("Insuffient Coins To Apply New Paint!",14);
									//cout << "Insuffient Balance To Apply New Paint!";
								{
									//USE SLEEP
									Sleep(1000);
									//for (loop_iterator = 0; loop_iterator < 90000100; loop_iterator++) {}
								}
							}
							delete Final_Option;
							delete Final_Option_Num;
						}
						if (Input[3] == 2) {
							system("CLS");
							PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
							Printing_Cords = { 40, 11 };
							static short Color;
							Color = Player_profile[Profile_Selected].get_Car_Color(Input[2]);
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Color);
							static char UserInput;
							SetConsoleCursorPosition(Console, { 55,8 });	cout << "Sell Car for " << Cars_Shop[Input[2]].get_price() / 2 << "\?";
							SetConsoleCursorPosition(Console, { 55,10 });	cout << "N. Don't Sell";
							SetConsoleCursorPosition(Console, { 55,12 });	cout << "Y. Sell";
							UserInput = _getch();
							if (UserInput == 'y' || UserInput == 'Y') {
								Player_profile[Profile_Selected] + Cars_Shop[Input[2]].get_price() / 2;
								Player_profile[Profile_Selected].set_Player_Has_Car(Input[2], false);
							}
						}
					}
				}
				else if (Input[1] == 4)	//BUY ITEMS
				{
					system("CLS");
					PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());	//SetConsoleTextAttribute(Console, 15);
					Print_Center_Aligned("BUY ITEMS", 5, 15);//	SetConsoleCursorPosition(Console, { 58,5 });
					position = 7;
					for (loop_iterator = 0; loop_iterator < 4; loop_iterator++)
					{
						SetConsoleCursorPosition(Console, { 45,position++ }); cout << loop_iterator << ". Item: " << items[loop_iterator].get_Char_Item_Name();
						SetConsoleCursorPosition(Console, { 75,short(position - 1) }); cout << "Price " << items[loop_iterator].get_price();
					}
					Print_Center_Aligned("4. Leave Shop", 14, 15);
					Input[2] = _getch() - '0';
					Validate_Input(0, Input[2], 4);
					if (!(Input[2] == 4))
					{
						if (!(Player_profile[Profile_Selected].check_if_Player_has_item(Input[2])))
						{
							if (Player_profile[Profile_Selected].get_Coins() >= items[Input[2]].get_price())
							{
								Player_profile[Profile_Selected].Buy_Item(Input[2]);
								Player_profile[Profile_Selected] - items[Input[2]].get_price();
								PrintInterface("Coins ", ADMIN.Coins_Settings(), 11, Player_profile[Profile_Selected].get_Coins());
								if (Input[2] == 1)
									Gun::update_Gun_Maganize(10);
							}
							else {
								Print_Center_Aligned("Need More Coins!", 13, 15);
								//USE SLEEP
								Sleep(1000);
								//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
							}
						}
						else {
							Print_Center_Aligned("Already owned", 13, 15);
							//USE SLEEP
							Sleep(1000);
							//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
						}
					}
				}
				else if (Input[1] == 5)
				{
					system("CLS");
					Print_Center_Aligned("Items Owned", 5, 15);//	SetConsoleCursorPosition(Console, { 58,5 });
					short position = 12;
					for (loop_iterator = 0; loop_iterator < 4; loop_iterator++)
						if (Player_profile[Profile_Selected].check_if_Player_has_item(loop_iterator)) {
							SetConsoleCursorPosition(Console, { 55, position++ });
							cout << loop_iterator << ". " << items[loop_iterator].get_Char_Item_Name();
						}
					//USE SLEEP
					Sleep(1000);
					//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
				}
				else if (Input[1] == 6)
				{
					bool Profile_Deleted = 0;
					Reponsive_UI_Thread_Running = 1;
					system("CLS");
					Reponsive_UI_PauseResume = 1;
					while (Reponsive_UI_PauseResume) {
						get_console_size();
						Print_Center_Aligned("Delete Profile ?", 5, 15);
						Print_Center_Aligned("1. Yes, Delete Profile.", 7, 15);			//SetConsoleCursorPosition(Console, { 54,7 });
						Print_Center_Aligned("2. No, Don\'t Delete Profile.", 8, 15);	//SetConsoleCursorPosition(Console, { 54,8 });		
						if (_kbhit())
						{
							Input[2] = _getch() - '0';		//Validate_Input()
							if (Input[2] == 1) {
								Profile_Deleted = 1;
								Player_profile[Profile_Selected].~Driver();
								for (short j = Profile_Selected; j <= Driver::get_No_of_Player_Profiles(); j++)
									Player_profile[j] = Player_profile[j + 1];
								break;
							}
							if (Input[2] == 2 || Input[2] == 1)
								Reponsive_UI_PauseResume = 0;
						}
					}
					if (Profile_Deleted)
						break;
				}
				if (Input[1] == 7)
					break;

				message = "Welcome  !";
				message.insert(8, Player_profile[Profile_Selected].get_Driver_Name());
				Player_Profile_Menu(Input[1], ADMIN, Player_profile[Profile_Selected], message); // 7 options of Player Profile
				if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
					Player_profile[Profile_Selected].update_high_Score(Player.get_score());
				if (Input[1] == 7)
					break;
			}
			break;
		}
		case 2:	//Create Profile
		{
			system("CLS");
			Print_Center_Aligned("Profile Creation", 5, 15);	//SetConsoleCursorPosition(Console, { 54,5 });
			Driver::No_of_Player_Profiles++;
			Player_profile[Driver::No_of_Player_Profiles].set_Player_Name();
			break;
		}
		case 3: //Instructions
		{
			system("CLS");
			Print_GamePlay_Instructions(Player, 0);
			//USE SLEEP
			Sleep(1000);
			//for (loop_iterator = 0; loop_iterator < 454400000; loop_iterator++) {}
			break;
		}
		}// End of Switch
		Main_Menu(Input[0], Player_profile, sizeof(Player_profile) / sizeof(Driver));
	}//End OF While loop
	ofstream ofstream_ob2;
	ofstream_ob2.open("Player Profiles.txt", ios::out);
	ofstream_ob2.write((char*)&Player_profile, sizeof(Player_profile));
	ofstream_ob2.close();
	Reponsive_UI_Thread_Running = 0; RESPONSIVE_THREADING = 0;
	ReponsiveUI.join();
}//End of Main