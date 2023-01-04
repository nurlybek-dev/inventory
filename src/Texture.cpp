#include "Texture.h"

Texture::Texture(std::string path, int x, int y)
{
    mTexture = RenderManager::Instance()->LoadTexture(path);
    mPos.x = x;
    mPos.y = y;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &mPos.w, &mPos.h);
    mIsClipped = false;
}

Texture::Texture(std::string path, SDL_Rect pos, SDL_Rect clip)
{
    mTexture = RenderManager::Instance()->LoadTexture(path);
    mPos = pos;
    mClip = clip;
    mIsClipped = true;
}

Texture::Texture(std::string path) : Texture(path, 0, 0)
{
}

Texture::~Texture()
{
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

void Texture::SetPos(int x, int y)
{
    mPos.x = x;
    mPos.y = y;
}

void Texture::SetWidth(int w)
{
    mPos.w = w;
}

void Texture::SetHeight(int h)
{
    mPos.h = h;
}

SDL_Rect Texture::Pos()
{
    return mPos;
}

int Texture::GetWeight()
{
    return mPos.w;
}

int Texture::GetHeight()
{
    return mPos.h;
}

void Texture::Render()
{
    RenderManager::Instance()->RenderTexture(mTexture, mIsClipped ? &mClip : nullptr, &mPos);
}
