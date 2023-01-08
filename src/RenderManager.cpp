#include "RenderManager.h"

RenderManager* RenderManager::sInstance = nullptr;

RenderManager* RenderManager::Instance()
{
    if(sInstance == nullptr)
        sInstance = new RenderManager();

    return sInstance;
}

void RenderManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

bool RenderManager::Init()
{
    bool success = true;
    if( SDL_Init(SDL_INIT_VIDEO) == -1 ) {
        success = false;
        SDL_Log("Error init SDL. SDL_Error: %s\n", SDL_GetError());
    } else {
        SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI);
        mWindow = SDL_CreateWindow("SDL BASE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
        if(mWindow == nullptr)
        {
            SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
            if(mRenderer == nullptr)
            {
                SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags))
            {
                SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }

            if(TTF_Init() == -1)
            {
                SDL_Log( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }

            mFont = TTF_OpenFont("assets/kenvector_future.ttf", 24);
        }
    }

    return success;
}

void RenderManager::Clear()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void RenderManager::Render()
{
    SDL_RenderPresent(mRenderer);
}

void RenderManager::RenderTexture(SDL_Texture* texture, SDL_Rect *srcrect, SDL_Rect *dstrect)
{
    SDL_RenderCopy(mRenderer, texture, srcrect, dstrect);
}

void RenderManager::RenderText(std::string text, SDL_Rect srcrect)
{
    SDL_Texture *newTexture = nullptr;

    SDL_Surface *loadedSurface = TTF_RenderText_Solid(mFont, text.c_str(), {255, 255, 255, 255});
    if(loadedSurface == nullptr)
    {
        SDL_Log("Unable to create text %s! SDL_ttf Error: %s\n", text.c_str(), TTF_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if( newTexture == nullptr )
        {
            SDL_Log( "Unable to create text from %s! SDL Error: %s\n", text.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }
    SDL_RenderCopy(mRenderer, newTexture, nullptr, &srcrect);
    SDL_DestroyTexture(newTexture);
}

void RenderManager::RenderWrappedText(std::string text, SDL_Rect srcrect, Uint32 wrapLength)
{
    SDL_Texture *newTexture = nullptr;

    SDL_Surface *loadedSurface = TTF_RenderText_Blended_Wrapped(mFont, text.c_str(), {255, 255, 255, 255}, wrapLength);
    if(loadedSurface == nullptr)
    {
        SDL_Log("Unable to create text %s! SDL_ttf Error: %s\n", text.c_str(), TTF_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if( newTexture == nullptr )
        {
            SDL_Log( "Unable to create text from %s! SDL Error: %s\n", text.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }
    SDL_RenderCopy(mRenderer, newTexture, nullptr, &srcrect);
    SDL_DestroyTexture(newTexture);
}

SDL_Texture* RenderManager::LoadTexture(std::string path)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Unable to load %s. IMG_Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        if(texture == nullptr) {
            SDL_Log("Error create texture from surface %s. SDL_Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    return texture;
}
