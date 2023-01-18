#include "Stats.h"
#include "Tooltip.h"
#include "Character.h"
#include "Equipment.h"


EquipmentSlot::EquipmentSlot(ItemType type, Equipment* equipment)
{
    mType = type;
    mEquipment = equipment;
    mItem = nullptr;
    mTexture = new Texture("assets/Inventory.png", {0,0,32,32}, {4, 21, 32, 32});
}

EquipmentSlot::~EquipmentSlot()
{
    delete mTexture;
    mTexture = nullptr;

    if(mItem) {
        delete mItem;
        mItem = nullptr;
    }
}

bool EquipmentSlot::Equip(Item* item)
{
    if(mType != item->Type()) return false;
    Unequip();
    mItem = item;
    mItem->SetPos(mTexture->Pos().x, mTexture->Pos().y);
    mItem->Effect(mEquipment->GetCharacter()->GetStats());
    return true;
}

void EquipmentSlot::Unequip()
{
    if(mItem != nullptr) {
        mItem->UnEffect(mEquipment->GetCharacter()->GetStats());
        mEquipment->GetCharacter()->GetInventory()->AddItem(mItem);
    }
    mItem = nullptr;
}


void EquipmentSlot::SetPos(int x, int y)
{
    mTexture->SetPos(x, y);
}


void EquipmentSlot::Render()
{
    mTexture->Render();
    if(mItem != nullptr) mItem->Render();
}

void EquipmentSlot::Input(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;

    SDL_Rect rect = mTexture->Pos();
    if(x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        if(mItem != nullptr)
        {
            Tooltip::Instance()->Show(mItem);
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                Unequip();
            }
        }
    }
}

Equipment::Equipment(Character* character, int x, int y)
{
    // mBackground = new Texture("assets/Equipment.png", 220, 0);
    mBackground = new Texture("assets/Inventory.png", {x, y, 108, 40}, {0, 0, 1, 1});
    // mBackground->SetPos(220, SCREEN_HEIGHT - mBackground->GetHeight() - 32);
    mCharacter = character;

    mEquipments[WEAPON] = new EquipmentSlot(WEAPON, this);
    mEquipments[ARMOR] = new EquipmentSlot(ARMOR, this);
    mEquipments[ARTIFACT] = new EquipmentSlot(ARTIFACT, this);

    mEquipments[WEAPON]->SetPos(x + 4, y + 4);
    mEquipments[ARMOR]->SetPos(x + 38, y + 4);
    mEquipments[ARTIFACT]->SetPos(x + 72, y + 4);
}

Equipment::~Equipment()
{
    mCharacter = nullptr;

    delete mBackground;
    mBackground = nullptr;

    for(auto && e : mEquipments)
    {
        delete e.second;
        e.second = nullptr;
    }

    mEquipments.clear();
}

bool Equipment::Equip(Item* item)
{
    ItemType type = item->Type();
    return mEquipments[type]->Equip(item);
}

void Equipment::Unequip(ItemType type)
{
    mEquipments[type]->Unequip();
}

void Equipment::Render()
{
    mBackground->Render();
}

void Equipment::RenderItems()
{
    for (auto &&i : mEquipments)
    {
        i.second->Render();
    }
}

void Equipment::Input(SDL_Event event)
{
    for (auto &&i : mEquipments)
    {
        i.second->Input(event);
    }
}

Character* Equipment::GetCharacter()
{
    return mCharacter;
}