#include "startscreen.hpp"

void StartScreen::_init() {}

void StartScreen::_ready()
{
    title = get_node<godot::Label>("TitleContainer/Title");
}

void StartScreen::_process(float delta)
{
    time_passed += delta;
    godot::Vector2 new_position = godot::Vector2(-400 + 10.0 * sin(time_passed * 2.0), 10.0 * cos(time_passed * 1.5));
    title->set_position(new_position);
}

void StartScreen::_on_Start_pressed()
{
    get_tree()->change_scene("res://Game.tscn");
}

void StartScreen::_register_methods()
{
    register_method("_ready", &StartScreen::_ready);
    register_method("_process", &StartScreen::_process);
    register_method("_on_Start_pressed", &StartScreen::_on_Start_pressed);
}
