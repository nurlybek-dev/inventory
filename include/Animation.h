#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include <string>
#include "Texture.h"

class Animation
{
    public:
        Animation(std::string name, std::string path, SDL_Rect rect, SDL_Rect clip, 
                    int count, int offset, double animationDuration, bool loop, bool autoPlay, bool reverse);
        ~Animation();

        void Render();
        void Update(float delta);
        void Input(SDL_Event event);

        void Play();
        void Stop();

        bool End();

    private:
        std::string mName;
        double mAnimationDuration;
        double mAnimationTime;
        int mCount;
        int mCurrentFrame;
        bool mLoop;
        bool mIsPlaying;
        SDL_Rect mRect;
        std::vector<Texture*> mFrames;
};

#endif