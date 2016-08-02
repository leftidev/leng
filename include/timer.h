#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <SDL2/SDL.h>

namespace leng {

class Timer {
public:
    Timer();

    // Clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    // Get timer's time
    uint32_t getTicks();

    // Check status
    bool isStarted();
    bool isPaused();

private:
    // Clock time when timer started
    uint32_t startTicks;

    // Ticks stored when the timer was paused
    uint32_t pausedTicks;

    // Timer status
    bool paused;
    bool started;
};
    
} // namespace leng

#endif // TIMER_H
