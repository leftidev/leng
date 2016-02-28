#include <iostream>

#include "sound_manager.h"

namespace leng {
    
SoundEffect::SoundEffect(const char* path) {
    chunk = Mix_LoadWAV(path);
    if(!chunk) {
	std::cout << "Mix_LoadWAV error: " << Mix_GetError() << std::endl;
    }
}

SoundEffect::~SoundEffect() {
    Mix_FreeChunk(chunk);
    chunk = nullptr;
}

void SoundEffect::play(int loops /* = 0 */) {
    if(Mix_PlayChannel(-1, chunk, loops) == -1) {
	std::cout << "Mix_PlayChannel error: " << Mix_GetError() << std::endl;
    }
}

SoundManager::SoundManager() {
    // MIX_INIT_FAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
	std::cout << "Mix_Init error: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
	std::cout << "Mix_OpenAudio error: " << Mix_GetError() << std::endl;
    }
}

SoundManager::~SoundManager() {
    Mix_FreeMusic(music);
}

void SoundManager::load_music(const char* path) {
    music = Mix_LoadMUS(path);
    if(!music) {
	std::cout << "Mix_LoadMUS error: " << Mix_GetError() << std::endl;
    }
}	
    
void SoundManager::play(int loops /* = -1 */) {
    // loops -1 forever, n = number of times
    if(Mix_PlayMusic(music, loops) == -1) {
	std::cout << "Mix_PlayMusic error:" << Mix_GetError() << std::endl;
    }
}

void SoundManager::pause() {
    Mix_PauseMusic();
}

void SoundManager::resume() {
    Mix_ResumeMusic();
}

void SoundManager::stop() {
    Mix_HaltMusic();
}

} // namespace leng
