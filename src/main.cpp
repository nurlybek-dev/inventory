#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Inventory.h"
#include "Equipment.h"
#include "Tooltip.h"
#include "Character.h"


bool init();
void loop();

RenderManager* gRenderManager = nullptr;
Tooltip* gTooltip;
Character* gCharacter;

int main(int, char**) {
    if(init()) {
        gCharacter = new Character("assets/PNG/brutal-helm.png", 0, SCREEN_HEIGHT - 32);
        gCharacter->SetActive(true);
        gTooltip = Tooltip::Instance();
        loop();
    }
    
    return 0;
}

bool init() {
    gRenderManager = RenderManager::Instance();
    return gRenderManager->Init();
}

void loop() {
    SDL_Event event;
    bool running = true;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            gTooltip->Hide();
            int x = event.motion.x;
            int y = event.motion.y;

            SDL_Rect rect = gCharacter->Pos();
            if(event.type == SDL_MOUSEBUTTONDOWN && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
            {
                gCharacter->SetActive(!gCharacter->Active());
            }
            if(gCharacter->Active()) gCharacter->Input(event);
        }

        gRenderManager->Clear();
        gCharacter->Render();

        if(gCharacter->Active())
        {
            std::string healthStr = "Health: " + std::to_string(gCharacter->GetStats()->GetStat(HEALTH));
            std::string damageStr = "Damage: " + std::to_string(gCharacter->GetStats()->GetStat(DAMAGE));
            std::string armorStr = "Armor: " + std::to_string(gCharacter->GetStats()->GetStat(ARMOR));

            gRenderManager->RenderText(healthStr, {300, 0, (int)healthStr.size() * 24, 24});
            gRenderManager->RenderText(damageStr, {300, 30, (int)damageStr.size() * 24, 24});
            gRenderManager->RenderText(armorStr, {300, 60, (int)armorStr.size() * 24, 24});
        }


        gTooltip->Render();
        gRenderManager->Render();
    }

    TTF_Quit();
    SDL_Quit();
}