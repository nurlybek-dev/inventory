#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

#include <map>
#include "Item.h"

class Character;
class Equipment;
class EquipmentSlot {
    public:
        EquipmentSlot(ItemType type, Equipment* equipment);
        ~EquipmentSlot();

        bool Equip(Item* item);
        void Unequip();
        
        void SetPos(int x, int y);

        void Render();
        void Input(SDL_Event event);

    private:
        Equipment* mEquipment;
        Texture* mTexture;
        Item* mItem;
        ItemType mType;
};

class Equipment
{
    public:
        static Equipment* Instance();
        static void Release();

    public:
        Equipment(Character* character);
        ~Equipment();

        bool Equip(Item* item);
        void Unequip(ItemType slot);

        void Render();
        void RenderItems();
        void Input(SDL_Event event);

        Character* GetCharacter();

    private:
        static Equipment* sInstance;
        
        Character* mCharacter;
        Texture* mBackground;
        std::map<ItemType, EquipmentSlot*> mEquipments;
};

#endif
