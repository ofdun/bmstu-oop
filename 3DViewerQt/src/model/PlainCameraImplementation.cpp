#include "PlainCameraImplementation.h"

static void decomposeTransform(const Matrix<double> &M, Matrix<double> &T, Matrix<double> &R)
{
    T = {{
        {1, 0, 0, M[0][3]},
        {0, 1, 0, M[1][3]},
        {0, 0, 1, M[2][3]},
        {M[3][0], M[3][1], M[3][2], 1}
    }};

    R = {{
        {M[0][0], M[0][1], M[0][2], 0},
        {M[1][0], M[1][1], M[1][2], 0},
        {M[2][0], M[2][1], M[2][2], 0},
        {0, 0, 0, 1}
    }};
}


Point PlainCameraImplementation::getDir() const
{
    return dir;
}

void PlainCameraImplementation::setPos(const Point &pos)
{
    this->pos = pos;
}

Point PlainCameraImplementation::getPos() const
{
    return pos;
}

Point PlainCameraImplementation::getUp() const
{
    return up;
}

Point PlainCameraImplementation::getRight() const
{
    return right;
}

void PlainCameraImplementation::setUp(const Point &up)
{
    this->up = up;
}

void PlainCameraImplementation::setRight(const Point &right)
{
    this->right = right;
}

void PlainCameraImplementation::setDir(const Point &angle)
{
    this->dir = angle;
}

void PlainCameraImplementation::transform(const Matrix<double> &transformationMatrix)
{
    auto translation = Matrix<double>(4, 4);
    auto rotation = Matrix<double>(4, 4);

    decomposeTransform(transformationMatrix, translation, rotation);

    pos.transform(translation);

    right.transform(rotation);
    dir.transform(rotation);
    up.transform(rotation);
}
