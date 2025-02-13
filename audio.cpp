#include "audio.hpp"
#include "engine.hpp"

// Sound listener

sound_listener* global_sound_listener = nullptr;

sound_listener::sound_listener(float x, float y)
{
    this->x = x;
    this->y = y;
    if(sound_listener != nullptr) {
        std::cerr << "Warning: Multiple sound listeners detected. Only one sound listener is supported." << std::endl;
        return;
    }

    global_sound_listener = this;
}

void sound_listener::change_position(float x, float y)
{
    this->x = x;
    this->y = y;

    // Calculate volume for all 2D sounds
    for(sound_2d* sound_it : get_2d_sounds())
    {
        float distance = sqrt(pow(sound_it->x - this->x, 2) + pow(sound_it->y - this->y, 2));
        float volume = 1 - distance / 100;
        if(volume < 0) {
            volume = 0;
        }
        sound_it->volume = volume;
    }
}

// 1D Sound emitter

sound::sound(std::string path)
{
    this->path = path;
    this->file = Mix_LoadMUS(path.c_str());

    if(!this->file) {
        std::cerr << "Mix_LoadMUS Error loading audio file: " << this->path << std::endl;
    }
}

void sound::play()
{
    Mix_PlayMusic(this->file, 0);
}

void sound::stop()
{
    Mix_HaltMusic();
}

void sound::pause()
{
    Mix_PauseMusic();
}

void sound::resume()
{
    Mix_ResumeMusic();
}

// 2D sound emitter

std::list<sound_2d*> &get_2d_sounds()
{
    static std::list<sound_2d*> 2d_sounds;
    return 2d_sounds;
}

sound_2d::sound(std::string path, float x, float y)
{
    this->path = path;
    this->file = Mix_LoadMUS(path.c_str());

    this->x = x;
    this->y = y;

    if(!this->file) {
        std::cerr << "Mix_LoadMUS Error loading audio file: " << this->path << std::endl;
    }
}

void sound_2d::play()
{
    Mix_PlayMusic(this->file, 1);
}

void sound_2d::stop()
{
    Mix_HaltMusic();
}

void sound_2d::pause()
{
    Mix_PauseMusic();
}

void sound_2d::resume()
{
    Mix_ResumeMusic();
}