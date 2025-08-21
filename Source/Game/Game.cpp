#include "../../Includes/Game/Game.h"
#include "../../Includes/Utils/Utils.h"

#include <iostream>
#include <algorithm>
class Canvas2D;
Game* Game::Instance;

Game::Game(){
    std::cout << "Hello, World! \n";
}

Game* Game::GetInstance(){
    
    if( !Instance ) Instance = new Game();
    
    return Instance;

}   

Canvas2D* canvas;

void Game::setCanvas( Canvas2D& canv ){ canvas = &canv; }

Canvas2D& Game::getCanvas(){ return *canvas; }


void Game::update( Canvas2D* canv, float deltaTime, Image& img ) {
    for( auto& e : entities ){
        
        e->update( canv, deltaTime, img );
    
    }

}

void Game::init(){

    
    Entity* e = createEntity( 0, 0, 1, 100, 100 );
    
    std::string path = Utils::pathIn( "\\tiles.png" );
    
    Image* img = createImage( path.c_str() );
    
    e->setImage( std::unique_ptr<Image>(img) );
    
}

Entity* Game::createEntity( float x, float y, float z, float w, float h ){

    auto e = std::make_unique<Entity>(x, y, z, w, h);
    Entity* ptr = e.get();
    entities.push_back(std::move(e));

    std::sort(entities.begin(), entities.end(),
    [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){
        return a->getZ() < b->getZ();
    });

    return ptr;
}

Image* Game::createImage( const char* realPath ){

    Image* img = canvas->loadTexture( realPath );

    return img;
}


