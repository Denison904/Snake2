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

    void newFood(int num);//NEED UPGRADE THIS FUNCTION

    std::vector<int> Scan(int num);

    bool checkBorder(int x, int y);
    bool checkFood(int x, int y);
    bool checkSnake(int x, int y);
    bool checkEnemy(int x, int y,int num);
    bool checkHead(int x, int y, int num);

//function for study and save
    void stady();
    void SaveGame(std::vector<int> rr, std::vector<int**> F);
    bool searchFileFood();

    
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