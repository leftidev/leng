#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2/SDL_mixer.h>

namespace leng {

    class SoundEffect {
    public:
	SoundEffect(const char* path);
	~SoundEffect();

	void play(int loops = 0);

	Mix_Chunk* chunk;
    };

    class SoundManager {
    public:
	SoundManager();
	~SoundManager();
	void load_music(const char* path);
	void play(int loops = -1);
	void pause();
	void resume();
	void stop();
	
	Mix_Music* music;
    };
} // namespace leng

#endif // SOUND_MANAGER_H
