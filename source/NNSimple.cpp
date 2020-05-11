#include "../header/NNSimple.h"

NNSimple::NNSimple(){};

NNSimple::NNSimple(std::vector<int> width){
    srand(std::time(NULL));
    value.resize(width.size());
    weights.resize(width.size());
    treshold.resize(width.size());
    for (int i = 0; i < width.size(); i++)
    {
        value[i].resize(width[i]);
        weights[i].resize(width[i]);
        treshold[i].resize(width[i]); 
        if(i>0)
        for (int j = 0; j < width[i]; j++)
        {
            treshold[i][j]= (rand()%int(pow(eps,-1)+0.5))*eps*2-0.5;
            weights[i][j].resize(width[i - 1]);
            for (int k = 0; k < width[i - 1]; k++)
            {
                weights[i][j][k] = (rand() % int(pow(eps, -1) + 0.5)) * eps * 2 - 0.5;
            }
        }
    }

}

NNSimple::NNSimple(std::string filename){
    std::fstream file;
    file.open(filename);

    if (file.is_open())
    {
        std::vector<int> width;
        int tmp;
        file>>tmp;
        width.resize(tmp);
        for (int i = 0; i < width.size(); i++)
        {
            
        }
        
        for (int i = 0; i < width.size(); i++)
        {
                        
        }
        
        
    }
    else
    {
        "Error! File is not open!\n";
        return;
    }
    
}


NNSimple::NNSimple(std::string input, std::string answer) {

    std::ifstream fileIn, fileRR;
    fileIn.open(input);
    fileRR.open(answer);
    if (fileIn.is_open()&&fileRR.is_open())
    {
        std::cout << "Start reeding Input\n";
        int count = 0;// число чисел в файле
        int temp = 0;//Временная переменная

        int count_space = 0;
        char symbol = 'a';
       
        while (!fileIn.eof())
        {
            fileIn >> temp;
            std::cout << count << "\n";
            count++;
        }

        fileIn.seekg(0,std::ios::beg);

        while (!fileIn.eof())
        {
            fileIn.get(symbol);
            std::cout << symbol;
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }

        fileIn.seekg(0, std::ios_base::beg);



        

        int n = count / (count_space + 1);//число строк
        int m = count_space + 1;//число столбцов на единицу больше числа пробелов

        std::vector<std::vector<double>> tmp;
        tmp.resize(n);
        for (int i = 0; i < n; i++)
        {
            tmp[i].resize(m);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                fileIn>>tmp[i][j];
            }
        }

       //---------------------------------

        count = 0;
        std::cout << "Start reeding RR\n";
        while (!fileRR.eof())
        {
            fileRR >> temp;
            count++;
        }

        fileRR.seekg(0, std::ios::beg);
        fileRR.clear();


        count_space = 0;
        
        while (!fileRR.eof())
        {

            fileRR.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }

        fileRR.seekg(0, std::ios::beg);
        fileRR.clear();


        n = count / (count_space + 1);//число строк
        m = count_space + 1;//число столбцов на единицу больше числа пробелов

        std::vector<std::vector<double>> tmpRR;
        tmpRR.resize(n);
        for (int i = 0; i < n; i++)
        {
            tmpRR[i].resize(m);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                fileRR >> tmpRR[i][j];
            }
        }
            
        std::vector<int> width;
        width.push_back(tmp[0].size()); 

        width.push_back(tmpRR[0].size());

        *this = NNSimple(width);

        int min = tmp.size();
        std::cout << "Start"<< std::endl;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        double e1, e2;
begSt:
       e1=0, e2=0;
    

            if (min > tmpRR.size()) min = tmpRR.size();

            do
            {
                e2 = e1;

                e1 = 0;

                for (int i = 0; i < min; i++)
                {
                    
                    setInput(tmp[i]);
                    ForwardfeedSimple();
                    /*for (int k = 0; k < min; k++)
                    {
                        double et = 0;
                        setInput(tmp[k]);
                        ForwardfeedSimple();
                        for (int j = 0; j < tmpRR[i].size(); j++)
                        {
                            et += powl(tmpRR[k][j] - value[value.size() - 1][j], 2);
                        }
                        std::cout << "Error T = " << et << std::endl;
                    }*/
                    BackPropagetion(tmpRR[i]);

                }
#pragma omp parallel for
                for (int i = 0; i < min; i++)
                {
                    setInput(tmp[i]);
                    ForwardfeedSimple();
#pragma omp parallel for
                    for(int j=0; j<tmpRR[i].size(); j++)
                        e1+= powl(tmpRR[i][j] - value[value.size() - 1][j], 2);
                }
                
                std::cout << "Error = " <<std::setprecision(8) <<e1 << " Delta " << std::setprecision(8) << e2-e1<< std::endl;
            } while (abs(e1 - e2) > eps);//eps*eps );
  
       
         if (e1 / (min * value[value.size() - 1].size()) > 0.01) {
            std::cout << "New layer" << std::endl;
            width.push_back(width[width.size() - 1]);
            width[width.size() - 2] = width[width.size() - 3];
            *this = NNSimple(width);
            goto begSt;
          }
       
        end = std::chrono::system_clock::now();
        int elapsed_seconds;
        elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count();
        std::cout << "Error = " << std::setprecision(8) << e1 << " Delta " << std::setprecision(8) << e2 - e1 << std::endl;
        std::cout << "Total time : " << elapsed_seconds / 1000.0 << " sec" <<std::endl;
        std::cout << "\nPress any kay\n";

        std::cout << " width " << width.size() << std::endl;
        char anykay;
        std::cin >> anykay;
    }
    else
    {
        std::cout << "Error filename!\n";
        exit(4);
    }

}


void NNSimple::setInput(std::vector<double> input){
    value[0] = input;
}

void NNSimple::setInput(std::vector<int> input) {
    for (int i = 0; i < value[0].size(); i++)
    {
        value[0][i] = input[i];
    }
}

std::vector<double> NNSimple::getOutput()
{
    return value[value.size()-1];
}




void NNSimple::ForwardfeedSimple(){
    for (int i = 1; i < value.size(); i++)
    {
        for (int j = 0; j < value[i].size(); j++)
        {
            double arg = treshold[i][j];
            for (int k = 0; k < value[i - 1].size(); k++)
            {
                arg += value[i - 1][k] * weights[i][j][k];
            }
            value[i][j] = act(arg);
        }
    }
}

double NNSimple::act(double x){
    return  x/(1-exp(-x));
}



double NNSimple::diff(double x) {
    return (act(x - 2 * eps) - 8 * act(x - eps) + 8 * act(x + eps) - act(x + 2 * eps)) / (12 * eps);
}

double NNSimple::diff(double x, int n,  int p, int m) {
    std::vector<std::vector<double>> slog;
    double tmpW = weights[n][p][m];
    weights[n][p][m] += -2 * eps;
    ForwardfeedSimple();
    slog.push_back(value[value.size() - 1]);
    weights[n][p][m] = tmpW - eps;
    ForwardfeedSimple();
    slog.push_back(value[value.size() - 1]);
    weights[n][p][m] = tmpW + eps;
    ForwardfeedSimple();
    slog.push_back(value[value.size() - 1]);
    weights[n][p][m] = tmpW +2 * eps;
    ForwardfeedSimple();
    slog.push_back(value[value.size() - 1]);

    return 0;
}

void NNSimple::BackPropagetion(std::vector<double> rr) {

    std::vector<std::vector<double>> sigm = value;
    std::vector<std::vector<std::vector<double>>> dw = weights;
    std::vector<std::vector<double>> dt = treshold;
    for (int cur = 0; cur < value[value.size() - 1].size(); cur++)
    {/*
    //    double E = 0;

    //    for (int i = 0; i < value[value.size() - 2].size(); i++)
    //    {

    //        for (int j = 0; j < value[value.size() - 1].size(); j++)
    //        {
    //            arg += weights[1][j][i] * value[0][i];
    //        }
    //        E += (rr[cur] - act(arg)) * (rr[cur] - act(arg));
    //    }
    //    */
    //    //  E /= value[0].size();
    //    //  double arg = treshold[treshold.size()-1][cur];

        double arg;
#pragma omp parallel for
        for (int i = 1; i < value.size(); i++)
        {
            if (i != value.size() - 1)
                for (int j = 0; j < value[i].size(); j++)
                {

                    arg = treshold[i][j];
                    for (int k = 0; k < value[i - 1].size(); k++)
                    {
                        arg += value[i - 1][k] * weights[i][j][k];
                    }
                    value[i][j] = act(arg);
                }
            else
            {
                arg = treshold[i][cur];
                for (int k = 0; k < value[i - 1].size(); k++)
                {
                    arg += value[i - 1][k] * weights[i][cur][k];
                }

                value[value.size() - 1][cur] = act(arg);
            }
        } 
        for (int j = 0; j < value[value.size()-2].size(); j++)
        {
            
            dw[weights.size()-1][cur][j] = eps * (rr[cur] - value[value.size() - 1][cur]) * diff(arg)*value[value.size()-2][j];
        }
        dt[dt.size()-1][cur] = eps * (rr[cur] - value[value.size() - 1][cur]) * diff(arg);
        sigm[sigm.size()-1][cur] = eps* (rr[cur] - value[value.size() - 1][cur]) * diff(arg);
    }

        

//-----------------------------------------------------------------------------------------------------------------------------------------

    double err = 0;
    for (int i = value.size() - 2; i > 0; i--)
    {
        
        for (int j = 0; j < value[i].size(); j++)
        {
            sigm[i][j] = 0;
            for (int k = 0; k < value[i+1].size(); k++)
            {
                sigm[i][j] += sigm[i + 1][k] * weights[i + 1][k][j];
            }
            sigm[i][j] *= diff(Arg(i, j));
            for (int  k = 0; k < value[i-1].size(); k++)
            {
                dw[i][j][k] = eps * sigm[i][j] * value[i - 1][k];
            }
            dt[i][j] = eps * sigm[i][j];
        }

    }
    for (int i = 1; i < weights.size(); i++)
    {
        for (int j = 0; j < weights[i].size(); j++)
        {
            for (int k = 0; k < weights[i-1].size(); k++)
            {
                weights[i][j][k] += dw[i][j][k];
            }
        }
    }
    for (int i = 1; i < treshold.size(); i++)
    {
        for (int j = 0; j < treshold[i].size(); j++)
        {
            treshold[i][j] += dt[i][j];
        }
    }
}

void NNSimple::BackPropagetionITMO(std::vector<double> rr){

    std::vector<std::vector<double>> sigm = value;
    for (int i = 0; i < value[value.size()-1].size(); i++)
    {
        sigm[value.size() - 1][i] = (value[value.size() - 1][i] - rr[i]) * (value[value.size() - 1][i]) * (1 - value[value.size() - 1][i]);
    }
    for (int i = value.size() - 2; i < 1; i--)
    {
        for (int j = 0; j < value[i].size(); j++)
        {
            double sum = treshold[i+1][j];
            for (int k = 0; k < value[i+1].size(); k++)
            {
                sum += sigm[i + 1][k] * weights[i + 1][k][j];
            }
            sigm[i][j] = (1 - value[i][j]) * value[i][j] * sum;
        }

    }
    for (int  i = 0; i < weights.size(); i++)
    {
        for (int j = 0; j < weights[i].size(); j++)
        {
            for (int k = 0; k < weights[i][j].size(); k++)
            {

            }
        }
    }

}


double NNSimple::PI(){
    double tmp=0;
    int i=0;
    do
    {
        tmp = 4.0/(2*i+1)*(pow(-1, i));
        pi+= tmp;
        i++;
    } while (tmp>eps);
    return tmp;
}

void NNSimple::Save(std::string filename)
{
    std::fstream file(filename);
    if (file.is_open())
    {
        file << value.size()<<'\n';
        for (int i = 0; i < value.size(); i++)
        {
            file <<value[i].size();
            if (i != value.size() - 1)
                    file << ' ';
        }

        
    }

}

double NNSimple::Arg(int _i, int _j)
{
    double arg; 
    for (int i = 1; i < value.size(); i++)
    {
        for (int j = 0; j < value[i].size(); j++)
        {
            arg = treshold[i][j];
            for (int k = 0; k < value[i-1].size(); k++)
            {
                arg += value[i - 1][k] * weights[i][j][k];
            }
            value[i][j] = act(arg);
            if (i == _i && j == _j)
                return arg;
        }
    }

    
}


