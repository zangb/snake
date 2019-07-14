#ifndef COLOUR_H
#define COLOUR_H

#include "WinAdapt.h"


class Colour{

private:
    int red, green, blue;


public:
    //standard constructor for 3 integer as parameter
    Colour(int r, int g, int b){
        red = r;
        green = g;
        blue = b;
    }
    //copy constructor
    Colour(const Colour& c){
        red = c.getRed();
        green = c.getGreen();
        blue = c.getBlue();
    }

    //returns value for red
    int getRed()const{
        return red;
    }
    //returns value for green
    int getGreen()const{
        return green;
    }
    //returns value for blue
    int getBlue()const{
        return blue;
    }


    //function to set Colour
    void setColor(int r, int g, int b){
        red = r;
        green = g;
        blue = b;
    }
    //function to set Colour to Colour
    void setColor(const Colour& c){
        red = c.getRed();
        green = c.getGreen();
        blue = c.getBlue();
    }


protected:

};





#endif