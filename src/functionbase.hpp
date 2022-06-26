#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <RectangleShape2D.hpp>
#include <ColorRect.hpp>

#include "global.hpp"
#include "functionutil.hpp"

class FunctionBase : public godot::Area2D
{
    GODOT_CLASS(FunctionBase, godot::Area2D)

    godot::Ref<godot::RectangleShape2D> collision_shape;
    godot::ColorRect *visualized_area;
    Expression expression;

public:
    int grade = 1;
    godot::String cur_expr = "x";
    void _init();
    void _ready();
    real_t calculate(real_t value);
    void upgrade();
    int get_value();
    void sell();
    void set_function(godot::String nexpr);
    void set_range_visible(bool enable);

    static void _register_methods();
};
