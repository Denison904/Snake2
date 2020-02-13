#include "Game.h"

Game::Game(int n, int r, int high, int width){
    if (n*4<(high-2)*(-2+width))
    {
        std::cout<<"Error (space)!\n";
        exit(1);
    }

    snake = new Snake[n];

    this->high=high;
    this->width=width;
    this->numofSnake=n;
    int stepX, stepY;
    radius = r;
    scan = new int[r*r-1];
    char a;
    
    stepX= 0;
    stepY=int((high-2)/(n+2));;   
    
    std::cout<<"Do u want add border?\n";
    std::cin>>a;
    if(a=='y'||a=='Y'){
        std::cout<<"How much?";
        std::cin>>numofBorder;
        border = new int*[numofBorder];
        for (int i = 0; i < numofBorder; i++)
        {
            border[i]=new int[2];
            std::cout<<"Enter coord x: \n";
            std::cin>>border[i][0];
            std::cout<<"Enter coord y: \n";
            std::cin>>border[i][1];
            if (checkBorder(border[i][0], border[i][1])||checkSnake(border[i][0], border[i][1]))
            {
                std::cout<<"Error! This border can't be used!\n";
                delete[] border[i];
                i--;
            }
        }
        
        std::cout<<"Complite!\n";
    }else
    {
        numofBorder=0;
    }
    if((width-2)*(high-2)>100)
        numofFood = (width-2)*(high-2)/100;
    else
        numofFood =1;
    food =new int*[numofFood];
    srand(time(NULL));
    for (int i = 0; i < numofFood; i++)
    {
        food[i]=new int[2];
        food[i][0]=rand()%(width-2)+1;//0 - Ox
        food[i][1]=rand()%(high-2)+1;//1 - Oy
        if (checkFood(food[i][0],food[i][1])||checkBorder(food[i][0], food[i][1])||checkSnake(food[i][0], food[i][1]))
        {
            
        }
        
    }   
    
    
}


Game::~Game(){
    delete[] snake;
    delete[] scan;
    for (int i = 0; i < numofBorder; i++)
    {
        delete[] border[i];
    }
    delete[] border;
    for (int i = 0; i < numofFood; i++)
    {
        delete[] food[i];
    }
    delete[] food;
}

void Game::Logic(){
    for (int i = 0; i < numofSnake; i++)
    {
        if(snake[i].getAlive())
        {
            if(checkBorder(snake[i].getTailX(0),snake[i].getTailY(0))|| checkEnemy(i))
            {
                 snake[i].setAlive();
            }else
            {
                bool eat =false;
                int tmpX, tmpY;
                if(checkFood(snake[i].getTailX(0),snake[i].getTailY(0)))
                { 
                    eat = true;
                    tmpX= snake[i].getTailX(snake[i].getBody()-1);
                    tmpY= snake[i].getTailY(snake[i].getBody()-1);
                }

                switch (snake[i].getCourse())
                {
                    case 0: snake[i].setMove(-1,0);
                        break;
                    case 1: snake[i].setMove(0,-1);
                        break;
                    case 2: snake[i].setMove(1,0);
                        break;
                    case 3: snake[i].setMove(0,1);
                        break;
                    default:
                        break;
                }

                if(eat){
                    snake[i].setTailX(tmpX);
                    snake[i].setTailY(tmpY);
                    snake[i].setFullHungry();
                }
                snake[i].setHungry();
            }
        }
    }
}

void Game::Drow(){
     if (numofAlive>0)
	{
		//system("cls");
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || i == high - 1 || j == width - 1)
				{
					std::cout << "#";
				}
                else if (checkBorder(j,i))
                {
                    std::cout<<"#";
                }
				else if (checkSnake(j, i))
				{
                    for (int k = 0; k < numofSnake; k++)
                    {
                        if (checkHead(j,i,k))
                        {
                            std::cout<<"O";
                            break;
                        }                  
                        else{
                            std::cout << "o";
                            break;
                        }
                    	
                    }
                }
				else  if (checkFood(j, i)) {
					std::cout << "F";
				}
				else std::cout << " ";
			}
			std::cout << '\n';
		}
		std::cout << "Stap: " << step << std::endl;
	}
	
}

void Game::Input(std::vector<int> x){
    for (int i = 0; i < numofSnake; i++)
    {
        if(snake[i].getAlive()){
            snake[i].setCourse(x[i]);
        }
    }
    
}