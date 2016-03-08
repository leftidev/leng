#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL_mixer.h>

namespace leng {

class SoundEffect {
public:
    SoundEffect(const char* path);
    ~SoundEffect();

    void play(int loops = 0);

private:
    Mix_Chunk* chunk;
};
    
class Music {
public:
    Music(const char* path);
    ~Music();
    void play(int loops = -1);
    void pause();
    void resume();
    void stop();
	
private:
    Mix_Music* music;	
};
    
static void soundInit();

} // namespace leng

#endif // SOUND_H
