#pragma once

#include "NecessaryLib.hpp"

class Bob: public Drawable, public Transformable
{
    private:
        CircleShape circle;
        float radius;
        virtual void draw(RenderTarget& target, RenderStates states) const{    
            target.draw(circle);
        }
    public:
        Bob(float x, float y, float radius, Color color);
        bool contains(Vector2i coord);
        void setPosition(Vector2f coord);
};

Bob::Bob(float x, float y, float _radius, Color color){
    radius = _radius;
    circle.setRadius(_radius);
    circle.setPosition(x,y);
    circle.setFillColor(color);
}

bool Bob::contains(Vector2i coord){
    if(coord.x > circle.getPosition().x && coord.x < circle.getPosition().x + radius &&
        coord.y > circle.getPosition().y && coord.y < circle.getPosition().y + radius)
        return true;
    else
        return false;
}

void Bob::setPosition(Vector2f coord){
    circle.setPosition(coord);
}