#pragma once

class Matrix {
    public:
    static void Identity(float* out);
    static void RotateZ( float angleRad, float* out );
    static void RotateX( float angleRad, float* out );
    static void RotateY( float angleRad, float* out );
    static void Transition( float x, float y, float z, float* out );
    static void Scale( float sx, float sy, float sz, float* out );
    static void MultiplyMat4(float out[16], const float a[16], const float b[16]);
    static void MultiplyMat4_2(const float* a, const float* b, float* result);

    static void CreateTransformMatrix ( float* matrix, float x, float y, float sx, float sy, float rotX, float rotY, float rotZ );
    static void EmptyMatrix ( float* matrix );

};