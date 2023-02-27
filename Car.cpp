#include "Car.h"
#include<string>
//Car::Car() : Car_Color(10), Car_Width(4), Car_Height(5) {}
void Car::set_Car_Shape(char New_Car_Shape[]) { strcpy_s(Car_Shape, New_Car_Shape); }
void Car::set_Car_Color(short New_Car_Color) { Car_Color = New_Car_Color; }
void Car::set_Car_Width(short New_Car_Height) { Car_Width = New_Car_Height; }
void Car::set_Car_Height(short New_Car_Height) { Car_Height = New_Car_Height; }
short Car::get_Car_Color() const { return Car_Color; }
short Car::get_Car_Width() const { return Car_Width; }
short Car::get_Car_Height() const { return Car_Height; }
char* Car::get_Car_Shape() { return Car_Shape; }
Car::~Car() {
	strcpy_s(Car_Shape, " ");
}