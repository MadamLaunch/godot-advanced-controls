#include "Touchpads.hpp"


void Touchpads::_register_methods() {
	register_method("_process", &Touchpads::_process);
	
	register_method("get_sdl_versions", &Touchpads::get_sdl_versions);
	register_method("get_name", &Touchpads::get_name);
	
	register_method("get_touches", &Touchpads::get_touches);
	register_method("get_average", &Touchpads::get_average);
}


Array Touchpads::get_touches(const int device) {
	Array coordinates;
	
	SDL_GameController* gc = SDLContainer::get(device);
	if (gc == NULL) coordinates;
	
	int pads = SDL_GameControllerGetNumTouchpads(gc);
	for (int p = 0; p < pads; p++) {
		int fingers = SDL_GameControllerGetNumTouchpadFingers(gc, p);
		for (int f = 0; f < fingers; f++) {
			Uint8 s;
			float x;
			float y;
			float z;
			SDL_GameControllerGetTouchpadFinger(gc, p, f, &s, &x, &y, &z);
			if (s) coordinates.push_back(Vector3(x, y, z));
		}
	}
	
	return coordinates;
}


Vector3 Touchpads::get_average(const int device) {
	float x = 0;
	float y = 0;
	float z = 0;
	float count = 0;
	
	SDL_GameController* gc = SDLContainer::get(device);
	if (gc == NULL) return Vector3();
	
	int pads = SDL_GameControllerGetNumTouchpads(gc);
	for (int p = 0; p < pads; p++) {
		int fingers = SDL_GameControllerGetNumTouchpadFingers(gc, p);
		for (int f = 0; f < fingers; f++) {
			Uint8 s;
			float _x;
			float _y;
			float _z;
			SDL_GameControllerGetTouchpadFinger(gc, p, f, &s, &_x, &_y, &_z);
			if (s) {
				x += _x;
				y += _y;
				z += _z;
				count++;
			}
		}
	}
	
	if (count > 1) {
		x /= count;
		y /= count;
		z /= count;
	}
	
	return Vector3(x, y, z);
}
