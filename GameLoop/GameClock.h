#ifndef GAMECLOCK_H
#define GAMECLOCK_H
#include <ctime>

class GameClock
{
 private:
 struct timespec current_time;
 struct timespec start_time;
 struct timespec elapsed_time;
 
 public:
 GameClock();
 struct timespec GetStartTime();
 struct timespec GetCurrentTime();
 struct timespec GetElapsedTime();
 void SleepFor(unsigned int nanoseconds);
};

#endif