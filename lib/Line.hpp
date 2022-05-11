#pragma once

#include "NecessaryLib.hpp"

class Line: public Drawable, public Transformable
{
    private:
        Vertex line[2];
        virtual void draw(RenderTarget& target, RenderStates states) const{ 
            target.draw(line, 2, Lines);
        }
    public:
        Line();
        Line(float startX, float startY, float endX, float endY);
        void setPosition(float startX, float startY, float endX, float endY);
        void setLineColor(Color color);
};

Line::Line(){
    line[0].position = Vector2f(0, 0);
    line[1].position = Vector2f(0, 0);
}

Line::Line(float startX, float startY, float endX, float endY){
    line[0].position = Vector2f(startX, startY);
    line[1].position = Vector2f(endX, endY);
}

void Line::setPosition(float startX, float startY, float endX, float endY){
    line[0].position = Vector2f(startX, startY);
    line[1].position = Vector2f(endX, endY);
}

void Line::setLineColor(Color color){
    line[0].color = color;
    line[1].color = color;
}
