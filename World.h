#ifndef WORLD
#define WORLD 
#include "Punkt.h"
#include "WinAdapt.h"

class World  {
private: 
    Punkt position;
    Punkt size;
public:
    World(Punkt POS, Punkt SIZE);    
    Punkt GetPos();
    Punkt GetSize();
    void Draw();
};

World::World(Punkt POS, Punkt SIZE){
    position = POS;
    size = SIZE;
}
Punkt World::GetPos(){
    return position;
}
Punkt World::GetSize(){
    return size;
}
void World::Draw(){
	FillCol(34, 139, 34);
    Rect(GetPos().X, GetPos().Y, GetSize().X, GetSize().Y);
}

#endif