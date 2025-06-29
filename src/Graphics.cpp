#ifndef Graphics_CPP
#define Graphics_CPP

#include "../lib/glfw3.h"
#include "Game.cpp"
#include <cmath>

struct Color {
    float red;
    float green;
    float blue;
};

void numberRend(int xPos, int yPos, int num, Color color);
void flagRend(int xPos, int yPos);
void tileRend(int xPos, int yPos, Color color, bool mine);
void numberColorController(int xPos, int yPos);

enum Mode {
    GREEN,
    RED,
    GRAY
};


void tileRendColorized(int xPos, int yPos, Color color) {
    switch (Field[yPos][xPos].doType)
    {
    case OPENED:
        switch (Field[yPos][xPos].tileType) {
        case MINE:
            tileRend(xPos, yPos, color, true);
            break;
        case EMPTY:
            tileRend(xPos, yPos, color, false);
            numberColorController(xPos, yPos);
            break;
        }
        break;
    case FLAG:
        tileRend(xPos, yPos, color, false);
        flagRend(xPos, yPos);
        break;
    case NONE:
        tileRend(xPos, yPos, color, false);
        break;
    }
}

void tileRendController(int xPos, int yPos, Mode mode) // Контроллер который определяет как рендерить ячейку
{
    switch (mode) {
    case RED:
        tileRendColorized(xPos, yPos, Color{.7f, .2f, .2f});
        break;
    case GREEN:
        tileRendColorized(xPos, yPos, Color{.2f, 1.f, .2f});
        break;
    case GRAY:
        tileRendColorized(xPos, yPos, Color{1.f, 1.f, 1.f});
        break;
    }
}

void numberColorController(int xPos, int yPos)
{ // Контроллер который определяет как рендерить цвет числа
    int num = Field[yPos][xPos].minesNearbyCount;
    switch (num)
    {
    case 1:
        numberRend(xPos, yPos, num, Color{0.0f, 0.0f, 0.7f});
        break;
    case 2:
        numberRend(xPos, yPos, num, Color{0.0f, 0.7f, 0.7f});
        break;
    case 3:
        numberRend(xPos, yPos, num, Color{0.0f, 0.7f, 0.0f});
        break;
    case 4:
        numberRend(xPos, yPos, num, Color{0.35f, 0.7f, 0.0f});
        break;
    case 5:
        numberRend(xPos, yPos, num, Color{0.7f, 0.7f, 0.0f});
        break;
    case 6:
        numberRend(xPos, yPos, num, Color{0.7f, 0.35f, 0.0f});
        break;
    case 7:
        numberRend(xPos, yPos, num, Color{0.7f, 0.0f, 0.0f});
        break;
    case 8:
        numberRend(xPos, yPos, num, Color{0.4f, 0.0f, 0.0f});
        break;
    }
}

void tileRend(int xPos, int yPos, Color color, bool mine) // Рендер ячейки
{
    glLoadIdentity();
    glScalef(1.0f / MAP_WIGTH * 2, 1.0f / MAP_HEIGHT * 2, 1.0f);
    glTranslatef(xPos - MAP_WIGTH / 2, yPos - MAP_HEIGHT / 2, 1.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(color.red - 0.2f, color.green - 0.2f, color.blue - 0.2f);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(color.red - 0.1f, color.green - 0.1f, color.blue - 0.1f);
    glVertex2f(-1.0f, 1.0f);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(1.0f, 1.0f);
    glColor3f(color.red - 0.2f, color.green - 0.2f, color.blue - 0.2f);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(color.red - 0.1f, color.green - 0.1f, color.blue - 0.1f);
    glVertex2f(1.0f, -1.0f);
    glColor3f(color.red, color.green, color.blue);
    glVertex2f(1.0f, 1.0f);
    if (mine)
    {
        glColor3f(0.1f, 0.1f, 0.1f);
        glVertex2f(-0.75f, -0.75f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(-0.75f, 0.75f);
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex2f(0.75f, 0.75f);
        glColor3f(0.1f, 0.1f, 0.1f);
        glVertex2f(-0.75f, -0.75f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(0.75f, -0.75f);
        glColor3f(0.3f, 0.3f, 0.3f);
        glVertex2f(0.75f, 0.75f);
    }
    glEnd();
}

void flagRend(int xPos, int yPos) // Рендер флага
{
    glLoadIdentity();
    glScalef(1.0f / MAP_WIGTH * 2, 1.0f / MAP_HEIGHT * 2, 1.0f);
    glTranslatef(xPos - MAP_WIGTH / 2, yPos - MAP_HEIGHT / 2, 1.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.3f, 0.0f);
    glVertex2f(-0.7f, -0.7f);
    glColor3f(0.65f, 0.35f, 0.0f);
    glVertex2f(-0.7f, 0.7f);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(-0.4f, 0.7f);
    glColor3f(0.6f, 0.3f, 0.0f);
    glVertex2f(-0.7f, -0.7f);
    glColor3f(0.65f, 0.35f, 0.0f);
    glVertex2f(-0.4f, -0.7f);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(-0.4f, 0.7f);

    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.0f);
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.6f, 0.5f);
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 1.0f);
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.6f, 0.5f);
    glEnd();
}

void numberRend(int xPos, int yPos, int num, Color color) // Рендер числа
{
    glLoadIdentity();
    glScalef(1.0f / MAP_WIGTH * 2, 1.0f / MAP_HEIGHT * 2, 1.0f);
    glTranslatef(xPos - MAP_WIGTH / 2, yPos - MAP_HEIGHT / 2, 1.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glBegin(GL_TRIANGLES);
    if (num != 1 && num != 0 && num != 7)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.1f);
    }
    if (num != 1 && num != 4 && num != 7)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.9f);
    }
    if (num != 1 && num != 4)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.7f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.9f);
    }
    if (num != 2)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.1f);
    }
    if (num == 2 || num == 6 || num == 8 || num == 0)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, -0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, 0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.1f);
    }
    if (num != 5 && num != 6)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.3f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(0.5f, -0.1f);
    }
    if (num == 4 || num == 5 || num == 6 || num == 8 || num == 0)
    {
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, 0.9f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.3f, -0.1f);
        glColor3f(color.red, color.green, color.blue);
        glVertex2f(-0.5f, -0.1f);
    }
    glEnd();
}

#endif