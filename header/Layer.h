#pragma once

#include "Glob.h"


class Layer{
public:
    Layer(){};
    Layer(int size);// Generate empty layer;
    Layer(std::vector<std::vector<double>> weights);
    


    
private:
    std::vector<std::vector<double>> weights;
    std::vector<double> value;
    std::vector<double> h;
       
};