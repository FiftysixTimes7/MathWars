#pragma once

#include <Godot.hpp>
#include <MarginContainer.hpp>
#include <VBoxContainer.hpp>
#include <Label.hpp>
#include <InputEvent.hpp>
#include <OS.hpp>
#include <Dictionary.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <LineEdit.hpp>
#include <HSlider.hpp>

#include "map.hpp"
#include "decreaser.hpp"
#include "functionbase.hpp"
#include "custombutton.hpp"
#include "reversefunctiongenerator.hpp"
#include "splitter.hpp"

class Sidebar : public godot::MarginContainer
{
    GODOT_CLASS(Sidebar, godot::MarginContainer)

    godot::VBoxContainer *infolist;
    godot::Label *title;
    godot::Array items;
    godot::Vector2 focus;
    godot::Dictionary added_objects;
    Map *map;
    godot::Ref<godot::PackedScene> decreaser_scene;
    godot::Ref<godot::PackedScene> functionbase_scene;
    godot::Ref<godot::PackedScene> reversefunctiongenerator_scene;
    godot::Ref<godot::PackedScene> splitter_scene;
    bool response = true;

public:
    void _init();
    void _ready();
    void _input(godot::Variant event);
    void refresh();
    void add_splitter();
    void set_splitter_proportion(real_t value);
    void add_reversefunctiongenerator();
    void add_functionbase();
    void calculate_function_cost();
    void set_function();
    void add_decreaser();
    void upgrade();
    void sell();
    void game_over();

    static void _register_methods();
};
