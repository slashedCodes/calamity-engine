#include "audio.hpp"
#include "engine.hpp"

std::vector<bool> channels{false, false, false, false, false, false, false, false};

int find_free_channel()
{
    for(int i = 0; i < channels.size(); i++) {
        if(channels[i] == false) {
            channels[i] = true;
            return i;
        }
    }
    return -1;
}

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

sound::sound(std::string path, int loops)
{
    this->path = path;
    this->file = nullptr;
    this->channel = -1;
    this->loops = loops;
}

void sound::ensure_sound_loaded() {
    if(this->file == nullptr) {
        this->file = Mix_LoadWAV(this->path.c_str());
    }
}

void sound::change_volume(int volume)
{
    this->volume = volume;
    Mix_VolumeChunk(this->file, this->volume);
}

void sound::play()
{
    this->channel = find_free_channel();
    this->ensure_sound_loaded();
    Mix_PlayChannel(this->channel, this->file, this->loops);
}

void sound::stop()
{
    channels.at(this->channel) = false;
    Mix_HaltChannel(this->channel);
    this->channel = -1;
}

void sound::pause()
{
    Mix_Pause(this->channel);
}

void sound::resume()
{
    Mix_Resume(this->channel);
}

// 2D sound emitter

std::list<sound_2d*> &get_sounds_2d()
{
    static std::list<sound_2d*> sounds_2d;
    return sounds_2d;
}

sound_2d::sound_2d(std::string path, float x, float y, int loops)
{
    this->path = path;
    this->file = nullptr;
    this->loops = loops;
    this->channel = -1;

    this->x = x;
    this->y = y;

    get_sounds_2d().push_back(this);
}

void sound_2d::ensure_sound_loaded() {
    if(this->file == nullptr) {
        this->file = Mix_LoadWAV(this->path.c_str());
    }
}

void sound_2d::change_volume(int volume)
{
    this->volume = volume;
    Mix_VolumeChunk(this->file, this->volume);
}

void sound_2d::play()
{
    this->channel = find_free_channel();
    this->ensure_sound_loaded();
    Mix_PlayChannel(this->channel, this->file, 1);
}

void sound_2d::stop()
{
    channels.at(this->channel) = false;
    Mix_HaltChannel(this->channel);
    this->channel = -1;
}

void sound_2d::pause()
{
    Mix_Pause(this->channel);
}

void sound_2d::resume()
{
    Mix_Resume(this->channel);
}