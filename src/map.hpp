#pragma once

#include <Godot.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <TileMap.hpp>
#include <Path2D.hpp>
#include <Curve2D.hpp>

class Map : public godot::TileMap
{
    GODOT_CLASS(Map, godot::TileMap)

    int width, height;
    godot::Path2D *path;

public:
    godot::Array spawnA, spawnB, block, rawpath;
    void _init();
    void _ready();

    static void _register_methods();
};
