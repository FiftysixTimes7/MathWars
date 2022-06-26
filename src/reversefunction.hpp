#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <SceneTree.hpp>

class ReverseFunction : public godot::Area2D
{
    GODOT_CLASS(ReverseFunction, godot::Area2D)

public:
    godot::Vector2 velocity = godot::Vector2(0, 0);
    void _init();
    void _physics_process(double delta);
    void _on_Visibility_screen_exited();
    void _on_ReverseFunction_area_entered(godot::Area2D *area);

    static void _register_methods();
};
