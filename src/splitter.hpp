#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <RandomNumberGenerator.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <PathFollow2D.hpp>
#include <Control.hpp>

#include "global.hpp"

class Splitter : public godot::Area2D
{
    GODOT_CLASS(Splitter, godot::Area2D)

    godot::Ref<godot::RandomNumberGenerator> random;
    godot::Ref<godot::PackedScene> number_scene;

public:
    real_t proportion = 1;
    void _init();
    void _ready();
    void _on_Splitter_body_entered(godot::Node2D *body);
    void _on_Splitter_body_exited(godot::Node2D *body);
    void sell();

    static void _register_methods();
};
