#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <CircleShape2D.hpp>
#include <Label.hpp>
#include <VisibilityNotifier2D.hpp>

#include "functionutil.hpp"

class EnemyFunctionA : public godot::Area2D
{
    GODOT_CLASS(EnemyFunctionA, godot::Area2D)

    godot::Ref<godot::CircleShape2D> collision_shape;
    godot::Label *function_name;
    godot::VisibilityNotifier2D *visibility;
    Expression expression;

public:
    int radius = 20;
    godot::String expr = "x";
    godot::Vector2 velocity = godot::Vector2(0, 0);
    void _init();
    void _ready();
    void _draw();
    void _physics_process(double delta);
    void _on_Visibility_screen_exited();
    void _on_EnemyFunctionA_body_entered(godot::Node2D *body);

    static void _register_methods();
};
