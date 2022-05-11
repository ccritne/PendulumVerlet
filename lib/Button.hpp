#pragma once

#include "NecessaryLib.hpp"

class Button: public Drawable, public Transformable
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
        Button(float x, float y, float width, float height, Font& font);
        void setText(string text);
        Vector2f getCoord();        
        dim getDim();
        bool contains(Vector2i coord);
};

Button::Button(float x, float y, float width, float height, Font& font){
    h = height;
    w = width;

    box.setPosition(Vector2f(x, y));
    box.setSize(Vector2f(width, height));
    box.setOutlineThickness(1);
    box.setOutlineColor(Color::White);

    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(Color::Black);
    text.setPosition(Vector2f(x + 0.05, y + 0.05));

    text.setString("");
}

void Button::setText(string txt){
    text.setString(txt);

}

Vector2f Button::getCoord(){
    return box.getPosition();
}

dim Button::getDim(){
    return {w, h};
}

bool Button::contains(Vector2i coord){
    if(coord.x > box.getPosition().x && coord.x < box.getPosition().x + w &&
        coord.y > box.getPosition().y && coord.y < box.getPosition().y + h)
        return true;
    else
        return false;
}