#pragma once

#include <Godot.hpp>
#include <RigidBody2D.hpp>
#include <Label.hpp>
#include <Path2D.hpp>
#include <PathFollow2D.hpp>
#include <Curve2D.hpp>

#include "global.hpp"

class Number : public godot::RigidBody2D
{
    GODOT_CLASS(Number, godot::RigidBody2D)

    godot::Label *health_label;
    godot::Path2D *path;

public:
    godot::PathFollow2D *follow;
    int health = 1, velocity = 100;
    real_t offset = 0;
    bool split = false;
    void _init();
    void _ready();
    void _process();
    void _physics_process(double delta);

    static void _register_methods();
};
