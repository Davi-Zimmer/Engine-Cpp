#include "../../headers/Rect.h"
#include <iostream>

Rect::Rect( RectProps props ){
    x = props.x;
    y = props.y;
    w = props.w;
    h = props.h;
    z = props.z;
    angle = props.angle;
}


float Rect::getX(){ return x; }
float Rect::getY(){ return y; }
float Rect::getW(){ return w; }
float Rect::getH(){ return h; }
float Rect::getAngle(){ return angle; }

void  Rect::setX( float f ) { x = f; }
void  Rect::setY( float f ) { y = f; }
void  Rect::setW( float f ) { w = f; }
void  Rect::setH( float f ) { h = f; }
void  Rect::setAngle( float f ) { angle = f; }

SimpleRect Rect::extractPosition()
{
    return { x, y, w, h };
}

void Rect::draw(){

}

RectTriangles Rect::extractTriangles(){

    Triangle t1 = {
        x,     y,
        x + w, y,
        x,     y + h
    };

    Triangle t2 = {
        x + w, y,
        x + w, y + h,
        x,     y + h
    };

    return { t1, t2 };

}