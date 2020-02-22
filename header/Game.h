#pragma once
#include "../header/Glob.h"
#include "../header/Snake.h"

class Game{
    public:
    Game(int n, int r, int high,int width);
    ~Game();

    void Test(){
        int x = 5, y = 5;
        snake = new Snake[1];
        snake[0] = Snake(0,5,5);
        if(checkSnake(x ,y )){
            std::cout<<"Y\n";
        }else{
            std::cout<<"N\n";
        }
    }

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
    
//  function for study and save
    void stady();
    void SaveGame(std::vector<int*> rr, std::vector<int**> F, std::vector<std::vector<int>> scanData);
    bool searchFileFood();

    int getNumAlive();

//  bool operator==(const std::vector<int>& left, const std::vector<int>& right);
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