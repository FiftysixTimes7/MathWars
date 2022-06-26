#include "custombutton.hpp"

void CustomButton::_init() {}

void CustomButton::_ready() {}

void CustomButton::_process(double delta)
{
    if (cost >= 0)
    {
        if (cost == 1)
            set_tooltip("-1 Coin");
        else
            set_tooltip("-" + godot::String::num_int64(cost) + " Coins");
        if (cost > coins)
            set_disabled(true);
        else
            set_disabled(false);
    }
    else
    {
        if (cost == -1)
            set_tooltip("+1 Coin");
        else
            set_tooltip("+" + godot::String::num_int64(-cost) + " Coins");
        set_disabled(false);
    }
}

void CustomButton::_register_methods()
{
    godot::register_method("_ready", &CustomButton::_ready);
    godot::register_method("_process", &CustomButton::_process);
    godot::register_property("cost", &CustomButton::cost, 0);
}
