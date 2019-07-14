#include <iostream>
#include "WinAdapt.h"
#include "Textbox.h"
#include "Punkt.h"
#include "World.h"
#include "Snakebody.h"
#include "Exception.h"
#include "Colour.h"
#include "Apple.h"
using namespace std;



int counter = 0, length = 0, fooditems = 0;

World world(Punkt (100,100), Punkt (500,500));

Textbox Headline("Snake friendo", Punkt(250,10), Punkt(350, 30));
Scorebox Score("Score: ", Punkt(250, 33), Punkt(350, 53), &length);
//place the head as first snakebody object
Snakebody Snake(Punkt (300,290), 119);

//Textbox_Pointer for notification boxes
Textbox* message = NULL;

//declare colors for head and body
Colour headColor(100, 200, 100);
Colour bodyColor(0, 100, 0);   
Colour msgColour(150,150,150);

//Foodpointer
Apple* food = NULL;



//bool for pause
int running = 0;

void VtlInit(){
    cout << "Welcome to Snake" << endl;
}

void VtlZyk(){
    if(running > 0){
        //Shit to do for food
        Snakebody* temp = Snake.NextBody;
        if(fooditems == 0){ 
            int fail = 0;
            while(fail == 0){
            fail = 1;
            food = new Apple();
            if(temp != NULL){
            do {
                    if((food->GetPos()) == temp->GetPos()){
                        delete food;
                        fail = 0;
                    }
                    temp = temp->NextBody;
                } while (temp != NULL&& food != NULL);
                temp = Snake.NextBody;
            }
            }
            fooditems = 1;
        }

        temp = Snake.NextBody;
		if (fooditems != 0) {
			if (Snake.GetPos() == (food->GetPos()) && length != 0) {
				while (temp->NextBody != NULL) {
					temp = temp->NextBody;
				}
				temp->AppendBodyEle();
				++length;
                
				delete food;
				fooditems = 0;
			}
			else if (Snake.GetPos() == (food->GetPos()) && length == 0) {
				Snake.AppendBodyEle();
				++length;
                
				delete food;
				fooditems = 0;
			}
		}
        //End of food shit
        
        //Update Score

		
	   
        //fetches current orientation and if the snake still is inside the world
        //for every key hit

        if(Snake.GetOrientation() == 119&&Snake.GetPos().Y-10>world.GetPos().Y){ //W               
        Snake.SetHeadpos(Punkt(Snake.GetPos().X, Snake.GetPos().Y-10));
        }
        if(Snake.GetOrientation() == 97&&Snake.GetPos().X-10>world.GetPos().X){    //A x-5
        Snake.SetHeadpos(Punkt(Snake.GetPos().X-10, Snake.GetPos().Y));
        }
        if(Snake.GetOrientation() == 115&&Snake.GetPos().Y+10<world.GetSize().Y){ //Sy+5
        Snake.SetHeadpos(Punkt(Snake.GetPos().X, Snake.GetPos().Y+10));
        }
        if(Snake.GetOrientation() == 100&&Snake.GetPos().X+10<world.GetSize().X){ //Dx+5
        Snake.SetHeadpos(Punkt(Snake.GetPos().X+10, Snake.GetPos().Y));
        }

        //New orientation and positioning for the bodyparts
        //alternative as vector
        while(temp!=NULL){
            try{
                if(Snake.GetPos() == temp->GetPos()){
                    throw CollisionExcept(1, message, running);
                }
            }
            catch (CollisionExcept& e){
                e.what();
            }
            temp->SetHeadpos(Punkt(temp->GetPrevPos().X, temp->GetPrevPos().Y)); //Setting new position to the one of the previous object, same with orientation
            temp->SetPrevPos(temp->PrevBody->GetPos());                            //Retrieving new position from previous object and saving it
            temp->SetOrientation(temp->GetPrevorient());	
            temp->SetPrevorient(temp->PrevBody->GetOrientation());      		
            temp = temp->NextBody;
        }
        Score.updateScore();
    }
}

void VtlPaint(int xl, int yo, int xr, int yu){
    world.Draw();
    Headline.Draw();
    Score.Draw();
    Snake.Draw(headColor);
	Snakebody* temp = Snake.NextBody;
	while(temp != NULL){
		temp->Draw(bodyColor);
		temp = temp->NextBody;
	}
    if(message != NULL){
        FillCol(msgColour);
        message->Draw();
    }
    if(food!=NULL){
        food->Draw();
    }
}

void VtlKeyHit(int key){
    if(running == 0){
        running = 1;
    }
    if(key == 119&&Snake.GetPos().Y>100){ //W               
    Snake.SetOrientation(119);
    }
    if(key == 97&&Snake.GetPos().X>100){    //A
    Snake.SetOrientation(97);
    }
    if(key == 115&&Snake.GetPos().Y+10<500){ //S
    Snake.SetOrientation(115);
    }
    if(key == 100&&Snake.GetPos().X+10<500){ //D
    Snake.SetOrientation(100);
    }
    
}

void VtlMouse(int X, int Y){

    if(running == -1){
        //to reset click on the grey box

        if(X > 150 && X < 450 && Y > 250 && Y < 350){
            //reset button was hit
            running = 0;
            length = 0;
            Snake.SetHeadpos(Punkt(300,290));


            //delete body
            Snake.ResetBody();
            
            delete message;
            message = NULL;
            delete food;
            fooditems = 0;
        }
    }
}
