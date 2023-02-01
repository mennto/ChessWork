#include "Bishop.h"
#define BISHOP_SIZE 0.2
Bishop::Bishop(){
	value = 3;
}

void Bishop::texture(){
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(0.5,texture_color, 0.5);
	glVertex2f(location.getX() - BISHOP_SIZE + CELL, location.getY() + BISHOP_SIZE);
	glVertex2f(location.getX() + BISHOP_SIZE, location.getY() - BISHOP_SIZE + CELL);
	glEnd();
}

bool Bishop::enemyOnCell(Figure** enemies,Point a, Figure*& enemyObj) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a) {
			enemyObj = enemies[i];
			return true;
		}
	return false;
}

bool Bishop::friendOnCell(Figure** friends, Point a) {
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) {
			friends[i]->setDefended(true);
			return true;
		}
	return false;
}

void Bishop::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list) {
	popFields();
	Point a;
	Figure* enemyObj;
	int x, y, dx = 1, dy = 1, kof = -1;
	int loop = 1;
	bool onCell = false;
	if (bound)
		fillBounded(friends, enemies, board);
	while (loop++ <= 4) {
		x = location.x + dx;
		y = location.y + dy;
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
						buf.x += dx;
						buf.y += dy;
					}
				}
				else {
					Point buf;
					buf = a;
					Figure* nextEnemy;
					while (buf.x >= 1 && buf.x <= 8 &&
						buf.y >= 1 && buf.y <= 8) {
						buf.x += dx;
						buf.y += dy;
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
			x += dx;
			y += dy;
		}
		onCell = false;
		if (loop % 2)
			dx *= kof;
		else
			dy *= kof;
	}
	filed = true;
}