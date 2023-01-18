#ifndef _ITEM_H_
#define _ITEM_H_

#include <map>
#include <string>
#include "Texture.h"
#include "Stats.h"


enum ItemType {
    ARMOR,
    WEAPON,
    ARTIFACT,
    NONE
};

class Item {
    public:
        Item(std::string name, std::string iconPath, ItemType itemType);
        ~Item();

        void Render();
        void Input(SDL_Event event);

        void SetPos(int x, int y);
        SDL_Rect Pos();
        ItemType Type();
        std::string Name();
        std::string Description();
        void Name(std::string name);
        void Description(std::string description);

        void AddEffect(Stats::StatType type, int value);
        std::map<Stats::StatType, int> GetEffects();
        void Effect(Stats* stats);
        void UnEffect(Stats* stats);

    private:
        std::string mName;
        std::string mDescription;
        Texture* mTexture;
        ItemType mType;
        std::map<Stats::StatType, int> mEffectors;

};

#endif
