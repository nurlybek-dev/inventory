#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class RenderManager
{
    public:
        static RenderManager* Instance();
        static void Release();

    public:
        RenderManager();
        ~RenderManager();

        void Render(SDL_Texture* texture, SDL_Rect clip, SDL_Rect pos);

        bool Init();

        SDL_Texture* LoadTexture(std::string path);

        void Clear();
        void Render();
        void RenderTexture(SDL_Texture* texture, SDL_Rect *pos, SDL_Rect *clip);
        void RenderText(std::string text, SDL_Rect pos);

    private:
        static RenderManager* sInstance;

        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;

        TTF_Font* mFont;
};

#endif
