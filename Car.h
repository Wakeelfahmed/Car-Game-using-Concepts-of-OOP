#pragma once
class Car {
private:
	short Car_Color{ 10 };
	short Car_Width{ 4 };
	short Car_Height{ 5 };
public:
	char Car_Shape[25]{ 0 };
	void set_Car_Shape(char New_Car_Shape[]);
	void set_Car_Color(short New_Car_Color);
	void set_Car_Width(short New_Car_Height);
	void set_Car_Height(short New_Car_Height);
	short get_Car_Color() const;
	short get_Car_Width() const;
	short get_Car_Height() const;
	char* get_Car_Shape();
	~Car();
};