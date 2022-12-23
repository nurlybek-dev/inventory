#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <vector>
#include <string>
#include "Texture.h"
#include "Item.h"

class Character;
class Inventory;
class InventorySlot {
    public:
        InventorySlot(int index, Inventory* mInventory);
        ~InventorySlot();

        bool AddItem(Item* item);
        Item* GetItem();
        Item* PopItem();

        int Index();
        void Index(int index);
        void SetPos(int x, int y);

        void Render();
        void Input(SDL_Event event);

    private:
        Inventory* mInventory;
        Texture* mTexture;
        int mIndex;
        Item* mItem;
};


class Inventory {
    public:
        Inventory(Character* character);
        ~Inventory();

        Item* GetItem(int index);
        Item* PopItem(int index);
        bool AddItem(Item* item);
        bool AddItem(Item* item, int index);

        void Render();
        void RenderItems();
        void Input(SDL_Event event);

        Character* GetCharacter();

    private:
        Character* mCharacter;
        Texture* mBackground;
        std::vector<InventorySlot*> mSlots;
};

#endif