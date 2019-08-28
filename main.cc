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

std::vector<sf::RectangleShape> make_rectangle_pair(const double x_pos, const double y_pos)
{
    const auto gap_size = 800.f;

    auto top = sf::RectangleShape(sf::Vector2f(50.f, y_pos));
    top.setFillColor(sf::Color::White);
    top.setPosition(x_pos, 0.0);

    auto bottom = sf::RectangleShape(sf::Vector2f(50.f, MAX_HEIGHT - y_pos - gap_size));
    bottom.setFillColor(sf::Color::White);
    bottom.setPosition(x_pos, y_pos + gap_size);

    std::vector<sf::RectangleShape> pair {top, bottom};

    return pair;
}


std::vector<sf::RectangleShape> make_rectangles()
{
    const std::vector<std::vector<double>> obstacle_positions {{1200.0, 0.0}, 
                                                    {2200.0, 0.0}, 
                                                    {1500, WINDOW_HEIGHT-500}};

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

    for (int offset=0; offset < 1000000; offset+=1000)
    {
        auto pair = make_rectangle_pair(800.0 + offset, offset/10.0 + 100);
        for (auto rect: pair)
        {
            shapes.push_back(rect);
        }
    }

    return shapes;
}

sf::CircleShape make_bird_shape(const Bird & bird)
{
    sf::CircleShape shape(BIRD_DIAMETER);

    if (bird.is_dead()){
        shape.setFillColor(sf::Color::Red);
    }
    else {
        shape.setFillColor(sf::Color::Green);
    }

    shape.setPosition(BIRD_HORIZONTAL_OFFSET, bird.get_height());

    return shape;
}

sf::RectangleShape make_bird_rectangle(const Bird & bird)
{        
    auto rectangle = sf::RectangleShape(sf::Vector2f(2*BIRD_DIAMETER, 2*BIRD_DIAMETER));
    rectangle.setPosition(BIRD_HORIZONTAL_OFFSET, bird.get_height());

    return rectangle;
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

bool check_for_collisions(Bird & bird, const std::vector<sf::RectangleShape> & rectangles)
{   
    for (auto rectangle: rectangles)
    {
        if (is_collision(bird, rectangle))
        {
            bird.set_dead(true);
            return true;
        }
    }
    return false;
}

sf::Text draw_game_over_text()
{
    sf::Text text;

    text.setString("GAME OVER");
    text.setCharacterSize(MAX_WIDTH/2.0); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(MAX_WIDTH/2.0, MAX_HEIGHT/2.0);

    return text;
}

void draw_game_over_window(sf::RenderWindow & window, Bird & bird)
{
    if (bird.is_dead())
    {
        const auto dead_bird_shape = make_bird_shape(bird);
        window.draw(dead_bird_shape);
        const auto text = draw_game_over_text();
        window.draw(text);
        window.display();
    }
}

void wait_to_start_game(sf::RenderWindow & window, Bird & bird, std::vector<sf::RectangleShape> & rectangles)
{
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

    return;
}


void wait_to_close_window(sf::RenderWindow & window)
{
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

    return;
}

void update_game(sf::RenderWindow & window,
                 Bird & bird,
                 std::vector<sf::RectangleShape> & rectangles,
                 bool shouldFlap)
{
    bird.update_state(shouldFlap);
    update_obstacles(rectangles);
    update_window(window, bird, rectangles);
    
    check_for_collisions(bird, rectangles);

    return;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(MAX_WIDTH, MAX_HEIGHT), "Flappy Bird!");

    auto bird = Bird();
    std::vector<sf::RectangleShape> rectangles;

    if (OBSTACLES){
        rectangles = make_rectangles();
    }

    bool shouldFlap = false;

    wait_to_start_game(window, bird, rectangles);
 
    while (window.isOpen() && !bird.is_dead())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            shouldFlap = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }

        update_game(window, bird, rectangles, shouldFlap);

        std::this_thread::sleep_for (std::chrono::milliseconds(UPDATE_RATE_MILLIS));
    }

    draw_game_over_window(window, bird);

    wait_to_close_window(window);

    return 0;
}