#ifndef _DIALOGUE_H_
#define _DIALOGUE_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "AnimatedText.h"

class Dialogue 
{
    public:
        Dialogue(const std::string &text);
        ~Dialogue();

        void Render();
        void Update();
        Dialogue* Input(SDL_Event event);

        void SetText(const std::string& text);
        void SetChoices(const std::vector<std::string>& choices, const std::vector<Dialogue*>& nextDialogues);
        void AddChoise(const std::string& choice, Dialogue* nextDialog);

        std::vector<std::string> GetChoices();
        Dialogue* SelectChoice(int index);

    private:
        std::string mText;
        std::vector<std::string> mChoices;
        std::vector<Dialogue*> mNextDialogues;
        AnimatedText *mAnimatedText;
};

#endif