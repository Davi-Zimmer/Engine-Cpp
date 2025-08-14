#include "../../Includes/Math/Matrix.h"
#include <cmath>
#include <algorithm>


using std::cos;
using std::sin;

void Matrix::Identity(float* out) {
    for (int i = 0; i < 16; i++)
        out[i] = (i % 5 == 0) ? 1.0f : 0.0f;
}

void Matrix::RotateX(float angleRad, float* out) {
    float c = cos(angleRad);
    float s = sin(angleRad);
    Matrix::Identity(out);

    out[5] = c;
    out[6] = s;
    out[9] = -s;
    out[10] = c;
}

void Matrix::RotateY(float angleRad, float* out) {
    float c = cos(angleRad);
    float s = sin(angleRad);
    Matrix::Identity(out);

    out[0] = c;
    out[2] = -s;
    out[8] = s;
    out[10] = c;
}

void Matrix::RotateZ(float angleRad, float* out) {
    float c = cos(angleRad);
    float s = sin(angleRad);
    Matrix::Identity(out);

    out[0] = c;
    out[1] = s;
    out[4] = -s;
    out[5] = c;
}

void Matrix::Transition(float x, float y, float z, float* out) {
    Matrix::Identity(out);
    out[12] = x;
    out[13] = y;
    out[14] = z;
}

void Matrix::Scale(float sx, float sy, float sz, float* out) {
    Matrix::Identity(out);
    out[0] = sx;
    out[5] = sy;
    out[10] = sz;
}

void Matrix::MultiplyMat4_2(const float* a, const float* b, float* result) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result[col * 4 + row] =
                a[0 * 4 + row] * b[col * 4 + 0] +
                a[1 * 4 + row] * b[col * 4 + 1] +
                a[2 * 4 + row] * b[col * 4 + 2] +
                a[3 * 4 + row] * b[col * 4 + 3];
        }
    }
}

void Matrix::MultiplyMat4(float out[16], const float a[16], const float b[16]) {

    float result[16];
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col) {
            result[col + row * 4] = 0.0f;
            for (int i = 0; i < 4; ++i)
                result[col + row * 4] += a[i + row * 4] * b[col + i * 4];
        }
    std::copy(result, result + 16, out);
}

void Matrix::CreateTransformMatrix ( float* matrix, float x, float y, float sx, float sy, float rotX, float rotY, float rotZ ) {
    // Identidade
    float identity[16] = {
        1, 0, 0, 0,   
        0, 1, 0, 0,   
        0, 0, 1, 0,   
        0, 0, 0, 1
    };

    float scale[16] = {
        sx, 0,  0, 0,
        0,  sy, 0, 0,
        0,  0,  1, 0,
        0,  0,  0, 1
    };

    float radX = rotX;
    float radY = rotY;
    float radZ = rotZ;

    float rotMatX[16] = {
        1,         0,          0, 0,
        0, cos(radX), -sin(radX), 0,
        0, sin(radX),  cos(radX), 0,
        0,         0,          0, 1
    };

    float rotMatY[16] = {
        cos(radY), 0, sin(radY), 0,
        0,         1, 0,         0,
       -sin(radY), 0, cos(radY), 0,
        0,         0, 0,         1
    };

    float rotMatZ[16] = {
        cos(radZ), -sin(radZ), 0, 0,
        sin(radZ),  cos(radZ), 0, 0,
        0,          0,         1, 0,
        0,          0,         0, 1
    };

    float transform[16];
    MultiplyMat4(transform, rotMatZ, scale);
    MultiplyMat4(transform, rotMatY, transform);
    MultiplyMat4(transform, rotMatX, transform);

    std::copy(identity, identity + 16, matrix);
    MultiplyMat4(matrix, transform, matrix);

    // Translação (na NDC)
    matrix[12] = x;
    matrix[13] = y;
}

void Matrix::EmptyMatrix ( float* matrix ) {
    for (int i = 0; i < 16; i++)
        matrix[i] = (i % 5 == 0) ? 1.0f : 0.0f;
}

