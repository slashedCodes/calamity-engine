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

class camera {
    public:
        camera(int x, int y, std::vector<int> background_color);
        int x;
        int y;
        std::vector<int> background_color{255, 255, 255, 255};
};

class sprite {
    public:
        sprite(int x, int y, int width, int height, std::string texture_path);
        void ensure_texture_loaded();
        int x;
        int y;
        int width;
        int height;
        std::string texture_path;
        SDL_Texture* texture;
};

extern camera* global_camera;
extern std::list<sprite*> sprites;
extern std::list<SDL_Rect> rects;
extern std::list<std::string> loaded_textures;
extern SDL_Renderer* renderer;

SDL_Texture* load_texture(std::string path);
void update_rects();
void draw_rects();
bool is_button_down(SDL_GameControllerButton button);
int get_joystick_axis(SDL_GameControllerAxis axis);

// debug functions
void draw_rect(int x, int y, int width, int height, std::vector<int> color);

#endif // ENGINE_H