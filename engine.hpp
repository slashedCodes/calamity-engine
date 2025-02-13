#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

class camera
{
public:
    camera(float x, float y, std::vector<int> background_color);
    float x;
    float y;
    std::vector<int> background_color{255, 255, 255, 255};
};

class sprite
{
public:
    sprite(float x, float y, int width, int height, std::string texture_path);
    void ensure_texture_loaded();
    float x;
    float y;
    int width;
    int height;
    std::string texture_path;
    SDL_Texture *texture;
};

extern camera *global_camera;
extern std::list<std::string> loaded_textures;
extern SDL_Renderer *renderer;
extern SDL_Event input_event;

std::list<sprite *> &get_sprites();
std::list<SDL_Rect> &get_rects();
SDL_Texture *load_texture(std::string path);
void update_rects();
void draw_rects();

// debug functions
void draw_rect(float x, float y, int width, int height, std::vector<int> color);

#endif // ENGINE_H