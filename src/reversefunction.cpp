#include "reversefunction.hpp"

void ReverseFunction::_init() {}

void ReverseFunction::_physics_process(double delta)
{
    godot::Array enemy_funcs = get_tree()->get_nodes_in_group("EnemyFunctions");
    if (enemy_funcs.size() > 0)
    {
        godot::Vector2 position = get_global_position();
        godot::Node2D *target = enemy_funcs[0];
        real_t distance = position.distance_to(target->get_position());
        for (int i = 1; i < enemy_funcs.size(); ++i)
        {
            real_t ndistance = position.distance_to(((godot::Node2D *)enemy_funcs[i])->get_position());
            if (ndistance < distance)
            {
                target = enemy_funcs[i];
                distance = ndistance;
            }
        }
        velocity = godot::Vector2(100, 0).rotated((target->get_position() - position).angle());
    }
    set_position(get_position() + velocity * delta);
}

void ReverseFunction::_on_Visibility_screen_exited()
{
    queue_free();
}

void ReverseFunction::_on_ReverseFunction_area_entered(godot::Area2D *area)
{
    area->queue_free();
    queue_free();
}

void ReverseFunction::_register_methods()
{
    godot::register_method("_physics_process", &ReverseFunction::_physics_process);
    godot::register_method("_on_Visibility_screen_exited", &ReverseFunction::_on_Visibility_screen_exited);
    godot::register_method("_on_ReverseFunction_area_entered", &ReverseFunction::_on_ReverseFunction_area_entered);
    godot::register_property("velocity", &ReverseFunction::velocity, godot::Vector2(0, 0));
}
