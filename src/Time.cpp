#include "Time.h"

Time* Time::sInstance = nullptr;

Time* Time::Instance()
{
    if(sInstance == nullptr)
        sInstance = new Time();
    
    return sInstance;
}

void Time::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Time::Time()
{
    mNow = SDL_GetPerformanceCounter();
    mLast = 0;
    mDeltaTime = 0;
    mCountedFrames = 0;
    mStartTicks = SDL_GetTicks();
    mCapTimer;
}

Time::~Time()
{

}

void Time::Tick()
{
    mCapTimer = SDL_GetTicks();
    mTime = SDL_GetTicks() - mStartTicks;

    mLast = mNow;
    mNow = SDL_GetPerformanceCounter();

    mDeltaTime = (double)((mNow - mLast)*1000 / (double)SDL_GetPerformanceFrequency() );
    mDeltaTime *= 0.001;

    // SDL_Log("Delta: %f\n", mDeltaTime);

}

void Time::Update()
{
    float avgFPS = mCountedFrames / ( mTime / 1000.f );
    if( avgFPS > 2000000 )
    {
        avgFPS = 0;
    }

    // SDL_Log("Average FPS: %f\n", avgFPS);
}

void Time::Delay()
{
    ++mCountedFrames;
    int frameTicks = SDL_GetTicks() - mCapTimer;
    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
    }
}

double Time::DeltaTime()
{
    return mDeltaTime;
}
