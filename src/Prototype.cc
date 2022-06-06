#define DEBUG
#include <sqlite3.h>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "SQLConnector.h"
#include "SimulationTable.h"
#include "CameraTable.h"
#include "MeasurementTable.h"
#include "VehicleType.hpp"

int prototype(int argc, char *argv[])
{
   // std::string filepath = "../zpr.db";

   // auto database = std::make_unique<SQLConnector>(filepath);
   // std::string name = "TEST3";
   // SimulationTable simulation_table(name);
   // database->insertData(simulation_table);

   // CameraTable camera_table(1, 3, 0.2, 0.3);
   // database->insertData(camera_table);

   // MeasurementTable measurement_table(5, 6, 1.2, VehicleType::Car, camera_table, simulation_table);
   // database->insertData(measurement_table);
   // sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
   //  sf::CircleShape shape(25.f);
   //  shape.setPosition(25., 25.);
   //  shape.setFillColor(sf::Color::Red);

   //  while (window.isOpen())
   //  {
   //      sf::Event event;
   //      while (window.pollEvent(event))
   //      {
   //          if (event.type == sf::Event::Closed)
   //              window.close();
   //      }

   //      window.clear();
   //      window.draw(shape);
   //      window.display();
   //  }
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::CircleShape shape(25.f);
    double pos = 25.;
    shape.setPosition(pos, pos);
    shape.setFillColor(sf::Color::Red);
    
    sf::RectangleShape line1(sf::Vector2f(150.f, 20.f));
    line1.setPosition(5., 25.);

    sf::RectangleShape line2(sf::Vector2f(150.f, 20.f));
    line2.setPosition(155., 5.);
    line2.rotate(90);

    sf::RectangleShape car(sf::Vector2(10.f, 10.f));
    car.setPosition(5., 25.f+20.f-10.f);
    car.setFillColor(sf::Color::Transparent);
    
    int counter = 0;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
      //   pos += 1.;
      //   shape.setPosition(pos, pos);
        shape.move(1, 1);
        if (counter < 150-20)
        {
           car.move(1,0);
           counter++;
        }
        else
        {
           car.move(0,1);
        }
        
        window.draw(shape);
        window.draw(line1);
        window.draw(line2);
        window.draw(car);

        // end the current frame
        window.display();
        usleep(10*1000);
    }

    return 0;
}