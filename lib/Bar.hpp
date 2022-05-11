#pragma once

#include "NecessaryLib.hpp"
#include "Line.hpp"

class Bar: public Drawable, public Transformable
{
    private:
        Line line;
        Text labelBar;
        
        bool textVisible = true;

        virtual void draw(RenderTarget& target, RenderStates states) const { 
            target.draw(line);
            if(textVisible) 
                target.draw(labelBar);
        }

    public:
        Bar(float xStart, float yStart, float xEnd, float yEnd, string label, Font& font, bool _textVisible, int textSize);
        Bar();
};


Bar::Bar(float xStart, float yStart, float xEnd, float yEnd, string label, Font& font, bool _textVisible, int textSize){

    textVisible = _textVisible;
    
    labelBar.setFont(font);
    labelBar.setCharacterSize(textSize);
    labelBar.setString(label);

    double widthText = labelBar.getLocalBounds().width;
    double heightText = labelBar.getLocalBounds().height;

    if(xStart == xEnd)
        labelBar.setPosition(xStart - widthText/2, yEnd);
    else
        labelBar.setPosition(xStart - (widthText + 1), yEnd - heightText); 

    line.setPosition(xStart, yStart, xEnd, yEnd);

};
