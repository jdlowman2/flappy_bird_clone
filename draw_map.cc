// Author: Joseph Lowman
#include <SFML/Graphics.hpp>

#include "bird.hh"
#include "constants.hh"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include <vector>

const double WINDOW_WIDTH = MAX_WIDTH;
const double WINDOW_HEIGHT = MAX_HEIGHT;

const double BIRD_HORIZONTAL = 100.0;
const double BIRD_DIAMETER = 100.0;

std::vector<sf::RectangleShape> make_rectangles()
{
    const std::vector<std::vector<double>> obstacle_positions {{1000.0, 0.0}, {2000.0, 0.0}, {1500, WINDOW_HEIGHT-500}};

    std::vector<sf::RectangleShape> shapes;

    for (int horizontal_offset = 0; horizontal_offset < 1000000; horizontal_offset+=1000)
    {
        for (const auto position: obstacle_positions)
        {
            auto rectangle = sf::RectangleShape(sf::Vector2f(50.f, 500.f));
            rectangle.setFillColor(sf::Color::White);
            rectangle.setPosition(position.front() + horizontal_offset, position.back());

            shapes.push_back(rectangle);
        }
    }
    return shapes;
}

sf::CircleShape make_bird_shape(const Bird & bird)
{
    const auto height = bird.get_height();
    sf::CircleShape shape(BIRD_DIAMETER);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(BIRD_HORIZONTAL, height);

    return shape;
}

sf::RectangleShape make_bird_rectangle(const Bird & bird)
{        
    auto rectangle = sf::RectangleShape(sf::Vector2f(200.f, 200.f));
    rectangle.setPosition(BIRD_HORIZONTAL, bird.get_height());

    return rectangle;
}

sf::CircleShape make_dead_bird_shape(const Bird & bird)
{
    const auto height = bird.get_height();
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(BIRD_HORIZONTAL, height);

    return shape;
}

void update_obstacles(std::vector<sf::RectangleShape> & obstacles)
{
    for (auto & obstacle: obstacles)
    {        
        obstacle.move(TIMESTEP * SPEED_OBSTACLES, 0.0);
    }
}

void update_window(sf::RenderWindow & window, const Bird & bird, const std::vector<sf::RectangleShape> & rectangles)
{
    window.clear();
    window.draw(make_bird_shape(bird));
    for (auto rect: rectangles)
    {
        window.draw(rect);
    }
    window.display();
}

bool is_collision(const Bird & bird, const sf::RectangleShape & rectangle)
{
    const auto bird_rectangle = make_bird_rectangle(bird);

    const auto bird_bounds = bird_rectangle.getGlobalBounds();
    const auto obstacle_bounds = rectangle.getGlobalBounds();


    auto result = obstacle_bounds.intersects(bird_bounds);

    if (result == 1)
    {
        std::cout << "Collision detected! " << std::endl;
    }

    return result;
}

bool is_collision(const Bird & bird, const std::vector<sf::RectangleShape> & rectangles)
{   
    const auto height = bird.get_height();
    if (height <= 0.0 || height >= MAX_HEIGHT)
    {
        return true;
    }

    for (auto rectangle: rectangles)
    {
        if (is_collision(bird, rectangle))
        {
            return true;
        }
    }
    return false;
}



sf::Text draw_game_over()
{
    sf::Text text;

    text.setString("GAME OVER");
    text.setCharacterSize(MAX_WIDTH/2.0); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(MAX_WIDTH/2.0, MAX_HEIGHT/2.0);

    return text;
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "SFML works!");

    Bird bird;
    bird.set_height(MAX_HEIGHT-1000);

    auto rectangles = make_rectangles();
    int indx = 0;
    bool shouldFlap = false;
    bool is_dead = false;

    std::cout << "Press <spacebar> to start" << std::endl;

    bool start_game = false;
    update_window(window, bird, rectangles);

    while (!start_game)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                start_game = true;
            }
        }
    }
 
    while (window.isOpen() && !is_dead)
    {
        indx++;
        sf::Event event;
        while (window.pollEvent(event))
        {
            shouldFlap = false;

            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                shouldFlap = true;
            }
        }

        bird.update_state(shouldFlap);
        update_obstacles(rectangles);
        update_window(window, bird, rectangles);

        if (is_collision(bird, rectangles))
        {   
            is_dead = true;
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(25));
    }


    if (is_dead)
    {
        const auto dead_bird_shape = make_dead_bird_shape(bird);
        window.draw(dead_bird_shape);
        const auto text = draw_game_over();
        window.draw(text);
        window.display();
    }

    std::cout << "Press <Q> in the game screen to exit" << std::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}