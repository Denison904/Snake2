#pragma once
#include "Glob.h"
//#include "Layer.h"

class NNSimple{
public:
    NNSimple();
    NNSimple(std::vector<int> width);

    void setInput(std::vector<double> input);
    std::vector<double> getOutput();
    void ForwardfeedSimple();
    std::vector<double> proiz(const std::vector<std::vector<double>>&w, const std::vector<double>&v, const std::vector<double> &h);


    double act(double x);


    void BackPropagetion(std::vector<double> rr);
    double diff(double x);
    double Error(std::vector<double> rr);

    double PI();
    //  //bool operator==(const std::vector<double>& left, const std::vector<double>& right);
    //  std::vector<double> operator*(const std::vector<std::vector<double>>& left, const std::vector<double>& right);
    //  std::vector<double> operator-(const std::vector<double> &right);

    void test();
private:
    //std::vector<Layer> layer;
    std::vector<std::vector<double>> value;
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> h;
    double eps = pow(10,-6);
    double sumError = 0;
    std::vector<std::vector<double>> Error;
    double learningRate = 1*pow(10,-4);
    double pi = 0 ;
};