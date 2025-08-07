#pragma once

class Image {
    int width;
    int height;
    unsigned int texture;
    float transform[16];

    float rotX;
    float rotY;
    float rotZ;
    float scale;

    public:
        Image( unsigned int textt, int w, int h );
        int getWidth();
        int getHeight();
        int getTexture();

        float* getTransform();
        void setTransform( const float* mat );

        float getRotationX();
        float getRotationY();
        float getRotationZ();
        float getScale();

        float setRotationX( float angle );
        float setRotationY( float angle );
        float setRotationZ( float angle );
        float setScale( float scale );
};