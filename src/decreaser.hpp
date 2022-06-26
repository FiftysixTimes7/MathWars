#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>
#include <Label.hpp>

#include "global.hpp"
#include "number.hpp"
#include "functionbase.hpp"

class Decreaser : public godot::Area2D
{
    GODOT_CLASS(Decreaser, godot::Area2D)

    godot::Label *Amount;

public:
    godot::Array functions;
    int grade = 1;
    void _init();
    void _ready();
    void _on_Decreaser_area_entered(godot::Area2D *area);
    void _on_Decreaser_area_exited(godot::Area2D *area);
    void _on_Decreaser_body_entered(godot::Node2D *body);
    void upgrade();
    void sell();

    static void _register_methods();
};
