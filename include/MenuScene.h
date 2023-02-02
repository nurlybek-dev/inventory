#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include <map>
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
        enum BookTab {
            PROFILE,
            STATUS,
            INVENTORY,
            QUESTS,
            SAVES,
            SETTINGS,
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
        BookTab mBookTab;
        
        Texture* mDeskTexture;
        Texture* mBookClosed;
        Texture* mBookOpened;

        std::map<BookTab, Texture*> mBookTabTextures;

        Animation* mBookOpen;
        Animation* mBookClose;
        Animation* mFlipLeft;
        Animation* mFlipRight;

};

#endif