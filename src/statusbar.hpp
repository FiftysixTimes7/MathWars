#pragma once

#include <Godot.hpp>
#include <MarginContainer.hpp>
#include <Label.hpp>

#include "global.hpp"
#include "game.hpp"
#include "sidebar.hpp"

class Statusbar : public godot::MarginContainer
{
    GODOT_CLASS(Statusbar, godot::MarginContainer)

    godot::Label *status;

public:
    void _init();
    void _ready();
    void _process();

    static void _register_methods();
};
