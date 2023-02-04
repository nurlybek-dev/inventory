#include "DialogueManager.h"

DialogueManager::DialogueManager()
{
    Dialogue dialogue7;
    dialogue7.id = "7";
    dialogue7.text = "Тест русского языка так то.";
    dialogue7.nextID = "1";
    dialogue7.type = DialogueType::STORY;

    Dialogue dialogue1;
    dialogue1.id = "1";
    dialogue1.type = DialogueType::CHOICE;
    dialogue1.text = "Wait, for what purpose are you going to the city";
    dialogue1.choices = {Choice("I'm a traveler, heading to the tavern.", "2"), Choice("What's your business?", "3")};

    Dialogue dialogue2;
    dialogue2.id = "2";
    dialogue2.type = DialogueType::CHOICE;
    dialogue2.text = "You can go through, you can get to the tavern on the left road.";
    dialogue2.choices = {Choice("(Continue)", "4")};

    Dialogue dialogue3;
    dialogue3.id = "3";
    dialogue3.type = DialogueType::CHOICE;
    dialogue3.text = "With such an attitude, I won't let you into the city, go cool off and come back.";
    dialogue3.choices = {Choice("(Continue)", "5")};

    Dialogue dialogue4;
    dialogue4.id = "4"; 
    dialogue4.type = DialogueType::CHOICE;
    dialogue4.text = "You entered the city and reached the tavern, mission accomplished.";
    dialogue4.choices = {Choice("(END)", "-1")};

    Dialogue dialogue5;
    dialogue5.id = "5";
    dialogue5.type = DialogueType::CHOICE;
    dialogue5.text = "You have set up camp at the edge of the forest and rested, you can return to the gate.";
    dialogue5.choices = {Choice("Head towards the gate.", "1"), Choice("Rest another day and just chill in forest.", "6")};

    Dialogue dialogue6;
    dialogue6.id = "6";
    dialogue6.type = DialogueType::CHOICE;
    dialogue6.text = "You walk in forest, bathed in the river and very tired.";
    dialogue6.choices = {Choice("Come back to camp and sleep.", "5")};

    Dialogue lastDialogue;
    lastDialogue.id = "-1";
    lastDialogue.type = DialogueType::STORY;

    mDialogues[dialogue7.id] = dialogue7;
    mDialogues[dialogue1.id] = dialogue1;
    mDialogues[dialogue2.id] = dialogue2;
    mDialogues[dialogue3.id] = dialogue3;
    mDialogues[dialogue4.id] = dialogue4;
    mDialogues[dialogue5.id] = dialogue5;
    mDialogues[dialogue6.id] = dialogue6;
    mDialogues[lastDialogue.id] = lastDialogue;

    mCurrentDialogue = "7";
    mLastDialogue = "-1";
}

DialogueManager::~DialogueManager()
{
    mDialogues.clear();
}

DialogueType DialogueManager::GetType()
{
    return mDialogues[mCurrentDialogue].type;
}

std::string DialogueManager::NextID()
{
    return mDialogues[mCurrentDialogue].nextID;
}

bool DialogueManager::IsEnd()
{
    return mCurrentDialogue == mLastDialogue;
}

std::string DialogueManager::GetText()
{
    return mDialogues[mCurrentDialogue].text;
}

std::vector<Choice> DialogueManager::GetChoices()
{
    return mDialogues[mCurrentDialogue].choices;
}

void DialogueManager::SelectChoice(int index)
{
    mCurrentDialogue = mDialogues[mCurrentDialogue].choices[index].nextID;
}

void DialogueManager::Next()
{
    mCurrentDialogue = mDialogues[mCurrentDialogue].nextID;
}
