#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "WinAdapt.h"
#include <iostream>
#include "Punkt.h"
#include "Colour.h"

class Snakebody {
private:
    Punkt headpos;
	Punkt prevpos;
    int orientation; //119 top, 97 left, 115 bottom, 100 right
	int prevorient;
public:    
	~Snakebody();
    Snakebody* PrevBody;
    Snakebody* NextBody;
    //default constructor for first object
    Snakebody(Punkt POS, int Orientation);
    //constructor for adding a object to the double enchanged list
    Snakebody(Punkt POS, Punkt PREVPOS, int PREVORIENT, Snakebody* prev, Snakebody* next);
    Punkt GetPos();
	Punkt GetPrevPos();
    int GetOrientation();
    void SetHeadpos(Punkt Headpos);
	void SetPrevPos(Punkt POS);
	int GetPrevorient();
	void SetPrevorient(int ORIENT);
    void Draw(const Colour& c);
    void SetOrientation(int Orientation);
    void AppendBodyEle();
    void ResetBody();
};
Snakebody::~Snakebody() {
	if (NextBody != NULL) {
		delete NextBody;
	}
}
Snakebody::Snakebody(Punkt POS, int Orientation){
    headpos = POS;
	orientation = Orientation;
	prevpos = Punkt(0, 0);
    NextBody = NULL;
    PrevBody = NULL;
}
Snakebody::Snakebody(Punkt POS, Punkt PREVPOS, int PREVORIENT, Snakebody* prev, Snakebody* next){
    headpos = POS;
	prevpos = PREVPOS;
	prevorient = PREVORIENT;
    PrevBody = prev;
    NextBody = next;
}
Punkt Snakebody::GetPrevPos() {
	return prevpos;
}
Punkt Snakebody::GetPos(){
    return headpos;
}
int Snakebody::GetOrientation(){
    return orientation;
}
int Snakebody::GetPrevorient(){
	return prevorient;
}
void Snakebody::SetOrientation(int Orientation){
    orientation = Orientation;
}
void Snakebody::SetPrevorient(int ORIENT) {
	prevorient = ORIENT;
}

void Snakebody::SetHeadpos(Punkt Headpos){
	headpos = Headpos;
}
void Snakebody::SetPrevPos(Punkt POS) {
	prevpos = POS;
}

void Snakebody::Draw(const Colour& c){
	 FillCol(c);
     Rect(GetPos().X-5, GetPos().Y-5, GetPos().X+5, GetPos().Y+5);
}
void Snakebody::AppendBodyEle(){
    NextBody = new Snakebody(GetPos(),	GetPrevPos(), GetOrientation(), this, NULL);
    NextBody->PrevBody = this;
    //119 top, 97 left, 115 bottom, 100 right
    if(GetOrientation()== 119){
        NextBody->SetHeadpos(Punkt(GetPos().X, GetPos().Y+10));
        NextBody->SetOrientation(119);
		NextBody->SetPrevPos(GetPos());
    }
    if(GetOrientation()== 97){
        NextBody->SetHeadpos(Punkt(GetPos().X+10, GetPos().Y));
        NextBody->SetOrientation(97);
		NextBody->SetPrevPos(GetPos());
    }
    if(GetOrientation()== 115){
        NextBody->SetHeadpos(Punkt(GetPos().X, GetPos().Y-10));
        NextBody->SetOrientation(115);
		NextBody->SetPrevPos(GetPos());
    }
    if(GetOrientation()== 100){
        NextBody->SetHeadpos(Punkt(GetPos().X-10, GetPos().Y));
        NextBody->SetOrientation(100);
		NextBody->SetPrevPos(GetPos());
    }
}

void Snakebody::ResetBody(){
    delete NextBody;
    NextBody = NULL;
}

#endif

