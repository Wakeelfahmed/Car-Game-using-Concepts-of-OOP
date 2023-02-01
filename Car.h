#pragma once
class Car {
protected:
	char Car_Shape[25]{ 0 };
	int Car_Color;
	int Car_Width;
	int Car_Height;
public:
	Car();
	void set_Car_Shape(char New_Car_Shape[]);
	void set_Car_Color(int New_Car_Color);
	void set_Car_Width(int New_Car_Height);
	void set_Car_Height(int New_Car_Height);
	int get_Car_Color() const;
	int get_Car_Width() const;
	int get_Car_Height() const;
	char* get_Car_Shape();
	~Car();
};