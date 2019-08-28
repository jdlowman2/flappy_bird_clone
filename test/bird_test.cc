// Author: Joseph Lowman

#include <cassert>
#include <iostream>
#include <string>
#include <cmath>
#include "../bird.hh"

const double ALMOST_EQUAL = 0.001;

template <typename T>
void print(T object){
    std::cout << object << std::endl;
    return;
}

void almost_zero(double arg)
{
    // std::cout << "Value is: " << abs(arg);
    // std::cout << " compared to " << ALMOST_EQUAL << std::endl;
    assert(abs(arg) < ALMOST_EQUAL);
}

template <typename T>
bool expect_true(T val1, T val2)
{
    if (val1==val2)
    {
        return true;
    }
    std::cout << "\nTest failed" << std::endl;
    std::cout << "Value 1: " << val1 << " Value2: " << val2 << "\n"<< std::endl;
    return false;
}

int make_bird_flap_once()
{
    const double initial_position = MAX_HEIGHT/2.0;
    auto bird = Bird();

    assert(bird.get_height() == initial_position);

    bird.set_height(initial_position + FLAP_HEIGHT);
    assert(bird.get_height() == initial_position + FLAP_HEIGHT);
    return 0;
}

int make_bird_drop_once()
{
    auto bird = Bird();

    bird.set_height(MAX_HEIGHT);
    bird.set_height(MAX_HEIGHT-DROP_DISTANCE);
    assert(bird.get_height()==(MAX_HEIGHT-DROP_DISTANCE));
    return 0;
}

int bird_reaches_top()
{
    auto bird = Bird();
    assert(bird.is_dead()==false);

    bird.set_height(0.0 + FLAP_HEIGHT/2.0);
    bird.set_velocity(0.0);
    bird.update_state(true);

    assert(bird.get_height()==0.0);
    assert(bird.is_dead()==true);

    return 0;
}

int bird_reaches_floor()
{
    auto bird = Bird();
    bird.set_height(MIN_HEIGHT);
    bird.set_velocity(0.0);

    bird.set_height(bird.get_height() - DROP_DISTANCE);

    assert(bird.get_height()==MIN_HEIGHT);
    return 0;
}

int falling_bird()
{
    auto bird = Bird();
    bird.set_height(0.0);
    bird.set_velocity(0.0);

    bird.update_state(false);

    assert(bird.get_velocity() == TIMESTEP*GRAVITY);
    assert(bird.get_height() == 0.0 + TIMESTEP*TIMESTEP*GRAVITY);

    bird.update_state(false);

    assert(bird.get_velocity() == 2*TIMESTEP*GRAVITY);
    assert(bird.get_height() == 0.0 + 3*TIMESTEP*TIMESTEP*GRAVITY);


    bird.update_state(false);
    assert(bird.get_velocity() == 3*TIMESTEP*GRAVITY);
    almost_zero(bird.get_velocity() - 3*TIMESTEP*GRAVITY);

    const double val = bird.get_height() - ( 0.0 + 6*TIMESTEP*TIMESTEP*GRAVITY); 
    almost_zero(val);

    return 0;
}



int main()
{
    int result;
    result = make_bird_flap_once();
    print("Result of make_bird_flap_once: ");
    print(result);

    result = make_bird_drop_once();
    print("Result of make_bird_drop_once: ");
    print(result);

    result = bird_reaches_top();
    print("Result of bird_reaches_top: ");
    print(result);

    result = bird_reaches_floor();
    print("Result of bird_reaches_floor: ");
    print(result);

    result = falling_bird();
    print("Result of falling_bird: ");
    print(result);

    return 0;
}
