#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"
#include "Equipment.h"
#include "Stats.h"

class Character
{
    public:
        enum CharacterTabs {
            StatsTab,
            InventoryTab,
            JournalTab
        };
    public:
        Character();
        ~Character();

        Inventory* GetInventory();
        Equipment* GetEquipment();
        Stats* GetStats();

        void Update();
        void Input(SDL_Event event);
        void Render();

        Character::CharacterTabs Active();
        void SetActive(Character::CharacterTabs tab);

    private:
        Inventory* mInventory;
        Equipment* mEquipment;
        Stats* mStats;

        Texture *mIconsBackground;
        Texture *mStatsIcon;
        Texture *mInventoryIcon;
        Texture *mJournalIcon;

        Character::CharacterTabs mActiveTab;
};

#endif