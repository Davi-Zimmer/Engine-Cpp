
#include <iostream>
#include "../../Includes/Game/Entities/Entity.h"
#include "../../Includes/Utils/Utils.h"
#include "../../Includes/Graphics/Canvas2D.h"
#include "../../Includes/managers/EventManager.h"


float x = 0;

Entity::Entity( float x, float y, float z, float w, float h ) : BaseObject( x, y, z, w, h ){

    /*
        EventManager em = EventManager::GetInstance(); 

        float spd = 5;

        em.onKeyDown( GLFW_KEY_W, [](){
            setX( getX() + spd );
        });

        em.onKeyUp( GLFW_KEY_A, [](){
            std::cout << "release A\n";
        });

        em.onKeyHold( GLFW_KEY_D, [](){
            std::cout << "hold D\n";
        });
    */

}

void Entity::setImage( std::unique_ptr<Image> img ){
    image = std::move(img);
}
void Entity::update( Canvas2D* canv, float deltaTime, Image i ){

    // imagem passada por parametros
    //canv->drawSprite( &i   , 0, 0, 100, 100, 0, 0  , 20, 20 );

    // imagem da classe
    canv->drawSprite( image.get(), 128, 0, 32, 32, 0, -200, 200, 200 );

}