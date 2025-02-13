#ifndef MAIN_H
#define MAIN_H
#include "engine.hpp"
#ifndef GAME_START
inline void start() {}
#else
void start();
#endif
#ifndef GAME_UPDATE
inline void update(float delta) {}
#else
void update(float delta);
#endif
#ifndef GAME_INPUT
inline void input(SDL_Event event) {}
#else
void input(SDL_Event event);
#endif
#ifndef GAME_DBG_UPDATE
inline void debug_update() {}
#else
void debug_update();
#endif
#endif