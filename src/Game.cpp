#ifndef Game_CPP
#define Game_CPP

#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <functional>
#include <iostream>

int getRand(int max);
void gameInit();
bool tileOnField(int xPos, int yPos);
int minesNearby(int xPos, int yPos);
void tileFlagChange(int xPos, int yPos);
void tileOpen(int xPos, int yPos);

// Общие значения (Хотите меняйте)
#define WINDOW_HEIGHT 700
#define WINDOW_WIGTH 700
#define MAP_HEIGHT 15
#define MAP_WIGTH 15
#define MAP_MINE_PERCENTAGE 10
#define MINES_COUNT 40

enum TileType {
    MINE, // мина
    EMPTY  // ничего (цифра/белая клетка)
};

enum DoType {
    FLAG,
    NONE,
    OPENED
};

struct Tile {
    TileType tileType = EMPTY;
    DoType doType = NONE;
    int minesNearbyCount = 0;
};

bool isGenerated = false; // Сгенерированно ли поле
int openedTilesCount = 0;
bool isInitialized = false;

std::function<void(void)> onFail;
std::function<void(void)> onWin;

Tile Field[MAP_HEIGHT][MAP_WIGTH]; // Игровое поле из ячеек

// Другие переменные
int allMines = std::round((MAP_HEIGHT * MAP_WIGTH * 1.0) / 100 * MAP_MINE_PERCENTAGE);

int getRand(int max)
{
    return std::rand() % (max);
}

bool isWin()
{
    return (openedTilesCount == MAP_HEIGHT * MAP_WIGTH - allMines);
}

void gameInit()
{
    isInitialized = true;
    srand(time(0));
    int xPos, yPos;
    for (int xTile = 0; xTile < MAP_WIGTH; xTile++) // Установка чисел соприкосающихся мин
    {
        for (int yTile = 0; yTile < MAP_HEIGHT; yTile++)
        {
            Field[yTile][xTile].tileType = EMPTY;
            // Field[yTile][xTile].doType = NONE;
        }
    }
    for (int i = 0; i < MINES_COUNT; i++) {
        do {
            xPos = getRand(MAP_HEIGHT);
            yPos = getRand(MAP_WIGTH);
        } while (Field[yPos][xPos].tileType == EMPTY && Field[yPos][xPos].doType != NONE);
        Field[yPos][xPos].tileType = MINE;
    }

    for (int xTile = 0; xTile < MAP_WIGTH; xTile++) // Установка чисел соприкосающихся мин
    {
        for (int yTile = 0; yTile < MAP_HEIGHT; yTile++)
        {
            if (Field[yTile][xTile].tileType == EMPTY)
            {
                Field[yTile][xTile].minesNearbyCount = minesNearby(xTile, yTile);
            }
        }
    }
}

void openAll() // Проигрыш
{
    for (int xTile = 0; xTile < MAP_WIGTH; xTile++)
    {
        for (int yTile = 0; yTile < MAP_HEIGHT; yTile++)
        {
            Field[yTile][xTile].doType = OPENED;
        }
    }
}

void execForNear(int xPos, int yPos, std::function<void(int, int)> func)
{
    for (int xOffset = -1; xOffset <= 1; xOffset++)
    {
        for (int yOffset = -1; yOffset <= 1; yOffset++)
        {
            if (tileOnField(xPos + xOffset, yPos + yOffset))
            {
                func(xPos + xOffset, yPos + yOffset);
            }
        }
    }
}

void tileOpen(int xPos, int yPos) // Функция открытия ячейки
{
    if (Field[yPos][xPos].doType == NONE)
    {
        Field[yPos][xPos].doType = OPENED;
        std::cout << "pos: (" << xPos << ", " << yPos << ")\n";
        if (Field[yPos][xPos].tileType == MINE)
        {
            openAll();
            onFail();
        }
        else // Рекурсия чтобы открыть все соприкосающиеся ячейки если на этой ячейке 0
        {
            if (Field[yPos][xPos].minesNearbyCount == 0 && isInitialized)
            {
                execForNear(xPos, yPos, [] (int x, int y) {
                    if (Field[y][x].tileType == EMPTY && Field[y][x].doType != OPENED)
                        tileOpen(x, y);
                });
            }
        }
    }
    if (isWin()) {
        onWin();
    }
    if (!isInitialized)
        gameInit();
}

void tileFlagChange(int xPos, int yPos) // Функция установки/убирания флага
{
    if (Field[yPos][xPos].doType != OPENED)
    {
        Field[yPos][xPos].doType = (Field[yPos][xPos].doType == FLAG ? NONE : OPENED);
    }
}

int minesNearby(int xPos, int yPos) // Функция подсчёта кол-ва мин вокруг ячейки
{
    int minesFinded = 0;
    for (int xOffset = -1; xOffset <= 1; xOffset++)
    {
        for (int yOffset = -1; yOffset <= 1; yOffset++)
        {
            if (tileOnField(xPos + xOffset, yPos + yOffset))
            {
                if (Field[yPos + yOffset][xPos + xOffset].tileType == MINE)
                {
                    minesFinded++;
                }
            }
        }
    }
    return minesFinded;
}
bool tileOnField(int xPos, int yPos) // Функция проверки что ячейка на поле
{
    if (xPos > -1 && yPos > -1 && yPos < MAP_HEIGHT && xPos < MAP_WIGTH)
    {
        return true;
    }
    return false;
}

#endif