#pragma once

#include "NecessaryLib.hpp"
#include "Line.hpp"
#include "Bar.hpp"
#include "Point.hpp"
#include "evaluate.hpp"

class Graph: public Drawable, public Transformable
{
    private:
        double widthGraph, heightGraph;
        double graphX, graphY;

        int precision = 4;

        Line AxesX;
        Line AxesY;

        double maxIntervalX, minIntervalX;
        double maxIntervalY, minIntervalY;

        Font font;

        vector<Bar> bars;

        vector<Point> points;

        double padding;
        double margin;

        double lengthX, lengthWMX;
        double lengthY, lengthWMY;

        double CoordLastBarX, CoordLastBarY;

        int textSize = 15;

        double radiusPoint = 1;

        int accurate = 10000;

        virtual void draw(RenderTarget& target, RenderStates states) const{ 

            target.draw(AxesX);
            target.draw(AxesY);

            for(int i = 0; i < bars.size(); i++)
                target.draw(bars[i]);

            for(int i = 0; i < points.size(); i++)
                target.draw(points[i]);    
        
        }
    public:
        Graph(double xStart, double yStart, double xEnd, double yEnd, double padding, double margin, Font& _font);
        void plot(string function, double minRange, double maxRange,  Color);
        void setPoints(vector<point>, Color);
        void addPoint(Point p);
        void removeFirstPoint();
        void setRadiusPoint(double radius);
        void setFunction(string, double, double);
        void setPrecisionDecimal(int precision);
        int getSize();
        void clear();

};


void Graph::plot(string function, double minRange, double maxRange, Color color = Color::White){

        for(int i = 0; i < accurate; i++){
            double x = minRange + (maxRange - minRange)*i/accurate;
            double y = evaluate(change(function, x));

            if(!isinf(y))
                points.push_back(Point(x, y, color));
        }

        minIntervalY = points[0].getCoords(). y;
        maxIntervalY = points[0].getCoords().y;

        minIntervalX = points[0].getCoords().x;
        maxIntervalX = points[0].getCoords().x;

        for(int i = 0; i < points.size(); i++){
            minIntervalY = min(double(points[i].getCoords().y), minIntervalY);
            maxIntervalY = max(double(points[i].getCoords().y), maxIntervalY);

            minIntervalX = min(double(points[i].getCoords().x), minIntervalX);
            maxIntervalX = max(double(points[i].getCoords().x), maxIntervalX);
        }

        for(int i = 0; i < points.size(); i++){
            double x = graphX + margin*lengthX + determineCoordInAxes(points[i].getCoords().x, minIntervalX, maxIntervalX, lengthWMX, true);
            double y = graphY + margin*lengthY + determineCoordInAxes(points[i].getCoords().y, minIntervalY, maxIntervalY, lengthWMY, false);
            points[i].setPosition(x-radiusPoint, y-radiusPoint);
        }

        int counter = 15;

        bars.clear();
        
        double segmentToAddY = double((maxIntervalY - minIntervalY)/counter);
        double labelY = minIntervalY;

        double segmentToAddX = double((maxIntervalX - minIntervalX)/counter);
        double labelX = minIntervalX;

        double coordx = graphX + margin*lengthX;
        double coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

        double segmentX = double(lengthWMX/counter);

        int i = 0;
        while(counter--){
            Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, to_string(labelX), font, true, textSize);
            bars.push_back(tmpX);
            coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
            Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, to_string(labelY), font, true, textSize);
            bars.push_back(tmpY);

            labelY += segmentToAddY;
            labelX += segmentToAddX;

            coordx += segmentX;
        } 
        
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);

}

void Graph::setPoints(vector<point> pointsCoordinates, Color color = Color::White){
    bars.clear();
    int lastSize = points.size();

    minIntervalY = min(minIntervalY, pointsCoordinates[0].y);
    maxIntervalY = max(maxIntervalY, pointsCoordinates[0].y);

    for(int i = 0; i < pointsCoordinates.size(); i++){
        minIntervalY = min(pointsCoordinates[i].y, minIntervalY);
        maxIntervalY = max(pointsCoordinates[i].y, maxIntervalY);
        for(int j = i + 1; j < pointsCoordinates.size(); j++)
            if(pointsCoordinates[i].x > pointsCoordinates[j].x)
                swap(pointsCoordinates[i], pointsCoordinates[j]);
    }    

    minIntervalX = min(minIntervalX, pointsCoordinates[0].x);
    maxIntervalX = max(maxIntervalX, pointsCoordinates[pointsCoordinates.size() - 1].x);

    
    points.clear();
    
    for(int i = 0; i < points.size(); i++){
            double x = graphX + margin*lengthX + determineCoordInAxes(points[i].getCoords().x, minIntervalX, maxIntervalX, lengthWMX, true);
            double y = graphY + margin*lengthY + determineCoordInAxes(points[i].getCoords().y, minIntervalY, maxIntervalY, lengthWMY, false);
            points[i].setPosition(x - radiusPoint, y - radiusPoint);
    }

    for(int i = 0; i < pointsCoordinates.size(); i++){
        double valX = pointsCoordinates[i].x;
        double valY = pointsCoordinates[i].y;

        double x = graphX + margin*lengthX + determineCoordInAxes(valX, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin*lengthY + determineCoordInAxes(valY, minIntervalY, maxIntervalY, lengthWMY, false);
        
        Point p(radiusPoint, x - radiusPoint, y - radiusPoint);
        p.setColor(color);

        points.push_back(p);
    }  

    int counter = 10;

    float segmentToAddY = double((maxIntervalY - minIntervalY)/counter);
    float labelY = minIntervalY;

    float segmentToAddX = double((maxIntervalX - minIntervalX)/counter);
    float labelX = minIntervalX;

    double coordx = graphX + margin*lengthX;
    double coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

    double segmentX = double(lengthX/counter);

    int i = 0;
        while(counter--){
            Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, to_string(labelX), font, true, textSize);
            bars.push_back(tmpX);
            coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
            Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, to_string(labelY), font, true, textSize);
            bars.push_back(tmpY);

            labelY += segmentToAddY;
            labelX += segmentToAddX;

            coordx += segmentX;
        } 

        if(margin == 0){
            Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, to_string(labelX), font, true, textSize);
            bars.push_back(tmpX);
            coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
            Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, to_string(labelY), font, true, textSize);
            bars.push_back(tmpY);
        }      
      
}

Graph::Graph(double xStart, double yStart, double xEnd, double yEnd, double _padding, double _margin, Font& _font){

    widthGraph = xEnd - xStart;
    heightGraph = yEnd - yStart;

    padding = _padding; 
    margin = _margin;

    font = _font;

    graphX = xStart + padding*widthGraph;
    graphY = yStart + padding*heightGraph;

    lengthX = widthGraph - 2*widthGraph*padding;
    lengthY = heightGraph - 2*heightGraph*padding; 

    lengthWMX = widthGraph*(1- 2*(padding + margin));
    lengthWMY = heightGraph*(1 - 2*(padding + margin));

    AxesX.setPosition(graphX, graphY + lengthY, graphX + lengthX, graphY + lengthY);

    AxesY.setPosition(graphX, graphY, graphX, graphY + lengthY);

    maxIntervalX = 0;
    minIntervalX = 0;

    maxIntervalY = 0;
    minIntervalY = 0;
}

void Graph::addPoint(Point p){

    bars.clear();

    points.push_back(p);

    minIntervalY = min(double(p.getCoords().y), minIntervalY);
    maxIntervalY = max(double(p.getCoords().y), maxIntervalY);

    minIntervalX = points[0].getCoords().x;
    maxIntervalX = p.getCoords().x;

    for(int i = 0; i < points.size(); i++){
        double valX = points[i].getCoords().x;
        double valY = points[i].getCoords().y;

        double x = graphX + margin*lengthX + determineCoordInAxes(valX, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin*lengthY + determineCoordInAxes(valY, minIntervalY, maxIntervalY, lengthWMY, false);

        points[i].setPosition(x - radiusPoint, y - radiusPoint);
    }  
    
    int counter = 10;

    float segmentToAddY = double((maxIntervalY - minIntervalY)/counter);
    float labelY = minIntervalY;

    float segmentToAddX = double((maxIntervalX - minIntervalX)/counter);
    float labelX = minIntervalX;

    double coordx = graphX + margin*lengthX;
    double coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

    double segmentX = double(lengthX/counter);
    
    int i = 0;

    double prec = double(pow(10.0, double(precision)));

    while(counter--){
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, truncate(to_string(ceil(labelX*prec)/prec), precision), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, truncate(to_string(ceil(labelY*prec)/prec),precision), font, true, textSize);
        bars.push_back(tmpY);

        labelY += segmentToAddY;
        labelX += segmentToAddX;

        coordx += segmentX;
    } 

    if(margin == 0){
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, truncate(to_string(ceil(labelX*prec)/prec), precision), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin*lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, truncate(to_string(ceil(labelY* prec)/prec),precision), font, true, textSize);
        bars.push_back(tmpY);
    }
    
}

void Graph::setRadiusPoint(double radius){
    radiusPoint = radius;
}

void Graph::setFunction(string function, double a, double b){
    bars.clear();
    plot(function, a, b);
}

void Graph::clear(){
    maxIntervalX = 0;
    minIntervalX = 0;

    maxIntervalY = 0;
    minIntervalY = 0;
    points.clear();
}

void Graph::removeFirstPoint(){
    points.erase(points.begin());
}

int Graph::getSize(){
    return points.size();
}

void Graph::setPrecisionDecimal(int _precision){
    precision = _precision;
}