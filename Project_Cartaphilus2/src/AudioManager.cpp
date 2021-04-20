#include "AudioManager.h"
#include "Commons.h"
#include "Text.h"

Audio::Audio(std::string path)
{
    LoadMusic(path);
}

Audio::~Audio()
{
    Mix_CloseAudio();
    m_music = nullptr;
}

void Audio::LoadMusic(std::string path)
{
    m_music = Mix_LoadMUS(path.c_str());
    if (m_music == nullptr)
    {
        std::string error = Mix_GetError();
        LOG("Failed to load the music. Error: " + error);
    }
}

void Audio::LoopMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(m_music, -1);
    }
}

void Audio::PlayOnce()
{
    Mix_PlayMusic(m_music, 1);
}
