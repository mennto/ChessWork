#include "Queen.h"
#define QUEEN_SIZE 0.27
Queen::Queen(){
	fillHelper();
	value = 8;
}

void Queen::texture() {
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.5, texture_color, 0.5);
	glVertex2f(location.getX() + 0.5, location.getY() + QUEEN_SIZE);
	glVertex2f(location.getX() + 0.5, location.getY() + CELL - QUEEN_SIZE);
	glVertex2f(location.getX() + QUEEN_SIZE, location.getY() + 0.5);
	glVertex2f(location.getX() + CELL - QUEEN_SIZE, location.getY() + 0.5);
	glVertex2f(location.getX() + CELL - QUEEN_SIZE, location.getY() + CELL - QUEEN_SIZE);
	glVertex2f(location.getX() + QUEEN_SIZE, location.getY() + QUEEN_SIZE);
	glVertex2f(location.getX() - QUEEN_SIZE + CELL, location.getY() + QUEEN_SIZE);
	glVertex2f(location.getX() + QUEEN_SIZE, location.getY() - QUEEN_SIZE + CELL);
	glEnd();
}

void Queen::fillHelper(){
	int masX[] = { 0,1,1,1,0,-1,-1,-1 };
	int masY[] = { 1,1,0,-1,-1,-1,0,1 };
	Point a;
	for (int i = 0; i < 8; i++) {
		a.x = masX[i];
		a.y = masY[i];
		helper.push_back(a);
	}
}

void Queen::popHelper(){
	int amount = helper.size();
	for (int i = 0; i < amount; i++)
		helper.pop_back();
}

int Queen::findKing(){
	return 0;
}

bool bounded(Point a, Figure** enemies) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getValue() == 10 && enemies[i]->getLocation() == a)
			return true;
	return false;
}

bool Queen::enemyOnCell(Figure** enemies, Point a,Figure *&enemyobj){
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a) {
			enemyobj = enemies[i];
			return true;
		}
	return false;
}

bool Queen::friendOnCell(Figure** friends, Point a){
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) {
			friends[i]->setDefended(true);
			return true;
		}
	return false;
}

void Queen::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list){
	popFields();
	bool onCell = false;//кто-то на клетке
	int x, y,dx=0,dy=0;
	Point a;
	Figure* enemyObj;		
	int loop = 0;
	if (bound)
		fillBounded(friends, enemies, board);
	while (loop <= helper.size() - 1) {
		x = location.x + helper[loop].x;
		y = location.y + helper[loop].y;
		while (x >= 1 && x <= 8 &&
			y >= 1 && y <= 8 && !onCell) {
			a.x = x;
			a.y = y;
			if (friendOnCell(friends, a))
				onCell = true;
			else if (enemyOnCell(enemies, a, enemyObj)) {
				if (enemyObj->getValue() == 10) {
					Point buf;
					buf = a;
					while (buf.x >= 1 && buf.x <= 8 &&
						buf.y >= 1 && buf.y <= 8) {
						side ? board[(int)buf.x - 1][(int)buf.y - 1].setDefByWhite(true) : board[(int)buf.x - 1][(int)buf.y - 1].setDefByBlack(true);
						buf.x += helper[loop].x;
						buf.y += helper[loop].y;
					}
				}
				else {
					Point buf;
					buf = a;
					Figure* nextEnemy;
					while (buf.x >= 1 && buf.x <= 8 &&
						buf.y >= 1 && buf.y <= 8) {
						buf.x += helper[loop].x;
						buf.y += helper[loop].y;
						if (enemyOnCell(enemies, buf, nextEnemy))
							if (nextEnemy->getValue() == 10)
								enemyObj->setBound(true);
							else
								break;
					}
				}
				if ((kingCheck && whenChecked(a, check_list)) || !kingCheck) {
					if ((bound && boundFields(a)) || !bound) {
						side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
						possible_fields.push_back(a);
						onCell = true;
					}
				}
			}
			else {
				if ((kingCheck && whenChecked(a, check_list)) || !kingCheck) {
					if ((bound && boundFields(a)) || !bound) {
						side ? board[(int)a.x - 1][(int)a.y - 1].setDefByWhite(true) : board[(int)a.x - 1][(int)a.y - 1].setDefByBlack(true);
						possible_fields.push_back(a);
					}
				}
			}
			x += helper[loop].x;
			y += helper[loop].y;
		}
		onCell = false;
		loop++;
	}
	filed = true;	
}
