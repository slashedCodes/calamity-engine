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
sound_listener listener(20, 20);
sound_2d dj_khaled_son("assets/dj_khaled_son.ogg", 100, 100);

float y_velocity = 0;
float gravity = 5;
bool draw_debug_outlines = true;

void start()
{
    dj_khaled_son.play();
}

// Called before rendering
void update(float delta)
{
    // Gravity
    y_velocity += gravity * delta;
    bird.y += y_velocity * delta * 100;

    // Update listener position
    listener.change_position(bird.x, bird.y);
}

void input(SDL_Event event)
{
    if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
    {
        y_velocity = -2;
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
