#include "Pawn.h"
#define PAWN_SIZE 0.4
Pawn::Pawn(){
	value = 1;
	justStarted = false;
}
//a
void Pawn::enPassant(Figure** enemies){
	Point leftPassant = location, rightPassant = location;
	leftPassant.x--;
	rightPassant.x++;
	if (side && location.y == 5 && pawnOnCell(enemies, leftPassant)) {
		leftPassant.y++;
		if ((bound && boundFields(leftPassant)) || !bound)
			possible_fields.push_back(leftPassant);
	}
	if (side && location.y == 5 && pawnOnCell(enemies, rightPassant)) {
		rightPassant.y++;
		if ((bound && boundFields(rightPassant)) || !bound)
			possible_fields.push_back(rightPassant);
	}
	if (!side && location.y == 4 && pawnOnCell(enemies, leftPassant)) {
		leftPassant.y--;
		if ((bound && boundFields(leftPassant)) || !bound)
			possible_fields.push_back(leftPassant);
	}
	if (!side && location.y == 4 && pawnOnCell(enemies, rightPassant)) {
		rightPassant.y--;
		if ((bound && boundFields(rightPassant)) || !bound)
			possible_fields.push_back(rightPassant);
	}
}

bool Pawn::pawnOnCell(Figure** enemies, Point a) {
	for (int i = 0; i < CNT; i++)
		if (enemies[i]->getLocation() == a && enemies[i]->getValue() == 1&&enemies[i]->getJustStarted())
			return true;
	return false;
}
void Pawn::texture(){
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.5, texture_color, 0.5);
	glVertex2f(location.getX()+ PAWN_SIZE,location.getY()+ PAWN_SIZE/3);//2.3 2.2
	glVertex2f(location.getX()+CELL- PAWN_SIZE, location.getY() + PAWN_SIZE/3);//2.7 2.2
	glVertex2f(location.getX() + PAWN_SIZE, location.getY()+CELL - PAWN_SIZE/3);//2.3 2.7
	glVertex2f(location.getX() + CELL - PAWN_SIZE, location.getY()+CELL- PAWN_SIZE/3);//2.7 2.7
	glEnd();
}

void Pawn::friendOnCell(Figure** friends, Point a) {
	for (int i = 0; i < CNT; i++)
		if (friends[i]->getLocation() == a) 
			friends[i]->setDefended(true);
}

void Pawn::firstMove(Figure **enemies, Figure** friends, bool kingCheck, vector<Point> check_list){
	Point ww,w;
	bool firstCell = false,secondCell=false;
	ww.x = location.x;
	side ? ww.y = location.y + 2 * CELL : ww.y = location.y - 2 * CELL;
	ww.safe =w.safe= true;
	w.x = location.x;
	side ? w.y = location.y + CELL : w.y = location.y - CELL;
	for (int i = 0; i < CNT; i++) {
		if (enemies[i]->getLocation() == w || friends[i]->getLocation() == w)
			firstCell = true;
		if (enemies[i]->getLocation() == ww || friends[i]->getLocation() == ww)
			secondCell = true;
	}
	if (!firstCell)
		if ((kingCheck && whenChecked(w, check_list)) || !kingCheck)
			if ((bound && boundFields(w)) || !bound) 
		possible_fields.push_back(w);
	if (!secondCell&&!touched&&!firstCell)
		if ((kingCheck && whenChecked(ww, check_list)) || !kingCheck)
			if ((bound && boundFields(ww)) || !bound) 
		possible_fields.push_back(ww);
}


void Pawn::fillPosibleFields(Figure** enemies, Figure** friends, Board board[][SIZE], bool kingCheck, vector<Point> check_list) {
	popFields();
	if (bound)
		fillBounded(friends,enemies,board);
	firstMove(enemies, friends,kingCheck, check_list);
	enPassant(enemies);
	Point wa, wd;
	wa.x = location.x - 1;
	wd.x = location.x + 1;
	side ? wa.y = wd.y = location.y + 1 : wa.y = wd.y = location.y - 1;	
	friendOnCell(friends, wa);
	friendOnCell(friends, wd);
	if (wa.x >= 1 && wa.x <= 8 && wa.y >= 1 && wa.y <= 8)
		side ? board[(int)wa.x - 1][(int)wa.y - 1].setDefByWhite(true) : board[(int)wa.x - 1][(int)wa.y - 1].setDefByBlack(true);
	if (wd.x >= 1 && wd.x <= 8 && wd.y >= 1 && wd.y <= 8)
		side ? board[(int)wd.x - 1][(int)wd.y - 1].setDefByWhite(true) : board[(int)wd.x - 1][(int)wd.y - 1].setDefByBlack(true);
	for (int i = 0; i < CNT; i++) {
		if (enemies[i]->getLocation() == wa)
			if ((kingCheck && whenChecked(wa, check_list)) || !kingCheck)
				if ((bound && boundFields(wa)) || !bound)
					possible_fields.push_back(wa);
		if (enemies[i]->getLocation() == wd)
			if ((kingCheck && whenChecked(wd, check_list)) || !kingCheck)
				if ((bound && boundFields(wd)) || !bound)
					possible_fields.push_back(wd);
	}
	filed = true;
}

bool Pawn::move(float x, float y, Figure** friends, Figure** enemies){
	Point passant;
	passant.y=y-1;
	passant.x = x;
	for(int i=0;i<CNT;i++)
		if (side&&pawnOnCell(enemies, passant)&&location.x!=x) {
			for (int i = 0; i < CNT; i++)
				if (enemies[i]->getLocation() == passant)
					enemies[i]->del();
		}
	passant.y = y + 1;
	if(!side && pawnOnCell(enemies, passant) && location.x != x) {
		for (int i = 0; i < CNT; i++)
			if (enemies[i]->getLocation() == passant)
				enemies[i]->del();
	}
	if (!touched && !justStarted)
		justStarted = true;
	else
		justStarted = false;
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
