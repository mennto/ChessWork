#pragma once
struct Point{
	float x; 
	float y;
	bool safe;
public:
	Point();
	Point(float x, float y);

	float getX();
	float getY();
	bool getSafe();

	void setX(float x);
	void setY(float y);
	void setSafe(bool a);

	bool operator ==(Point& obj);
	Point operator+(Point& obj);
	Point operator-(Point obj);
};