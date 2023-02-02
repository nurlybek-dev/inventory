#ifndef _ANIMATED_TEXT_H_
#define _ANIMATED_TEXT_H_

#include <string>
#include <vector>
#include "Texture.h"

class AnimatedText
{
    public:
        AnimatedText(std::string text, int x, int y, int wrapLength, int fontSize);
        ~AnimatedText();

        void Update(float delta);
        void Render();
        
        bool End();
    
    private:
        std::string mText;
        std::string mRenderedText;

        int mRenderedLetters;
        int mX;
        int mY;
        int mFontSize;
        int mWrapLength;
};

#endif