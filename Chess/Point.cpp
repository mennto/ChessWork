#include "Point.h"

Point::Point(){
	x = 0;
	y = 0;
	safe = false;
}

Point::Point(float x, float y){
	this->x = x;
	this->y = y;
}

float Point::getX(){
	return x;
}
//a
float Point::getY(){
	return y;
}

bool Point::getSafe(){
	return safe;
}

void Point::setX(float x){
	this->x = x;
}

void Point::setY(float y){
	this->y = y;
}

void Point::setSafe(bool a){
	safe = a;
}

bool Point::operator==(Point& obj){
	return y == obj.y && x == obj.x;
}

Point Point::operator+(Point& obj){
	this->x += obj.x;
	this->y += obj.y;
	return *this;
}

Point Point::operator-(Point obj) {
	this->x -= obj.x;
	this->y -= obj.y;
	return *this;
}