#define DEBUG
#include <sqlite3.h>
#include <math.h> 
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
#include "Simulation.h"

int main(int argc, char *argv[])
{
//    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
//     sf::CircleShape shape(25.f);
//     double pos = 25.;
//     shape.setPosition(pos, pos);
//     shape.setFillColor(sf::Color::Red);
    
//     sf::RectangleShape line1(sf::Vector2f(150.f, 20.f));
//     line1.setPosition(5., 25.);

//     sf::RectangleShape line2(sf::Vector2f(150.f, 20.f));
//     line2.setPosition(155.+20., 5.);
//     line2.rotate(90);

//     sf::RectangleShape car(sf::Vector2(10.f, 10.f));
//     car.setPosition(5., 25.f+20.f-10.f);
//     car.setFillColor(sf::Color::Red);

//     sf::RectangleShape dot(sf::Vector2(10.f, 10.f));
//     dot.setPosition(100.f*cos(90.f*M_PI/180),100.f*sin(90.f*M_PI/180));
//     dot.setFillColor(sf::Color::Red);

//    //  sf::CircleShape camera_point(2.f);
//    //  camera_point.setRadius(10.f);
//    //  camera_point.setPosition(170.f, 30.f);
//    //  camera_point.setFillColor(sf::Color::Blue);
    
//     sf::CircleShape camera(30.f, 3);
//     camera.setFillColor(sf::Color(0,255,0,200));
//     camera.setPosition(100.f,0.f);
//    //  camera.setPosition(170.f, 30.f);
//     camera.rotate(90.f);

//      sf::CircleShape camera2(30.f, 3);
//     camera2.setFillColor(sf::Color(128,255,0,200));
//     camera2.setPosition(100.f,0.f);
//    //  camera.setPosition(170.f, 30.f);
//     // camera2.rotate(90.f);
    
//     int counter = 0;
//     // run the program as long as the window is open
//     while (window.isOpen())
//     {
//         // check all the window's events that were triggered since the last iteration of the loop
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // "close requested" event: we close the window
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         // clear the window with black color
//         window.clear(sf::Color::Black);

//         // draw everything here...
//         // window.draw(...);
//       //   pos += 1.;
//       //   shape.setPosition(pos, pos);
//         // shape.move(1, 1);
//         // if (counter < 150-20)
//         // {
//         //    car.move(1,0);
//         //    counter++;
//         // }
//         // else
//         // {
//         //    car.move(0,1);
//         // }

//         auto bounding_box = car.getGlobalBounds();
//         auto bounding_box_2 = line1.getGlobalBounds();

//         if(bounding_box.intersects(bounding_box_2))
//         {
//             std::cout << "Na drodze" << std::endl;
//             car.move(1,0);
//             if(bounding_box.intersects(bounding_box_2))
//             {
//                 std::cout << "Git" << std::endl;
//             }
//             else
//             {
//                 std::cout << "Wylecial" << std::endl;
//                 usleep(10000*1000);
//             }
//         }

//         // else
//         // {
//         //     std::cout << "Poza droga" << std::endl;
//         //     car.move(0,1);
//         // }

        
//         window.draw(shape);
//         window.draw(line1);
//         window.draw(line2);
//         window.draw(car);
//         window.draw(camera);
//         window.draw(camera2);

//         // end the current frame
//         window.display();
//         usleep(10*1000);
//     }
    
    auto rc1 = RoadConfig(5, 25, 150.f, 20.f, Move(MoveType::RIGHT, MoveType::NONE));
    auto rc2 = RoadConfig(175, 5, 150.f, 20.f, Move(MoveType::NONE, MoveType::DOWN), 90);

    // auto vc1 = VehicleConfig(5, 35, 1, VehicleType::Car, sf::Color::Red, 10.f);
    auto vc1 = VehicleConfig(5, 35, 1, VehicleType::Car, sf::Color::Red, 10.f);
    auto vc2 = VehicleConfig(5, 35, 2, VehicleType::Car, sf::Color::Blue, 10.f);

    std::vector<RoadConfig> rcv;
    std::vector<VehicleConfig> vcv;

    rcv.push_back(rc1);
    rcv.push_back(rc2);
    vcv.push_back(vc1);
    vcv.push_back(vc2);

    auto config = Config(0,1,0,25,rcv,vcv);
    auto sim = Simulation(config);
    sim.run();
    return 0;
}