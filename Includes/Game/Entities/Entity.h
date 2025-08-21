#pragma once

#include "../Objects/BaseObject.h"
#include "../../Graphics/Image.h"

class Canvas2D; 
#include "../../Graphics/Canvas2D.h"


class Entity : public BaseObject {

    std::unique_ptr<Image> image;

    public:
    Entity( float x, float y, float z, float w, float h );
    void setImage( std::unique_ptr<Image> img );

    void update( Canvas2D* canv, float deltaTime, Image i );

};

