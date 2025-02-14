#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include "engine.hpp"

class sound {
    public:
        sound(std::string path, int loops);
        void play();
        void stop();
        void pause();
        void resume();
        void ensure_sound_loaded();
        void change_volume(int volume);

        int channel;
        int loops;
        int volume;
        std::string path;
        Mix_Chunk* file;
};

class sound_2d {
    public:
        sound_2d(std::string path, float x, float y, int loops);
        void play();
        void stop();
        void pause();
        void resume();
        void ensure_sound_loaded();
        void change_volume(int volume);

        std::string path;
        Mix_Chunk* file;
        int channel;
        int loops;
        int volume;
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