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
std::vector<Character*> gCharacters;

int main(int, char**) {
    if(init()) {
        gCharacters.push_back(new Character("assets/PNG/brutal-helm.png", 0, SCREEN_HEIGHT - 32));
        gCharacters.push_back(new Character("assets/PNG/brutal-helm.png", 32, SCREEN_HEIGHT - 32));
        gCharacters.push_back(new Character("assets/PNG/brutal-helm.png", 64, SCREEN_HEIGHT - 32));
        gCharacters[0]->SetActive(true);
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
            for(int i=0; i<gCharacters.size(); i++)
            {
                int x = event.motion.x;
                int y = event.motion.y;

                SDL_Rect rect = gCharacters[i]->Pos();
                if(event.type == SDL_MOUSEBUTTONDOWN && x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
                {
                    for(int j=0; j<gCharacters.size(); j++)
                    {
                        gCharacters[j]->SetActive(false);
                    }
                    gCharacters[i]->SetActive(true);
                    break;
                }
                if(gCharacters[i]->Active()) gCharacters[i]->Input(event);
            }
        }

        gRenderManager->Clear();
        for(int i=0; i<gCharacters.size(); i++)
        {
            gCharacters[i]->Render();

            if(gCharacters[i]->Active())
            {
                std::string healthStr = "Health: " + std::to_string(gCharacters[i]->GetStats()->GetStat(HEALTH));
                std::string damageStr = "Damage: " + std::to_string(gCharacters[i]->GetStats()->GetStat(DAMAGE));
                std::string armorStr = "Armor: " + std::to_string(gCharacters[i]->GetStats()->GetStat(ARMOR));

                gRenderManager->RenderText(healthStr, {300, 0, (int)healthStr.size() * 24, 24});
                gRenderManager->RenderText(damageStr, {300, 30, (int)damageStr.size() * 24, 24});
                gRenderManager->RenderText(armorStr, {300, 60, (int)armorStr.size() * 24, 24});
            }
        }


        gTooltip->Render();
        gRenderManager->Render();
    }

    TTF_Quit();
    SDL_Quit();
}