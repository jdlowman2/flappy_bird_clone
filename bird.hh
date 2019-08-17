// Author: Joseph Lowman

#pragma once

#include "constants.hh"

#include <algorithm>
#include <iostream>
#include <vector>

class Bird
{
public:
    Bird()
    {
        height_ = 0;
        velocity_ = FLAP_VELOCITY;
        acceleration_ = GRAVITY;
    }

    void flap()
    {
        height_ = std::min(height_ + FLAP_HEIGHT, MAX_HEIGHT);

        return;
    }

    void drop()
    {
        height_ = std::max(height_ - DROP_DISTANCE, MIN_HEIGHT);

        return; 
    }

    void set_height(const double new_height)
    {
        height_ = std::min(new_height, MAX_HEIGHT);

        return;
    }

    void set_velocity(const double new_velocity)
    {
        velocity_ = new_velocity;
    }

    void update_state(bool is_flap)
    {
        double new_velocity = (is_flap) ? FLAP_VELOCITY : velocity_ + TIMESTEP*acceleration_;

        set_velocity(new_velocity);
        set_height(height_ + TIMESTEP*velocity_);

        print_state();

        return;
    }

    double get_height() const
    {
        return height_;
    }

    double get_velocity() const
    {
        return velocity_;
    }

    void print_state() const
    {
        std::cout << "Height| Velocity | Acceleration " << std::endl;
        std::cout << height_ << "  "<< velocity_<< "  " << acceleration_ << std::endl;
    }

private:
    double height_;

    double velocity_;

    double acceleration_;
};