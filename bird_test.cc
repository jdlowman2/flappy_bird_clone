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


int make_bird_flap_once()
{
    auto bird = Bird();
    assert(bird.get_height()==0);

    bird.flap();
    assert(bird.get_height()==FLAP_HEIGHT);
    return 0;
}

int make_bird_drop_once()
{
    auto bird = Bird();

    bird.set_height(MAX_HEIGHT);
    bird.drop();
    assert(bird.get_height()==(MAX_HEIGHT-DROP_DISTANCE));
    return 0;
}

int bird_reaches_top()
{
    auto bird = Bird();
    bird.set_height(MAX_HEIGHT);
    assert(bird.get_height()==MAX_HEIGHT);

    bird.flap();
    assert(bird.get_height()==MAX_HEIGHT);
    return 0;
}

int bird_reaches_floor()
{
    auto bird = Bird();

    bird.drop();
    assert(bird.get_height()==MIN_HEIGHT);
    return 0;
}

int falling_bird()
{
    auto bird = Bird();
    bird.set_height(MAX_HEIGHT);

    bird.update_state(false);

    assert(bird.get_velocity() == TIMESTEP*GRAVITY);
    assert(bird.get_height() == MAX_HEIGHT + TIMESTEP*TIMESTEP*GRAVITY);

    bird.update_state(false);

    assert(bird.get_velocity() == 2*TIMESTEP*GRAVITY);
    assert(bird.get_height() == MAX_HEIGHT + 3*TIMESTEP*TIMESTEP*GRAVITY);


    bird.update_state(false);
    assert(bird.get_velocity() == 3*TIMESTEP*GRAVITY);
    almost_zero(bird.get_velocity() - 3*TIMESTEP*GRAVITY);

    const double val = bird.get_height() - ( MAX_HEIGHT + 6*TIMESTEP*TIMESTEP*GRAVITY); 
    almost_zero(val);

    return 0;
}

int one_spacebar() 
{
    auto bird = Bird();

    // Flap
    bird.set_height(MIN_HEIGHT);

    bird.update_state(true);

    assert(bird.get_velocity() == FLAP_VELOCITY);
    assert(bird.get_height() == MIN_HEIGHT + TIMESTEP*FLAP_VELOCITY);

    bird.update_state(false);

    assert(bird.get_velocity() == FLAP_VELOCITY + TIMESTEP*GRAVITY);

    const double expected_height = MIN_HEIGHT + TIMESTEP*FLAP_VELOCITY - TIMESTEP*(FLAP_VELOCITY + TIMESTEP*GRAVITY);
    almost_zero(bird.get_height() - expected_height);

    bird.update_state(false);

    almost_zero(bird.get_velocity() - (FLAP_VELOCITY + 2*TIMESTEP*GRAVITY));
    almost_zero(bird.get_height() - expected_height - TIMESTEP*(FLAP_VELOCITY + 2*TIMESTEP*GRAVITY));

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

    result = one_spacebar();
    print("Result of one_spacebar: ");
    print(result);

    return 0;
}
