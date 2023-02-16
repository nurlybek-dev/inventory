#ifndef _HEADER_H_
#define _HEADER_H_

#include <string>
#include <vector>
#include "Texture.h"

class Header {
    public:
        Header(const std::string& text);
        ~Header();

        void Render();

        void SetText(const std::string& text);

    private:
        std::string mText;

        SDL_Rect mLeftRect;
        SDL_Rect mRightRect;
        SDL_Rect mTextRect;

        Texture* mLeftTexture;
        Texture* mRightTexture;
        std::vector<Texture*> mMiddleTextures;
};

#endif