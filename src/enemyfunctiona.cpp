#include "enemyfunctiona.hpp"

void EnemyFunctionA::_init() {}

void EnemyFunctionA::_ready()
{
    collision_shape = get_node<godot::CollisionShape2D>("EffectedArea")->get_shape();
    function_name = get_node<godot::Label>("FunctionName");
    visibility = get_node<godot::VisibilityNotifier2D>("Visibility");
    collision_shape->set_radius(radius);
    function_name->set_text(expr);
    visibility->set_rect(godot::Rect2(-radius, -radius, 2 * radius, 2 * radius));
    expression.set(expr.utf8().get_data());
}

void EnemyFunctionA::_draw()
{
    draw_arc(godot::Vector2(0, 0), radius, 0, 2 * M_PI, 64, godot::Color(1, 0, 0, 0.3));
}

void EnemyFunctionA::_physics_process(double delta)
{
    set_position(get_position() + velocity * delta);
}

void EnemyFunctionA::_on_Visibility_screen_exited()
{
    queue_free();
}

void EnemyFunctionA::_on_EnemyFunctionA_body_entered(godot::Node2D *body)
{
    real_t health = body->get("health");
    health = expression(health);
    body->set("health", health);
}

void EnemyFunctionA::_register_methods()
{
    godot::register_method("_ready", &EnemyFunctionA::_ready);
    godot::register_method("_draw", &EnemyFunctionA::_draw);
    godot::register_method("_physics_process", &EnemyFunctionA::_physics_process);
    godot::register_method("_on_Visibility_screen_exited", &EnemyFunctionA::_on_Visibility_screen_exited);
    godot::register_method("_on_EnemyFunctionA_body_entered", &EnemyFunctionA::_on_EnemyFunctionA_body_entered);
    godot::register_property("radius", &EnemyFunctionA::radius, 20);
    godot::register_property("expr", &EnemyFunctionA::expr, godot::String("x"));
    godot::register_property("velocity", &EnemyFunctionA::velocity, godot::Vector2(0, 0));
}
