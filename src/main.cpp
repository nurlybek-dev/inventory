#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Tooltip.h"
#include "SceneManager.h"
#include "Time.h"

bool init();
void loop();

RenderManager* gRenderManager = nullptr;
SceneManager *gSceneManager;
Tooltip* gTooltip;
Time* gTime;

int main(int, char**) {
    if(init()) {
        gTooltip = Tooltip::Instance();
        gSceneManager = SceneManager::Instance();
        gTime = Time::Instance();
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
        gTime->Tick();

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            gTooltip->Hide();
            int x = event.motion.x;
            int y = event.motion.y;
            gSceneManager->Input(event);
        }

        gTime->Update();

        if(gSceneManager->EndScene()) {
            running = false;
            continue;
        }

        gSceneManager->Update(gTime->DeltaTime());

        gRenderManager->Clear();

        gSceneManager->Render();

        gTooltip->Render();
        gRenderManager->Render();

        gTime->Delay();
    }

    Time::Release();
    Tooltip::Release();
    SceneManager::Release();
    RenderManager::Release();

    SDL_Quit();
}