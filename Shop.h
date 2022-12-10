#pragma once
#include<iostream>
#include"Car.h"
using namespace std;
class Shop
{
protected:
	int Price;
public:
	Shop();
	Shop(int price);
	void set_Item_Price(int price);
	int get_price() const;
};
class Items_Shop : public Shop {
private:
	char Item_Name[50] = "";
public:
	void  set_Item_Name(string Name);
	char* get_Char_Item_Name();
	void Print_Details();
	void User_Input();
};
class Car_Shop : public Shop {
private:
	Car Cars;
public:
	Car_Shop();
	void set_Car_Shape(string Name);
	void set_Car_Width(int Car_Width);
	void set_Car_Height(int Car_Height);
	void set_Car_Color(int Car_Color);
	Car get_Car() const;
	int get_Car_Color() const;
	char* get_Car_Shape();
};