#pragma once
#include "Glob.h"
#include "Snake.h"

class Game{
    public:
    Game(int n, int r, int high,int width);
    ~Game();

    void Logic();
    void Drow();
    void Input(std::vector<int> x);

    void scan();

    bool checkBorder(int x, int y);
    bool checkFood(int x, int y);
    bool checkSnake(int x, int y);
    bool checkEnemy(int num);
    bool checkHead(int x, int y, int num);

    void stady();
    void SaveGame();
    private:
    Snake* snake;
    int radius;
    int *scan;
    int numofSnake;
    int high;
    int width;
    int** border;
    int numofBorder;
    int numofFood;
    int** food;
    int numofAlive;
    int step;
};