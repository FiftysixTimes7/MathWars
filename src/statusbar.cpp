#include "statusbar.hpp"

void Statusbar::_init() {}

void Statusbar::_ready()
{
    status = get_node<godot::Label>("Status");

    connect("game_over", get_node<Game>("/root/Game"), "game_over");
    connect("game_over", get_node<Sidebar>("/root/Game/Sidebar"), "game_over");
}

void Statusbar::_process()
{
    godot::String s("Coins: ");
    s += godot::String::num_int64(coins);
    s += "  |  Score: ";
    s += godot::String::num_int64(score);

    status->set_text(s);
    if (coins < 0)
        emit_signal("game_over");
}

void Statusbar::_register_methods()
{
    godot::register_method("_ready", &Statusbar::_ready);
    godot::register_method("_process", &Statusbar::_process);
    godot::register_signal<Statusbar>("game_over");
}
