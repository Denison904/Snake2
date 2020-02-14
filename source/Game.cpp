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
            if(checkBorder(snake[i].getTailX(0),snake[i].getTailY(0))|| checkEnemy(snake[i].getTailX(0),snake[i].getTailY(0),i))
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
    std::cout<<"\n\n";
	if (numofSnake ==1)
    {
        int x= snake[0].getTailX(0)-radius;
        int y= snake[0].getTailY(0) -radius;

        for (int i = 0; i < radius*2+1; i++)
        {
            for (int j = 0; j < radius*2+1; j++)
            {
                if(i+y == 0 || j+x == 0 || i+y == high - 1 || j+x == width - 1)
				{
					std::cout << "#";
				}
                else if (checkBorder(j+x,i+y))
                {
                    std::cout<<"#";
                }
				else if (x+j==0&&y+i==0)
                {
                    std::cout<<"O";
                }                  
                else if(checkSnake(j+x,i+y)){
                    std::cout << "o";
                }
				else  if (checkFood(j+x, i+y)) {
					std::cout << "F";
				}
				else std::cout << "0";
                
            }
            
        }
        
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

//NEED UPGRADE THIS FUNCTION !!!
void Game::newFood(int num){
    do
    {
        food[num][0]=rand()%(width-2)+1;
        food[num][1]=rand()%(high-2)+1;
    } while (checkSnake(food[num][0],food[num][1])||checkFood(food[num][0],food[num][1])||checkBorder(food[num][0],food[num][1]));
    
}

std::vector<int> Game::Scan(int num){
    int newX, newY;
    std::vector<int> inp;
    newX = snake[num].getTailX(0)-radius;
    newY = snake[num].getTailY(0)-radius;
    for (int i = 0; i < 2*radius+1; i++)//y
    {
        for (int j = 0; j < 2*radius+1; j++)//x
        {
            if (checkBorder(j,i)||checkEnemy(j,i,num))
            {
                inp.push_back(-1);
            }else if(checkFood(j,i))
            {
                inp.push_back(1);
            }else
            {
                inp.push_back(0);
            }            
        }
    }
    return inp;
}

bool Game::checkBorder(int x, int y){
    if(x<=0||y<=0||x>=width||y>=high){
        return false;
    }else{
        for (int i = 0; i < numofBorder; i++)
        {
            if(x==border[i][0]&&y==border[i][1])
                return true;
        }
        
    }
}

bool Game::checkFood(int x, int y){
    for (int i = 0; i < numofFood; i++)
    {
        if (food[i][0]==x&&food[i][1]==y)
        {
            return true;
        }else
        {
            return false;
        }
    }
}

bool Game::checkSnake(int x, int y){
    for (int i = 0; i < numofSnake; i++)
    {
        if (snake[i].getAlive())
        {
            for (int j = 0; j < snake[i].getBody(); j++)
            {
                if(snake[i].getTailX(j)==x&&snake[i].getTailY(j)==y){
                    return true;
                }
            }
        }
        
    }
    return false;
}

bool Game::checkEnemy(int x, int y , int num){
    for (int i = 0; i < numofSnake; i++)
    {
        if (i!=num)
        {
            if (snake[i].getAlive())
            {
                for (int j = 0; j < snake[i].getBody(); j++)
                {
                    if(snake[i].getTailX(j)==x&&snake[i].getTailY(j)==y){
                        return true;
                    }
                }
            }
            
        }
        
    }
    
}

bool Game::checkHead(int x, int y, int num){
    if (snake[num].getTailY(0)==y&&snake[num].getTailX(0)==x)
    {
        return true;
    }else
    {
        return  false;
    }    
}

void Game::stady(){
    for (int i = 0; i < numofFood; i++)
    {
        food[i][0]=rand()%(width-2)+1;
        food[i][0]=rand()%(high -2)+1;
    }
    
    std::vector<int> rr;
    std::vector<int**> F;
    
    do
    {
        Logic();
        Drow();
        std::vector<int> inp;
        char a;
        a = getchar();
        switch (a)
        {
        case 'A':case 'a':
            inp.push_back(0);
            break;
        case 'W':case 'w':
            inp.push_back(1);;
            break;
        case 'D':case 'd':
            inp.push_back(2);
        case 'S':case 's':
            inp.push_back(3);
        default:
            break;
        }
        Input(inp);
        F.push_back(food);
        rr.push_back(inp[0]);
    } while (snake[0].getAlive());
    SaveGame(rr,F);
}

//Finish this function (delete replay step in rr and F)
void Game::SaveGame(std::vector<int> rr, std::vector<int**> F){
    std::string fileNameRR;
    std::string fileNameFood;
    if (radius<5)
    {
        fileNameRR = "radius"+std::to_string(radius)+"RR.txt";
    }else
    {
        fileNameRR = "radius"+std::to_string(5)+"RR.txt";
    }
    std::fstream RR, Food;
    RR.open(fileNameRR,std::fstream::in |std::fstream::out| std::fstream::in);
    Food.open(fileNameFood, std::fstream::in |std::fstream::out| std::fstream::in);


}