#pragma once

#include <Godot.hpp>
#include <Label.hpp>
#include <SceneTree.hpp>

class StartScreen : public godot::Control
{
    GODOT_CLASS(StartScreen, godot::Control)

    real_t time_passed = 0;
    godot::Label *title;

public:
    void _init();
    void _ready();
    void _process(float delta);
    void _on_Start_pressed();

    static void _register_methods();
};
