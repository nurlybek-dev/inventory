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

    delete mItem;
    mItem = nullptr;
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

Equipment::Equipment(Character* character)
{
    mBackground = new Texture("assets/Equipment.png", 220, 0);
    mBackground->SetPos(220, SCREEN_HEIGHT - mBackground->GetHeight() - 32);
    mCharacter = character;

    mEquipments[HELM] = new EquipmentSlot(HELM, this);
    mEquipments[LEFT_HAND] = new EquipmentSlot(LEFT_HAND, this);
    mEquipments[RIGHT_HAND] = new EquipmentSlot(RIGHT_HAND, this);
    mEquipments[BOOT] = new EquipmentSlot(BOOT, this);

    mEquipments[HELM]->SetPos(mBackground->Pos().x + 21, mBackground->Pos().y + 4);
    mEquipments[LEFT_HAND]->SetPos(mBackground->Pos().x + 4, mBackground->Pos().y + 38);
    mEquipments[RIGHT_HAND]->SetPos(mBackground->Pos().x + 38, mBackground->Pos().y + 38);
    mEquipments[BOOT]->SetPos(mBackground->Pos().x + 21, mBackground->Pos().y + 72);
}

Equipment::~Equipment()
{
    delete mBackground;
    mBackground = nullptr;
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