#include "enemyfunctionb.hpp"

void EnemyFunctionB::_init()
{
}

void EnemyFunctionB::_ready()
{
    function_name = get_node<godot::Label>("FunctionName");
    switch (mode)
    {
    case 0:
        function_name->set_text("f+" + godot::String::num_int64(value));
        break;
    case 1:
        function_name->set_text("f*" + godot::String::num(value));
        break;
    case 2:
        function_name->set_text("f^" + godot::String::num(value));
        break;
    case 3:
        function_name->set_text("f*x^" + godot::String::num(value));
        break;
    case 4:
        function_name->set_text("fac(f)");
        break;
    case 5:
        function_name->set_text("abs(tan(f))");
        break;
    }
}

void EnemyFunctionB::_draw()
{
    draw_arc(godot::Vector2(0, 0), 15, 0, 2 * M_PI, 64, godot::Color(1, 0, 0, 0.3));
}

void EnemyFunctionB::_physics_process(double delta)
{
    set_position(get_position() + velocity * delta);
}

void EnemyFunctionB::_on_Visibility_screen_exited()
{
    queue_free();
}

void EnemyFunctionB::_on_EnemyFunctionA_area_entered(godot::Area2D *area)
{
    godot::String cur_expr = area->get("cur_expr");
    switch (mode)
    {
    case 0:
        area->call("set_function", cur_expr + "+" + godot::String::num_int64(value));
        break;
    case 1:
        area->call("set_function", "(" + cur_expr + ")*" + godot::String::num(value));
        break;
    case 2:
        area->call("set_function", "(" + cur_expr + ")^" + godot::String::num(value));
        break;
    case 3:
        area->call("set_function", "(" + cur_expr + ")*x^" + godot::String::num(value));
        break;
    case 4:
        area->call("set_function", "fac(" + cur_expr + ")");
        break;
    case 5:
        area->call("set_function", "abs(tan(" + cur_expr + "))");
        break;
    }
    queue_free();
}

void EnemyFunctionB::_register_methods()
{
    godot::register_method("_ready", &EnemyFunctionB::_ready);
    godot::register_method("_draw", &EnemyFunctionB::_draw);
    godot::register_method("_physics_process", &EnemyFunctionB::_physics_process);
    godot::register_method("_on_Visibility_screen_exited", &EnemyFunctionB::_on_Visibility_screen_exited);
    godot::register_method("_on_EnemyFunctionA_area_entered", &EnemyFunctionB::_on_EnemyFunctionA_area_entered);
    godot::register_property("mode", &EnemyFunctionB::mode, 0);
    godot::register_property("value", &EnemyFunctionB::value, (real_t)0);
    godot::register_property("velocity", &EnemyFunctionB::velocity, godot::Vector2(0, 0));
}
