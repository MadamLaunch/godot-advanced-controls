#ifndef SENSORS_H
#define SENSORS_H

#include <Godot.hpp>
#include <Node.hpp>
#include <SDL2/SDL.h>

#include "SDLContainer.hpp"

using namespace godot;


class Sensors : public Node {
	GODOT_CLASS(Sensors, Node)
	
	Vector3 get_sensor(int device, SDL_SensorType type);
public:
	static void _register_methods();
	
	void _init() { SDLContainer::add_node(); }
	void _process(const double p_delta) { SDLContainer::process(); }
	
	Array get_sdl_versions() { return SDLContainer::versions(); }
	String get_name(int device) { return SDLContainer::name(device); }
	
	Vector3 get_accelerometer(int device) { return get_sensor(device, SDL_SENSOR_ACCEL); }
	Vector3 get_gyroscope(int device) { return get_sensor(device, SDL_SENSOR_GYRO); }
};

#endif // SENSORS_H
