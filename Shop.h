#pragma once
#include<iostream>
#include"Car.h"
using namespace std;
class Shop
{
protected:
	short Price;
public:
	Shop();
	Shop(short price);
	void set_Item_Price(short price);
	short get_price() const;
};
class Items_Shop : public Shop {
private:
	char Item_Name[50] = "";
public:
	void  set_Item_Name(string Name);
	char* get_Char_Item_Name();
	void Print_Details() const;
	void User_Input();
};
class Car_Shop : public Shop {
private:
	Car Cars;
public:
	Car_Shop();
	void set_Car_Shape(string Name);
	void set_Car_Width(short Car_Width);
	void set_Car_Height(short Car_Height);
	void set_Car_Color(short Car_Color);
	Car get_Car() const;
	short get_Car_Color() const;
	char* get_Car_Shape();
};