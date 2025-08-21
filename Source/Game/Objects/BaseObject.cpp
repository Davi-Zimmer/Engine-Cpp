#include "../../Includes/Game/Objects/BaseObject.h"

BaseObject::BaseObject( float x, float y, float z, float w, float h ){

    position = { x, y, z, w, h };

}

float* BaseObject::extractPosition(){
    
    float* a = reinterpret_cast<float*>(&position);

    return a;

}


float BaseObject::getX(){ return position.x; }
float BaseObject::getY(){ return position.y; }
float BaseObject::getZ(){ return position.z; }
float BaseObject::getW(){ return position.w; }
float BaseObject::getH(){ return position.h; }

void  BaseObject::setX( float x ){ position.x = x; }
void  BaseObject::setY( float y ){ position.y = y; }
void  BaseObject::setZ( float z ){ position.z = z; }
void  BaseObject::setW( float w ){ position.w = w; }
void  BaseObject::setH( float h ){ position.h = h; }
