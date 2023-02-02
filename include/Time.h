#ifndef _TIME_H_
#define _TIME_H_

#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

#include "SDL2/SDL.h"

class Time
{
    public:
        static Time* Instance();
        static void Release();

    public:
        Time();
        ~Time();

        void Tick();
        void Update();

        void Delay();
        double DeltaTime();

    private:
        static Time* sInstance;

        Uint32 mTime;
        Uint64 mNow;
        Uint64 mLast;
        double mDeltaTime;
        int mCountedFrames;
        Uint32 mStartTicks;
        Uint32 mCapTimer;

};

#endif