#pragma once


struct Position {
    float x;
    float y;
    float z;
    float w;
    float h;
};


class BaseObject {

    Position position;

    public:

    BaseObject( float x, float y, float z, float w, float h );


    float* extractPosition();

    float getX();
    float getY();
    float getZ();
    float getW();
    float getH();

    void setX( float x );
    void setY( float y );
    void setZ( float z );
    void setW( float w );
    void setH( float h );

};