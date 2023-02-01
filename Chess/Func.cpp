#include "Func.h"

void DrawSquare(float x, float y, float red, float green, float blue) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(red, green, blue);
    glVertex2f(x, y);
    glVertex2f(x + CELL, y);
    glVertex2f(x, y + CELL);
    glVertex2f(x + CELL, y + CELL);
    glEnd();
}

void DrawSquare(float x, float y,bool check){
    glBegin(GL_TRIANGLE_STRIP);
    if (check)
        glColor3f(1, 0, 0);
    else
        glColor3f(0, 0, 1);
    glVertex2f(x, y);
    glVertex2f(x + 2*FAULT, y);
    glVertex2f(x, y + 2*FAULT);
    glVertex2f(x + 2*FAULT, y + 2*FAULT);
    glEnd();
}

void DrawMATE(float x, float y){
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.8, 0.4, 0.2);
    glVertex2f(x, y);
    glVertex2f(x + CELL, y);
    glVertex2f(x, y + CELL);
    glVertex2f(x + CELL, y + CELL);
    glEnd();
}

void DrawTransformationPanel(float x, float y){
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.255, 0.128, 0);
    glVertex2f(x, y);
    glVertex2f(x + 4, y);
    glVertex2f(x, y + CELL);
    glVertex2f(x + 4, y + CELL);
        glEnd();
}
