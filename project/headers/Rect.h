#pragma once
#include <array>


struct RectProps
{
    float x=0, y=0, w=0, h=0, z=0, angle=0;
};

struct SimpleRect
{
    float x, y, w, h;
};

struct Triangle
{
    float x1, y1, x2, y2, x3, y3;
};


struct RectTriangles
{
    std::array< Triangle, 2 > triangles;
};

class Rect {

    private:
        float x, y, z, w, h, angle;

    public:
           
        Rect( RectProps props );

    float getX();
    float getY();
    float getW();
    float getH();
    float getAngle();

    void setX( float f );
    void setY( float f );
    void setW( float f );
    void setH( float f );
    void setAngle( float f );


    SimpleRect extractPosition();


    void draw();

    RectTriangles extractTriangles();
};