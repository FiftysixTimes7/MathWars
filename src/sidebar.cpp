#include "sidebar.hpp"

void Sidebar::_init()
{
    decreaser_scene = godot::ResourceLoader::get_singleton()->load("res://Decreaser.tscn");
    functionbase_scene = godot::ResourceLoader::get_singleton()->load("res://FunctionBase.tscn");
    reversefunctiongenerator_scene = godot::ResourceLoader::get_singleton()->load("res://ReverseFunctionGenerator.tscn");
    splitter_scene = godot::ResourceLoader::get_singleton()->load("res://Splitter.tscn");
}

void Sidebar::_ready()
{
    infolist = get_node<godot::VBoxContainer>("InfoList");
    title = get_node<godot::Label>("InfoList/Title");
    map = get_node<Map>("/root/Game/MapContainer/Map");
}

void Sidebar::_input(godot::Variant event)
{
    godot::Ref<godot::InputEvent> e = event;
    if (e->is_class("InputEventMouseButton") && e->is_pressed() && response)
    {
        godot::Vector2 pos = e->get("position");
        if (pos.x > godot::OS::get_singleton()->get_window_size().x + get_margin(0))
            return;
        if (added_objects.has(focus) && ((godot::Node *)added_objects[focus])->get_name().find("FunctionBase") != -1)
            ((FunctionBase *)added_objects[focus])->set_range_visible(false);
        focus = map->world_to_map(godot::Vector2(pos.x, pos.y - 30));
        refresh();
    }
}

void Sidebar::refresh()
{
    for (int i = 0; i < items.size(); ++i)
        ((godot::Node *)items[i])->queue_free();
    items.clear();
    switch (map->get_cell(focus.x, focus.y))
    {
    case 0:
    {
        if (!added_objects.has(focus))
        {
            title->set_text("Regular Block");
            CustomButton *b1 = CustomButton::_new();
            b1->set_text("Add a Function Base");
            b1->set("cost", 5);
            b1->connect("pressed", this, "add_functionbase");
            items.append(b1);
            godot::Control *b2container = godot::Control::_new();
            b2container->set_margin(2, 250);
            b2container->set_margin(3, 53);
            CustomButton *b2 = CustomButton::_new();
            godot::Label *b2l = godot::Label::_new();
            b2l->set_align(1);
            b2l->set_valign(1);
            b2l->set_margin(2, 250);
            b2l->set_margin(3, 53);
            b2l->set_text("Add a Reverse\nFunction Generator");
            b2->add_child(b2l);
            b2->set("cost", 10);
            b2->connect("pressed", this, "add_reversefunctiongenerator");
            b2->set_margin(2, 250);
            b2->set_margin(3, 53);
            b2container->add_child(b2);
            items.append(b2container);
        }
        else if (((godot::Node *)added_objects[focus])->get_name().find("FunctionBase") != -1)
        {
            title->set_text("Function Base");
            ((FunctionBase *)added_objects[focus])->set_range_visible(true);
            godot::Label *func = godot::Label::_new();
            func->set_align(1);
            func->set_valign(1);
            godot::String cur_expr = ((godot::Node *)added_objects[focus])->get("cur_expr");
            func->set_text(cur_expr);
            items.append(func);
            godot::LineEdit *edit = godot::LineEdit::_new();
            edit->set_placeholder(cur_expr);
            edit->connect("text_changed", this, "calculate_function_cost");
            items.append(edit);
            CustomButton *b0 = CustomButton::_new();
            b0->set_text("Set Function");
            b0->connect("pressed", this, "set_function");
            items.append(b0);
            CustomButton *b1 = CustomButton::_new();
            b1->set_text("Upgrade (+Range)");
            int grade = ((godot::Node *)added_objects[focus])->get("grade");
            b1->set("cost", round(pow(200, grade)));
            b1->connect("pressed", this, "upgrade");
            items.append(b1);
            CustomButton *b2 = CustomButton::_new();
            b2->set_text("Sell");
            b2->set("cost", -(int)((godot::Node *)added_objects[focus])->call("get_value"));
            b2->connect("pressed", this, "sell");
            items.append(b2);
        }
        else if (((godot::Node *)added_objects[focus])->get_name().find("ReverseFunctionGenerator") != -1)
        {
            title->set_text("Reverse Function\nGenerator");
            ReverseFunctionGenerator *d = added_objects[focus];
            CustomButton *b1 = CustomButton::_new();
            b1->set_text("Upgrade (-CoolDown)");
            int grade = d->get("grade");
            b1->set("cost", pow(10, grade));
            b1->connect("pressed", this, "upgrade");
            items.append(b1);
            CustomButton *b2 = CustomButton::_new();
            b2->set_text("Sell");
            b2->set("cost", -(9 + (round(pow(10, grade)) - 1) / 9));
            b2->connect("pressed", this, "sell");
            items.append(b2);
        }
        break;
    }
    case 1:
        title->set_text("Base");
        break;
    case 2:
    {
        if (focus.x == (int)map->spawnA[0] && focus.y == (int)map->spawnA[1])
            title->set_text("Function Generator\n(Enemy A)\nTargeting\nNumbers");
        else if (focus.x == (int)map->spawnB[0] && focus.y == (int)map->spawnB[1])
            title->set_text("Function Generator\n(Enemy B)\nTargeting\nFunction Bases");
        else
            title->set_text("Number Source");
        break;
    }
    case 3:
        title->set_text("Blocked");
        break;
    case 5:
    {
        if (!added_objects.has(focus))
        {
            title->set_text("Regular Path");
            CustomButton *b1 = CustomButton::_new();
            b1->set_text("Add a Decreaser");
            b1->set("cost", 1);
            b1->connect("pressed", this, "add_decreaser");
            items.append(b1);
            CustomButton *b2 = CustomButton::_new();
            b2->set_text("Add a Splitter");
            b2->set("cost", 10);
            b2->connect("pressed", this, "add_splitter");
            items.append(b2);
        }
        else if (((godot::Node *)added_objects[focus])->get_name().find("Decreaser") != -1)
        {
            title->set_text("Decreaser");
            Decreaser *d = added_objects[focus];
            for (int i = 0; i < d->functions.size(); ++i)
            {
                FunctionBase *f = d->functions[i];
                godot::Label *l = godot::Label::_new();
                l->set_align(1);
                l->set_valign(1);
                l->set_text(f->cur_expr);
                items.append(l);
            }
            CustomButton *b1 = CustomButton::_new();
            b1->set_text("Upgrade (+Amount)");
            int grade = d->get("grade");
            b1->set("cost", pow(2, grade));
            b1->connect("pressed", this, "upgrade");
            items.append(b1);
            CustomButton *b2 = CustomButton::_new();
            b2->set_text("Sell");
            b2->set("cost", -(pow(2, grade) - 1));
            b2->connect("pressed", this, "sell");
            items.append(b2);
        }
        else if (((godot::Node *)added_objects[focus])->get_name().find("Splitter") != -1)
        {
            title->set_text("Splitter");
            Splitter *d = added_objects[focus];
            godot::Label *l = godot::Label::_new();
            l->set_align(1);
            l->set_valign(1);
            l->set_text("1:" + godot::String::num(d->get("proportion")));
            items.append(l);
            godot::HSlider *s = godot::HSlider::_new();
            s->set_ticks(3);
            s->set_min(-1);
            s->set_max(1);
            s->set_step(0.01);
            s->connect("value_changed", this, "set_splitter_proportion");
            items.append(s);
            CustomButton *b = CustomButton::_new();
            b->set_text("Sell");
            b->set("cost", -10);
            b->connect("pressed", this, "sell");
            items.append(b);
        }
        break;
    }
    default:
        title->set_text("Click on a block to\nshow its info");
    }
    for (int i = 0; i < items.size(); ++i)
        infolist->add_child(items[i]);
}

void Sidebar::add_splitter()
{
    godot::Node *l = splitter_scene->instance();
    ((godot::Node2D *)l)->set_position(map->map_to_world(focus) + map->get_cell_size() / 2);
    map->add_child(l);
    added_objects[focus] = l;
    coins -= 10;
    refresh();
}

void Sidebar::set_splitter_proportion(real_t value)
{
    Splitter *splitter = added_objects[focus];
    splitter->set("proportion", pow(10, value));
    godot::Label *info = items[0];
    info->set_text("1:" + godot::String::num(splitter->get("proportion")));
}

void Sidebar::add_reversefunctiongenerator()
{
    godot::Node *l = reversefunctiongenerator_scene->instance();
    ((godot::Control *)l)->set_position(map->map_to_world(focus) + godot::Vector2(1, 1));
    map->add_child(l);
    added_objects[focus] = l;
    coins -= 10;
    refresh();
}

void Sidebar::add_functionbase()
{
    godot::Node *l = functionbase_scene->instance();
    ((godot::Node2D *)l)->set_position(map->map_to_world(focus) + map->get_cell_size() / 2);
    added_objects[focus] = l;
    map->add_child(l);
    coins -= 5;
    refresh();
}

void Sidebar::calculate_function_cost()
{
    godot::String cur_expr = ((godot::Node *)added_objects[focus])->get("cur_expr");
    godot::String text = ((godot::LineEdit *)items[1])->get_text();
    CustomButton *b0 = items[2];
    b0->set("cost", evaluate(text.utf8().get_data()) - evaluate(cur_expr.utf8().get_data()));
}

void Sidebar::set_function()
{
    FunctionBase *base = added_objects[focus];
    godot::String cur_expr = base->get("cur_expr");
    godot::String text = ((godot::LineEdit *)items[1])->get_text();
    coins -= evaluate(text.utf8().get_data()) - evaluate(cur_expr.utf8().get_data());
    base->set_function(text);
    refresh();
}

void Sidebar::add_decreaser()
{
    godot::Node *l = decreaser_scene->instance();
    ((godot::Node2D *)l)->set_position(map->map_to_world(focus) + map->get_cell_size() / 2);
    added_objects[focus] = l;
    map->add_child(l);
    coins -= 1;
    refresh();
}

void Sidebar::upgrade()
{
    ((godot::Node *)added_objects[focus])->call("upgrade");
    refresh();
}

void Sidebar::sell()
{
    ((godot::Node *)added_objects[focus])->call("sell");
    added_objects.erase(focus);
    refresh();
}

void Sidebar::game_over()
{
    title->set_text("Game Over!");
    for (int i = 0; i < items.size(); ++i)
        ((godot::Node *)items[i])->queue_free();
    items.clear();
    response = false;
}

void Sidebar::_register_methods()
{
    godot::register_method("_ready", &Sidebar::_ready);
    godot::register_method("_input", &Sidebar::_input);
    godot::register_method("refresh", &Sidebar::refresh);
    godot::register_method("add_splitter", &Sidebar::add_splitter);
    godot::register_method("set_splitter_proportion", &Sidebar::set_splitter_proportion);
    godot::register_method("add_reversefunctiongenerator", &Sidebar::add_reversefunctiongenerator);
    godot::register_method("add_functionbase", &Sidebar::add_functionbase);
    godot::register_method("calculate_function_cost", &Sidebar::calculate_function_cost);
    godot::register_method("set_function", &Sidebar::set_function);
    godot::register_method("add_decreaser", &Sidebar::add_decreaser);
    godot::register_method("upgrade", &Sidebar::upgrade);
    godot::register_method("sell", &Sidebar::sell);
    godot::register_method("game_over", &Sidebar::game_over);
}
