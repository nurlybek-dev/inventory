#include "Map.h"
#include "RenderManager.h"
#include "Tooltip.h"

MapNode::MapNode(std::string name, std::string description, SDL_Rect rect)
{
    mRect = rect;
    mName = name;
    mDescription = description;
}

MapNode::~MapNode()
{}

void MapNode::Input(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;

    if(x > mRect.x && x < mRect.x + mRect.w && y > mRect.y && y < mRect.y + mRect.h)
    {
        Tooltip::Instance()->Show(this);
    }
}

void MapNode::Update(float delta)
{
}

void MapNode::Render()
{
    // int x = Pos().x + Pos().w / 2;
    // int y = Pos().y + Pos().h / 2;
    // for(int i=0; i < mConnections.size(); i++)
    // {
    //     SDL_Rect r = mConnections[i]->Pos();
    //     RenderManager::Instance()->DrawLine(x, y, r.x + r.w / 2, r.y + r.h / 2);
    // }
}

void MapNode::AddConnection(MapNode* node)
{
    mConnections.push_back(node);
}

SDL_Rect MapNode::Pos()
{
    return mRect;
}

std::string MapNode::Name() const
{
    return mName;
}

std::string MapNode::Description() const
{
    return mDescription;
}

Map::Map()
{
    mBackground = new Texture("assets/Map.jpg", 0, 0);
    MapNode* cave = new MapNode("Cave", "Evil cave", {13, 13, 100, 70});
    MapNode* tower = new MapNode("Tower", "Human defence point agains evil", {208, 114, 50, 70});
    MapNode* gaznag = new MapNode("Gaznag", "Civilian city", {429, 62, 130, 120});
    MapNode* varson = new MapNode("Varson", "Hunters town", {290, 196, 54, 42});
    MapNode* castle = new MapNode("Castle", "Soldiers home", {140, 285, 100, 90});
    MapNode* anston = new MapNode("Anston", "Small village", {344, 320, 76, 52});
    MapNode* coalMine = new MapNode("Coal mine", "Export coal", {494, 370, 56, 52});
    MapNode* ruinMine = new MapNode("Ruin mine", "Ruined mine", {20, 378, 56, 48});
    MapNode* village = new MapNode("Village", "Agracultur village", {131, 451, 74, 47});
    MapNode* copperMine = new MapNode("Cooper mine", "Export cooper", {8, 510, 56, 52});
    MapNode* ironMine = new MapNode("Iron mine", "Export Iron", {164, 535, 56, 52});
    MapNode* ruins = new MapNode("Ruins", "Ancient human city", {356, 488, 110, 80});

    cave->AddConnection(tower);

    tower->AddConnection(cave);
    tower->AddConnection(castle);
    tower->AddConnection(gaznag);

    gaznag->AddConnection(tower);
    gaznag->AddConnection(varson);
    gaznag->AddConnection(anston);

    varson->AddConnection(gaznag);
    varson->AddConnection(anston);

    anston->AddConnection(varson);
    anston->AddConnection(castle);
    anston->AddConnection(coalMine);
    anston->AddConnection(ruins);
    anston->AddConnection(village);

    coalMine->AddConnection(anston);

    castle->AddConnection(tower);
    castle->AddConnection(ruinMine);
    castle->AddConnection(anston);

    ruins->AddConnection(anston);
    ruins->AddConnection(village);

    village->AddConnection(anston);
    village->AddConnection(ruins);
    village->AddConnection(ironMine);
    village->AddConnection(copperMine);

    ruinMine->AddConnection(castle);

    ironMine->AddConnection(village);
    copperMine->AddConnection(village);

    mNodes.push_back(cave);
    mNodes.push_back(tower);
    mNodes.push_back(gaznag);
    mNodes.push_back(varson);
    mNodes.push_back(castle);
    mNodes.push_back(anston);
    mNodes.push_back(coalMine);
    mNodes.push_back(ruinMine);
    mNodes.push_back(village);
    mNodes.push_back(copperMine);
    mNodes.push_back(ironMine);
    mNodes.push_back(ruins);

}
Map::~Map()
{
    for (int i = 0; i < mNodes.size(); i++)
    {
        delete mNodes[i];
        mNodes[i] = nullptr;
    }
    mNodes.clear();

    delete mBackground;
    mBackground = nullptr;
}

void Map::Update(float delta)
{
    for (int i = 0; i < mNodes.size(); i++)
    {
        mNodes[i]->Update(delta);
    }
}

void Map::Input(SDL_Event event)
{
        for (int i = 0; i < mNodes.size(); i++)
    {
        mNodes[i]->Input(event);
    }
}

void Map::Render()
{
    mBackground->Render();
    for (int i = 0; i < mNodes.size(); i++)
    {
        mNodes[i]->Render();
    }
}
