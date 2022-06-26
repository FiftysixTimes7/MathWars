#include "decreaser.hpp"

void Decreaser::_init() {}

void Decreaser::_ready()
{
    Amount = get_node<godot::Label>("Amount");
    Amount->set_text("-" + godot::String::num_int64(grade));
}

void Decreaser::_on_Decreaser_area_entered(godot::Area2D *area)
{
    functions.append(area);
}

void Decreaser::_on_Decreaser_area_exited(godot::Area2D *area)
{
    functions.erase(area);
}

void Decreaser::_on_Decreaser_body_entered(godot::Node2D *body)
{
    real_t health = body->get("health");
    for (int i = 0; i < functions.size(); ++i)
    {
        FunctionBase *function = functions[i];
        health = function->calculate(health);
    }
    health -= grade;
    body->set("health", health);
}

void Decreaser::upgrade()
{
    int cost = pow(2, grade);
    grade += 1;
    coins -= cost;
    Amount->set_text("-" + godot::String::num_int64(grade));
}

void Decreaser::sell()
{
    coins += pow(2, grade) - 1;
    queue_free();
}

void Decreaser::_register_methods()
{
    godot::register_method("_ready", &Decreaser::_ready);
    godot::register_method("_on_Decreaser_area_entered", &Decreaser::_on_Decreaser_area_entered);
    godot::register_method("_on_Decreaser_area_exited", &Decreaser::_on_Decreaser_area_exited);
    godot::register_method("_on_Decreaser_body_entered", &Decreaser::_on_Decreaser_body_entered);
    godot::register_method("upgrade", &Decreaser::upgrade);
    godot::register_method("sell", &Decreaser::sell);
    godot::register_property("grade", &Decreaser::grade, 1);
}
