#pragma once
#include "Glob.h"

//#include "Layer.h"

class NNSimple{
public:
    NNSimple();
    NNSimple(std::vector<int> width);
    NNSimple(std::string filename);
    NNSimple(std::string input, std::string answer);


    void setInput(std::vector<double> input);
    void setInput(std::vector<int> input);
    std::vector<double> getOutput();
    void ForwardfeedSimple();
    
    double act(double x);
    
    void BackPropagetion(std::vector<double> rr);
    void BackPropagetionITMO(std::vector<double> rr);
    double diff(double x);
    double diff(double x, int n, int p, int m);
    double Error(std::vector<double> rr);
    double PI();
    
    void Save(std::string filename);


    double Arg(int i, int j);
    
private:
    std::vector<std::vector<double>> value;
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> treshold;
    double eps = pow(10,-6);
    double sumError = 0;
    double learningRate = 1*pow(10,-1);
    double pi = 0 ;
};