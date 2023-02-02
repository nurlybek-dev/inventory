#include "Dialogue.h"
#include "RenderManager.h"

Dialogue::Dialogue(const std::string &text)
{
    mAnimatedText = nullptr;
    SetText(text);
}

Dialogue::~Dialogue()
{
    delete mAnimatedText;
    mAnimatedText = nullptr;

    for(int i = 0; i < mNextDialogues.size(); i++) {
        delete mNextDialogues[i];
        mNextDialogues[i] = nullptr;
    }
    mNextDialogues.clear();
}

void Dialogue::Render()
{
    mAnimatedText->Render();
    // RenderManager::Instance()->RenderWrappedText(mText, 210, 10, 580);
    if(mAnimatedText->End()) {
        int cy = 360;
        for(int i = 0; i < mChoices.size(); i++) {
            RenderManager::Instance()->RenderText(std::to_string(i+1) + ".", 210, cy);
            SDL_Rect textRect = RenderManager::Instance()->RenderWrappedText(mChoices[i], 240, cy, 532);
            cy += textRect.h;
        }
    }
}

void Dialogue::Update(float delta)
{
    mAnimatedText->Update(delta);
}

Dialogue* Dialogue::Input(SDL_Event event)
{
    if(mAnimatedText->End()) {
        if(event.type == SDL_KEYUP)
        {
            for(int i=0; i <= mChoices.size(); i++)
            {
                if(event.key.keysym.sym == std::to_string(i+1).c_str()[0])
                {
                    return SelectChoice(i);
                }
            }
        }
    }
    return nullptr;
}

void Dialogue::SetText(const std::string &text)
{
    mAnimatedText = new AnimatedText(text, 210, 10, 580, 24);
    // mText = text;
}

void Dialogue::SetChoices(const std::vector<std::string> &choices, const std::vector<Dialogue*>& nextDialogues)
{
    mChoices.clear();
    mChoices = choices;

    mNextDialogues.clear();
    mNextDialogues = nextDialogues;
}

void Dialogue::AddChoise(const std::string &choice, Dialogue* nextDialogue)
{
    mChoices.push_back(choice);
    mNextDialogues.push_back(nextDialogue);
}

std::vector<std::string> Dialogue::GetChoices()
{
    return mChoices;
}

Dialogue* Dialogue::SelectChoice(int index)
{
    return mNextDialogues[index];
}
