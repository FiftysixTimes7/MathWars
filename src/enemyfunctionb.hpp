#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <Label.hpp>

class EnemyFunctionB : public godot::Area2D
{
    GODOT_CLASS(EnemyFunctionB, godot::Area2D)

    godot::Label *function_name;

public:
    int mode = 0;
    real_t value = 0;
    godot::Vector2 velocity = godot::Vector2(0, 0);
    void _init();
    void _ready();
    void _draw();
    void _physics_process(double delta);
    void _on_Visibility_screen_exited();
    void _on_EnemyFunctionA_area_entered(godot::Area2D *area);

    static void _register_methods();
};
