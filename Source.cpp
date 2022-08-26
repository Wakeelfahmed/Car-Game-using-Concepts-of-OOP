#include<iostream>
#include<fstream>
#include<conio.h>
#include<ctime>
#include<string.h>
#include<string>
#include<windows.h>
#include<thread>
using namespace std;
COORD UI_NEW, UI_OLD;
bool Reponsive_UI_PauseResume = 0, Reponsive_UI_Thread_running = 0;
CONSOLE_SCREEN_BUFFER_INFO csbi;

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
void get_console_sz()
{
	while (0)
	{
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		UI_OLD = UI_NEW;
		UI_NEW.Y = csbi.srWindow.Bottom - csbi.srWindow.Top; //y  vertical
		UI_NEW.X = csbi.srWindow.Right - csbi.srWindow.Left;   //x hori
		if (UI_NEW.X != UI_OLD.X || UI_NEW.Y != UI_OLD.Y)
			system("CLS");
		Reponsive_UI_Thread_running = 0;
	}
}
void Print_Center_Aligned(string Message, short Horizontal_Sc_height) {
	int Message_Newlegth = Message.size();
	int Message_legth_Correction = Message.size();
	if (Message.size() % 2 == 1) {
		Message_legth_Correction = (Message.size() / 2);
	}
	else 
		Message_legth_Correction = (Message.size() / 2) - 1;     // Center Align
	SetConsoleCursorPosition(Console, { short(UI_NEW.X / 2 - Message_legth_Correction) , Horizontal_Sc_height });
	cout << Message;
}
void hidecursor()
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(Console, &info);
}
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
class Car {
protected:
	char Car_Shape[25];
	int Car_Color;
	int Car_Width;
	int Car_Height;
public:
	Car() : Car_Color(10), Car_Width(4), Car_Height(5) {}
	void set_Car_Shape(char New_Car_Shape[]) { strcpy_s(Car_Shape, New_Car_Shape); }
	void set_Car_Color(int New_Car_Color) { Car_Color = New_Car_Color; }
	void set_Car_Width(int New_Car_Height) { Car_Width = New_Car_Height; }
	void set_Car_Height(int New_Car_Height) { Car_Height = New_Car_Height; }
	int get_Car_Color() const { return Car_Color; }
	int get_Car_Width() const { return Car_Width; }
	int get_Car_Height() const { return Car_Height; }
	char* get_Car_Shape() { return Car_Shape; }
	~Car() {
		strcpy_s(Car_Shape, " ");
	}
};
class SUPERADMIN {
private:
	int Password; //To Allow ADMIN TO ACCESS Special Features.
	COORD Coins;
	COORD Score;
	COORD High_Score;
	COORD Lives;
public:
	SUPERADMIN() {
		Password = 1234;
		Coins = { 100,6 };
		Score = { 87,10 };
		High_Score = { 80, 7 };
		Lives = { 103 , 4 };
	}
	COORD Coins_Settings() const { return Coins; }
	COORD High_Score_Settings() const { return High_Score; }
	COORD Lives_Setting()const { return Lives; };
};
class Game_Play
{
protected:
	Car Game_Car;
	int GamePLay_Difficulty;
	bool Collsion;
	COORD Position_Cordinates;
public:
	Game_Play() : Position_Cordinates({ 0,0 }), Collsion(0), GamePLay_Difficulty(90000) {}
	void set_Position_COORDS(int x, int y) { Position_Cordinates.X = x;		Position_Cordinates.X = y; }
	bool get_Collision_Status() const { return Collsion; }
	COORD get_Player_Position() const { return Position_Cordinates; }
	int getPosition_X() const { return Position_Cordinates.X; }
	int getPosition_Y() const { return Position_Cordinates.X; }
	void setPosition_Y(int Y) { Position_Cordinates.X = Y; }
	void Update_Position_X(int x) { Position_Cordinates.X = x; }
	void Update_Position_Y(int y) { Position_Cordinates.X = y; }
	virtual void Draw_Car() = 0;
	void Erase_Car()
	{
		COORD X_and_Y;
		SetConsoleCursorPosition(Console, Position_Cordinates);
		X_and_Y.X = Position_Cordinates.X;
		X_and_Y.X = Position_Cordinates.X + 1;
		SetConsoleCursorPosition(Console, X_and_Y);
		for (int i = 0; i < 25; i++)
		{
			if (i % 5 == 0)
			{
				SetConsoleCursorPosition(Console, X_and_Y);
				X_and_Y.X++;
			}
			cout << " ";
		}
	}
	int get_Car_width() { return Game_Car.get_Car_Width(); }
	void set_Difficulty(int Difficulty) { GamePLay_Difficulty = Difficulty; }
	int get_Difficulty() const { return GamePLay_Difficulty; }
};
class Driver
{
protected:
	char Driver_Name[50] = "";		int High_score;		int Coins;		bool isActive;
	char Items_Owned_Names[51][50];		bool items_owned[10];
	Car Car_Owned[10];		bool Cars_Owned_Check[10];
	static int No_of_Player_Profiles;
public:
	Driver() : Coins(4000), High_score(0), items_owned{ false }, Cars_Owned_Check{ false }, isActive(false) {}
	bool get_IsActive_Status()const { return isActive; }
	int static get_No_of_Player_Profiles() { return No_of_Player_Profiles; }
	void static Increment_No_of_Profiles() { No_of_Player_Profiles++; }
	static void reset_Number_ofProfiles() { No_of_Player_Profiles = -1; }
	void set_Player_Name() { isActive = true; cout << "Enter Name: "; cin.getline(Driver_Name, 50, '\n'); }
	char* get_Driver_Name() { return Driver_Name; }
	void Buy_Item(char Name[], int Item_Index) {
		strcpy_s((Items_Owned_Names[Item_Index]), Name);
		items_owned[Item_Index] = true;
	}
	char* get_item_Owned_Name(int index) {
		if (items_owned[index] == 1 || items_owned[index] == true)
			return Items_Owned_Names[index];
	}
	void Display_items_Owned()
	{
		short position = 12;
		for (int i = 0; i < 4; i++)
			if (items_owned[i] == true || items_owned[i] == 1) {
				SetConsoleCursorPosition(Console, { 55, position++ });
				cout << i << ". " << Items_Owned_Names[i];
			}
	}
	void update_high_Score(int new_high_score) { High_score = High_score + (new_high_score - High_score); }
	int get_high_score() const { return High_score; }
	void set_Player_Has_Car(int Car_Number, bool TrueFalse) { Cars_Owned_Check[Car_Number] = TrueFalse; }
	bool check_if_Player_has_item(int item_Index) const { return items_owned[item_Index]; }
	bool check_if_Player_has_Car(int item_Index) const { return Cars_Owned_Check[item_Index]; }
	void Buy_Car(Car New_Car, int Car_Number) { Car_Owned[Car_Number] = New_Car; Cars_Owned_Check[Car_Number] = true; }
	void set_Car_Color(int Color, int Car_Number) { Car_Owned[Car_Number].set_Car_Color(Color); }
	int get_Car_width(int index) { return Car_Owned[index].get_Car_Width(); }
	int get_Car_Color(int Car_Number) const { return Car_Owned[Car_Number].get_Car_Color(); }
	Car get_Player_Car(int Car_Number)const { return Car_Owned[Car_Number]; }
	int get_Number_of_Cars_Owned()
	{
		int Counter = 0;
		for (int i = 0; i < 10; i++)
			if (Cars_Owned_Check[i] == true)
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
		for (int i = 0; i < 10; i++) {
			items_owned[i] = false;
			Cars_Owned_Check[i] = false;
			Car_Owned[i].~Car();
			strcpy_s(Items_Owned_Names[i], "");
		}
	}
};
int Driver::No_of_Player_Profiles = -1;
class Player_GamePlay : public Game_Play	//Player car
{
protected:
	Driver Driver_of_Car;
	int Score;
	int Lives;
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
		new_Position.X = Position_Cordinates.X;
		SetConsoleTextAttribute(Console, Game_Car.get_Car_Color()); //Car Owned Color
		for (int i = 0; i <= (4 * Game_Car.get_Car_Height()); i++)			//		for (int i = 0; i < car.size(); i++)
		{
			if (i % 4 == 0)
			{
				new_Position.X++;
				SetConsoleCursorPosition(Console, new_Position);
			}
			cout << Car[i];
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
	bool get_items_Availabe_fr_Driv(int Index) const {
		if (Driver_of_Car.check_if_Player_has_item(Index))
			return true;
		return false;
	}
	void display_Score() {
		COORD Score_Position = { 83,4 };
		SetConsoleTextAttribute(Console, 14);
		SetConsoleCursorPosition(Console, Score_Position);
		cout << "Score:" << Score;
		return;
	}
	void reset_Score() { Score = 0; }
	int get_score() const { return Score; }
	int get_Lives() const { return Lives; }
	void Display_Lives(COORD Lives_Setting) {
		SetConsoleCursorPosition(Console, { Lives_Setting.X,short(Lives_Setting.X - 1) });
		SetConsoleTextAttribute(Console, 13);
		cout << "Lives";
		for (int i = 0; i < Lives; i++)
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
protected:
	int Bullet_color = 9;
	string bullet = "\x18";
	COORD Bullet_Position;
	bool Active_Bullet_Status;
	bool Bullet_Collision_wh_Enemy_car_status;
public:
	static int Gun_Maganize;
	static int Number_of_Active_Bullets;
	static int Maganize_Counter;
	static bool Maganize_Reload[10];
	Gun()
	{
		Maganize_Counter = 0;
		Number_of_Active_Bullets = 0;
		bullet = "\x18";
		Active_Bullet_Status = 1;
		Bullet_Collision_wh_Enemy_car_status = 0;
		Gun_Maganize = 5;
		for (int i = 0; i < 3; i++)
		{
			Maganize_Reload[i];
		}
	}		//Check this
	static void update_Gun_Maganize(int newMaganize) { Gun_Maganize = newMaganize; }
	static int get_Gun_Maganize() { return  Gun_Maganize; }
	void Fire_Bullet(Player_GamePlay Player, int Signal)
	{
		Maganize_Counter++;
		cout << "\a";
		Active_Bullet_Status = 1;
		Number_of_Active_Bullets++;
		Bullet_Position = Player.get_Player_Position();
		if (Player.get_items_Availabe_fr_Driv(2) && Signal == 1)
		{
			if (Player.get_Car_width() == 3) {
				Bullet_Position.X += 1;
			}
			if (Player.get_Car_width() == 4) {
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
	void Move_Bullet(Gun bullets[])
	{
		if (!(Bullet_Position.X < 2))
		{
			bullet = "\x18";
			Bullet_Position.X--;
			SetConsoleTextAttribute(Console, Bullet_color);
			SetConsoleCursorPosition(Console, Bullet_Position);
			cout << bullet;
			SetConsoleCursorPosition(Console, { Bullet_Position.X, short(Bullet_Position.X + 1) });
			cout << " ";
		}
		if ((Bullet_Position.X < 2))
		{
			SetConsoleCursorPosition(Console, { Bullet_Position.X, short((Bullet_Position.X)) });
			cout << " ";
			Active_Bullet_Status = 0;
		}
	}
	COORD get_Bullet_Position() const { return Bullet_Position; }
	int get_Bullet_Position_Y() const { return Bullet_Position.X; }
	int get_Bullet_Position_X() const { return Bullet_Position.X; }
	bool get_Active_Bullet_Status() const { return Active_Bullet_Status; }
	void set_Bullet_Collision_wh_Enemy_car_status(bool truefalse) { Bullet_Collision_wh_Enemy_car_status = truefalse; }
	bool get_Bullet_Collision_wh_Enemy_car_status() const { return Bullet_Collision_wh_Enemy_car_status; }
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
		if (Maganize_Reload[4] == false && Maganize_Reload[0] == true && Maganize_Reload[1] == true && Maganize_Reload[2] == true && Maganize_Reload[3] == true)
		{
			Maganize_Reload[4] = true;
			Gun::Maganize_Counter = 0;
			SetConsoleTextAttribute(Console, 9);
			SetConsoleCursorPosition(Console, { 42,28 });
			cout << "     Fire     ";
			return;
		}
	}
	static bool get_Maganize_Reload(int index) { return Maganize_Reload[index]; }
	~Gun() {
		bullet = "\x18";
		Bullet_Position = { 0 ,0 };
		Active_Bullet_Status = 0;
		if (Number_of_Active_Bullets != 0)
			Number_of_Active_Bullets--;
	}
};
int Gun::Gun_Maganize = 5;
int Gun::Number_of_Active_Bullets = 0; // static initialization
int Gun::Maganize_Counter = 0; // static initialization
bool Gun::Maganize_Reload[10] = { true };
class Enemy_car : public Game_Play		//***** Enemy Car *****//
{
protected:
	bool Enemy_car_Active;
public:
	Enemy_car() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.X = 4;	//Starting point of Enemy
		Game_Car.set_Car_Color(12);
		char Car[25] = " -- *±±*±±±±*±±* vv ";
		Game_Car.set_Car_Shape(Car);
	}
	int generate_Enemy_X_coordinate() { return 0 + (rand() % WIN_WIDTH + 2); }
	void resetEnemy() {
		Position_Cordinates.X = generate_Enemy_X_coordinate();
		Position_Cordinates.X = 4;
	}
	bool get_Enemy_Alive_Status() const { return Enemy_car_Active; }
	void Draw_Car(Player_GamePlay& Player_GamePlay) //Enemy Car 
	{
		if (get_Collision_Status())
			return;
		COORD new_Position = { 0,0 }; //bullet_Position;
		{
			if (!(Position_Cordinates.X > SCREEN_HEIGHT + 2) && !get_Collision_Status())
			{
				char car[25];
				strcpy_s(car, Game_Car.get_Car_Shape());
				Position_Cordinates.X++;
				SetConsoleCursorPosition(Console, Position_Cordinates);
				int count = 0;
				new_Position = Position_Cordinates;
				int counter = 0;
				for (int i = 19; i >= 0; i--)
				{
					counter++;
					if (counter == 5)
					{
						counter = 1;
						new_Position.X--;
						SetConsoleCursorPosition(Console, new_Position);
					}
					SetConsoleTextAttribute(Console, Game_Car.get_Car_Color());
					if (!(new_Position.X > SCREEN_HEIGHT - 2)) {
						cout << car[i];
					}
				}
				if (new_Position.X > SCREEN_HEIGHT - 2)
				{
					Enemy_car_Active = 0;
					++Player_GamePlay;
					Player_GamePlay.display_Score();
				}
				//int minus = 0;				//if (Player_GamePlay.get_items_Availabe_fr_Driv(2))				//	minus = 2000;				//for (int i = 0; i < Player_GamePlay.get_Difficulty() - minus; i++) {}			//	for (int i = 0; i < 988999 - minus; i++) {}	//HOW FAST ENEMY WILL MOVE			/*//	for (int i = 0; i < 918080 - minus; i++) {}	//HOW FAST ENEMY WILL MOVE*/
				EraseEnemyTrail();
				if (new_Position.X > SCREEN_HEIGHT - 2)
					resetEnemy();
			}
			else
				return;
		}
	}
	void Draw_Car() {}
	void EraseEnemyTrail() {
		COORD Old_Position;
		Old_Position.X = Position_Cordinates.X;
		Old_Position.X = (Position_Cordinates.X - 5);
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
class Shop
{
protected:
	int Price;
public:
	Shop() : Price(0) {}
	Shop(int price) : Price(price) {}
	void set_Item_Price(int price) { this->Price = price; }
	int get_price() const { return Price; }
};
class Items_Shop : public Shop {
private:
	char Item_Name[50] = "";
public:
	void  set_Item_Name(string Name) { strcpy_s(Item_Name, Name.c_str()); }
	char* get_Char_Item_Name() { return Item_Name; }
	void Print_Details() { cout << "\nName of item: "; cout << Item_Name;	cout << "\tPrice: "; cout << Price; }
	void User_Input()
	{
		cin.ignore();		cout << "Enter Name of item:";			cin.getline(Item_Name, 50, '\n');
		cout << "Enter Price:"; 			cin >> Price;
	}
};
class Car_Shop : public Shop {
private:
	Car Cars;
public:
	Car_Shop() { Price = 100; }
	void set_Car_Shape(string Name) { char Cararray[25]; strcpy_s(Cararray, Name.c_str());	Cars.set_Car_Shape(Cararray); }
	void set_Car_Width(int Car_Width) { Cars.set_Car_Width(Car_Width); }
	void set_Car_Height(int Car_Height) { Cars.set_Car_Height(Car_Height); }
	void set_Car_Color(int Car_Color) { Cars.set_Car_Color(Car_Color); }
	Car get_Car() const { return Cars; }
	int get_Car_Color() const { return Cars.get_Car_Color(); }
	char* get_Car_Shape() { return Cars.get_Car_Shape(); }
};
void Validate_Input(int start, int& Input, int end) {
	while (Input < start || Input > end)
		Input = _getch() - '0';
}
bool Gun_jammed_Status() {
	int Counter = 0;
	for (int i = 0; i < 3; i++) {
		if (Gun::get_Maganize_Reload(i) == true)
			Counter++;
	}
	if (Counter == 3)
	{
		//cout << "  FIRE!!  ";
		return true;
	}
	//cout << "  !NO FIRE  ";
	return false;
}
void Print_Car_Char_Array(Car_Shop Cars[], COORD& position, int i, bool signal, int Color) {
	SetConsoleCursorPosition(Console, { short(position.X - 3), short(position.X + 2) });
	SetConsoleTextAttribute(Console, 15);//White - 15
	cout << i << ". ";
	int yincrease = position.X;
	char* car = Cars[i].get_Car_Shape();	//	" ^^ [±±] ±± [±±] -- ";  " ^^ \n[±±]\n ±± \n[±±]\n -- "
	SetConsoleCursorPosition(Console, { position.X,position.X });
	SetConsoleTextAttribute(Console, Color);
	for (int j = 0; j < strlen(car); j++)
	{
		if (j % (4) == 0)
			SetConsoleCursorPosition(Console, { position.X,short(yincrease++) });
		cout << car[j];
	}
	if (signal) {
		SetConsoleTextAttribute(Console, 15);
		SetConsoleCursorPosition(Console, { short(position.X - 2),short(position.X + 5) });
		cout << "Price " << Cars[i].get_price() << endl;
	}
	position.X += 13; //position.Y -= 4;
}
/*void Read_Player_Profile_From_file(Driver Player_profile[]) {
	ifstream ifstream_ob;
	ifstream_ob.open("Player_profile.txt", ios::in);
	//cout << "\nReading the object from a file : \n";
	ifstream_ob.read((char*)&Player_profile, sizeof(Player_profile));
	ifstream_ob.close();
}
void Write_Player_Profile_to_File(Driver Player_Profile[]) {
	ofstream ofstream_ob;
	ofstream_ob.open("Player_profile.txt", ios::out);
	//for (int i = 0; i < 2; i++)
	ofstream_ob.write((char*)&Player_Profile, sizeof(Player_Profile));
	ofstream_ob.close();
}
void Read_Items_From_File(Shop items[]) {
	ifstream ifstream_ob;
	ifstream_ob.open("Items_Inventory.txt", ios::in);
	cout << "\nReading the object from a file : \n";
	ifstream_ob.read((char*)&items, sizeof(items));
	ifstream_ob.close();
}*/
void Print_GamePlay_Instructions(Player_GamePlay Player, bool signal) {
	short positionX, positionY;
	if (signal) {
		SetConsoleTextAttribute(Console, 14);
		positionX = 100;	positionY = 8;
	}
	else {
		SetConsoleTextAttribute(Console, 15);
		positionX = 58;	positionY = 7;
	}
	SetConsoleCursorPosition(Console, { short(positionX - 1),positionY++ });		cout << "Instruction:";
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
void get_console_size()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	UI_OLD = UI_NEW;
	UI_NEW.Y = csbi.srWindow.Bottom - csbi.srWindow.Top; //y  vertical
	UI_NEW.X = csbi.srWindow.Right - csbi.srWindow.Left;   //x hori
	if (UI_NEW.X != UI_OLD.X || UI_NEW.Y != UI_OLD.Y)
		system("CLS");
}
void Main_Menu(int& Input, Driver Player_profile[])
{
	system("CLS");
	Reponsive_UI_Thread_running = 1;
	Player_profile->reset_Number_ofProfiles();
	for (int i = 0; i < 15; i++)
		if (Player_profile[i].get_IsActive_Status())
			Player_profile->Increment_No_of_Profiles();
	Reponsive_UI_PauseResume = 1; 
	while (Reponsive_UI_PauseResume) {
		get_console_size();
		Reponsive_UI_Thread_running = 0;
		if (Driver::get_No_of_Player_Profiles() >= 0)
		{
			SetConsoleTextAttribute(Console, 15);
			Print_Center_Aligned("1. Career/Profile", 6);
			//SetConsoleCursorPosition(Console, { 53,6 });
			//cout << "1. Career/Profile";
		}
		else
		{
			SetConsoleTextAttribute(Console, 8);
			//SetConsoleCursorPosition(Console, { 53,6 });
			Print_Center_Aligned("1. Career/Profile", 6);
			//cout << "1. Career/Profile";
		}
		SetConsoleTextAttribute(Console, 15);
		//SetConsoleCursorPosition(Console, { 53,7 });	cout << "2. Create Profile";
		Print_Center_Aligned("2. Create Profile", 7);
		Print_Center_Aligned("3. View Instructions", 8);
		Print_Center_Aligned("4. Exit App (Player Progress will be Saved)", 9);
		//SetConsoleCursorPosition(Console, { 53,8 });	cout << "3. View Instructions";
		//SetConsoleCursorPosition(Console, { 53,9 });	cout << "4. Exit App (Player Progress will be Saved)";
		if (_kbhit()) {
			Input = _getch() - '0';
			if (Driver::get_No_of_Player_Profiles() <= -1)
				if (Input < 2 || Input > 4) {
					if (_kbhit())
						Input = _getch() - '0';
				}
				else
				{
					Reponsive_UI_PauseResume = 0;
				}
				//Validate_Input(2, Input, 4);
			else {
				if (Input < 1 || Input > 4) {
					if (_kbhit())
						Input = _getch() - '0';
				}
				else
				{
					Reponsive_UI_PauseResume = 0;
				}
			}
				//Validate_Input(1, Input, 4);// cout << "\a";
		}
	}
	
}
void Player_Profile_Menu(int& Input) {
	//system("CLS");
	short position = 10;
	SetConsoleTextAttribute(Console, 15);
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "1. Select Car and Play";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "2. Buy Car";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "3. Display Owned Cars";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "4. Shop items";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "5. View Items in Inventory";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "6. Delete Profile";
	SetConsoleCursorPosition(Console, { 51,position++ }); cout << "7. Exit Profile";
	Input = _getch() - '0'; cout << "\a";
	Validate_Input(1, Input, 7);
}
void Shop_Items_ReadWrite_Menu(int & input) {
	cout << "Intentory Read() Wirte()\n0.View Exisiting Data\t1.Enter Data\t2.Write to File\t\n(any other key to leave)";
	input = _getch() - '0';
	Reponsive_UI_PauseResume = 0;
}
int main()
{
	//PlaySound(TEXT("mixkit-retro-video-game-bubble-laser-277.wav"), NULL, SND_ASYNC);	//cout << "played"; //	cout << "not played";
	HWND hWnd = GetConsoleWindow();		ShowWindow(hWnd, SW_SHOWMAXIMIZED);	//Make Console open in Maximized window.
	Player_GamePlay Car1;
	SetConsoleTextAttribute(Console, 15);
	Items_Shop items[10];	/* ITEMS SHOP */	Car_Shop Cars_Shop[10]; /* CARS SHOP */
	{ifstream ifstream_ob;
	ifstream_ob.open("Items_Inventory.txt", ios::in);
	ifstream_ob.read((char*)&items, sizeof(items));
	ifstream_ob.close(); }
	hidecursor();
	SUPERADMIN ADMIN;
	int input;
	{items[0].set_Item_Name("Gun");		items[0].set_Item_Price(800);	items[1].set_Item_Name("Extended Maganize"); items[1].set_Item_Price(800);
	items[2].set_Item_Name("Double Gun");	items[2].set_Item_Price(1500);	items[3].set_Item_Name("Quick Reload");	items[3].set_Item_Price(600);
}
	Reponsive_UI_PauseResume = 1;
	//while (Reponsive_UI_PauseResume)
	{
		Shop_Items_ReadWrite_Menu(input);
	}
	while (input >= 0 && input < 3) /*ITEMS SHOP READ WRITE*/ {
		if (input == 0)
			for (int i = 0; i < 3; i++)
				items[i].Print_Details();
		else if (input == 1)
			for (int i = 0; i < 3; i++)
				items[i].User_Input();
		else if (input == 2)
		{
			ofstream ofstream_ob;
			ofstream_ob.open("Items_Inventory.txt", ios::out);
			ofstream_ob.write((char*)&items, sizeof(items));
			ofstream_ob.close();
		}
		Shop_Items_ReadWrite_Menu(input);
	}
	int y;	int Profile_Selected, Car_Selected, Input[5], No_of_Enemies = 4;
	Driver Player_profile[15];
	cout << "\nDo you want to Read Players Records\?\nPress 1 to Read (any other key to leave)";
	y = _getch() - '0';	cout << "\a";
	if (y == 1)
	{
		ifstream ifstream_ob1;
		ifstream_ob1.open("Player_profile.txt", ios::in);
		ifstream_ob1.read((char*)&Player_profile, sizeof(Player_profile));
		ifstream_ob1.close();
		for (int i = 0; i < 15; i++)
			if (Player_profile[i].get_IsActive_Status())
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
	thread ReponsiveUI(get_console_sz);
	Player_GamePlay Player;		//Player.set_Position_COORDS(20, 20);		//Player.Draw_Car();
	Main_Menu(Input[0], Player_profile);
	Driver Selected_Driver_0, Selected_Driver_1;
	while (Input[0] == 1 || Input[0] == 2 || Input[0] == 3)
	{
		short position2 = 7, position = 0;
		char chcheck = 't';
		switch (Input[0])
		{
		case 1:	//Select Profile
		{
			system("CLS");
			position = 12; //SEEMS USELESS
			SetConsoleCursorPosition(Console, { 53,5 });	//Select Profile
			cout << "Select your Profile";
			for (int i = 0; i <= Driver::get_No_of_Player_Profiles(); i++) {
				SetConsoleCursorPosition(Console, { 50,position++ });
				if (Player_profile[i].get_IsActive_Status())
					cout << i << ". " << Player_profile[i].get_Driver_Name();
			}
			Profile_Selected = _getch() - '0'; cout << "\a";
			Validate_Input(0, Profile_Selected, Driver::get_No_of_Player_Profiles());
			system("CLS");
			SetConsoleTextAttribute(Console, 15);
			SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
			Selected_Driver_0 = Player_profile[Profile_Selected];
			Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
			cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
			string Message = "Welcome back  !";
			Message.insert(13, Player_profile[Profile_Selected].get_Driver_Name());
			SetConsoleCursorPosition(Console, { short((UI_NEW.X / 2) - (Message.size() / 2)),5 });//org
			cout << Message;
			SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
			SetConsoleTextAttribute(Console, 12);
			cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
			Player_Profile_Menu(Input[1]);
			while (Input[1] >= 1 || Input[1] <= 7)
			{
				if (Input[1] == 1)				//Select Car and Play
				{
					if (Player_profile[Profile_Selected].get_Number_of_Cars_Owned() == 0)
					{
						system("CLS");
						SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
						cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
						SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
						SetConsoleTextAttribute(Console, 12);
						cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
						SetConsoleCursorPosition(Console, { 50,short(position - 8) });
						SetConsoleTextAttribute(Console, 15);
						cout << "You don't have any Car";
						SetConsoleCursorPosition(Console, { 50,short(position - 7) });
						cout << "Buy Car first !!";
						for (int i = 0; i < 454400000; i++) {}
					}
					else
					{
						system("CLS");
						position = 5;
						SetConsoleCursorPosition(Console, { 55,4 });	cout << "Select your Car";
						COORD Printing_Cords = { 33 ,7 };
						int Counter = 0;
						for (int i = 0; i < 10; i++)
							if (Player_profile[Profile_Selected].check_if_Player_has_Car(i))
							{
								if (Counter == 5) {
									Printing_Cords = { 33 ,14 };
								}
								Print_Car_Char_Array(Cars_Shop, Printing_Cords, i, 0, Player_profile[Profile_Selected].get_Car_Color(i));
								Counter++;
							}
						Car_Selected = _getch() - '0';
						while (!Player_profile[Profile_Selected].check_if_Player_has_Car(Car_Selected) || (Car_Selected < 0 || Car_Selected > 9))
						{
							cout << "Select Car from your owned Car list only";
							Car_Selected = _getch() - '0'; cout << "\a";
						}
						Player.Set_Player_Car(Player_profile[Profile_Selected].get_Player_Car(Car_Selected));
						system("CLS");
						SetConsoleTextAttribute(Console, 15);
						SetConsoleCursorPosition(Console, { 55,4 });	cout << "Select Difficulty";
						SetConsoleCursorPosition(Console, { 58,6 });	cout << "1. Easy";
						SetConsoleCursorPosition(Console, { 58,8 });	cout << "2. Medium";
						SetConsoleCursorPosition(Console, { 58,10 });	cout << "3. Hard";
						Input[2] = _getch() - '0';
						Validate_Input(1, Input[2], 3);
						if (Input[2] == 1)								Player.set_Difficulty(900000);
						else if (Input[2] == 2) { No_of_Enemies = 5;		Player.set_Difficulty(90000); } //Medium
						else if (Input[2] == 3) { No_of_Enemies = 6;		Player.set_Difficulty(40000); } //Hard
						/*
						if (Input[2] == 1)								Player.set_Difficulty(900000);
						else if (Input[2] == 2) { No_of_Enemies = 5;		Player.set_Difficulty(90000); } //Medium
						else if (Input[2] == 3) { No_of_Enemies = 6;		Player.set_Difficulty(60000); } //Hard*/
						char ch1;
						SetConsoleTextAttribute(Console, 15);
						SetConsoleCursorPosition(Console, { 15,22 });
						cout << "q - Cancel";
						SetConsoleCursorPosition(Console, { 48,19 });
						cout << "Press Spacebar To Start Game!";
						ch1 = _getch(); cout << "\a";
						Player.reset_Score();
						int Score_Coins_Counter = 0;
						if (ch1 == 32)
						{
							Player.Reset_Lives();
							system("CLS");
							Player.Display_Lives((ADMIN.Lives_Setting()));
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							SetConsoleTextAttribute(Console, 11);
							cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
							srand(unsigned int(time(0)));
							COORD Position;	Position.X = WIN_WIDTH;	Position.X = SCREEN_HEIGHT;
							Gun bullets[50];
							position2 = 8;
							Enemy_car  Enemy2[10];
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
							SetConsoleTextAttribute(Console, 12);
							SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
							cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << "  ";
							Print_GamePlay_Instructions(Player, 1);
							bool Game_Running = true;
							static int Counter = 0;
							Counter = 0;
							Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
							while (ch1 != 'q' && Game_Running)
							{
								for (int i = 0; i < Player.get_Difficulty(); i++) {}	//Game Lag/Difficulty
								SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
								SetConsoleTextAttribute(Console, 11);
								cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
								if (Score_Coins_Counter % 10 == 0 && Score_Coins_Counter != 0)
								{
									Player_profile[Profile_Selected].Give_Coins();
									Score_Coins_Counter = 0;
								}
								if (Player.get_items_Availabe_fr_Driv(1)) { Gun::Gun_Maganize = 10; }
								if (Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2))
								{
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
										for (int i = 0; i < 5; i++)
											Gun::Maganize_Reload[i] = false;
									}
									else if (ch1 == 32 && Player.get_items_Availabe_fr_Driv(0) || Player.get_items_Availabe_fr_Driv(2) && Gun_jammed_Status() && ch1 == 32)
									{
										if (Gun_jammed_Status())
										{
											bullets[Gun::Number_of_Active_Bullets].Fire_Bullet(Player, 1);
										}
										if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
										{
											SetConsoleCursorPosition(Console, { 44,28 });
											cout << "RELOADING!!!";
											for (int i = 0; i < 5; i++)
												Gun::Maganize_Reload[i] = false;
										}
										if (Player.get_items_Availabe_fr_Driv(2) && Gun_jammed_Status()) {

											bullets[Gun::Number_of_Active_Bullets].Fire_Bullet(Player, 2);
											if (Gun::Maganize_Counter % Gun::get_Gun_Maganize() == 0 && Gun::Maganize_Counter != 0)
											{
												SetConsoleCursorPosition(Console, { 42,28 });
												cout << "RELOADING!!!";
												for (int i = 0; i < 5; i++)
													Gun::Maganize_Reload[i] = false;
											}
										}
									}
									/*else if (ch1 == 'x' || ch1 == 'X') {
										COORD Genederight = { 15,15 };
										COORD Genedeleft = { 15,15 }; //Player.get_Player_Position()
										int Counter = 0;
										for (int i = 0; i < 10; i++)
										{
											SetConsoleCursorPosition(Console, Genederight);
											cout << "@";
											Genederight.X++;
											if (Counter == 1) {
												Genederight.Y++;
												Counter = 0;
											}
											for (int i = 0; i < 9999999; i++) {}
											Counter++;
										}
										for (int i = 0; i < 10; i++)
										{
											SetConsoleCursorPosition(Console, Genedeleft);
											cout << "#";
											for (int i = 0; i < 9999999; i++) {}

											Genedeleft.X--; Genedeleft.Y++;
										}

									}*/
									else if (ch1 == 'p' || ch1 == 'P') {
										while (chcheck != 'p')
										{
											chcheck = _getch();
										}
										chcheck = 't';
									}
									else if (ch1 == 'q') {
										break;
									}
								}
								for (int enemy_loop = 0; enemy_loop < No_of_Enemies; enemy_loop++)
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
										SetConsoleTextAttribute(Console, 12);
										SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
										cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
										COORD Position_Cordinates_enemy = Enemy2[enemy_loop].get_Player_Position(); // Enemy CAR Position
										COORD Player_Position = Player.get_Player_Position();
										//if ((Position_Cordinates.Y - 1) >= Player_Position.Y && (Position_Cordinates.Y - 10) <= Player_Position.Y)
										if ((Position_Cordinates_enemy.X - 1) >= Player_Position.X && (Position_Cordinates_enemy.X - 11) <= Player_Position.X)//(//Position_Cordinates.Y - 1) == Player_Position.Y 
											/*//	|| (Position_Cordinates.Y - 2) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 3) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 4) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 5) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 6) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 7) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 8) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 9) == Player_Position.Y
											//	|| (Position_Cordinates.Y - 10) == Player_Position.Y)*/
										{
											if (Position_Cordinates_enemy.X == Player_Position.X
												|| Position_Cordinates_enemy.X + 1 == Player_Position.X		//player right by one, enemy left(pos).
												|| Position_Cordinates_enemy.X + 2 == Player_Position.X	//// player right by two, enemy left(pos).
												|| Player.get_Car_width() == 4 && Position_Cordinates_enemy.X + 3 == Player_Position.X //(pos)player right ,enemy left.   player most left collision with enemy most right(disable in thinner car)
												|| Position_Cordinates_enemy.X - 3 == Player_Position.X	//(pos)player left ,enemy right.   player most right collision with enemy most left
												|| Position_Cordinates_enemy.X - 2 == Player_Position.X	// player left by two, enemy right(pos).
												|| Position_Cordinates_enemy.X - 1 == Player_Position.X)	// player left by one, enemy right(pos).			
											{
												// COLLISION DETECTION !!!
												--Player;
												Player.Display_Lives((ADMIN.Lives_Setting()));
												if (Player.get_Lives() == 0) {
													system("CLS");
													SetConsoleTextAttribute(Console, 10);
													SetConsoleCursorPosition(Console, { 57,9 });
													cout << "-----------";
													SetConsoleCursorPosition(Console, { 58,10 });
													cout << "GAME OVER";
													SetConsoleCursorPosition(Console, { 57,11 });
													cout << "-----------";
													SetConsoleCursorPosition(Console, { 57,12 });
													cout << "Score:" << Player.get_score();
													SetConsoleCursorPosition(Console, { 65,14 });
													cout << "Press any key to Continue";
													SetConsoleCursorPosition(Console, { 50,14 });
													cout << "0. Restart";
													int INPUTGAMEPLAY = 12;
													for (int i = 0; i < 100099999; i++) {}
													INPUTGAMEPLAY = _getch() - '0';
													if (INPUTGAMEPLAY == 0) {
														system("CLS");
														Game_Running = true;
														Player.Reset_Lives();
														Player.reset_Score();
														Print_GamePlay_Instructions(Player, 1);
														Player.display_Score();
														Player.Display_Lives((ADMIN.Lives_Setting()));
														SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
														SetConsoleTextAttribute(Console, 11);
														cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
														SetConsoleTextAttribute(Console, 12);
														SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
														cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << "  ";
													}
													else {
														system("CLS");
														Game_Running = false;
													}
												}
												Enemy2[enemy_loop].Update_Position_Y(Position_Cordinates_enemy.X - 5);
												Enemy2[enemy_loop].Erase_Car();
												Player.Draw_Car();
												Enemy2[enemy_loop].resetEnemy(); //for checking
											}
										}
										else
											Enemy2[enemy_loop].update_Collision_Status(0);
										for (int i = 0; i < Gun::Number_of_Active_Bullets; i++)
										{
											if (bullets[i].get_Active_Bullet_Status() == 0)
											{
												bullets[i].~Gun();
												for (int j = i; j < Gun::Number_of_Active_Bullets; j++) {
													bullets[j] = bullets[j + 1];
												}
											}
											if (Enemy2[enemy_loop].getPosition_Y() == bullets[i].get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 1 == bullets[i].get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 2 == bullets[i].get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 3 == bullets[i].get_Bullet_Position_Y() || Enemy2[enemy_loop].getPosition_Y() - 4 == bullets[i].get_Bullet_Position_Y())
											{
												if (Enemy2[enemy_loop].getPosition_X() == bullets[i].get_Bullet_Position_X()		//left most (1st col)
													|| (Enemy2[enemy_loop].getPosition_X() + 1) == bullets[i].get_Bullet_Position_X()	// 2nd column
													|| (Enemy2[enemy_loop].getPosition_X() + 2) == bullets[i].get_Bullet_Position_X()	//3rd col
													|| (Enemy2[enemy_loop].getPosition_X() + 3) == bullets[i].get_Bullet_Position_X())	//4th col, right most
												{
													Enemy2[enemy_loop].Update_Position_Y(Position_Cordinates_enemy.X - 5);
													Enemy2[enemy_loop].Erase_Car();
													Enemy2[enemy_loop].resetEnemy();
													bullets[i].~Gun();
													for (int j = i; j < Gun::Number_of_Active_Bullets; j++)
													{
														bullets[j] = bullets[j + 1];
													}
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
													SetConsoleTextAttribute(Console, 12);
													SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
													cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << "  ";
													bullets[i].set_Bullet_Collision_wh_Enemy_car_status(1);
												}
											}
										}
									}
								}
								for (int i = 0; i < Gun::Number_of_Active_Bullets; i++)
									bullets[i].Move_Bullet(bullets);
							}
						}
					}
				}
				else if (Input[1] == 2) {	//Buy Car
					system("CLS");
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
					short position1 = 7;
					COORD Printing_Cords = { 33 ,7 };
					SetConsoleCursorPosition(Console, { 59,5 }); cout << "BUY CAR";
					for (int i = 0; i < 9; i++)
					{
						if (i == 5)
							Printing_Cords = { 33 ,14 };
						Print_Car_Char_Array(Cars_Shop, Printing_Cords, i, 1, Cars_Shop[i].get_Car_Color());
					}
					Input[2] = _getch() - '0';
					Validate_Input(0, Input[2], 8);
					if (!(Player_profile[Profile_Selected].check_if_Player_has_Car(Input[2])))
					{
						if (Player_profile[Profile_Selected].get_Coins() >= Cars_Shop[Input[2]].get_price())
						{
							Player_profile[Profile_Selected].Buy_Car(Cars_Shop[Input[2]].get_Car(), Input[2]);
							Player_profile[Profile_Selected] - Cars_Shop[Input[2]].get_price();
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							SetConsoleTextAttribute(Console, 11);
							cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
							Player.set_Driver_of_Car((Player_profile[Profile_Selected]));
						}
						else {
							cout << "Need More Coins!";
							for (int i = 0; i < 454400000; i++) {}
						}
					}
					else
					{
						SetConsoleCursorPosition(Console, { 55,24 });
						SetConsoleTextAttribute(Console, 15);
						cout << "Already owned";
						for (int i = 0; i < 454400000; i++) {}
					}
				}
				else if (Input[1] == 3)	//CAR GARAGE
				{
					system("CLS");
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
					short position1 = 7;
					COORD Printing_Cords = { 33 ,7 };
					int Counter = 0;
					SetConsoleCursorPosition(Console, { 57,5 }); cout << "CAR GARAGE";
					for (int i = 0; i < 9; i++)
					{
						if (Counter == 5) {
							Printing_Cords = { 33 ,14 };
						}
						if (Player_profile[Profile_Selected].check_if_Player_has_Car(i)) {
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, i, 1, Player_profile[Profile_Selected].get_Car_Color(i));
							Counter++;
						}
					}
					SetConsoleCursorPosition(Console, { 50,23 });
					SetConsoleTextAttribute(Console, 15);
					cout << "9.    Leave Garage";
					Input[2] = _getch() - '0';
					if (Input[2] >= 0 && Input[2] <= 8)
					{
						system("CLS");
						SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
						cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
						Printing_Cords = { 40, 11 };
						int Color = Player_profile[Profile_Selected].get_Car_Color(Input[2]);
						Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Color);
						SetConsoleCursorPosition(Console, { 55,10 });
						cout << "1. Change Car color";
						SetConsoleCursorPosition(Console, { 55,12 });
						cout << "2. Sell Car";
						Input[3] = _getch() - '0';	cout << "\a";
						if (Input[3] == 1)
						{
							system("CLS");
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							SetConsoleTextAttribute(Console, 11);
							cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
							Printing_Cords = { 40, 11 };
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Player_profile[Profile_Selected].get_Car_Color(Input[2]));
							SetConsoleCursorPosition(Console, { 55,4 });		cout << "Select New Color";
							Printing_Cords = { 65,7 };
							int yincrease = Printing_Cords.X;
							for (int i = 1; i <= 15; i++)
							{
								SetConsoleCursorPosition(Console, Printing_Cords);
								SetConsoleTextAttribute(Console, i);
								if (i < 10)
									cout << "0";
								cout << i << ". \xDB\xDB";
								Printing_Cords.X += 15;
								if (i % 2 == 0)
								{
									Printing_Cords.X += 2;
									Printing_Cords.X = 65;
								}
							}
							SetConsoleCursorPosition(Console, { 30,25 });
							cout << "20. Cancel";
							SetConsoleCursorPosition(Console, { 45,25 });
							cout << "21. Apply Paint for 50 coins";
							Input[3] = _getch() - '0';		string s1 = to_string(Input[3]);
							Input[3] = _getch() - '0';	cout << "\a";	string s2 = to_string(Input[3]);
							string Final_Option = s1 + s2;
							int Final_Option_Num = stoi(Final_Option);
							int temp_Last_option = Final_Option_Num;
							while (Final_Option_Num >= 1 && Final_Option_Num <= 15)
							{
								Printing_Cords = { 40, 11 };
								Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 0, Final_Option_Num);
								temp_Last_option = Final_Option_Num;
								Input[3] = _getch() - '0';	string s1 = to_string(Input[3]);
								Input[3] = _getch() - '0';	cout << "\a";	string s2 = to_string(Input[3]);
								string Final_Option = s1 + s2;
								Final_Option_Num = stoi(Final_Option);
							}
							SetConsoleTextAttribute(Console, 15);
							if (Final_Option_Num == 21 && !(temp_Last_option == Final_Option_Num))
							{
								if (Player_profile[Profile_Selected].get_Coins() >= 50)
								{
									Player_profile[Profile_Selected] - 50;
									system("CLS");
									SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
									SetConsoleTextAttribute(Console, 11);
									cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
									Printing_Cords = { 40, 11 };
									Player_profile[Profile_Selected].set_Car_Color(temp_Last_option, Input[2]);
									Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Player_profile[Profile_Selected].get_Car_Color(Input[2]));
									SetConsoleCursorPosition(Console, { 50,15 });
									cout << "Congrats! New Paint is Applied";
									for (int i = 0; i < 90000100; i++) {}
								}
								else
									cout << "Insuffient Balance To Apply New Paint!";
								for (int i = 0; i < 90000100; i++) {}
							}
						}
						if (Input[3] == 2) {
							system("CLS");
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							SetConsoleTextAttribute(Console, 11);
							cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
							Printing_Cords = { 40, 11 };
							int Color = Player_profile[Profile_Selected].get_Car_Color(Input[2]);
							Print_Car_Char_Array(Cars_Shop, Printing_Cords, Input[2], 1, Color);
							char UserInput;
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
					SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
					cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
					SetConsoleCursorPosition(Console, { 58,5 }); cout << "BUY ITEMS";
					position = 7;
					SetConsoleCursorPosition(Console, { 45,position++ });
					for (int i = 0; i < 4; i++)
					{
						cout << i << ". ";
						cout << "Item: " << items[i].get_Char_Item_Name();
						SetConsoleCursorPosition(Console, { 75,short(position - 1) });
						cout << "Price " << items[i].get_price();
						SetConsoleCursorPosition(Console, { 45,position++ });
					}
					Input[2] = _getch() - '0';
					cout << "\a";
					if (!(Player_profile[Profile_Selected].check_if_Player_has_item(Input[2])))
					{
						if (Player_profile[Profile_Selected].get_Coins() >= items[Input[2]].get_price())
						{
							Player_profile[Profile_Selected].Buy_Item(items[Input[2]].get_Char_Item_Name(), Input[2]);
							Player_profile[Profile_Selected] - items[Input[2]].get_price();
							SetConsoleTextAttribute(Console, 11);
							SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
							cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
							if (Input[2] == 1)Gun::update_Gun_Maganize(10);
						}
						else {
							cout << "Need More Coins!";
							for (int i = 0; i < 454400000; i++) {}
						}
					}
					else {
						cout << "Already owned";
						for (int i = 0; i < 454400000; i++) {}
					}
				}
				else if (Input[1] == 5)
				{
					system("CLS");
					SetConsoleCursorPosition(Console, { 58,5 }); cout << "Items Owned";
					short position = 12;
					for (int i = 0; i < 4; i++)
					{
						Player_profile[Profile_Selected].Display_items_Owned();
					}
					for (int i = 0; i < 454400000; i++) {}
				}
				else if (Input[1] == 6)
				{
					system("CLS");
					SetConsoleCursorPosition(Console, { 55,0 });	cout << "Delete Profile ?";
					SetConsoleCursorPosition(Console, { 54,5 });	cout << "1. Yes, Delete Profile.";
					SetConsoleCursorPosition(Console, { 54,6 });	cout << "2. No, Don\'t Delete Profile.";
					Input[2] = _getch() - '0';	cout << "\a";
					if (Input[2] == 1) {
						Player_profile[Profile_Selected].~Driver();
						for (int j = Profile_Selected; j <= Driver::get_No_of_Player_Profiles(); j++)
							Player_profile[j] = Player_profile[j + 1];
					}
					break;
				}
				if (Input[1] == 7)
				{
					break;
				}
				system("CLS");
				SetConsoleTextAttribute(Console, 15);
				SetConsoleCursorPosition(Console, ADMIN.Coins_Settings());
				cout << "Coins " << Player_profile[Profile_Selected].get_Coins();
				if (Player.get_score() > Player_profile[Profile_Selected].get_high_score())
					Player_profile[Profile_Selected].update_high_Score(Player.get_score());
				SetConsoleTextAttribute(Console, 12);
				SetConsoleCursorPosition(Console, ADMIN.High_Score_Settings());
				cout << "High Score " << Player_profile[Profile_Selected].get_high_score() << " ";
				Player_Profile_Menu(Input[1]); // 7 options of Player Profile
				if (Input[1] == 7)
					break;
			}
			break;
		}
		case 2:	//Create Profile
		{
			system("CLS");
			SetConsoleCursorPosition(Console, { 54,5 });	cout << "Profile Creation";
			Driver::Increment_No_of_Profiles();
			SetConsoleCursorPosition(Console, { 50,7 });
			Player_profile[Driver::get_No_of_Player_Profiles()].set_Player_Name();
			break;
		}
		case 3: //Instructions
		{
			system("CLS");
			Print_GamePlay_Instructions(Player, 0);
			for (int i = 0; i < 454400000; i++) {}
			break;
		}
		}// End of Switch
		Main_Menu(Input[0], Player_profile);
	}//End OF While loop
	ofstream ofstream_ob2;
	ofstream_ob2.open("Player_profile.txt", ios::out);
	ofstream_ob2.write((char*)&Player_profile, sizeof(Player_profile));
	ofstream_ob2.close();
	ReponsiveUI.join();
}//End of Main