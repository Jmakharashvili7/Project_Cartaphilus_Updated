#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <iostream>
#include <SDL_mixer.h>

class Audio
{
public:
    Audio(std::string path);
    ~Audio();

    void LoadMusic(std::string path);
    void LoopMusic();
    void PlayOnce();
private:
    Mix_Music* m_music;
};
#endif // AUDIOMANAGER_H