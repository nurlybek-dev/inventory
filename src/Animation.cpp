#include "Animation.h"


/*
5 frame
duration 3 seconds
current time += double;
3 = 5
1 = x
x = (1 * 5) / 3
*/
Animation::Animation(std::string name, std::string path, SDL_Rect rect, SDL_Rect clip, 
            int count, int offset, double animationDuration, bool loop, bool autoPlay, bool reverse)
{
    mName = name;
    mAnimationDuration = animationDuration;
    mAnimationTime = 0.0;
    mCurrentFrame = 0;
    mLoop = loop;
    mIsPlaying = false;
    mCount = count;
    mRect = rect;
    for (int i = 0; i < count; i++)
    {
        mFrames.push_back(new Texture(path, rect, clip));
        if(reverse)
            clip.x -= rect.w + offset;
        else
            clip.x += rect.w + offset;
    }

    if(autoPlay) {
        Play();
    }
}

Animation::~Animation()
{
    for (int i = 0; i < mFrames.size(); i++)
    {
        delete mFrames[i];
        mFrames[i] = nullptr;
    }
    mFrames.clear();
}

void Animation::Render()
{
    mFrames[mCurrentFrame]->Render();
}

void Animation::Update(float delta)
{
    if(mIsPlaying) {
        if(mAnimationTime > mAnimationDuration) {
            mCurrentFrame = mCount - 1;
            if(mLoop) {
                mAnimationTime = 0;
            } else {
                mIsPlaying = false;
            }
        }
        else
        {
            mCurrentFrame = (int)((mAnimationTime * mCount) / mAnimationDuration);
            mAnimationTime += delta;
        }
    }
}

void Animation::Input(SDL_Event event)
{

}

void Animation::Play()
{
    mIsPlaying = true;
    mCurrentFrame = 0;
    mAnimationTime = 0;
}

void Animation::Stop()
{
    mIsPlaying = false;
}

bool Animation::End()
{
    return !mIsPlaying;
}