#pragma once

#include <Godot.hpp>
#include <Button.hpp>

#include "global.hpp"

class CustomButton : public godot::Button
{
    GODOT_CLASS(CustomButton, godot::Button)

public:
    int cost = 0;
    void _init();
    void _ready();
    void _process(double delta);

    static void _register_methods();
};
