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
        height_ = MAX_HEIGHT/2.0;
        velocity_ = FLAP_VELOCITY;
        acceleration_ = GRAVITY;
        is_dead_ = false;
    }

    void flap()
    {
        set_height(height_ + FLAP_HEIGHT);
        return;
    }

    void drop()
    {
        set_height(height_ - DROP_DISTANCE);
        return; 
    }

    void set_height(const double new_height)
    {
        height_ = std::min(new_height, MAX_HEIGHT);
        height_ = std::max(new_height, MIN_HEIGHT);

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

        if (height_ <= MIN_HEIGHT || height_ >= MAX_HEIGHT)
        {
            set_dead(true);
        }

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
        std::cout << "Height| Velocity | Acceleration | Alive " << std::endl;
        std::cout << height_ << "  "<< velocity_<< "  " << acceleration_ << "   "<< is_dead_ << std::endl;
    }

    bool is_dead() const
    {
        return is_dead_;
    }

    void set_dead(const bool status)
    {
        is_dead_ = status;
    }

private:
    double height_;

    double velocity_;

    double acceleration_;

    bool is_dead_;
};