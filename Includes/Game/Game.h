#pragma once

class Canvas2D;
class Entity;

#include <vector>
#include "../Graphics/Image.h"

#include "../Graphics/Canvas2D.h"
#include "../Game/Entities/Entity.h"

class Game {

    Game();

    static Game* Instance;

    Canvas2D* canvas;

    std::vector<std::unique_ptr<Entity>> entities = {};


    public:

    static Game* GetInstance();

    void setCanvas( Canvas2D& canv );

    Canvas2D& getCanvas();

    void update( Canvas2D* canv, float deltaTime, Image& img );

    void init();

    // void addToEntitiesList( Entity& e );
    Image* createImage( const char* path );
    Entity* createEntity( float x, float y, float z, float w, float h );




};