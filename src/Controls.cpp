#ifndef Controls_CPP
#define Controls_CPP

#include "Game.cpp"
#include "../lib/glfw3.h"
#include <cmath>

double cursorPosX;
double cursorPosY;

void MouseButton_CB(GLFWwindow *window, int button, int action, int mods)
{
    int cursorPosYRevers = abs(cursorPosY - WINDOW_HEIGHT);
    int currentTilePosX = round(cursorPosX * 1.0 / WINDOW_WIGTH * MAP_WIGTH - 0.5);
    int currentTilePosY = round(cursorPosYRevers * 1.0 / WINDOW_HEIGHT * MAP_HEIGHT - 0.5);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        tileFlagChange(currentTilePosX,currentTilePosY);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        tileOpen(currentTilePosX,currentTilePosY);
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        gameInit();
    }
}

void CursorSetPos_CB(GLFWwindow *window, double xpos, double ypos)
{
    cursorPosX = xpos;
    cursorPosY = ypos;
}

#endif