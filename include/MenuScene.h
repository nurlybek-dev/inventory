#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "Scene.h"
#include "Texture.h"
#include "Button.h"

class MenuScene : public Scene
{
    public:
        MenuScene();
        ~MenuScene();

        void Update(float delta) override;
        void Render() override;
        void Input(SDL_Event event) override;
    private:
        Button* mStartButton;
        Button* mExitButton;
};

#endif