#include "reversefunctiongenerator.hpp"

void ReverseFunctionGenerator::_init()
{
    reversefunction_scene = godot::ResourceLoader::get_singleton()->load("res://ReverseFunction.tscn");
}

void ReverseFunctionGenerator::_ready()
{
    cooldown = get_node<godot::Timer>("CoolDown");
}

void ReverseFunctionGenerator::_process()
{
    set_frame_color(godot::Color(1, 1, 0, 0.5 * cooldown->get_time_left() / cooldown->get_wait_time()));
    if (cooldown->get_time_left() == 0 && get_tree()->get_nodes_in_group("EnemyFunctions").size() > 0)
    {
        godot::Node *rf = reversefunction_scene->instance();
        ((godot::Node2D *)rf)->set_position(godot::Vector2(15, 15));
        add_child(rf);
        cooldown->start();
    }
}

void ReverseFunctionGenerator::upgrade()
{
    int cost = round(pow(10, grade));
    grade += 1;
    coins -= cost;
    cooldown->set_wait_time(10.0 / grade);
}

void ReverseFunctionGenerator::sell()
{
    coins += 9 + (round(pow(10, grade)) - 1) / 9;
    queue_free();
}

void ReverseFunctionGenerator::_register_methods()
{
    godot::register_method("_ready", &ReverseFunctionGenerator::_ready);
    godot::register_method("_process", &ReverseFunctionGenerator::_process);
    godot::register_method("upgrade", &ReverseFunctionGenerator::upgrade);
    godot::register_method("sell", &ReverseFunctionGenerator::sell);
    godot::register_property("grade", &ReverseFunctionGenerator::grade, 1);
}
