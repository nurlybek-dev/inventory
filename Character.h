#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Inventory.h"
#include "Equipment.h"
#include "Stats.h"

class Character
{
    public:
        Character(std::string iconPath, int x, int y);
        ~Character();

        Inventory* GetInventory();
        Equipment* GetEquipment();
        Stats* GetStats();

        void Input(SDL_Event event);
        void Render();

        bool Active();
        void SetActive(bool value);

        SDL_Rect Pos();

    private:
        Texture* mIcon;
        Inventory* mInventory;
        Equipment* mEquipment;
        Stats* mStats;

        bool mActive;
};

#endif