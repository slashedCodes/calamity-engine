#ifndef INPUT_H
#define INPUT_H

#include "engine.hpp"

bool is_button_down(SDL_GameControllerButton button);
int get_joystick_axis(SDL_GameControllerAxis axis);

#endif