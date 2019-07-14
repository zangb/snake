#ifndef TEXTBOX
#define TEXTBOX

#include <iostream>
#include <string>
#include "WinAdapt.h"
#include "Punkt.h"
#include "World.h"

class Textbox : public World {
    private:
    std::string text;
    Punkt position;
    Punkt size;
    public:
    Textbox(std::string TEXT, Punkt pos, Punkt size);
    std::string GetText();
    void SetText(std::string TEXT);
    void Draw();
};

Textbox::Textbox(std::string TEXT, Punkt POS, Punkt SIZE): World(POS, SIZE){
    text = TEXT;
}

std::string Textbox::GetText(){
    return text;
}

void Textbox::SetText(std::string TEXT){
    text = TEXT;
}

void Textbox::Draw(){
 Rect(GetPos().X, GetPos().Y, GetSize().X, GetSize().Y);
 Text(GetPos().X + (GetSize().X - GetPos().X) / 2 - (text.size() * 3.2), GetPos().Y + (GetSize().Y - GetPos().Y) / 2 - 10, GetText().c_str());
}

#endif