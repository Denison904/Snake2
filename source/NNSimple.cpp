#include "../header/NNSimple.h"

// std::vector<double> operator*(const std::vector<std::vector<double>> &left, const std::vector<double>& right){
//      if (left[0].size()==right.size())
//      {
//         std::vector<double> ans(right.size(), 0);
//         for (int i = 0; i < left.size(); i++)
//         {   
//             for (int k = 0; k < right.size(); k++)
//             {
//                 ans[i][0]+=left[i][k]*right[k];
//             }
//         }  

//         return ans;
//      }else
//      {
//          exit(-1);
//      }    
// }

// std::vector<double> operator-(std::vector<double> &left, std::vector<double> &right){
//     if (left.size()==right.size())
//     {
//         for (int i = 0; i < left.size(); i++)
//         {
//             left[i]-=right[i];
//         }
//         return left;
//     }
    

// }

NNSimple::NNSimple(){};

NNSimple::NNSimple(std::vector<int> width){

    layer.resize(width.size());
    for (int i = 0; i < width.size(); i++)
    {
        layer[i]=Layer(width[i]);
    }   
    

}

NNSimple::NNSimple(std::string filename){
    std::fstream file;
    file.open(filename);

    if (file.is_open())
    {
        std::vector width;
        int tmp;
        file>>tmp;
        width.resize(tmp);
        for (int i = 0; i < width.size(); i++)
        {
            file>>width[i];
        }
        layer = width.size();
        for (int i = 0; i < layer; i++)
        {
            
            weights[i].resize(layer);
            h[i].resize(layer);
            for (int j = 0; j < width[i]; j++)
            {
                weights[i][j].resize(width[i-1]);//DODLAT'
            }
            
        }
        
        
    }
    else
    {
        "Error! File is not open!\n";
        return;
    }
    
}


void NNSimple::setInput(std::vector<double> input){
    value[0]=input;
}

void NNSimple::ForwardfeedSimple(){

    for (int i = 1; i < layer; i++)
    {
        value[i]=weights[i-1]*value[i-1]-h[i];
    }

}

std::vector<double> NNSimple::getOutput(){
    return value[value.size()-1];
}

void NNSimple::ForwardfeedSimple(){
    for (int i = 0; i < value.size()-1; i++)
    {
        value[i+1] = proiz(weights[i],value[i], h[i+1]);
    }
}

double NNSimple::act(double x){
    return 2*x/(1-exp(-x))+1;
}

std::vector<double> NNSimple::proiz(const std::vector<std::vector<double>>& w,const std::vector<double> v, const std::vector<double> &h ){
    std::vector<double> tmp = h;
    std::vector<double> answ(tmp.size());
    for (int i = 0; i < w.size(); i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            tmp[i] +=w[i][j]*v[j];
        }
    }
    for (int i = 0; i < tmp.size(); i++)
    {
        answ[i] = act(tmp[i]);
    }
    
    return  answ;
}


void NNSimple::BackPropagetion(std::vector<double>rr){

}

double NNSimple::diff(double x){
    return (act(x-2*eps)-8*act(x-eps)+8*act(x+eps)-f(x-2*eps))/(12*eps);
}

double NNSimple::Error(std::vector<double> rr){
    Error.resize(value.size());
    for (int i = 0; i < ; i++)
    {
        Error[i].resize(value[i].size());
        for (int j = 0; j < count; j++)
        {
            Error[i][j]=0;
        } 
    }
    
    

}


double NNSimple::PI(){
    double tmp=0;
    int i=0;
    do
    {
        tmp = 4./(2*i+1)*(pow(-1, i));
        pi+= tmp;
        i++;
    } while (tmp>eps);
     
}