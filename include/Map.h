#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "Texture.h"


class MapNode 
{
    public:
        MapNode(std::string name, std::string description, SDL_Rect rect);
        ~MapNode();

        void Update(float delta);
        void Input(SDL_Event event);
        void Render();

        void AddConnection(MapNode *node);

        SDL_Rect Pos();

        std::string Name() const;
        std::string Description() const;

    private:
        SDL_Rect mRect;
        std::string mName;
        std::string mDescription;
        std::vector<MapNode*> mConnections;
};


class Map
{
    public:
        Map();
        ~Map();

        void Update(float delta);
        void Input(SDL_Event event);
        void Render();

    private:
        Texture *mBackground;
        std::vector<MapNode*> mNodes;
};

#endif