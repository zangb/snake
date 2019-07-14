#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include "Textbox.h"


class CollisionExcept : std::exception{
private:
    int error;
    Textbox* mbox;
public:
    CollisionExcept(int Error, Textbox* messagebox);
    void what();
    int GetError();
};

int CollisionExcept::GetError(){
    return error;
}

CollisionExcept::CollisionExcept(int Error, Textbox* messagebox){
    error = Error;
    mbox = messagebox;
}
void CollisionExcept::what(){
    switch(GetError()){
        case 1: 
        mbox = new Textbox("You collided with your own body",Punkt(250,250), Punkt(30,30));
        
        break;
    }
}

#endif