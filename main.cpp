#define GAME_UPDATE
#define GAME_INPUT
#define GAME_DBG_UPDATE
#define GAME_START
#include "engine.hpp"
#include "input.hpp"
#include "audio.hpp"

#include <math.h>

sprite bird(20, 20, 40, 40, "assets/flappy.png");
sprite ground(0, 260, 480, 100, "assets/ground.png");
camera cam(0, 0, std::vector<int>{100, 100, 255, 255});

sprite sound_sprite = sprite(180, 180, 40, 40, "assets/sound.png");
sound_listener listener(20, 20);
sound_2d sound_emitter("assets/dj_khaled_son.ogg", 200, 200, -1);

float y_velocity = 0;
float gravity = 5;
bool draw_debug_outlines = true;

void start()
{
    sound_emitter.play();
}

// Called before rendering
void update(float delta)
{
    // Gravity
    y_velocity += gravity * delta;
    bird.y += y_velocity * delta * 100;

    // Update listener position
    listener.change_position(bird.x, bird.y);

    if(is_button_down(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
        sound_emitter.x += 1;
        sound_sprite.x += 1;
    }
    if(is_button_down(SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
        sound_emitter.x -= 1;
        sound_sprite.x -= 1;
    }
    if(is_button_down(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
        sound_emitter.y -= 1;
        sound_sprite.y -= 1;
    }
    if(is_button_down(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
        sound_emitter.y += 1;
        sound_sprite.y += 1;
    }
}

void input(SDL_Event event)
{
    switch(event.cbutton.button) {
        case SDL_CONTROLLER_BUTTON_X:
            gravity = 5;
            break;
        case SDL_CONTROLLER_BUTTON_Y:
            draw_debug_outlines = !draw_debug_outlines;
            break;
        case SDL_CONTROLLER_BUTTON_B:
            y_velocity = 0;
            gravity = 0;
            break;
        case SDL_CONTROLLER_BUTTON_A:
            y_velocity = -2;
            break;
    }
}

void draw_sprite_outline(sprite *sprite, std::vector<int> color)
{
    draw_rect(sprite->x, sprite->y, sprite->width, 2, color);
    draw_rect(sprite->x, sprite->y, 2, sprite->height, color);
    draw_rect(sprite->x + sprite->width, sprite->y, 2, sprite->height + 2, color);
    draw_rect(sprite->x, sprite->y + sprite->height, sprite->width + 2, 2, color);
}

void debug_update()
{
    if (draw_debug_outlines)
    {
        for (auto sprite_it : get_sprites())
        {
            draw_sprite_outline(sprite_it, std::vector<int>{255, 0, 0, 255});
        }
    }
}
