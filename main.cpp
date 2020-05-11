#include "header/Glob.h"
#include "header/Game.h"
#include "header/NNSimple.h"
#include "header/RNN.h"

/*
        1 радиус => 8 клеток 
        1 клетка => 3 данных (еда(0/1), пустота(0/1) ,препядствие (0/1)) 
*/

int MaxElem(std::vector<double> x) {
    double  m = x[0];
    int j = 0 ;
    for (int i = 1; i < x.size(); i++)
    {
        if (x[i] > m) {
            m = x[i];
            j = i;
        }
    }
    return j;
}

void Start() {
   // std::string in, rr,s;
    //std::cin >> in >> rr;
    //in = "C:\Users\TopPC\source\repos\Snake2\Trening\InputRadius1.txt";
    //rr = "C:\Users\TopPC\source\repos\Snake2\Trening\RRRadius1.txt";
    //NNSimple nn(in, rr);
    //NNSimple nn("C:\\Users\\TopPC\\source\\repos\\Snake2\\Trening\\InputRadius1.txt", "C:\\Users\\TopPC\\source\\repos\\Snake2\\Trening\\RRRadius1.txt");
    NNSimple nn("C:\\Users\\TopPC\\Desktop\\tmp\\InputRadius1.txt", "C:\\Users\\TopPC\\Desktop\\tmp\\RRRadius1.txt");
   // std::cin >> s;
   // nn.Save(s);
    Game game(1, 1,20, 20);
    //std::vector<int> tmp;
    //tmp.push_back(24);
    //tmp.push_back(4);
    // NNSimple nn(tmp);
    std::vector<int> cor(1);
    do
    {
        game.Drow();
        nn.setInput(game.getScan(0));
        nn.ForwardfeedSimple();
        std::vector<double> tmp = nn.getOutput();
        
        std::cout << "\n\n";
        
        for (int i = 0; i < tmp.size(); i++)
        {
            std::cout << tmp[i] << " ";
        }
        std::cout<<"\n\n";
        cor[0] = MaxElem( nn.getOutput());
        game.Input(cor);
        
        game.Logic();
    } while (game.getNumAlive()>0);
}


void Draw(std::vector<int> input) {
    int r = sqrt(input.size() + 1);
    int k = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (i == (r-1)/2 && j == (r-1)/2)
                std::cout << "@";
            else {
                if (input[k] ==1) {
                    std::cout << "F";
     
                }
                else if (input[k] == 0) {
                    std::cout << " ";
    
                }
                else {
                    std::cout << "#";

                }
                k++;
            }
        }
        std::cout << "\n";
    }
}

std::vector<int> Generate(int r) {
    r = pow(2 * r + 1, 2)-1;
    std::vector<int> s;
    for (int i = 0; i < r; i++)
    {
        s.push_back(rand() % 3 - 1);
    }
    return s;
}


std::vector<int> Generate(int r, int course) {
    r = pow(2 * r + 1, 2) - 1;
    std::vector<int> s; 
chose: 
    int count = 0;
    switch (course)
    {
    case 0:
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 2);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 2 - 1);
        
        
        if (count == 0) goto chose;
        break;
    case 1:
        s.push_back(rand() % 3-1);
        s.push_back(rand() % 2);
        s.push_back(rand() % 3-1);
        s.push_back(rand() % 3-1);
        s.push_back(rand() % 3-1);
        s.push_back(rand() % 2-1);
        s.push_back(rand() % 2-1);
        s.push_back(rand() % 2-1);
 
        if (s[0] == 1)
            count++;
        if (s[1] == 1)
            count++;
        if (s[2] == 1)
            count++;
        if (count == 0) goto chose;
        break;
    case 2:
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 2);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        
        if (s[3] == 1)
            count++;
        if (s[4] == 1)
            count++;
        if (s[5] == 1)
            count++;
        if (count == 0) goto chose;
        break;
    case 3:
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 2 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 3 - 1);
        s.push_back(rand() % 2);
        s.push_back(rand() % 3 - 1);
        
        if (s[5] == 1)
            count++;
        if (s[6] == 1)
            count++;
        if (s[7] == 1)
            count++;
        if (count == 0) goto chose;
        break;
    default:
        break;
    }
    return s;
}

std::vector<int> Answer(char a) {

    std::vector<int> an(4);

    switch (a)
    {
    case 'a': 
        for (int i = 0; i < 4; i++)
        {
            an[i] = 0;
            
        }   
        an[0] = 1;
        break;
    case 'w':
        for (int i = 0; i < 4; i++)
        {
            an[i] = 0;

        }
        an[1] = 1;
        break;
    case 'd':
        for (int i = 0; i < 4; i++)
        {
            an[i] = 0;

        }
        an[2] = 1;
        break;
    case 's':
        for (int i = 0; i < 4; i++)
        {
            an[i] = 0;

        }
        an[3] = 1;
        break;

    default:
        break;
    }
    return an;
}


void MakeInputOutput() {
    std::ofstream Inp;
    std::ofstream RR;

    std::string  path;
    
    int radius;

    std::cout << "Enter radius " << std::endl ;
    std::cin >> radius;
    std::cout << "Specify the path to the file \n";
    std::cin >> path;
    std::string filenameIn = path+"/InputRadius", filenameRR = path+"/RRRadius";
    std::string num;
    char n;
    int x = radius;
    while (x != 0)
    {
        n = char(x % 10 + 48);
        x /= 10;
        num = n + num;
    }
    filenameIn += num + ".txt";
    filenameRR += num + ".txt";
    Inp.open(filenameIn);
    RR.open(filenameRR); 

    char a;
    if (Inp.is_open() && RR.is_open()) {
        std::vector<std::vector<int>> input;
        std::vector<std::vector<int>> output;
beg:
        input.push_back(Generate(radius));
        std::cout << "Iter = " << input.size() << std::endl;
        Draw(input[0]);
        a = _getch();
        if (a == 'e')  goto beg;
        output.push_back(Answer(a));

        int iter = 1;

        do {

            std::vector<int> tmp;
position:     
            tmp = Generate(radius);
            int count = tmp.size();
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[i].size(); j++)
                {
                    if (tmp[j] == input[i][j]) {
                        count--;
                    }
                }
                if (count == 0)
                    goto position;
            }

            std::cout << "iter = " << iter++ << std::endl;
            Draw(tmp);
            a = _getch();
            std::cout << "-------------\n"<<a;
            if (a == 'e') goto position;
            if (a == 'n') goto pos2;
            input.push_back(tmp);
            output.push_back(Answer(a));

            std::cout << "\n\n";
  

        } while (a!='n');
pos2:
        for (int i = 0; i < input.size(); i++)
        {


            for (int j = 0; j < input[i].size(); j++)
            {
                switch (input[i][j])
                {
                case 1:
                    Inp << 1 << ' ' << 0 << ' ' << 0;
                    break;
                case 0:
                    Inp << 0 << ' ' << 1 << ' ' << 0;
                    break;
                case -1:
                    Inp << 0 << ' ' << 0 << ' ' << 1;
                    break;
                default:
                    break;
                }
                if (j != input[i].size() - 1)
                    Inp << ' ';
            }
          
            for (int j = 0; j < output[i].size(); j++)
            {
                RR << output[i][j];
                if (j != output[i].size() - 1)
                        RR << ' ';
            }
            if (i != input.size() - 1)
            {
                RR << '\n';  Inp << '\n';
            }

        }

    }
    else {
        std::cout << "Error file Inp/RR\n";
    }

}

void MakeInputOutput2() {
    std::ofstream Inp;
    std::ofstream RR;

    std::string  path;

    int radius;

    std::cout << "Enter radius " << std::endl;
    std::cin >> radius;
    std::cout << "Specify the path to the file \n";
    std::cin >> path;
    std::string filenameIn = path + "/InputRadius", filenameRR = path + "/RRRadius";
    std::string num;
    char n;
    int x = radius;
    while (x != 0)
    {
        n = char(x % 10 + 48);
        x /= 10;
        num = n + num;
    }
    filenameIn += num + ".txt";
    filenameRR += num + ".txt";
    Inp.open(filenameIn);
    RR.open(filenameRR);

    char a;
    if (Inp.is_open() && RR.is_open()) {
        std::vector<std::vector<int>> input;
        std::vector<std::vector<int>> output;

        input.push_back(Generate(radius));
        Draw(input[0]);
        std::cin >> a;  
        output.push_back(Answer(a));

        int iter = 1;
        std::vector<int> tmp;
        for(int cour =0 ; cour<4;cour++)
        for (int iter = 0; iter < 200; iter++)
        {


           
position:
            tmp = Generate(radius, cour);
            
           

            int count = tmp.size();
            for (int i = 0; i < input.size(); i++)
            {
                for (int j = 0; j < input[i].size(); j++)
                {
                    if (tmp[j] == input[i][j]) {
                        count--;
                    }
                }
                if (count == 0)
                    goto position;
            }

            std::cout << "iter = " << iter++ << std::endl;
            Draw(tmp);
            std::cin >> a;
            if (a == 'e') goto position;
            input.push_back(tmp);
            output.push_back(Answer(a));

            std::cout << "\n\n";


        } 
        for (int i = 0; i < input.size(); i++)
        {


            for (int j = 0; j < input[i].size(); j++)
            {
                switch (input[i][j])
                {
                case 1:
                    Inp << 1 << ' ' << 0 << ' ' << 0;
                    break;
                case 0:
                    Inp << 0 << ' ' << 1 << ' ' << 0;
                    break;
                case -1:
                    Inp << 0 << ' ' << 0 << ' ' << 1;
                    break;
                default:
                    break;
                }
                if (j != input[i].size() - 1)
                    Inp << ' ';
            }

            for (int j = 0; j < output[i].size(); j++)
            {
                RR << output[i][j];
                if (j != output[i].size() - 1)
                    RR << ' ';
            }
            if (i != input.size() - 1)
                RR << '\n';  Inp << '\n';
            
        }

    }
    else {
        std::cout << "Error file Inp/RR\n";
    }

}


int main(){
        
    Start();

 
    char a;
    std::cout<<"Enter algoritm (s/g/b/r/p/m..)\n";
    std::cin>>a;
    switch (a)
    {
        case'm':
            MakeInputOutput();
            break;
        case 'b': case 'B':
            


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