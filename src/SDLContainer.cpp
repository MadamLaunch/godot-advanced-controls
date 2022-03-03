#include "SDLContainer.hpp"


int SDLContainer::controller_count = 0;
vector<SDL_GameController*> SDLContainer::controllers = vector<SDL_GameController*>();
vector<string> SDLContainer::names = vector<string>();

string SDLContainer::compiled_version = string();
string SDLContainer::linked_version = string();

int SDLContainer::node_count = 0;
int SDLContainer::ran_process = 0;
bool SDLContainer::pump_events = true;


void SDLContainer::init() {
	SDL_Init(SDL_INIT_GAMECONTROLLER|SDL_INIT_SENSOR);
	
	SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE, "1");
	SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5, "1");
	SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_STEAM, "1");
	
	SDL_version compiled;
	SDL_VERSION(&compiled);
	compiled_version
		= to_string(compiled.major)
		+ "."
		+ to_string(compiled.minor)
		+ "."
		+ to_string(compiled.patch);
	
	SDL_version linked;
	SDL_GetVersion(&linked);
	linked_version
		= to_string(linked.major)
		+ "."
		+ to_string(linked.minor)
		+ "."
		+ to_string(linked.patch);
}


void SDLContainer::scan_for_controllers() {
	for(vector<SDL_GameController*>::iterator i = controllers.begin(); i != controllers.end(); i++) {
		SDL_GameControllerClose(*i);
	}
	controllers.clear();
	names.clear();
	
	controller_count = SDL_NumJoysticks();
	for(int j = 0; j < controller_count; j++) {
		SDL_GameController* gc = SDL_GameControllerOpen(j);
		
		SDL_GameControllerSetSensorEnabled(gc, SDL_SENSOR_ACCEL, SDL_TRUE);
		SDL_GameControllerSetSensorEnabled(gc, SDL_SENSOR_GYRO, SDL_TRUE);
		
		controllers.push_back(gc);
		names.push_back(string(SDL_GameControllerName(gc)));
	}
}


void SDLContainer::process() {
	if (pump_events) {
		SDL_PumpEvents();
		pump_events = false;
	}
	
	if (++ran_process >= node_count) {
		pump_events = true;
		ran_process = 0;
	}
}


godot::Array SDLContainer::versions() {
	godot::Array a;
	a.push_back(godot::String(compiled_version.c_str()));
	a.push_back(godot::String(linked_version.c_str()));
	
	return a;
}
