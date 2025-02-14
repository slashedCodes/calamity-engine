#include "audio.hpp"
#include "engine.hpp"

// Sound listener

sound_listener* global_sound_listener = nullptr;

sound_listener::sound_listener(float x, float y)
{
    this->x = x;
    this->y = y;
    std::cout << global_sound_listener << std::endl;
    if(global_sound_listener != nullptr) {
        std::cerr << "Warning: Multiple sound listeners detected. Only one sound listener is supported." << std::endl;
        return;
    }

    global_sound_listener = this;
}

void sound_listener::change_position(float x, float y)
{
    this->x = x;
    this->y = y;

    const float max_distance = 500.0f;

    // Calculate volume for all 2D sounds
    // todo actually change volume instead of changing a variable??
    for(sound_2d* sound_it : get_sounds_2d())
    {
        std::cout << "sound position" << sound_it->x << " " << sound_it->y << std::endl;
        float distance = sqrt(pow(sound_it->x - this->x, 2) + pow(sound_it->y - this->y, 2));
        
        int volume = 128 * (1 - (distance / max_distance));
        if (volume < 1) {
            volume = 1;
        }
        sound_it->change_volume(volume);
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

void sound::ensure_sound_loaded() {
    if(this->file == nullptr) {
        this->file = Mix_LoadMUS(this->path.c_str());
    }
}

void sound::change_volume(int volume)
{
    this->volume = volume;
    Mix_VolumeMusic(this->volume);
}

void sound::play()
{
    this->ensure_sound_loaded();
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

std::list<sound_2d*> &get_sounds_2d()
{
    static std::list<sound_2d*> sounds_2d;
    return sounds_2d;
}

sound_2d::sound_2d(std::string path, float x, float y)
{
    this->path = path;
    this->file = nullptr;

    this->x = x;
    this->y = y;

    if(!this->file) {
        std::cerr << "Mix_LoadMUS Error loading audio file: " << this->path << std::endl;
    }

    get_sounds_2d().push_back(this);
}

void sound_2d::ensure_sound_loaded() {
    if(this->file == nullptr) {
        this->file = Mix_LoadMUS(this->path.c_str());
    }
}

void sound_2d::change_volume(int volume)
{
    std::cout << "Changing volume to " << volume << std::endl;
    this->volume = volume;
    Mix_VolumeMusic(this->volume);
}

void sound_2d::play()
{
    this->ensure_sound_loaded();
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