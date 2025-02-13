#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include "engine.hpp"

class sound {
    public:
        sound(std::string path);
        void play();
        void stop();
        void pause();
        void resume();

        float volume;
        std::string path;
        Mix_Music* file;
};

class sound_2d {
    public:
        sound_2d(std::string path, float x, float y);
        void play();
        void stop();
        void pause();
        void resume();

        std::string path;
        Mix_Music* file;
        float volume;
        float x;
        float y;
};

class sound_listener {
    public:
        sound_listener(float x, float y);
        void change_position(float x, float y);

        float x;
        float y;
};

extern sound_listener* global_sound_listener;

std::list<sound_2d*> &get_sounds_2d();

#endif