#include "Shop.h"

Shop::Shop() : Price(0) {}
Shop::Shop(short price) : Price(price) {}
void Shop::set_Item_Price(short price) { this->Price = price; }
short Shop::get_price() const { return Price; }

void  Items_Shop::set_Item_Name(string Name) { strcpy_s(Item_Name, Name.c_str()); }
char* Items_Shop::get_Char_Item_Name() { return Item_Name; }
void Items_Shop::Print_Details() const { cout << "\nName of item: "; cout << Item_Name;	cout << "\tPrice: "; cout << Price; }
void Items_Shop::User_Input()
{
	cin.ignore();		cout << "Enter Name of item:";			cin.getline(Item_Name, 50, '\n');
	cout << "Enter Price:"; 			cin >> Price;
}

Car_Shop::Car_Shop() { Price = 100; }
void Car_Shop::set_Car_Shape(string Name) { char Cararray[25]; strcpy_s(Cararray, Name.c_str());	Cars.set_Car_Shape(Cararray); }
void Car_Shop::set_Car_Width(short Car_Width) { Cars.set_Car_Width(Car_Width); }
void Car_Shop::set_Car_Height(short Car_Height) { Cars.set_Car_Height(Car_Height); }
void Car_Shop::set_Car_Color(short Car_Color) { Cars.set_Car_Color(Car_Color); }
Car Car_Shop::get_Car() const { return Cars; }
short Car_Shop::get_Car_Color() const { return Cars.get_Car_Color(); }
char* Car_Shop::get_Car_Shape() { return Cars.get_Car_Shape(); }