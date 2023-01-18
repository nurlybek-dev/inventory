#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Texture.h"

class Button {
    public:
        Button(std::string text, int x, int y, int w, int h, int fontSize);
        ~Button();

        bool IsPressed();

        void Update();
        void Render();
        void Input(SDL_Event event);

    private:
        Texture* mTexture;
        std::string mText;
        bool mIsPressed;
        bool mIsPressedPrevFrame;
        int mFontSize;
};

#endif