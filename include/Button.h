#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Texture.h"

class Button {
    public:
        Button(std::string text, int x, int y);
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
};

#endif