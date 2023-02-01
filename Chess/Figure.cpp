#include "Figure.h"

Figure::Figure(){
}

Figure::Figure(float x, float y) {
	location.setX(x);
	location.setY(y);
}

vector<Point> Figure::getPosibleFields(){
	return possible_fields;
}

//get
Point Figure::getLocation(){
	return location;
}

bool Figure::getTouched(){
	return touched;
}

bool Figure::getSide(){
	return side;
}

bool Figure::getFiled(){
	return filed;
}

bool Figure::getDefended(){
	return defended;
}

bool Figure::getBound(){
	return bound;
}

int Figure::getValue(){
	return value;
}

bool Figure::getJustStarted() {
	return justStarted;
}

float Figure::getTextureColor(){
	return texture_color;
}

void Figure::setJustStarted(bool a) {
	justStarted = a;
}

void Figure::setFiled(bool a){
	filed = a;
}

//set
void Figure::setSide(bool a){
	side = a;
}

void Figure::setX(float x){
	location.setX(x);
}

void Figure::setY(float y){
	location.setY(y);
}

void Figure::setLocation(Point a){
	location = a;
}

void Figure::setTouched(bool a){
	touched = a;
}

void Figure::setTextureColor(float a){
	texture_color = a;
}

void Figure::setDefended(bool a){
	defended = a;
}

void Figure::setBound(bool a){
	bound = a;
}

//FUNC
void Figure::texture() {
}


void Figure::showPosibleFields() {
	for (int i = 0; i < possible_fields.size(); i++)
		DrawSquare(possible_fields[i].x, possible_fields[i].y,false);
}

void Figure::del(){//перву фигуру яку встречаешь, проверяешь есть ли за ней король, если да то связываешь
	location.x = 10;
	location.y = 10;
}

bool Figure::enemyOnCell(Figure** enemies, Point a) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a)
			return true;
	return false;
}

void Figure::fillBounded(Figure** friends, Figure** enemies, Board board[][SIZE]){
	Point buf;
	Figure* friendKing=friends[4];
	buf.x = location.x - friendKing->getLocation().x;
	buf.y = location.y - friendKing->getLocation().y;
	int dx = 0, dy = 0;
	if (buf.x > 0)
		dx = 1;
	else if(buf.x<0)
		dx = -1;
	if (buf.y > 0)
		dy = 1;
	else if(buf.y<0)
		dy = -1;
	Point a;
	a.x = friendKing->getLocation().getX();
	a.y = friendKing->getLocation().getY();
	while (a.x >= 1 && a.x <= 8 && a.y >= 1 && a.y <= 8 && !enemyOnCell(enemies, a)) {
		a.x += dx;
		a.y += dy;
		if (a.x != location.x || a.y != location.y) {
			side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
			bounded_fields.push_back(a);
		}
	}
}

bool Figure::boundFields(Point a){
	for (int i = 0; i < bounded_fields.size(); i++)
		if (bounded_fields[i] == a)
			return true;
	return false;
}

void Figure::popBounded(){
	int amount = bounded_fields.size();
	for (int i = 0; i < amount; i++)
		bounded_fields.pop_back();
}


void Figure::popFields() {
	int amount = possible_fields.size();
	for (int i = 0; i < amount; i++)
		possible_fields.pop_back();
	filed = false;
}

bool Figure::whenChecked(Point a,vector<Point> check_list){
	for (int i = 0; i < check_list.size(); i++)
		if (check_list[i] == a)
			return true;
	return false;
}

void Figure::fillPosibleFields(Figure** enemies, Figure** friends,Board board[][SIZE], bool kingCheck, vector<Point> check_list){
}

bool Figure::move(float x, float y, Figure** friends,Figure** enemies) {
	for (int i = 0; i < possible_fields.size(); i++)
		if (possible_fields[i].x == x &&
			possible_fields[i].y == y) {
			location.x = possible_fields[i].x;
			location.y = possible_fields[i].y;
			touched = true;
			popFields();
			return true;
		}
	//popFields();
	return false;
}