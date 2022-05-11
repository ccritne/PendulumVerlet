#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


struct coord{
    double x, y;
};

struct dim{
    double w, h;
};

struct point{
    double x, y;
    bool visible;
};

double determineCoordInAxes(double number, double minInterval, double maxInterval, double length, bool xORy){
    
    double percentage = (double)(double(number - minInterval)/ double(maxInterval - minInterval));

    if(xORy) //x
        return percentage*length;
    else     //y
        return (1-percentage)*length;


}

bool isNumber(string number_string)
{
    string::size_type sz;
    bool is_valid;
    double parsed_number = 0.0;
    try 
    { 
        parsed_number = std::stod(number_string, &sz); 
        is_valid = true; 
    } 
    catch(std::exception& ia) 
	{ 
        is_valid = false; 
    } 

    return is_valid;
}

string truncate(string str, int nDecimal){
    int iter = 0;
    while(str[iter] != '.')
        iter++;

    return str.substr(0, iter + nDecimal);
}