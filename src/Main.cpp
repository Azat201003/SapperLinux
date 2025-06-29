#include "../lib/glfw3.h"
#include "ErrorManager.cpp"
#include "Game.cpp"
#include "Graphics.cpp"
#include "Controls.cpp"
using namespace std;

int main()
{
    Mode mode = GRAY;
    onFail = [&] {
        mode = RED;
    };
    onWin = [&] {
        mode = GREEN;
    };
    if (!glfwInit())
    {
        ErrorSet 0x0001 CallError
    } // Вернуть ошибку 1 если glfw не инициализирован
    GLFWwindow *window = glfwCreateWindow(700, 700, "Sapper", NULL, NULL); // Создание окна glfw
    if (!window)
    {
        glfwTerminate();
        ErrorSet 0x0002 CallError
    } // Вернуть ошибку 2 если окно не создалось
    glfwMakeContextCurrent(window);                     // Выбрать контекст для glfw
    glfwSetMouseButtonCallback(window, MouseButton_CB); // Установка обратного вызова для нажатия кнопок мыши
    glfwSetCursorPosCallback(window, CursorSetPos_CB);
    while (!glfwWindowShouldClose(window))
    { // Главный цикл
        glClear(GL_COLOR_BUFFER_BIT);
        for (int xTile = 0; xTile < MAP_WIGTH; xTile++) // Отрисовка поля
        {
            for (int yTile = 0; yTile < MAP_HEIGHT; yTile++)
            {
                tileRendController(xTile, yTile, mode);
                glLoadIdentity();
                // std::cout << ((Field[yTile][xTile].doType == OPENED) ? "#" : "_");
            }
            // std::cout << "\n";
        }
        glfwSwapBuffers(window);
        glfwPollEvents(); // Стандартный режим событий
    }
    glfwTerminate();          // Уничтожить glfw
}