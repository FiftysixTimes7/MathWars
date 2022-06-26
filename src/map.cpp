#include "map.hpp"

void Map::_init()
{
    godot::Ref<godot::File> f = godot::File::_new();
    godot::Dictionary mapdata = {};
    if (f->file_exists("res://map.json"))
    {
        f->open("res://map.json", godot::File::READ);
        mapdata = godot::JSON::get_singleton()->parse(f->get_as_text())->get_result();
        f->close();
    }
    width = mapdata["width"];
    height = mapdata["height"];
    for (int i = 0; i < width + 2; ++i)
    {
        set_cell(i, 0, 4);
        set_cell(i, height + 1, 4);
    }
    for (int i = 1; i < height + 1; ++i)
    {
        set_cell(0, i, 4);
        set_cell(width + 1, i, 4);
    }
    for (int i = 1; i < width + 1; ++i)
        for (int j = 1; j < height + 1; ++j)
            set_cell(i, j, 0);
    spawnA = mapdata["spawnA"];
    spawnB = mapdata["spawnB"];
    set_cell(spawnA[0], spawnA[1], 2);
    set_cell(spawnB[0], spawnB[1], 2);
    rawpath = mapdata["path"];
    block = mapdata["block"];
    for (int i = 0; i < block.size(); ++i)
    {
        godot::Array b = block[i];
        set_cell(b[0], b[1], 3);
    }
}

void Map::_ready()
{
    path = get_node<godot::Path2D>("NumberPath");
    godot::Ref<godot::Curve2D> curve = path->get_curve();
    for (int i = 0; i < rawpath.size() - 1; ++i)
    {
        godot::Array cur = rawpath[i], nxt = rawpath[i + 1];
        if (cur[0] == nxt[0] && cur[1] < nxt[1])
            for (int j = cur[1]; j < (int)nxt[1] + 1; ++j)
                set_cell(cur[0], j, 5);
        else if (cur[0] == nxt[0] && cur[1] > nxt[1])
            for (int j = cur[1]; j > (int)nxt[1] - 1; --j)
                set_cell(cur[0], j, 5);
        else if (cur[0] < nxt[0])
            for (int j = cur[0]; j < (int)nxt[0] + 1; ++j)
                set_cell(j, cur[1], 5);
        else
            for (int j = cur[0]; j > (int)nxt[0] - 1; --j)
                set_cell(j, cur[1], 5);
        curve->add_point(map_to_world(godot::Vector2(cur[0], cur[1])) + godot::Vector2(get_cell_size().x / 2, get_cell_size().y / 2 + 30));
    }
    godot::Array start = rawpath.front(), end = rawpath.back();
    curve->add_point(map_to_world(godot::Vector2(end[0], end[1])) + godot::Vector2(get_cell_size().x / 2, get_cell_size().y / 2 + 30));
    set_cell(start[0], start[1], 2);
    set_cell(end[0], end[1], 1);
}

void Map::_register_methods()
{
    godot::register_method("_ready", &Map::_ready);
}
