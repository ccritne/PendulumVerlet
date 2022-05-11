#pragma once

#include "NecessaryLib.hpp"

class Point: public Drawable, public Transformable{
    private:
        double radiusPoint = 1;
        bool visible = true;
        float xG, yG;
        CircleShape p;
        virtual void draw(RenderTarget& target, RenderStates states) const{ 
            if(visible) 
                target.draw(p);
        }
    public:
        Point(double x, double y, sf::Color color);
        Point(double radiusPoint, float x, float y);
        Point(double radiusPoint, float x, float y, Color color);
        void setRadius(double radiusPoint);
        void setPosition(float x, float y);
        void setColor(Color color);
        void setVisible(bool condition);
        Color getColor();
        Vector2f getPosition();
        Vector2f getCoords();
};

Point::Point(double x, double y, sf::Color color){
    p.setRadius(radiusPoint);
    p.setPosition(x, y);
    xG = x;
    yG = y;
    p.setFillColor(color);
}

Point::Point(double radiusPoint, float x, float y){
    p.setRadius(radiusPoint);
    p.setPosition(x, y);
}

Point::Point(double radiusPoint, float x, float y, Color color){
    p.setRadius(radiusPoint);
    p.setPosition(x, y);
    p.setFillColor(color);
}

void Point::setRadius(double radiusPoint){
    p.setRadius(radiusPoint);
}

void Point::setPosition(float x, float y){
    p.setPosition( x, y);
}

void Point::setColor(Color color){
    p.setFillColor(color);
}

void Point::setVisible(bool condition){
    visible = condition;
}

Color Point::getColor(){
    return p.getFillColor();
}

Vector2f Point::getPosition(){
    return p.getPosition();
}

Vector2f Point::getCoords(){
    return Vector2f(xG, yG);
}