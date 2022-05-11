#include "lib/TextBox.hpp"
#include "lib/Button.hpp"
#include "lib/Graph.hpp"
#include "lib/Bob.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
	int paddingX = 450;
	int paddingY = 400;
	float rodG = 300.0;
	float radius = 10.0;
	float vel = 0.0;
	float rodC, weight, f, g = 9.81, dt;
	float angle = 0;
	float epot, ekin;
	float x = rodG*sin(angle), y = rodG*cos(angle);
	float posX = paddingX + x, posY = paddingY + y;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1980, 1200), "Pendulum", sf::Style::Default, settings);
	window.setFramerateLimit(60);
    Font font;
    font.loadFromFile("need/arial.ttf");
	Textbox weightBox(100, 20, 100, 20, font);
	Text weightTextBox;
	weightTextBox.setFont(font);
    weightTextBox.setPosition(Vector2f(105, 3));
    weightTextBox.setCharacterSize(12);
    weightTextBox.setString("Weight(kg):");

	Textbox rodBox(220, 20, 100, 20, font);
	Text rodTextBox;
	rodTextBox.setFont(font);
	rodTextBox.setPosition(Vector2f(225, 3));
    rodTextBox.setCharacterSize(12);
    rodTextBox.setString("Length(m):");

	Textbox AngleBox(340, 20, 100, 20, font);
	Text angleTextBox;
	angleTextBox.setFont(font);
	angleTextBox.setPosition(Vector2f(345, 3));
    angleTextBox.setCharacterSize(12);
    angleTextBox.setString("Angle(rad):");

	Textbox VelocityBox(460, 20, 100, 20, font);
	Text velocityTextBox;
	velocityTextBox.setFont(font);
	velocityTextBox.setPosition(Vector2f(465, 3));
    velocityTextBox.setCharacterSize(12);
    velocityTextBox.setString("Velocity(m/s):");

	Textbox dtBox(580, 20, 100, 20, font);
	Text dtTextBox;
	dtTextBox.setFont(font);
	dtTextBox.setPosition(Vector2f(580, 3));
    dtTextBox.setCharacterSize(12);
    dtTextBox.setString("dt(s):");

	Button sent(700, 17.5, 25, 25, font);
	sent.setText("GO!");

	Button stop(745, 17.5, 75, 25, font);
	stop.setText("STOP!");
	
	Bob bob(posX - radius,posY, radius, sf::Color::Blue);

	sf::RectangleShape rect(sf::Vector2f(800, 800));
	rect.setPosition(50, 50);
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(1);

	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(paddingX, paddingY)),
		sf::Vertex(sf::Vector2f(paddingX + x, paddingY + y + radius))
	};

	int iter = 0;

	bool start = false;
	bool stopped = false;

	bool condDrag = false;

	bool condMassa = false;
	bool condLength = false;
	bool condAngle = false;
	bool condVelocity = false;
	bool conddt = false;

	string weightText = "";
	string lengthText = "";
	string angleText = "";
	string velocityText = "";
	string dtText = "";

	ofstream AV("res/date1.txt");
	ofstream E("res/date2.txt");

	Text AngleVelocityDescription;

	AngleVelocityDescription.setFont(font);
	AngleVelocityDescription.setPosition(Vector2f(1200, 25));
	AngleVelocityDescription.setString("red - rad(t)	green - v(t)");
	AngleVelocityDescription.setCharacterSize(15);

	Graph AngleVelocity(1000, 50, 1800, 400, 0, 0, font);

	Text EnergyDescription("magenta - K(t)    yellow - U(t)    white - Em(t)", font);
	EnergyDescription.setCharacterSize(15);
	EnergyDescription.setFillColor(sf::Color::White);
	EnergyDescription.setOutlineColor(sf::Color::White);
	EnergyDescription.setPosition(Vector2f(1200, 450));
	Graph Energy(1000, 500, 1800, 850, 0, 0, font);

	int counter = 0;


	while (window.isOpen()){
		sf::Event event;

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
            if (event.type == Event::TextEntered && condMassa && event.text.unicode != 8 && event.text.unicode != 13)
                weightText += static_cast<char>(event.text.unicode);
            if (event.type == Event::TextEntered && condLength && event.text.unicode != 8 && event.text.unicode != 13)
                lengthText += static_cast<char>(event.text.unicode);
            if (event.type == Event::TextEntered && condAngle && event.text.unicode != 8 && event.text.unicode != 13){
                angleText += static_cast<char>(event.text.unicode);   
				if(!start)
					if(isNumber(angleText))
						angle=stold(angleText);				
				else{
					if(isNumber(weightText))
						weight = stold(weightText);
					if(isNumber(lengthText))
						rodC = stold(lengthText);
					if(isNumber(angleText))
						angle = stold(angleText);
					if(isNumber(velocityText))
						vel = stold(velocityText); 
					if(isNumber(dtText))
						dt = stold(dtText); 
				}
			}
            if (event.type == Event::TextEntered && condVelocity && event.text.unicode != 8 && event.text.unicode != 13)
                velocityText += static_cast<char>(event.text.unicode);     
            if (event.type == Event::TextEntered && conddt && event.text.unicode != 8 && event.text.unicode != 13)
                dtText += static_cast<char>(event.text.unicode);          
            if (event.type == Event::KeyPressed && condMassa && event.key.code == Keyboard::BackSpace && !weightText.empty())
                weightText.pop_back();
            if (event.type == Event::KeyPressed && condLength && event.key.code == Keyboard::BackSpace && !lengthText.empty())
                lengthText.pop_back();
            if (event.type == Event::KeyPressed && condAngle && event.key.code == Keyboard::BackSpace && !angleText.empty()){
                angleText.pop_back();
				if(!start){				   
					if(angleText.empty())
						angle = 0;
					else
						if(isNumber(angleText))
							angle=stold(angleText);	
				}else{
					if(isNumber(weightText))
						weight = stold(weightText);
					if(isNumber(lengthText))
						rodC = stold(lengthText);
					if(isNumber(angleText))
						angle = stold(angleText);
					if(isNumber(velocityText))
						vel = stold(velocityText); 
					if(isNumber(dtText))
						dt = stold(dtText); 
				}			
			}
            if (event.type == Event::KeyPressed && conddt && event.key.code == Keyboard::BackSpace && !dtText.empty())
                dtText.pop_back();
            if (event.type == Event::KeyPressed && condVelocity && event.key.code == Keyboard::BackSpace && !velocityText.empty())
                velocityText.pop_back();

			if(sent.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = false;
				condLength = false;
				condAngle = false;
				condVelocity = false;

				if(weightText == "") weightText = "1.0";
				if(lengthText == "") lengthText = "1.0";
				if(angleText == "") angleText = "1.570795";
				if(velocityText == "") velocityText = "0.0";
				if(dtText == "") dtText = "0.008";

				weight = stold(weightText);
				rodC = stold(lengthText);
				angle = stold(angleText);
				vel = stold(velocityText);
				dt = stold(dtText); 

				start = true;
				stopped = false;
				stop.setText("STOP!");
				
				Energy.clear();
				AngleVelocity.clear();

				iter = 0;
			}

			if(stop.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				start = !start;
				stopped = !stopped;
				if(stopped)
					stop.setText("CONTINUE!");
				else
					stop.setText("STOP!");
			}

			if(weightBox.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = true;
				condLength = false;
				condAngle = false;
				condVelocity = false;
				conddt = false;
			}
			
			if(rodBox.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = false;
				condLength = true;
				condAngle = false;
				condVelocity = false;
				conddt = false;
			}
			
			if(AngleBox.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = false;
				condLength = false;
				condAngle = true;
				condVelocity = false;
				conddt = false;
			}

			if(VelocityBox.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = false;
				condLength = false;
				condAngle = false;
				condVelocity = true;
				conddt = false;
			}

			if(dtBox.contains(Mouse::getPosition(window)) && (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)){
				condMassa = false;
				condLength = false;
				condAngle = false;
				condVelocity = false;
				conddt = true;
			}
		}

		if(weightBox.getText() != weightText)
            weightBox.setText(weightText);

		if(rodBox.getText() != lengthText)
            rodBox.setText(lengthText);
        
		if(AngleBox.getText() != angleText)
            AngleBox.setText(angleText);

		if(VelocityBox.getText() != velocityText)
            VelocityBox.setText(velocityText);

		if(dtBox.getText() != dtText)
            dtBox.setText(dtText);

		x=rodG*sin(angle);
		y=rodG*cos(angle);
		posX = paddingX + x;
		posY = paddingY + y;
		bob.setPosition({posX - radius, posY});

		if(start){
			angle = angle + vel*dt + 0.5*f/weight*dt*dt;
	    	vel = vel + 0.5 * dt * f/weight;
			f = -(g/rodC) * sin(angle) * weight;
			vel = vel + 0.5 * dt * f/weight;
			epot =  weight * g * (1-cos(angle));
			ekin =  0.5 * weight * vel*vel;

			AngleVelocity.addPoint(Point(dt*iter, angle, sf::Color::Red));
			AngleVelocity.addPoint(Point(dt*iter, vel, sf::Color::Green));

			Energy.addPoint(Point(dt*iter, ekin, sf::Color::Magenta));
			Energy.addPoint(Point(dt*iter, epot, sf::Color::Yellow));
			Energy.addPoint(Point(dt*iter, ekin+epot, sf::Color::White));

			AV << dt << dt*iter << angle << vel;
			AV << dt << dt*iter << ekin << epot << ekin+epot;

			iter++;
		}

		sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(paddingX, paddingY)),
				sf::Vertex(sf::Vector2f(paddingX + x, paddingY + y + radius))
		};

		window.clear();

		window.draw(rect);

	    window.draw(line,2,sf::Lines);
	    window.draw(bob);

		window.draw(weightBox);
		window.draw(rodBox);
		window.draw(AngleBox);
		window.draw(VelocityBox);
		window.draw(dtBox);

		window.draw(weightTextBox);
		window.draw(rodTextBox);
		window.draw(angleTextBox);
		window.draw(velocityTextBox);
		window.draw(dtTextBox);

		window.draw(AngleVelocity);
		window.draw(Energy);

		window.draw(AngleVelocityDescription);
		window.draw(EnergyDescription);

		window.draw(sent);
		window.draw(stop);
	    window.display();

	}

	return 0;
}
