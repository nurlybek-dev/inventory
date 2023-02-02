#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "Scene.h"
#include "Texture.h"
#include "Button.h"
#include "Animation.h"

class MenuScene : public Scene
{
    public:
        enum BookState {
            CLOSED,
            OPENED,
            OPENING,
            CLOSING,
            FLIPPING_LEFT,
            FLIPPING_RIGHT,
        };
    public:
        MenuScene();
        ~MenuScene();

        void Update(float delta) override;
        void Render() override;
        void Input(SDL_Event event) override;
    private:
        Button* mStartButton;
        Button* mExitButton;

        BookState mBookState;
        
        Texture* mBookClosed;
        Texture* mBookOpened;
        Animation* mBookOpen;
        Animation* mBookClose;
        Animation* mFlipLeft;
        Animation* mFlipRight;

};

#endif