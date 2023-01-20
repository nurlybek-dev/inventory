#include "AnimatedText.h"
#include "RenderManager.h"

AnimatedText::AnimatedText(std::string text, int x, int y, int wrapLength, int fontSize)
{
    mText = text;
    for(int i=0; i<mText.length(); i++)
    {
        mRenderedText += " ";
    }
    mRenderedLetters = 0;
    mX = x;
    mY = y;
    mFontSize = fontSize;
    mWrapLength = wrapLength;
}

AnimatedText::~AnimatedText()
{

}

void AnimatedText::Update()
{
    if(mRenderedLetters < mText.length()){
        mRenderedText[mRenderedLetters] = mText[mRenderedLetters];
        mRenderedLetters += 1;
    }
}

void AnimatedText::Render()
{
    RenderManager::Instance()->RenderWrappedText(mRenderedText, mX, mY, mWrapLength, mFontSize);
}

bool AnimatedText::End()
{
    return mRenderedLetters == mText.length();
}