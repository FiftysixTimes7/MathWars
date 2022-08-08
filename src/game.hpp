#pragma once

#include <Godot.hpp>
#include <Control.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <Timer.hpp>
#include <InputEvent.hpp>
#include <Label.hpp>
#include <RandomNumberGenerator.hpp>
#include <Path2D.hpp>
#include <PathFollow2D.hpp>
#include <RigidBody2D.hpp>
#include <SceneTree.hpp>

#include "global.hpp"
#include "map.hpp"

class Game : public godot::Control
{
    GODOT_CLASS(Game, godot::Control)

    Map *map;
    godot::Path2D *path;
    godot::PathFollow2D *follow;
    godot::Timer *number_timer, *spawna_timer, *spawnb_timer;
    godot::Label *spawna_label, *spawnb_label;
    godot::Vector2 spawnA, spawnB;
    godot::Ref<godot::RandomNumberGenerator> random;
    real_t default_velocity;
    godot::Ref<godot::PackedScene> number_scene, enemyfunctiona_scene, enemyfunctionb_scene;
    bool spawnb_started = false;

public:
    void _init();
    void _ready();
    void _process();
    void _on_NumberTimer_timeout();
    void _on_SpawnA_timeout();
    void _on_SpawnB_timeout();
    void game_over();
    void restart();

    static void _register_methods();
};
