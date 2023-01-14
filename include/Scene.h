#ifndef _SCENE_H_
#define _SCENE_H_

#include "SDL2/SDL.h"

class Scene 
{
    public:
        Scene();
        ~Scene();

        virtual void Render();
        virtual void Update();
        virtual void Input(SDL_Event event);
};

#endif