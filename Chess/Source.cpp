#include <GLFW/glfw3native.h>
#include<iostream>
#include <thread>
#include <chrono>
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Figure.h"
#include "Func.h"
#include "Board.h"
using namespace std;

float x, y;
bool active,turn,panel,endGame;//true-white false-black
Figure* buf;
vector <Point>check_listW;
vector <Point>check_listB;
vector <Figure*> transform;
Figure* lastLine;
Rook* pNewRook;
Board board[SIZE][SIZE];//наше поле
//WHITE FIGURES
Pawn w1, w2, w3, w4, w5, w6, w7, w8;
Rook wr1,wr2;
Knight  wk1, wk2;
Bishop wb1, wb2;
Queen whiteQueen;
King whiteKing;
Figure* white[CNT] = {&wr1,&wk1,&wb1,&whiteQueen,&whiteKing,&wb2,&wk2, &wr2, &w1, &w2, &w3, &w4, &w5, &w6, &w7, &w8 };
//BLACK FIGURES
Pawn  b1, b2, b3, b4, b5, b6, b7, b8;
Rook br1, br2;
Knight bk1, bk2;
Queen blackQueen;
King blackKing;
Bishop bb1, bb2;
Figure* black[CNT] = {&br1,&bk1,&bb1,&blackQueen,&blackKing,&bb2,&bk2 ,&br2, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8};
//пешка->ладья->конь->слон->ферзь->король
void pawnOnLastLine(Figure** mas) {
    for (int i = 8; i < CNT; i++) 
        if (mas[i]->getSide() && mas[i]->getLocation().getY() == 8&&mas[i]->getValue()==1||
            !mas[i]->getSide() && mas[i]->getLocation().getY() == 1 && mas[i]->getValue() == 1) {
            lastLine = mas[i];
            panel = true;
        }
}

void drawPanel() {
    DrawSquare(4, 4, 0.255, 0.128, 0);
    DrawSquare(4, 5, 0.255, 0.128, 0);
    DrawSquare(5, 4, 0.255, 0.128, 0);
    DrawSquare(5, 5, 0.255, 0.128, 0);
    Queen fakeQ;
    Bishop fakeB;
    Rook fakeR;
    Knight fakeK;
    fakeQ.setX(4);
    fakeQ.setY(4);
    fakeQ.setTextureColor(lastLine->getTextureColor());
    fakeQ.texture();
    fakeR.setX(4);
    fakeR.setY(5);
    fakeR.setTextureColor(lastLine->getTextureColor());
    fakeR.texture();
    fakeB.setX(5);
    fakeB.setY(4);
    fakeB.setTextureColor(lastLine->getTextureColor());
    fakeB.texture();
    fakeK.setX(5);
    fakeK.setY(5);
    fakeK.setTextureColor(lastLine->getTextureColor());
    fakeK.texture();
}

void endMoveForWhite() {
    for (int i = 0; i < CNT; i++) 
        white[i]->setJustStarted(false);
}

void endMoveForBlack() {
    for (int i = 0; i < CNT; i++) 
        black[i]->setJustStarted(false);
}

void popCheckList() {
    int amountW = check_listW.size(), amountB = check_listB.size();
    for (int i = 0; i < amountW; i++)
        check_listW.pop_back();
    for (int i = 0; i < amountB; i++)
        check_listB.pop_back();
}
void fillBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            board[i][j].setX(i+1);
            board[i][j].setY(j+1);
        }
}

void check() {
    if (whiteKing.getCheck())
        DrawSquare(whiteKing.getLocation().getX(), whiteKing.getLocation().getY(), true);
    if (blackKing.getCheck())
        DrawSquare(blackKing.getLocation().getX(), blackKing.getLocation().getY(), true);
}

void cleanDefended() {
    for (int i = 0; i < CNT; i++) {
        white[i]->setDefended(false);
        black[i]->setDefended(false);
    }
}

void cleanBoundForWhite() {
    for (int i = 0; i < CNT; i++) {
        white[i]->setBound(false);
        white[i]->popBounded();
    }
}

void cleanBoundForBlack() {
    for (int i = 0; i < CNT; i++) {
        black[i]->setBound(false);
        black[i]->popBounded();
    }
}
 
void refreshBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            board[i][j].setDefByWhite(false);
            board[i][j].setDefByBlack(false);
        }
}

void fillPosibleWays() {
    for (int i = 0; i < CNT; i++) {
        white[i]->fillPosibleFields(black,white,board,whiteKing.getCheck(),check_listW);
        black[i]->fillPosibleFields(white,black, board,blackKing.getCheck(),check_listB);
    }
    blackKing.fillPosibleFields(white,black, board,blackKing.getCheck(),check_listB);
    whiteKing.fillPosibleFields(black, white, board,whiteKing.getCheck(),check_listW);
}

int focus(int x,int y) {
    return (x % 2 + y % 2) % 2;
}

void identifyFigures(Figure **mas,int beg,int slice,bool side) {
    Point x;
    int count=0,limit=beg+2*slice;
    for(int i=beg;i!=limit;i+=slice)
        for (int j = 1; j <= SIZE; j++) {
            x.setX(j);
            x.setY(i);
            mas[count]->setLocation(x);
            mas[count]->setTextureColor(side);
            mas[count]->setSide(side);
            count++;
        }
}
void showFigures() {
    for (int i = 0; i < 16; i++) {
        white[i]->texture();
        black[i]->texture();
    }
}

void StartGame() {
    glLoadIdentity();
    glScalef(1 / (KOF * SIZE), 1 / (KOF * SIZE), 1);
    glTranslatef(-SIZE* KOF - 1, -SIZE * KOF - 1, 0);
    for (int x = 1; x <= SIZE; x++)
        for (int y = 1; y <= SIZE; y++) {
            int color = focus(x, y);
            DrawSquare(x, y,color ,color, color);
        }
}

void figuresWalk(Figure** mas,float x,float y,Figure** enemies,King friendKing, vector<Point> check_list) {
    float minX,minY;
    for (int i = 0; i < CNT; i++) {
        minX = mas[i]->getLocation().getX();
        minY = mas[i]->getLocation().getY();
        if (x >= minX + 0.01 && x <= minX + CELL - 0.01 &&
            y >= minY + 0.01 && y <= minY + CELL - 0.01) {
            mas[i]->setTextureColor(0.5);
             mas[i]->fillPosibleFields(enemies, mas,board,friendKing.getCheck(),check_list);//перенесты от сюдова нахрен
            active = true;
            buf = mas[i];
            return;
        }
    }

}

static void cursorPosithionCallBack(GLFWwindow* window, double xPos, double yPos) {
    x = (xPos/(HIGHT/2)*4)+1;
    y = (-yPos/(WIDE/2))*4+9;
}

bool checkCell(Figure** mas, int x, int y, Figure *&bufer) {
    for (int i = 0; i < CNT; i++)
        if (mas[i]->getLocation().getX() == x &&
            mas[i]->getLocation().getY() == y) {
            bufer = mas[i];
            return true;
        }
    return false;
}

void moveProcedure(Figure** friends,Figure** enemies) {
    int dx = x, dy = y;
    bool enemyOnCell = false;
    Figure* buf2=NULL;
    if (buf->getSide())
        enemyOnCell=checkCell(black, dx, dy, buf2);
    else
        enemyOnCell=checkCell(white, dx, dy, buf2);
    if (buf->move(dx, dy,friends,enemies)) {
        turn = !turn;
        if (enemyOnCell)
            buf2->del();
    }
    buf->setTextureColor(buf->getSide());
    buf = NULL;
    active = false;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    glfwSetCursorPosCallback(window, cursorPosithionCallBack);
    if (panel) {
        if (x >= 4 && x <= 6 && y >= 4 && y <= 6) {
            Queen *newQueen=new Queen();
            transform.push_back(newQueen);
            if (x >= 4 && x <= 5 && y >= 4 && y <= 5) {
                newQueen->setLocation(lastLine->getLocation());
                newQueen->setSide(lastLine->getSide());
                newQueen->setTextureColor(lastLine->getTextureColor());
                for (int i = 8; i < CNT; i++) {
                    if (white[i]->getLocation().getY() == 8 && white[i]->getValue() == 1)
                        white[i] = newQueen;
                    if (black[i]->getLocation().getY() == 1 && black[i]->getValue() == 1)
                        black[i] = newQueen;
                }
            }
            if (x >= 4 && x <= 5 && y >= 5 && y <= 6) {
                Rook* newRook = new Rook();
                transform.push_back(newQueen);
                newRook->setLocation(lastLine->getLocation());
                newRook->setSide(lastLine->getSide());
                newRook->setTextureColor(lastLine->getTextureColor());
                for (int i = 8; i < CNT; i++) {
                    if (white[i]->getLocation().getY() == 8 && white[i]->getValue() == 1)
                        white[i] = newRook;
                    if (black[i]->getLocation().getY() == 1 && black[i]->getValue() == 1)
                        black[i] = newRook;
                }
            }
            if (x >= 5 && x <= 6 && y >= 5 && y <= 6) {
                Knight* newKnight = new Knight();
                transform.push_back(newQueen);
                newKnight->setLocation(lastLine->getLocation());
                newKnight->setSide(lastLine->getSide());
                newKnight->setTextureColor(lastLine->getTextureColor());
                for (int i = 8; i < CNT; i++) {
                    if (white[i]->getLocation().getY() == 8 && white[i]->getValue() == 1)
                        white[i] = newKnight;
                    if (black[i]->getLocation().getY() == 1 && black[i]->getValue() == 1)
                        black[i] = newKnight;
                }
            }
            if (x >= 5 && x <= 6 && y >= 4 && y <= 5) {
                Bishop* newBishop = new Bishop();
                transform.push_back(newQueen);
                newBishop->setLocation(lastLine->getLocation());
                newBishop->setSide(lastLine->getSide());
                newBishop->setTextureColor(lastLine->getTextureColor());
                for (int i = 8; i < CNT; i++) {
                    if (white[i]->getLocation().getY() == 8 && white[i]->getValue() == 1)
                        white[i] = newBishop;
                    if (black[i]->getLocation().getY() ==1  && black[i]->getValue() == 1)
                        black[i] = newBishop;
                }
            }
            panel = false;
            lastLine->del();
            lastLine = NULL;
        }
    }
    else    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (x >= 4&& x <=5 && y >= 6&& y <= 7)
            int a = 1;
      
        if (turn)
            if (!active) {     
                figuresWalk(white, x, y, black,whiteKing,check_listW);
               refreshBoard();
            }
            else {
                moveProcedure(white,black);
                pawnOnLastLine(white);
                cleanDefended();   
                endMoveForBlack();
                cleanBoundForBlack();
                cleanBoundForWhite();
                fillPosibleWays();
                popCheckList();
                whiteKing.isCheck(black,check_listW);
                blackKing.isCheck(white,check_listB);
                fillPosibleWays();
                if (blackKing.isMate(black)) {
                    cout << "WHITE WINS";
                    endGame = true;
                    return;
                }
            }
        else
            if (!active) {
                figuresWalk(black, x, y, white,blackKing,check_listB);
               refreshBoard();
            }
            else {
                moveProcedure(black,white);
                pawnOnLastLine(black);
                cleanDefended();
                endMoveForWhite();
                cleanBoundForBlack();
                cleanBoundForWhite();
                fillPosibleWays();
                popCheckList();
                whiteKing.isCheck(black,check_listW);
                blackKing.isCheck(white,check_listB);
                fillPosibleWays();
                if (whiteKing.isMate(white)) {
                    cout << "BLACK WINS";
                    endGame = true;
                    return;
                }
            }
      
    }
}

int main(void){
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(HIGHT, WIDE, "Chess", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    identifyFigures(white,1,1,true);
    identifyFigures(black, 8,-1, false);
    fillBoard();
    turn = true;
    endGame = false;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        StartGame();
        showFigures();
        glfwSetMouseButtonCallback(window,mouse_button_callback);
        if (active)
            buf->showPosibleFields();
        if (panel)
            drawPanel();
        check();
        if (endGame)
            if (whiteKing.isMate(white))
                DrawMATE(whiteKing.getLocation().getX(), whiteKing.getLocation().getY());
            else
                DrawMATE(blackKing.getLocation().getX(), blackKing.getLocation().getY());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}