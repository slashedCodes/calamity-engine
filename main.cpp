#include "engine.hpp"

sprite peanits(0, 0, 100, 100, "peanits.png");;
camera cam(0, 0, std::vector<int>{255, 255, 255, 255});
bool dvd_screensaver_mode = false;

// Called before main loop
void start()
{
    //initialize_sprite(&peanits);
}

int count = 1;
int peanitsSpeedX = 1;
int peanitsSpeedY = 1;

// Called before rendering
void update()
{
    peanits.width = get_joystick_axis(SDL_CONTROLLER_AXIS_LEFTX) / 100;

    if (is_button_down(SDL_CONTROLLER_BUTTON_A)) {
        dvd_screensaver_mode = !dvd_screensaver_mode;
    }

    if(dvd_screensaver_mode) {
        count++;
        if(count > 20) {
            count = 1;

            peanits.x += peanitsSpeedX;
            peanits.y += peanitsSpeedY;

            if(peanits.x + peanits.width > 480 || peanits.x < 0) {
                peanitsSpeedX = -peanitsSpeedX;
            }
            if(peanits.y + peanits.height > 272 || peanits.y < 0) {
                peanitsSpeedY = -peanitsSpeedY;
            }
        }
    } else {
        if (is_button_down(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
            peanits.x++;
        }
        if (is_button_down(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
            peanits.x--;
        }
        if (is_button_down(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
            peanits.y++;
        }
        if (is_button_down(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
            peanits.y--;
        }
    }
}

// called after normal update function (for rendering debug shit)
void debug_update() {
    draw_rect(peanits.x, peanits.y, peanits.width, 2, std::vector<int>{0, 255, 0, 255});
    draw_rect(peanits.x, peanits.y, 2, peanits.height, std::vector<int>{0, 255, 0, 255});

    draw_rect(peanits.x, peanits.y, 2, 2, std::vector<int>{255, 0, 0, 255});
}

void input(SDL_Event event) {

}