#pragma once
#include "Glob.h"

class NNSimple{
public:
    NNSimple();
    
    void setInput();
    double* getOutput();
    void ForwardfeedSimple();
    
private:
    int layer;
    double ** value;
    double ***weights;
    double* input;
};