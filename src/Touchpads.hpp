#ifndef TOUCHPADS_H
#define TOUCHPADS_H

#include <Godot.hpp>
#include <Node.hpp>
#include <SDL2/SDL.h>

#include "SDLContainer.hpp"

using namespace godot;


class Touchpads : public Node {
	GODOT_CLASS(Touchpads, Node)
public:
	static void _register_methods();
	
	void _init() { SDLContainer::add_node(); }
	void _process(const double p_delta) { SDLContainer::process(); }
	
	Array get_sdl_versions() { return SDLContainer::versions(); }
	String get_name(int device) { return SDLContainer::name(device); }
	
	Array get_touches(const int device);
	Vector3 get_average(const int device);
};

#endif // TOUCHPADS_H
