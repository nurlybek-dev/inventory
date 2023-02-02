#ifndef _DIALOGUE_MANAGER_H_
#define _DIALOGUE_MANAGER_H_

#include <vector>
#include "Dialogue.h"

class DialogueManager {
    public:
        DialogueManager();
        ~DialogueManager();

        void Update(float delta);
        void Render();
        void Input(SDL_Event event);

        bool IsEnd();

    private:
        std::vector<Dialogue*> mDialogues;
        Dialogue* mCurrentDialogue;
        Dialogue* mLastDialogue;
};

#endif