#include "../../Includes/Graphics/Image.h"
#include "../../Includes/Math/Matrix.h"
#include <iostream>
#include <cstring> 


Image::Image( unsigned int tex, int w, int h ) {
    texture = tex;
    width = w;
    height = h;

    Matrix::EmptyMatrix( transform );
}

int Image::getWidth(){
    return width;
}

int Image::getHeight(){
    return height;
}

int Image::getTexture(){
    return texture;
}

float* Image::getTransform(){
    return transform;
}

void Image::setTransform( const float* mat ){

    std::memcpy( transform, mat, sizeof( float ) * 16 );

}


float Image::getRotationX(){
    return rotX;
}

float Image::getRotationY(){
    return rotY;
}

float Image::getRotationZ(){
    return rotZ;
}

float Image::getScale(){
    return scale;
}


void Image::setRotationX( float angle ){
    rotX = angle;
}

void Image::setRotationY( float angle ){
    rotY = angle;
}

void Image::setRotationZ( float angle ){
    rotZ = angle;
}

void Image::setScale( float s ){
    scale = s;
}