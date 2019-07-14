#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include "Textbox.h"

using namespace std;

class CollisionExcept : std::exception{
private:
    int error;
    Textbox** mbox;
    
public:
    CollisionExcept(int Error, Textbox*& messagebox, int& running);
    void what();
    int GetError();
    
};

int CollisionExcept::GetError(){
    return error;
}

CollisionExcept::CollisionExcept(int Error, Textbox*& messagebox, int& running){
    error = Error;
    mbox = &messagebox;
    running = -1;
}
void CollisionExcept::what(){
    switch(GetError()){
        case 1: 
        cout << "Collision with your body!" << endl;
        *mbox = new Textbox("WASTED",Punkt(150,250), Punkt(450,350));
        
        break;
    }
}

#endif