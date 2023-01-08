#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Inventory.h"
#include "Equipment.h"
#include "Tooltip.h"
#include "Character.h"
#include "Panel.h"


bool init();
void loop();

RenderManager* gRenderManager = nullptr;
Tooltip* gTooltip;
Character* gCharacter;
Panel* gLeftPanel;
Panel* gTopPanel;
Panel* gBottomPanel;

int main(int, char**) {
    if(init()) {
        gCharacter = new Character("assets/PNG/brutal-helm.png", 0, SCREEN_HEIGHT - 32);
        gCharacter->SetActive(true);
        gTooltip = Tooltip::Instance();
        gLeftPanel = new Panel(200, SCREEN_HEIGHT);
        gTopPanel = new Panel(600, 350);
        gBottomPanel = new Panel(600, 250);

        gLeftPanel->SetPos(0, 0);
        gTopPanel->SetPos(200, 0);
        gBottomPanel->SetPos(200, 350);
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
        gLeftPanel->Render();
        gTopPanel->Render();
        gBottomPanel->Render();

        std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis ut pretium ex. Mauris turpis arcu, luctus at sodales sed, venenatis ut augue. Phasellus aliquet, nulla sit amet fringilla commodo, risus erat fringilla orci, et fermentum diam ante mollis nisi. Integer eget nulla orci. Aliquam dapibus venenatis mattis.";

        int l = text.size() * 24;
        int w = 0;
        int h = 0;

        if(l > 580) {
            w = 580;
            h = (l / 580) * 24;
        } else {
            w = l;
            h = 24;
        }

        gRenderManager->RenderWrappedText(text, {210, 10, w, h}, w);

        for(int i = 1; i <= 5; i++) {
            gRenderManager->RenderText(std::to_string(i) + ".", {210, 360 + ((i-1) * 24), 48, 24});
            std::string choice = "Choice " + std::to_string(i);
            int cw = choice.size()*24;
            gRenderManager->RenderWrappedText(choice, {210+48, 360 + ((i-1) * 24), cw, 24}, cw);
        }

        // gCharacter->Render();

        // if(gCharacter->Active())
        // {
        //     std::string healthStr = "Health: " + std::to_string(gCharacter->GetStats()->GetStat(HEALTH));
        //     std::string damageStr = "Damage: " + std::to_string(gCharacter->GetStats()->GetStat(DAMAGE));
        //     std::string armorStr = "Armor: " + std::to_string(gCharacter->GetStats()->GetStat(ARMOR));

        //     gRenderManager->RenderText(healthStr, {300, 0, (int)healthStr.size() * 24, 24});
        //     gRenderManager->RenderText(damageStr, {300, 30, (int)damageStr.size() * 24, 24});
        //     gRenderManager->RenderText(armorStr, {300, 60, (int)armorStr.size() * 24, 24});
        // }

        gTooltip->Render();
        gRenderManager->Render();
    }

    TTF_Quit();
    SDL_Quit();
}