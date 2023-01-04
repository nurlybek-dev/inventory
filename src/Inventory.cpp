#include "Inventory.h"
#include "Tooltip.h"
#include "Character.h"

InventorySlot::InventorySlot(int index, Inventory* inventory)
{
    mIndex = index;
    mInventory = inventory;
    mItem = nullptr;
    mTexture = new Texture("assets/Inventory.png", {0,0,32,32}, {4, 21, 32, 32});
}

InventorySlot::~InventorySlot()
{
    delete mTexture;
    mTexture = nullptr;

    delete mItem;
    mItem = nullptr;
}

bool InventorySlot::AddItem(Item* item)
{
    if(mItem != nullptr) {
        // SDL_Log("Can't add there %d. Item: %s\n.", mIndex, mItem->Name().c_str());
        return false;
    } else {
        // SDL_Log("Add item %s to %d\n", item->Name().c_str(), mIndex);
        mItem = item;
        mItem->SetPos(mTexture->Pos().x, mTexture->Pos().y);
        return true;
    }
}

Item* InventorySlot::GetItem()
{
    return mItem;
}

Item* InventorySlot::PopItem()
{
    Item* item = mItem;
    mItem = nullptr;
    return item;
}

int InventorySlot::Index()
{
    return mIndex;
}

void InventorySlot::Index(int index)
{
    mIndex = index;
}

void InventorySlot::SetPos(int x, int y)
{
    mTexture->SetPos(x, y);
}


void InventorySlot::Render()
{
    mTexture->Render();
    if(mItem != nullptr) mItem->Render();
}

void InventorySlot::Input(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;

    SDL_Rect rect = mTexture->Pos();
    if(x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
    {
        if(mItem != nullptr)
        {
            Tooltip::Instance()->Show(mItem);
            if( event.type == SDL_MOUSEBUTTONDOWN)
            {
                Item* item = PopItem();
                mInventory->GetCharacter()->GetEquipment()->Equip(item);
            }
        }
    }
}

Inventory::Inventory(Character* character)
{
    mCharacter = character;
    mBackground = new Texture("assets/Inventory.png", 0, 0);
    mBackground->SetPos(0, SCREEN_HEIGHT - mBackground->GetHeight() - 32);

    mSlots.clear();
    int x = 0;
    int y = 0;
    for(int i=0; i<30; i++) {
        x = mBackground->Pos().x + i%6 * 32 + 4 + i%6 * 2;
        y = mBackground->Pos().y + i/6 * 32 + 2 + 16 + 1 + 2 + i/6 * 2;
        mSlots.push_back(new InventorySlot(i, this));
        mSlots[i]->SetPos(x, y);
    }

    Item* item1 = new Item("Crossbow", "assets/PNG/crossbow.png", LEFT_HAND);
    item1->Description("Crossbow can shoot");
    item1->AddEffect(DAMAGE, 1);
    Item* item2 = new Item("Gradius", "assets/PNG/gladius.png", LEFT_HAND);
    item2->Description("Gladius for gladiators");
    item2->AddEffect(DAMAGE, 2);
    Item* item3 = new Item("Gloves", "assets/PNG/gloves.png", RIGHT_HAND);
    item3->Description("Right hand gloves for mens");
    item3->AddEffect(HEALTH, 5);
    item3->AddEffect(ARMOR, 1);
    Item* item4 = new Item("Kevlar", "assets/PNG/kevlar.png", HELM);
    item4->Description("Good kevlar");
    item4->AddEffect(ARMOR, 5);

    AddItem(item1);
    AddItem(item2);
    AddItem(item3);
    AddItem(item4);
}

Inventory::~Inventory()
{
    for(int i=0; i<mSlots.size(); i++) {
        if(mSlots[i] != nullptr) {
            delete mSlots[i];
            mSlots[i] = nullptr;
        }
    }
    mSlots.clear();
}

Item* Inventory::GetItem(int index)
{
    return mSlots[index]->GetItem();
}
Item* Inventory::PopItem(int index)
{
    return mSlots[index]->PopItem();
}
bool Inventory::AddItem(Item* item) {
    for(int i=0; i<mSlots.size(); i++) {
        if(mSlots[i]->AddItem(item)) {
            return true;
        }
    }
    // SDL_Log("Not enough space\n");
    return false;
}
bool Inventory::AddItem(Item* item, int index)
{
    return mSlots[index]->AddItem(item);
}

void Inventory::Render()
{
    mBackground->Render();
}

void Inventory::RenderItems()
{
    for(int i=0; i<mSlots.size(); i++) {
        mSlots[i]->Render();
    }
}

void Inventory::Input(SDL_Event event)
{
    for(int i=0; i<mSlots.size(); i++) {
        mSlots[i]->Input(event);
    }
}

Character* Inventory::GetCharacter()
{
    return mCharacter;
}
