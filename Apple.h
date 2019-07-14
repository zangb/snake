#ifndef APPLE_H
#define APPLE_H
#include <iostream>
#include "Punkt.h"
#include "Colour.h"
#include "WinAdapt.h"
#include <cstdlib>
#include <ctime>

class Apple {
private:
    Punkt* pos;
public:     
    Apple();
    void Draw();
    Punkt GetPos();
};

Apple::Apple(){
    srand(time(0));
    int r = rand();
    int r2 = rand();
    pos = new Punkt((r%80)*5+100, (r2%80*5)+100);
}

void Apple::Draw(){
    FillCol(238,0,0);
    Rect(pos->X-5, pos->Y-5, pos->X+5,pos->Y+5);
}

Punkt Apple::GetPos(){
    return *(this->pos);
}

#endif