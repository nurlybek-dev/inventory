#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include "RenderManager.h"

class Texture
{
    public:
        Texture(std::string path);
        Texture(std::string path, int x, int y);
        Texture(std::string path, SDL_Rect pos, SDL_Rect clip);
        ~Texture();

        void SetPos(int x, int y);
        SDL_Rect Pos();

        void SetWidth(int w);
        void SetHeight(int h);

        void Render();

    private:
        SDL_Texture* mTexture;
        SDL_Rect mClip;
        SDL_Rect mPos;

        bool mIsClipped;
};

#endif
