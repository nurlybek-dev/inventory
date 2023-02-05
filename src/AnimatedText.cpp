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

void AnimatedText::Update(float delta)
{
    if(mRenderedLetters < mText.length()){
        mRenderedText[mRenderedLetters] = mText[mRenderedLetters];
        mRenderedLetters += 1;
    }
}

void AnimatedText::Render()
{
    if(mRenderedText.length()) RenderManager::Instance()->RenderWrappedText(mRenderedText, mX, mY, mWrapLength, mFontSize);
}

void AnimatedText::Clear()
{
    mRenderedLetters = 0;
    mRenderedText = "";
    mText = "";
}

void AnimatedText::SetText(const std::string &text, bool skipAnimation)
{
    mRenderedLetters = 0;
    mText = text;
    if(skipAnimation) {
        mRenderedText = mText;
        mRenderedLetters += text.length();
    } else {
        mRenderedText = "";
        for(int i=0; i<text.length(); i++)
        {
            mRenderedText += " ";
        }
    }
}

void AnimatedText::AddText(const std::string &text, bool skipAnimation)
{
    mText += text;
    if(skipAnimation) {
        mRenderedText += text;
        mRenderedLetters += text.length();
    } else {
        for(int i=0; i<text.length(); i++)
        {
            mRenderedText += " ";
        }
    }
}

std::string AnimatedText::GetText()
{
    return mText;
}

void AnimatedText::SkipAnimation()
{
    mRenderedText = mText;
    mRenderedLetters = mText.length();
}

bool AnimatedText::End()
{
    return mRenderedLetters == mText.length();
}
