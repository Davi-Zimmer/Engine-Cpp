#pragma once

class Image {
    int width;
    int height;
    unsigned int texture;

    public:
        Image( unsigned int textt, int w, int h );
        int getWidth();
        int getHeight();
        int getTexture();
};