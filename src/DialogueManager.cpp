#include "DialogueManager.h"

DialogueManager::DialogueManager()
{
    Dialogue* dialogue1 = new Dialogue("Wait, for what purposes are you going to the city?");
    Dialogue* dialogue2 = new Dialogue("You can go through, you can get to the tavern on the left road.");
    Dialogue* dialogue3 = new Dialogue("With such an attitude, I won't let you into the city, go cool off and come back.");
    Dialogue* dialogue4 = new Dialogue("You entered the city and reached the tavern, mission accomplished.");
    Dialogue* dialogue5 = new Dialogue("You have set up camp at the edge of the forest and rested, you can return to the gate.");
    Dialogue* dialogue6 = new Dialogue("You walk in forest, bathed in the river and very tired.");
    Dialogue* lastDialogue = new Dialogue("");

    dialogue1->SetChoices({"I'm a traveler, heading to the tavern.", "What's your business?"}, {dialogue2, dialogue3});
    dialogue2->SetChoices({"(Continue)"}, {dialogue4});
    dialogue3->SetChoices({"(Continue)"}, {dialogue5});
    dialogue4->SetChoices({"(END)"}, {lastDialogue});
    dialogue5->SetChoices({"Head towards the gate.", "Rest another day and just chill in forest."}, {dialogue1, dialogue6});
    dialogue6->SetChoices({"Come back to camp and sleep."}, {dialogue5});

    mCurrentDialogue = dialogue1;
    mLastDialogue = lastDialogue;

    mDialogues.push_back(dialogue1);
    mDialogues.push_back(dialogue2);
    mDialogues.push_back(dialogue3);
    mDialogues.push_back(dialogue4);
    mDialogues.push_back(dialogue5);
    mDialogues.push_back(dialogue6);
    mDialogues.push_back(lastDialogue);
}

DialogueManager::~DialogueManager()
{
    mCurrentDialogue = nullptr;
    mLastDialogue = nullptr;

    for(int i=0; i < mDialogues.size(); i++) {
        delete mDialogues[i];
        mDialogues[i] = nullptr;
    }
    mDialogues.clear();
}

void DialogueManager::Update()
{
    mCurrentDialogue->Update();
}

void DialogueManager::Render()
{
    mCurrentDialogue->Render();
}

void DialogueManager::Input(SDL_Event event)
{
    Dialogue* dialogue = mCurrentDialogue->Input(event);
    if(dialogue != nullptr) {
        mCurrentDialogue = dialogue;
    }
}

bool DialogueManager::IsEnd()
{
    return mCurrentDialogue == mLastDialogue;
}
