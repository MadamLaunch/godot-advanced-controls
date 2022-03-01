#ifndef SDLCONTAINER_H
#define SDLCONTAINER_H

#include <Godot.hpp>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;


class SDLContainer {
	static int controller_count;
	static vector<SDL_GameController*> controllers;
	static vector<string> names;
	
	static string compiled_version;
	static string linked_version;
	
	static int node_count;
	static int ran_process;
	static bool pump_events;
public:
	static void add_node() { node_count++; }
	static void remove_node() { node_count--; }
	
	static void init();
	static void scan_for_controllers();
	
	static void process();
	
	static bool invalid_index(int i) { return i < 0 || i >= controller_count; }
	static SDL_GameController* get(int g) { return invalid_index(g) ? NULL : controllers[g]; }
	
	static godot::String name(int g) { return invalid_index(g) ? godot::String() : godot::String(names[g].c_str()); }
	static godot::Array versions();
};

#endif // SDL_CONTAINER_H
