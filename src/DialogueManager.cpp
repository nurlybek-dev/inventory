#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "DialogueManager.h"
#include "SDL2/SDL.h"

using json = nlohmann::json;

DialogueManager::DialogueManager()
{
    Load("assets/dialogue.json");
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
    return mDialogues[mCurrentDialogue].type == DialogueType::END;
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

void DialogueManager::Load(std::string path)
{
    std::ifstream f(path.c_str());
    json data = json::parse(f);

    auto dialogues = data["dialogues"];
    for (json::iterator it = dialogues.begin(); it != dialogues.end(); ++it) {
        Dialogue dialogue;
        dialogue.id = (*it)["id"];
        dialogue.text = (*it)["text"];
        dialogue.nextID = (*it)["nextID"];

        std::string type = (*it)["type"];

        if (type == "START") dialogue.type = DialogueType::START;
        else if (type == "STORY") dialogue.type = DialogueType::STORY;
        else if (type == "CHOICE") dialogue.type = DialogueType::CHOICE;
        else if (type == "COMBAT") dialogue.type = DialogueType::COMBAT;
        else if (type == "ABILITY CHECK") dialogue.type = DialogueType::ABILITY_CHECK;
        else if (type == "END") dialogue.type = DialogueType::END;

        for(json::iterator ic = (*it)["choices"].begin(); ic != (*it)["choices"].end(); ++ic) {
            dialogue.choices.push_back(Choice((*ic)["text"], (*ic)["nextID"]));
        }

        mDialogues[dialogue.id] = dialogue;

        if(dialogue.type == DialogueType::START) {
            mCurrentDialogue = dialogue.nextID;
        }

        std::cout << "Load " << dialogue.id << ". Type: " << dialogue.type  << ". NextID: " << dialogue.nextID << std::endl;
    }
}
