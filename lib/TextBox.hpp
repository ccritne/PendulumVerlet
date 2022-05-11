#pragma once

#include "NecessaryLib.hpp"

class Textbox: public Drawable, public Transformable
{
    private:
        RectangleShape box;
        Text text;
        float h;
        float w;

        virtual void draw(RenderTarget& target, RenderStates states) const{    
            target.draw(box);
            target.draw(text);
        }
    public:
        Textbox(float x, float y, float width, float height, Font& font);
        void setText(string text);
        Vector2f getCoord();
        dim getDim();
        string getText();
        FloatRect getGlobalBounds();
        bool contains(Vector2i coord);
};

Textbox::Textbox(float x, float y, float width, float height, Font& font){
    h = height;
    w = width;

    box.setPosition(Vector2f(x, y));
    box.setSize(Vector2f(width, height));
    box.setOutlineThickness(1);
    box.setFillColor(Color::Black);
    box.setOutlineColor(Color::White);

    text.setFont(font);
    text.setPosition(Vector2f(x + 0.05, y + 0.05));
    text.setCharacterSize(12);
    text.setString("");
}

void Textbox::setText(string txt){
    text.setString(txt);
}

string Textbox::getText(){
    return text.getString();
}

Vector2f Textbox::getCoord(){
    return box.getPosition();
}

dim Textbox::getDim(){
    return {w, h};
}

bool Textbox::contains(Vector2i coord){
    if(coord.x > box.getPosition().x && coord.x < box.getPosition().x + w &&
        coord.y > box.getPosition().y && coord.y < box.getPosition().y + h)
        return true;
    else
        return false;
}
