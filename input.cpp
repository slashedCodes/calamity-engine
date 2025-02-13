#include "input.hpp"
#include "engine.hpp"

bool is_button_pressed(SDL_GameControllerButton button)
{
    if (input_event.type == SDL_CONTROLLERBUTTONDOWN && input_event.cbutton.button == button)
        return true;
    return false;
}

bool is_button_down(SDL_GameControllerButton button)
{
    SDL_GameController *controller = SDL_GameControllerOpen(0);

    if (controller == nullptr)
    {
        std::cerr << "Controller not found!" << std::endl;
        return false;
    }
    if (SDL_GameControllerGetButton(controller, button))
        return true;
    return false;

    SDL_GameControllerClose(controller); // Close the controller when done
}

int get_joystick_axis(SDL_GameControllerAxis axis)
{
    SDL_GameController *controller = SDL_GameControllerOpen(0);
    if (controller == nullptr)
        return false;
    return SDL_GameControllerGetAxis(controller, axis);
}