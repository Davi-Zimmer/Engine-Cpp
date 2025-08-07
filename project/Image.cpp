#include "./headers/Image.h"
#include <iostream>


Image::Image( unsigned int tex, int w, int h ) {
    texture = tex;
    width = w;
    height = h;
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