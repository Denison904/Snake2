#include "../header/Layer.h"


Layer::Layer(int size){
    value.resize(size);
    h.resize(size);
    weights.resize(size);

}