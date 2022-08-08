#include "game.hpp"

#include "map.hpp"
#include "number.hpp"

void Game::_init()
{
    number_scene = godot::ResourceLoader::get_singleton()->load("res://Number.tscn");
    enemyfunctiona_scene = godot::ResourceLoader::get_singleton()->load("res://EnemyFunctionA.tscn");
    enemyfunctionb_scene = godot::ResourceLoader::get_singleton()->load("res://EnemyFunctionB.tscn");
    random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
    random->randomize();
}

void Game::_ready()
{
    map = get_node<Map>("MapContainer/Map");
    path = godot::Path2D::_new();
    path->set_curve(get_node<godot::Path2D>("MapContainer/Map/NumberPath")->get_curve());
    follow = godot::PathFollow2D::_new();
    path->add_child(follow);
    add_child(path);
    spawnA = map->map_to_world(godot::Vector2((int)map->spawnA[0], (int)map->spawnA[1])) + godot::Vector2(0, 30);
    spawnB = map->map_to_world(godot::Vector2((int)map->spawnB[0], (int)map->spawnB[1])) + godot::Vector2(0, 30);
    number_timer = get_node<godot::Timer>("NumberTimer");
    spawna_timer = get_node<godot::Timer>("SpawnA");
    spawna_label = godot::Label::_new();
    spawna_label->set_align(1);
    spawna_label->set_valign(1);
    spawna_label->set_margin(0, -16);
    spawna_label->set_margin(1, -16);
    spawna_label->set_margin(2, 16);
    spawna_label->set_margin(3, 16);
    spawna_label->add_color_override("font_color", godot::Color(1, 1, 0));
    spawna_label->set_position(spawnA);
    add_child(spawna_label);
    spawnb_timer = get_node<godot::Timer>("SpawnB");
    spawnb_label = godot::Label::_new();
    spawnb_label->set_align(1);
    spawnb_label->set_valign(1);
    spawnb_label->set_margin(0, -16);
    spawnb_label->set_margin(1, -16);
    spawnb_label->set_margin(2, 16);
    spawnb_label->set_margin(3, 16);
    spawnb_label->add_color_override("font_color", godot::Color(1, 1, 0));
    spawnb_label->set_position(spawnB);
    add_child(spawnb_label);
    default_velocity = get_node<godot::Path2D>("/root/Game/MapContainer/Map/NumberPath")->get_curve()->get_baked_length() / 20;
}

void Game::_process()
{
    spawna_label->set_text(godot::String::num_int64(ceilf(spawna_timer->get_time_left())));
    if (!spawnb_started && get_tree()->get_nodes_in_group("FunctionBases").size() > 0)
    {
        spawnb_timer->start();
        spawnb_started = true;
    }
    if (spawnb_started)
        spawnb_label->set_text(godot::String::num_int64(ceilf(spawnb_timer->get_time_left())));
}

void Game::_on_NumberTimer_timeout()
{
    godot::Node *number = number_scene->instance();
    real_t velocity = 300 / pow(20, 0.5) - 300 / pow(score + 20, 0.5) + default_velocity;
    number->set("velocity", random->randf_range(velocity * 0.5, velocity * 1.5));
    number->set("health", random->randi_range(1, score / 2 + 1));
    add_child(number);
    real_t wait = 2 / pow(score + 10, 0.2);
    number_timer->set_wait_time(random->randf_range(wait * 0.5, wait * 2));
}

void Game::_on_SpawnA_timeout()
{
    follow->set_offset(random->randi());
    godot::Node *fa = enemyfunctiona_scene->instance();
    godot::Vector2 position = spawnA + map->get_cell_size() / 2;
    fa->set("position", position);
    godot::Vector2 velocity = godot::Vector2(random->randi_range(30, 80), 0);
    fa->set("velocity", velocity.rotated((follow->get_position() - position).angle()));
    fa->set("radius", floor(40 - 2000.0 / (score + 100)));
    int choice = random->randi_range(0, 6);
    while (choice == 6)
    {
        int second_chance = random->randi_range(0, 99);
        if (second_chance == 66)
            break;
        else
            choice = random->randi_range(0, 6);
    }
    switch (choice)
    {
    case 0:
        fa->set("expr", "x+" + godot::String::num_int64(random->randi_range(1, score / 5 + 1)));
        break;
    case 1:
        fa->set("expr", godot::String::num(random->randf_range(1, score / 100.0 + 1)) + "*x");
        break;
    case 2:
        fa->set("expr", "x^" + godot::String::num(random->randf_range(1, score / 1000.0 + 1)));
        break;
    case 3:
        fa->set("expr", godot::String::num(random->randf_range(1.05, score / 10000.0 + 1.05)) + "^x");
        break;
    case 4:
        fa->set("expr", "x*ln(x)");
        break;
    case 5:
        fa->set("expr", "abs(tan(x))");
        break;
    case 6:
        fa->set("expr", "fac(x)");
        break;
    }
    add_child(fa);
    spawna_timer->set_wait_time(5 + 250.0 / (score + 50));
}

void Game::_on_SpawnB_timeout()
{
    godot::Array bases = get_tree()->get_nodes_in_group("FunctionBases");
    if (bases.size() == 0)
        return;
    godot::Node2D *base = bases[random->randi() % bases.size()];
    godot::Node *fb = enemyfunctionb_scene->instance();
    godot::Vector2 position = spawnB + map->get_cell_size() / 2;
    fb->set("position", position);
    godot::Vector2 velocity = godot::Vector2(random->randi_range(30, 80), 0);
    fb->set("velocity", velocity.rotated((base->get_position() - position).angle()));
    int choice = random->randi_range(0, 5);
    while (choice == 5)
    {
        int second_chance = random->randi_range(0, 10);
        if (second_chance == 7)
            break;
        else
            choice = random->randi_range(0, 5);
    }
    while (choice == 4)
    {
        int second_chance = random->randi_range(0, 100);
        if (second_chance == 44)
            break;
        else
            choice = random->randi_range(0, 4);
    }
    fb->set("mode", choice);
    switch (choice)
    {
    case 0:
        fb->set("value", random->randi_range(1, score / 10 + 1));
        break;
    case 1:
        fb->set("value", random->randf_range(1, score / 200.0 + 1));
        break;
    case 2:
        fb->set("value", random->randf_range(1, score / 5000.0 + 1));
        break;
    case 3:
        fb->set("value", random->randf_range(0, score / 2000.0));
        break;
    }
    add_child(fb);
    spawnb_timer->set_wait_time(5 + 500.0 / (score + 50));
}

void Game::game_over()
{
    lose = true;
    number_timer->stop();
    spawna_timer->stop();
    spawnb_timer->stop();
}

void Game::restart()
{
    coins = 5;
    score = 0;
    lose = false;
    spawnb_started = false;
    spawnb_label->set_text("");
    godot::Array todel = get_tree()->get_nodes_in_group("NonStatic");
    for (int i = 0; i < todel.size(); ++i)
        ((godot::Node *)todel[i])->queue_free();
    number_timer->start();
    spawna_timer->start();
}

void Game::_register_methods()
{
    godot::register_method("_ready", &Game::_ready);
    godot::register_method("_process", &Game::_process);
    godot::register_method("_on_NumberTimer_timeout", &Game::_on_NumberTimer_timeout);
    godot::register_method("_on_SpawnA_timeout", &Game::_on_SpawnA_timeout);
    godot::register_method("_on_SpawnB_timeout", &Game::_on_SpawnB_timeout);
    godot::register_method("game_over", &Game::game_over);
    godot::register_method("restart", &Game::restart);
}
