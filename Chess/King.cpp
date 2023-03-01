#include "King.h"
#define KING_SIZE 0.2
King::King(){
	fillHelper();
	value = 10;
	leftCastling = false;
	rightCastling = false;
}

bool King::getCheck(){
	return check;
}//a

bool King::isMate(Figure** friends){
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getPosibleFields().size() > 0)
			return false;
	return true;
}

bool King::enemyFields(Figure *a,Point j){
	vector<Point> buf = a->getPosibleFields();
	for (int i = 0; i < buf.size(); i++)
		if (buf[i] == j&&!buf[i].safe)
			return true;
	return false;
}

bool King::isCheck(Figure** enemies,vector<Point> &check_list) {
	for (int i = 0; i < CNT; i++)
		if (enemyFields(enemies[i],location)) {
			int x1 = enemies[i]->getLocation().x - location.x;
			int y1 = enemies[i]->getLocation().y - location.y;
			while (x1 != 0 || y1 != 0) {
				Point checkPoint(location.x+x1, location.y+y1);
				check_list.push_back(checkPoint);
				if (x1 > 0)
					x1--;
				else if (x1 < 0)
					x1++;
				if (y1 > 0)
					y1--;
				else if (y1 < 0)
					y1++;
			}
				check = true;
			return true;
		}
		else
			check = false;
	return false;
}

void King::texture(){
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.5, texture_color, 0.5);
	glVertex2f(location.getX() + 0.5, location.getY() + KING_SIZE);
	glVertex2f(location.getX() + 0.5, location.getY() + CELL - KING_SIZE);
	glVertex2f(location.getX() + KING_SIZE, location.getY() + 0.5);
	glVertex2f(location.getX() + CELL - KING_SIZE, location.getY() + 0.5);
	glEnd();
}

void King::fillHelper(){
	int masX[] = { 0,1,1,1,0,-1,-1,-1 };
	int masY[] = { 1,1,0,-1,-1,-1,0,1 };
	Point a;
	for (int i = 0; i < 8; i++) {
		a.x = masX[i];
		a.y = masY[i];
		helper.push_back(a);
	}
}


bool King::move(float x, float y, Figure** friends, Figure** enemies){
	if (x + 2 == location.x&&rightCastling) {
		Point rookL;
		rookL.x = 4;
		side ? rookL.y = 1 : rookL.y = 8;
		location.x = x;
		friends[0]->setLocation(rookL);
		rightCastling = false;
		return true;
	}
	if (x - 2 == location.x&&leftCastling) {
		Point rookL;
		rookL.x = 6;
		side ? rookL.y = 1 : rookL.y = 8;
		location.x = x;
		friends[7]->setLocation(rookL);
		leftCastling = false;
		return true;
	}
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

bool King::defCell(Figure** enemies, Point a){
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation()==a&&enemies[i]->getDefended())
			return true;
	return false;
}

bool King::friendOnCell(Figure** friends, Point a){
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) {
			friends[i]->setDefended(true);
			return true;
		}
	return false;
}

bool King::enemyOnCell(Figure** enemies, Point a) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a)
			return true;
	return false;
}

void King::castling(Figure** friends,Figure** enemies,Board board[][SIZE]) {
	Point a1=location,a2=location,a3=location;
	if (!touched && !friends[0]->getTouched()) {
		a1.x += 1;
		a2.x += 2;
		if (side) {
			if (!friends[0]->getTouched() && !board[(int)a1.x - 1][(int)a1.y - 1].getDefByBlack() && !friendOnCell(friends, a1) && !enemyOnCell(enemies, a1))
				if (!board[(int)a2.x - 1][(int)a2.y - 1].getDefByBlack() && !friendOnCell(friends, a2) && !enemyOnCell(enemies, a2)) {
					possible_fields.push_back(a2);
					leftCastling = true;
				}
		}
		else
			if (!friends[0]->getTouched() && !board[(int)a1.x - 1][(int)a1.y - 1].getDefByWhite() && !friendOnCell(friends, a1) && !enemyOnCell(enemies, a1))
				if (!board[(int)a2.x - 1][(int)a2.y - 1].getDefByWhite() && !friendOnCell(friends, a2) && !enemyOnCell(enemies, a2)) {
					possible_fields.push_back(a2);
					leftCastling = true;
				}
		a1.x =location.x-1;
		a2.x = location.x - 2;
		a3.x = location.x - 3;
		if (side) {
			if (!friends[7]->getTouched() && !board[(int)a1.x - 1][(int)a1.y - 1].getDefByBlack() && !friendOnCell(friends, a1) && !enemyOnCell(enemies, a1))
				if (!board[(int)a2.x - 1][(int)a2.y - 1].getDefByBlack() && !friendOnCell(friends, a2) && !enemyOnCell(enemies, a2))
					if (!friendOnCell(friends, a3) && !enemyOnCell(enemies, a3)) {
						possible_fields.push_back(a2);
						rightCastling = true;
					}
		}
		else
			if (!friends[7]->getTouched() && !board[(int)a1.x - 1][(int)a1.y - 1].getDefByWhite() && !friendOnCell(friends, a1) && !enemyOnCell(enemies, a1))
				if (!board[(int)a2.x - 1][(int)a2.y - 1].getDefByWhite() && !friendOnCell(friends, a2) && !enemyOnCell(enemies, a2))
					if (!friendOnCell(friends, a3) && !enemyOnCell(enemies, a3)) {
						possible_fields.push_back(a2);
						rightCastling = true;
					}
	}
}

void King::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list){
	popFields();
	Point a;
	bool enemyPosibleWay;
	bool defendedCell;
	castling(friends, enemies, board);
	for (int i = 0; i < 8; i++) {
		enemyPosibleWay = false;
		defendedCell = false;
		a.x = location.x + helper[i].x;
		a.y = location.y + helper[i].y;
		if (a.x >= 1 && a.x <= 8 &&
			a.y >= 1 && a.y <= 8) {
			for (int j = 0; j < CNT; j++) {
				if (!enemyPosibleWay)
					enemyPosibleWay = enemyFields(enemies[j], a);
				defendedCell = defCell(enemies, a);
				if (!defendedCell)
					defendedCell = defCell(enemies, a);
			}
			if (side && !friendOnCell(friends, a) && !enemyPosibleWay && !defendedCell && !board[(int)a.x - 1][(int)a.y - 1].getDefByBlack()) {
				side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
				possible_fields.push_back(a);
			}
			else if (!side && !friendOnCell(friends, a) && !enemyPosibleWay && !defendedCell && !board[(int)a.x - 1][(int)a.y - 1].getDefByWhite()) {
				side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
				possible_fields.push_back(a);
			}
		}
	}
	filed = true;
}
