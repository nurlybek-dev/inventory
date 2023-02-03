#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "Scene.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Character.h"
#include "Panel.h"
#include "DialogueManager.h"
#include "Map.h"
#include "Book.h"

class GameScene : public Scene 
{
    public:
        GameScene();
        ~GameScene();

        void Update(float delta) override;
        void Render() override;
        void Input(SDL_Event event) override;

        void OpenMap();
        void CloseMap();
    
    private:
        Character* gCharacter;
        Panel* gLeftPanel;
        Panel* gTopPanel;
        Panel* gBottomPanel;
        Panel* gMapPanel;
        DialogueManager* gDialogueManager;

        Texture *mMapOpenIcon;
        Texture *mMapCloseIcon;
        Map* mMap;
        Book* mBook;

        bool mIsMapOpen;
};

#endif