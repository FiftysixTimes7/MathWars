#include <Godot.hpp>

#include "global.hpp"
#include "map.hpp"
#include "number.hpp"
#include "statusbar.hpp"
#include "sidebar.hpp"
#include "game.hpp"
#include "decreaser.hpp"
#include "functionbase.hpp"
#include "custombutton.hpp"
#include "enemyfunctiona.hpp"
#include "enemyfunctionb.hpp"
#include "reversefunction.hpp"
#include "reversefunctiongenerator.hpp"
#include "splitter.hpp"
#include "startscreen.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o)
{
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o)
{
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle)
{
	godot::Godot::nativescript_init(handle);

	godot::register_class<Map>();
	godot::register_class<Number>();
	godot::register_class<Statusbar>();
	godot::register_class<Sidebar>();
	godot::register_class<Game>();
	godot::register_class<Decreaser>();
	godot::register_class<FunctionBase>();
	godot::register_class<CustomButton>();
	godot::register_class<EnemyFunctionA>();
	godot::register_class<EnemyFunctionB>();
	godot::register_class<ReverseFunction>();
	godot::register_class<ReverseFunctionGenerator>();
	godot::register_class<Splitter>();
	godot::register_class<StartScreen>();
}
