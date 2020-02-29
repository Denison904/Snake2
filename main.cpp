#include "header/Glob.h"
#include "header/Game.h"
#include "header/NNSimple.h"
#include "header/RNN.h"
// void Stady(){
//     int r, h, w;
//     std::cout<<"Enter radius: ";
//     std::cin>>r;
//     std::cout<<"Enter high and width: ";
//     std::cin>>h>>w;
//     int n =1;
//     Game game(n,r,h,w);
//     game.stady();
//     std::cin>>r;
// }

// void NNBackProp(){
//     // int ns, r, h, w;
//     // std::cout<<"Enter number of snake: ";
//     // std::cin>>ns;
//     // std::cout<<"Enter radius: ";
//     // std::cin>>r;
//     // std::cout<<"Enter high and width: ";
//     // std::cin>>h>>w;
//     // Game game(ns,r,h,w);
//     // char a;
//     // std::cout<<"Do you want to study NN? (y/n)\n";
//     // std::cin>> a;
//     // if(a=='s')
//     // {
//     //     game.stady();

//     // }else
//     // {
        
//     // }
    
// }



int main(){
    char a;
    std::cout<<"Enter algoritm (s/g/b/r/p/..)\n";
    std::cin>>a;
    switch (a)
    {
        case 'b': case 'B':
            // NNSimple();
            break;
        case 'g': case 'G':
        {
            int n, w, h, r;
            std::cout << "Enter number of snake\n";
            std::cin >> n;
            std::cout << "Enter widht and high of map\n";
            std::cin >> w >> h;
            std::cout << "Enter radius\n";
            std::cin >> r;
            Game game(n, r, h, w);

        }
        break;
        case 's': case 'S':{
        //   Stady();
            int r, h, w;
            std::cout<<"Enter radius: ";
            std::cin>>r;
            std::cout<<"Enter high and width: ";
            std::cin>>h>>w;
            Game game(1,r,h,w);
            game.stady();
            std::cin>>r;
           //  delete &game;
           }
            break;
        case 'r': case 'R':
        {
            int n, w, h;
            std::cout << "Enter number of snake, high and width\n";
            std::cin >> n>> h>> w;
            Game gameR(n, h, w);
            std::vector<int> inp;
            inp.resize(n);
            char tmp;
            do
            {
                gameR.Drow();
                for (int i = 0; i < n; i++)
                {
                    inp[i] = rand() % 4;
                }
                gameR.Input(inp);
                gameR.Logic();
               // _sleep(800);
                //getchar();
                std::cin >> tmp;
            } while (gameR.getNumAlive()>0);
            std::cout << "Game Over\n";
            
        }
        break;
    default:
        break;
    }


    return 0;
}