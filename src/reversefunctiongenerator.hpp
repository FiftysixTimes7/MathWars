#pragma once

#include <Godot.hpp>
#include <ColorRect.hpp>
#include <Timer.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <SceneTree.hpp>
#include <Node2D.hpp>

#include "global.hpp"

class ReverseFunctionGenerator : public godot::ColorRect
{
    GODOT_CLASS(ReverseFunctionGenerator, godot::ColorRect)

    godot::Timer *cooldown;
    godot::Ref<godot::PackedScene> reversefunction_scene;

public:
    int grade = 1;
    void _init();
    void _ready();
    void _process();
    void upgrade();
    void sell();

    static void _register_methods();
};
