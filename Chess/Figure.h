#pragma once
#include<GLFW/glfw3.h>
#include <vector>
#include "Const.h"
#include "Point.h"
#include "Func.h"
#include "Board.h"

using namespace std;
//a
class Figure {
protected:
	Point location;
	vector <Point> possible_fields;
	vector <Point> bounded_fields;
	bool touched;
	bool justStarted;
	float texture_color;
	int value;
	bool filed;
	bool defended;
	bool bound;
	bool side; //true-white false-black
public:
	Figure();
	Figure(float x,float y);

	vector<Point> getPosibleFields();
	Point getLocation();
	
	bool getTouched();
	bool getSide();
	bool getFiled();
	bool getDefended();
	bool getBound();
	int getValue();
	bool getJustStarted();
	float getTextureColor();
	
	void setJustStarted(bool a);
	void setFiled(bool a);
	void setSide(bool a);
	void setX(float x);
	void setY(float y);
	void setLocation(Point a);
	void setTouched(bool a);
	void setTextureColor(float a);
	void setDefended(bool a);
	void setBound(bool a);

	void showPosibleFields();
	void del(); 
	bool enemyOnCell(Figure** enemies, Point a);
	void fillBounded(Figure** friends,Figure** enemies, Board board[][SIZE]);
	bool boundFields(Point a);
	void popBounded();
	void popFields();
	bool whenChecked(Point a,vector<Point> check_list);

	virtual void texture() = 0;
	virtual bool move(float x, float y,Figure **friends, Figure** enemies);
	
	
	virtual void fillPosibleFields(Figure** enemies, Figure** friends,Board board[][SIZE], bool kingCheck, vector<Point> check_list);
};