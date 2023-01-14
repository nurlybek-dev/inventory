#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

// #include "Tooltip.h"
#include "SceneManager.h"


bool init();
void loop();

RenderManager* gRenderManager = nullptr;
SceneManager *gSceneManager;
// Tooltip* gTooltip;

int main(int, char**) {
    if(init()) {
        // gTooltip = Tooltip::Instance();
        gSceneManager = SceneManager::Instance();
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
            // gTooltip->Hide();
            // int x = event.motion.x;
            // int y = event.motion.y;
            gSceneManager->Input(event);
        }

        if(gSceneManager->EndScene()) {
            running = false;
            continue;
        }

        gSceneManager->Update();

        gRenderManager->Clear();

        gSceneManager->Render();

        // gTooltip->Render();
        gRenderManager->Render();
    }

    TTF_Quit();
    SDL_Quit();
}