#include "Sensors.hpp"


void Sensors::_register_methods() {
	register_method("_process", &Sensors::_process);
	
	register_method("get_sdl_versions", &Sensors::get_sdl_versions);
	register_method("get_name", &Sensors::get_name);
	
	register_method("get_accelerometer", &Sensors::get_accelerometer);
	register_method("get_gyroscope", &Sensors::get_gyroscope);
}


Vector3 Sensors::get_sensor(int device, SDL_SensorType type) {
	SDL_GameController* gc = SDLContainer::get(device);
	if (gc == NULL) return Vector3();
	
	// Return blank if the specified sensor is missing/disabled.
	if (!SDL_GameControllerHasSensor(gc, type)
			|| !SDL_GameControllerIsSensorEnabled(gc, type))
		return Vector3();
	
	// Pull the sensor data.
	float a[3];
	SDL_GameControllerGetSensorData(gc, type, a, 3);
	
	return Vector3(a[0], a[1], a[2]);
}
