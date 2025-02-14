#include "engine.hpp"
#include "main.hpp"
#include "audio.hpp"
#include <SDL2/SDL_mixer.h>

// These two functions are dark magic. do not change or question them.
std::list<sprite *> &get_sprites()
{
    static std::list<sprite *> sprites;
    return sprites;
}

std::list<SDL_Rect> &get_rects()
{
    static std::list<SDL_Rect> rects;
    return rects;
}

camera *global_camera = nullptr;
std::list<std::string> loaded_textures;
SDL_Renderer *renderer = nullptr;
SDL_Event input_event;

camera::camera(float x, float y, std::vector<int> background_color)
{
    this->x = x;
    this->y = y;
    this->background_color = background_color;
    global_camera = this;
}

sprite::sprite(float x, float y, int width, int height, std::string texture_path)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->texture_path = texture_path;
    this->texture = nullptr;

    get_sprites().push_back(this);

    // Create a corresponding SDL_Rect and add it to the rects list
    SDL_Rect sprite_rect = {x, y, width, height};
    get_rects().push_back(sprite_rect);
}

void sprite::ensure_texture_loaded()
{
    if (this->texture == nullptr)
    {
        this->texture = load_texture(this->texture_path);
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);

    SDL_Window *window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        480,
        272,
        0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    start();

    int running = 1;
    float delta = 0.0;
    int old_time = 0;
    int new_time = 0;
    while (running)
    {
        // Delta time calculation
        new_time = SDL_GetTicks();
        delta = (new_time - old_time) / 1000.0;

        // Input
        SDL_PollEvent(&input_event);
        switch (input_event.type)
        {
        case SDL_QUIT:
            // End the loop if the programs is being closed
            running = 0;
            break;
        case SDL_CONTROLLERDEVICEADDED:
            // Connect a controller when it is connected
            SDL_GameControllerOpen(input_event.cdevice.which);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            input(input_event);
            break;
        }

        // Clear the screen
        SDL_RenderClear(renderer);
        update(delta);

        // Draw shit
        update_rects();
        draw_rects();

        // debug render
        debug_update();

        // Draw everything on a white background
        SDL_SetRenderDrawColor(renderer, global_camera->background_color[0], global_camera->background_color[1], global_camera->background_color[2], global_camera->background_color[3]);
        SDL_RenderPresent(renderer);

        old_time = new_time;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

SDL_Texture *load_texture(std::string path)
{
    std::cout << "Loading texture: " << path << std::endl;
    SDL_Surface *pixels = IMG_Load(path.c_str());
    if (pixels == nullptr)
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, pixels);
    if (texture == nullptr)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(pixels);
    loaded_textures.push_back(path);
    return texture;
}

void update_rects()
{
    auto sprite_it = get_sprites().begin();
    auto rect_it = get_rects().begin();
    while (sprite_it != get_sprites().end() && rect_it != get_rects().end())
    {
        (*rect_it).w = (*sprite_it)->width;
        (*rect_it).h = (*sprite_it)->height;
        (*rect_it).x = (*sprite_it)->x - global_camera->x; // Adjust for camera position
        (*rect_it).y = (*sprite_it)->y - global_camera->y; // Adjust for camera position
        ++sprite_it;
        ++rect_it;
    }
}

void draw_rects()
{
    auto sprite_it = get_sprites().begin();
    auto rect_it = get_rects().begin();
    while (sprite_it != get_sprites().end() && rect_it != get_rects().end())
    {
        (*sprite_it)->ensure_texture_loaded(); // ensure the texture is loaded
        SDL_RenderCopy(renderer, (*sprite_it)->texture, NULL, &(*rect_it));
        ++sprite_it;
        ++rect_it;
    }
}

// debug draw

void draw_rect(float x, float y, int width, int height, std::vector<int> color)
{
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderFillRect(renderer, &rect);
}