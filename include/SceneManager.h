#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "MenuScene.h"
#include "GameScene.h"

enum Scenes {
    MENU,
    GAME,
    END
};

class SceneManager
{
    public:
        static SceneManager* Instance();
        static void Release();

    public:
        SceneManager();
        ~SceneManager();

        void ChangeScene(Scenes scene);

        void Render();
        void Update();
        void Input(SDL_Event event);

        bool EndScene();

    private:
        static SceneManager* sInstance;
        Scene* mCurrentScene;
};

#endif