#include "number.hpp"

void Number::_init() {}

void Number::_ready()
{
    health_label = get_node<godot::Label>("Health");
    path = godot::Path2D::_new();
    path->set_curve(get_node<godot::Path2D>("/root/Game/MapContainer/Map/NumberPath")->get_curve());
    follow = godot::PathFollow2D::_new();
    follow->set_offset(offset);
    follow->set_loop(false);
    path->add_child(follow);
    add_child(path);
    set_position(follow->get_position());
    health_label->set_text(godot::String::num_int64(health));
    health_label->add_color_override("font_color", godot::Color(1, exp(-0.01 * health), 0));
}

void Number::_process()
{
    if (health <= 0)
    {
        coins += 5;
        score += 1;
        queue_free();
        return;
    }
    health_label->set_text(godot::String::num_int64(health));
    health_label->add_color_override("font_color", godot::Color(1, exp(-0.01 * health), 0));
}

void Number::_physics_process(double delta)
{
    follow->set_offset(follow->get_offset() + delta * velocity);
    set_position(follow->get_position());
    if (follow->get_offset() == path->get_curve()->get_baked_length())
    {
        coins -= health;
        queue_free();
    }
}

void Number::_register_methods()
{
    godot::register_method("_ready", &Number::_ready);
    godot::register_method("_process", &Number::_process);
    godot::register_method("_physics_process", &Number::_physics_process);
    godot::register_property("follow", &Number::follow, (godot::PathFollow2D *)NULL);
    godot::register_property("health", &Number::health, 1);
    godot::register_property("velocity", &Number::velocity, 100);
    godot::register_property("offset", &Number::offset, (real_t)0);
    godot::register_property("split", &Number::split, false);
}
