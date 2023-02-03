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

void AnimatedText::SetText(const std::string &text)
{
    mText = text;
    mRenderedText = "";
    for(int i=0; i<text.length(); i++)
    {
        mRenderedText += " ";
    }
}

void AnimatedText::AddText(const std::string &text)
{
    mText += text;
    for(int i=0; i<text.length(); i++)
    {
        mRenderedText += " ";
    }
}

bool AnimatedText::End()
{
    return mRenderedLetters == mText.length();
}
