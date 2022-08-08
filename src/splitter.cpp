#include "splitter.hpp"

void Splitter::_init()
{
    number_scene = godot::ResourceLoader::get_singleton()->load("res://Number.tscn");
}

void Splitter::_ready()
{
    random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
    random->randomize();
}

void Splitter::_on_Splitter_body_entered(godot::Node2D *body)
{
    if (!(bool)body->get("split"))
    {
        real_t offset = ((godot::PathFollow2D *)body->get("follow"))->get_offset();
        int health = body->get("health");
        int part1 = health / (proportion + 1);
        if (part1 == 0)
            return;
        int part2 = health - part1;
        int velocity = body->get("velocity");
        godot::Node *a = number_scene->instance(), *b = number_scene->instance();
        a->set("offset", offset);
        b->set("offset", offset);
        a->set("velocity", random->randf_range(velocity * 0.5, velocity * 1.5));
        b->set("velocity", random->randf_range(velocity * 0.5, velocity * 1.5));
        a->set("health", part1);
        b->set("health", part2);
        a->set("split", true);
        b->set("split", true);
        body->queue_free();
        get_node<godot::Control>("/root/Game")->call_deferred("add_child", a);
        get_node<godot::Control>("/root/Game")->call_deferred("add_child", b);
    }
}

void Splitter::_on_Splitter_body_exited(godot::Node2D *body)
{
    body->set("split", false);
}

void Splitter::sell()
{
    int grade = get_tree()->get_nodes_in_group("Splitters").size();
    coins += round(pow(5, grade));
    queue_free();
}

void Splitter::_register_methods()
{
    godot::register_method("_ready", &Splitter::_ready);
    godot::register_method("_on_Splitter_body_entered", &Splitter::_on_Splitter_body_entered);
    godot::register_method("_on_Splitter_body_exited", &Splitter::_on_Splitter_body_exited);
    godot::register_method("sell", &Splitter::sell);
    godot::register_property("proportion", &Splitter::proportion, (real_t)1);
}
