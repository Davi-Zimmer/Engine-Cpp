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

        void setRotationX( float angle );
        void setRotationY( float angle );
        void setRotationZ( float angle );
        void setScale( float scale );
};