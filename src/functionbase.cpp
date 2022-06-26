#include "functionbase.hpp"

void FunctionBase::_init() {}

void FunctionBase::_ready()
{
    collision_shape = get_node<godot::CollisionShape2D>("EffectedArea")->get_shape();
    visualized_area = get_node<godot::ColorRect>("VisualizedArea");
}

real_t FunctionBase::calculate(real_t value)
{
    return expression(value);
}

void FunctionBase::upgrade()
{
    int cost = round(pow(200, grade));
    grade += 1;
    coins -= cost;
    real_t extends = 32 * grade;
    collision_shape->set_extents(godot::Vector2(extends, extends));
    visualized_area->set_margin(0, -extends);
    visualized_area->set_margin(1, -extends);
    visualized_area->set_margin(2, extends);
    visualized_area->set_margin(3, extends);
}

int FunctionBase::get_value()
{
    return 4 + (round(pow(200, grade)) - 1) / 199 + expression.evaluate();
}

void FunctionBase::sell()
{
    coins += get_value();
    queue_free();
}

void FunctionBase::set_function(godot::String nexpr)
{
    cur_expr = nexpr;
    expression.set(nexpr.utf8().get_data());
}

void FunctionBase::set_range_visible(bool visible)
{
    visualized_area->set_visible(visible);
}

void FunctionBase::_register_methods()
{
    godot::register_method("_ready", &FunctionBase::_ready);
    godot::register_method("calculate", &FunctionBase::calculate);
    godot::register_method("upgrade", &FunctionBase::upgrade);
    godot::register_method("get_value", &FunctionBase::get_value);
    godot::register_method("sell", &FunctionBase::sell);
    godot::register_method("set_function", &FunctionBase::set_function);
    godot::register_method("set_range_visible", &FunctionBase::set_range_visible);
    godot::register_property("grade", &FunctionBase::grade, 1);
    godot::register_property("cur_expr", &FunctionBase::cur_expr, (godot::String) "x");
}
