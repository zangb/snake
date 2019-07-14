#ifndef EXCEPTION
#define EXCEPTION
#include <iostream>
#include "Textbox.h"


class CollisionExcept : std::exception{
private:
    int error;
public:
    CollisionExcept(int Error);
    void what();
    int GetError();
};

int CollisionExcept::GetError(){
    return error;
}

CollisionExcept::CollisionExcept(int Error){
    error = Error;
}
void CollisionExcept::what(){
    switch(GetError()){
        case 1: 
        Textbox* temp = new Textbox("You collided with your own body",Punkt(250,250), Punkt(30,30));
        temp->Draw();
        break;
    }
}

#endif